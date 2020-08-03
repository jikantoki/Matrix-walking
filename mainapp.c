#include<stdio.h>
#include<stdlib.h> //system("cls");で画面を綺麗に
#include<time.h> //UNIX時間の取得してsrand
#include<conio.h>//scanfみたいなやつ

//準備
int gmap[128][128];
int mapx,mapy;
int manx,many;
int i,j;
int savo=1,movd;
int err;
int moji;

//関数準備
int viewmap();
int makemap();
int setplayer();
int mapsize();

int main(void)//メイン
{
	FILE *logfile;
	logfile=fopen("matrixlog.txt","a+");
	fprintf(logfile,"\nLOGFILE\n");
//まず全部消す
	system("cls");

//マップサイズの設定
	mapsize();
	fprintf(logfile,"%d*%dにマップサイズを設定しました。\n",mapx,mapy);
	system("cls");
	
//マップ生成
	makemap();
	
//主人公のセット
	setplayer();
	
//マップの表示
	viewmap();
	
	fprintf(logfile,"ゲームが開始されました\n正常にマップを表\示しました\n");
	
//方向を聞く
	printf("進行方向の入力\n\"R\"キーで終了\n\"E\"キーでマップを再生成\n");
	//scanf("%d",&movd);
	moji=getch();
	
//ここからループ
	while(1){
		//押された数字によって進行方向を決める
		//switch(movd){
		switch(moji){
		case 115://Sキー
		case 83:
			if((many<mapy-1)&&(gmap[many+1][manx]>=1)&&(gmap[many+1][manx]<=2)){
				err=0;
				gmap[many][manx]=savo;
				fprintf(logfile,"下に移動しました\n");
				many+=1;
			}else if(gmap[many+1][manx]==8){
				fprintf(logfile,"ゲームをクリアしました\n");
				printf("Game clear!\n");
				err=2;
			}else{
				err=1;
			}
			break;
		case 97://Aキー
		case 65:
			if((manx>0)&&(gmap[many][manx-1]>=1)&&(gmap[many][manx-1]<=2)){
				err=0;
				gmap[many][manx]=savo;
				fprintf(logfile,"左に移動しました\n");
				manx-=1;
			}else if(gmap[many][manx-1]==8){
				fprintf(logfile,"ゲームをクリアしました\n");
				printf("Game clear!\n");
				err=2;
			}else{
				err=1;
			}
			break;
		case 100://Dキー
		case 68:
			if((manx<mapx-1)&&(gmap[many][manx+1]>=1)&&(gmap[many][manx+1]<=2)){
				err=0;
				gmap[many][manx]=savo;
				fprintf(logfile,"右に移動しました\n");
				manx+=1;
			}else if(gmap[many][manx+1]==8){
				fprintf(logfile,"ゲームをクリアしました\n");
				printf("Game clear!\n");
				err=2;
			}else{
				err=1;
			}
			break;
		case 119://Wキー
		case 87:
			if((many>0)&&(gmap[many-1][manx]>=1)&&(gmap[many-1][manx]<=2)){
				err=0;
				gmap[many][manx]=savo;
				fprintf(logfile,"上に移動しました\n");
				many-=1;
			}else if(gmap[many-1][manx]==8){
				fprintf(logfile,"ゲームをクリアしました\n");
				printf("Game clear!\n");
				err=2;
			}else{
				err=1;
			}
			break;
		case 101://Eキー
		case 69:
			mapsize();
			fprintf(logfile,"%d*%dにマップサイズを設定しました。\n",mapx,mapy);
			makemap();
			fprintf(logfile,"マップを再生成しました\n");
			setplayer();
			system("cls");
			viewmap();
			err=3;
			break;
		case 114://Rキー
		case 82:
			printf("Game over\n");
			fprintf(logfile,"ゲームが終了しました\n");
			err=2;
			break;
		default:
			err=1;
			break;
		}
	//エラーがなければ次の処理へ
		if(err==1){
			printf("\rその操作はできません");
			fprintf(logfile,"無効な操作をしました\n");
		}else if(err==2){
			break;
		}else if(err==3){
			;
		}else{
		//セーブオブジェクト
			savo=gmap[many][manx];
		//主人公の場所設定
			gmap[many][manx]=9;
		//マップ表示
			system("cls");
			viewmap();
			printf("進行方向の入力\n\"R\"キーで終了\n\"E\"キーでマップを再生成\n");
		}
	//先読み処理で聞く
		//scanf("%d",&movd);
		moji=getch();
	}
	
//終了処理
	fprintf(logfile,"正常にプログラムが終了しました\n\n");
	printf("End of program\n");
	fclose(logfile);
	return 0;
}
//ここまでmain
//ここから関数


//マップ作製の関数作成
int viewmap(void){
	for(i=0;i<mapy;i++){
		for(j=0;j<mapx;j++){
			switch(gmap[i][j]){
			case 0:
				printf("■");
				break;
			case 1:
				printf("　");
				break;
			case 2:
				printf("＠");
				break;
			case 3:
				printf("▲");
				break;
			case 8:
				printf("☆");
				break;
			case 9:
				printf("人");
				break;
			default:
				break;
			}
		}
		printf("\n");
	}
	printf("\n");
}

//ランダム地図作成の関数作成
int makemap(void){
	srand(time(NULL));//UNIX時間を取得してsrandにセット
	for(i=0;i<mapy;i++){//とりあえず全部1にする
		for(j=0;j<mapx;j++){
			gmap[i][j]=1;
		}
	}
	for(i=0;i<mapy;i++){//ここから外枠を0で埋める
		gmap[i][0]=0;
		gmap[i][mapx-1]=0;
	}
	for(i=0;i<mapx;i++){
		gmap[0][i]=0;
		gmap[mapy-1][i]=0;
	}//ここまで
	for(i=1;i<mapy-1;i++){//ランダム地図
		for(j=1;j<mapx-1;j++){
			gmap[i][j]=rand()%20;
			if(gmap[i][j]==4)gmap[i][j]=0;
			if((gmap[i][j]>=5)&&(gmap[i][j]<=20))gmap[i][j]=1;
		}
	}
	for(i=2;i<mapx*0.8;i++){//ここから主人公用の道を作成
		gmap[5][i]=1;
	}
	for(j=5;j<mapy*0.8;j++){
		gmap[j][i]=1;
	}//ここまで
	gmap[5][2]=1;//主人公用
	gmap[j][i]=8;//ゴールの設定
}

//主人公セットの関数作成
int setplayer(void){
	manx=2;
	many=5;
	gmap[many][manx]=9;
}

//マップサイズセットの関数作成
int mapsize(void){
	while(1){
		printf("マップの横サイズは？\n15～128→");
		scanf("%d",&mapx);
		if((mapx>=15)&&(mapx<=128))break;
		printf("そのサイズは無効です\n");
	}
	while(1){
		printf("マップの縦サイズは？\n15～64→");
		scanf("%d",&mapy);
		if((mapy>=15)&&(mapy<=64))break;
		printf("そのサイズは無効です\n");
	}
}
