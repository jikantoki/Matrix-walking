#include<stdio.h>
#include<stdlib.h> //system("cls");�ŉ�ʂ��Y���
#include<time.h> //UNIX���Ԃ̎擾����srand
#include<conio.h>//scanf�݂����Ȃ��

//����
int gmap[128][128];
int mapx,mapy;
int manx,many;
int i,j;
int savo=1,movd;
int err;
int moji;

//�֐�����
int viewmap();
int makemap();
int setplayer();
int mapsize();

int main(void)//���C��
{
	FILE *logfile;
	logfile=fopen("matrixlog.txt","a+");
	fprintf(logfile,"\nLOGFILE\n");
//�܂��S������
	system("cls");

//�}�b�v�T�C�Y�̐ݒ�
	mapsize();
	fprintf(logfile,"%d*%d�Ƀ}�b�v�T�C�Y��ݒ肵�܂����B\n",mapx,mapy);
	system("cls");
	
//�}�b�v����
	makemap();
	
//��l���̃Z�b�g
	setplayer();
	
//�}�b�v�̕\��
	viewmap();
	
	fprintf(logfile,"�Q�[�����J�n����܂���\n����Ƀ}�b�v��\\�����܂���\n");
	
//�����𕷂�
	printf("�i�s�����̓���\n\"R\"�L�[�ŏI��\n\"E\"�L�[�Ń}�b�v���Đ���\n");
	//scanf("%d",&movd);
	moji=getch();
	
//�������烋�[�v
	while(1){
		//�����ꂽ�����ɂ���Đi�s���������߂�
		//switch(movd){
		switch(moji){
		case 115://S�L�[
		case 83:
			if((many<mapy-1)&&(gmap[many+1][manx]>=1)&&(gmap[many+1][manx]<=2)){
				err=0;
				gmap[many][manx]=savo;
				fprintf(logfile,"���Ɉړ����܂���\n");
				many+=1;
			}else if(gmap[many+1][manx]==8){
				fprintf(logfile,"�Q�[�����N���A���܂���\n");
				printf("Game clear!\n");
				err=2;
			}else{
				err=1;
			}
			break;
		case 97://A�L�[
		case 65:
			if((manx>0)&&(gmap[many][manx-1]>=1)&&(gmap[many][manx-1]<=2)){
				err=0;
				gmap[many][manx]=savo;
				fprintf(logfile,"���Ɉړ����܂���\n");
				manx-=1;
			}else if(gmap[many][manx-1]==8){
				fprintf(logfile,"�Q�[�����N���A���܂���\n");
				printf("Game clear!\n");
				err=2;
			}else{
				err=1;
			}
			break;
		case 100://D�L�[
		case 68:
			if((manx<mapx-1)&&(gmap[many][manx+1]>=1)&&(gmap[many][manx+1]<=2)){
				err=0;
				gmap[many][manx]=savo;
				fprintf(logfile,"�E�Ɉړ����܂���\n");
				manx+=1;
			}else if(gmap[many][manx+1]==8){
				fprintf(logfile,"�Q�[�����N���A���܂���\n");
				printf("Game clear!\n");
				err=2;
			}else{
				err=1;
			}
			break;
		case 119://W�L�[
		case 87:
			if((many>0)&&(gmap[many-1][manx]>=1)&&(gmap[many-1][manx]<=2)){
				err=0;
				gmap[many][manx]=savo;
				fprintf(logfile,"��Ɉړ����܂���\n");
				many-=1;
			}else if(gmap[many-1][manx]==8){
				fprintf(logfile,"�Q�[�����N���A���܂���\n");
				printf("Game clear!\n");
				err=2;
			}else{
				err=1;
			}
			break;
		case 101://E�L�[
		case 69:
			mapsize();
			fprintf(logfile,"%d*%d�Ƀ}�b�v�T�C�Y��ݒ肵�܂����B\n",mapx,mapy);
			makemap();
			fprintf(logfile,"�}�b�v���Đ������܂���\n");
			setplayer();
			system("cls");
			viewmap();
			err=3;
			break;
		case 114://R�L�[
		case 82:
			printf("Game over\n");
			fprintf(logfile,"�Q�[�����I�����܂���\n");
			err=2;
			break;
		default:
			err=1;
			break;
		}
	//�G���[���Ȃ���Ύ��̏�����
		if(err==1){
			printf("\r���̑���͂ł��܂���");
			fprintf(logfile,"�����ȑ�������܂���\n");
		}else if(err==2){
			break;
		}else if(err==3){
			;
		}else{
		//�Z�[�u�I�u�W�F�N�g
			savo=gmap[many][manx];
		//��l���̏ꏊ�ݒ�
			gmap[many][manx]=9;
		//�}�b�v�\��
			system("cls");
			viewmap();
			printf("�i�s�����̓���\n\"R\"�L�[�ŏI��\n\"E\"�L�[�Ń}�b�v���Đ���\n");
		}
	//��ǂݏ����ŕ���
		//scanf("%d",&movd);
		moji=getch();
	}
	
//�I������
	fprintf(logfile,"����Ƀv���O�������I�����܂���\n\n");
	printf("End of program\n");
	fclose(logfile);
	return 0;
}
//�����܂�main
//��������֐�


//�}�b�v�쐻�̊֐��쐬
int viewmap(void){
	for(i=0;i<mapy;i++){
		for(j=0;j<mapx;j++){
			switch(gmap[i][j]){
			case 0:
				printf("��");
				break;
			case 1:
				printf("�@");
				break;
			case 2:
				printf("��");
				break;
			case 3:
				printf("��");
				break;
			case 8:
				printf("��");
				break;
			case 9:
				printf("�l");
				break;
			default:
				break;
			}
		}
		printf("\n");
	}
	printf("\n");
}

//�����_���n�}�쐬�̊֐��쐬
int makemap(void){
	srand(time(NULL));//UNIX���Ԃ��擾����srand�ɃZ�b�g
	for(i=0;i<mapy;i++){//�Ƃ肠�����S��1�ɂ���
		for(j=0;j<mapx;j++){
			gmap[i][j]=1;
		}
	}
	for(i=0;i<mapy;i++){//��������O�g��0�Ŗ��߂�
		gmap[i][0]=0;
		gmap[i][mapx-1]=0;
	}
	for(i=0;i<mapx;i++){
		gmap[0][i]=0;
		gmap[mapy-1][i]=0;
	}//�����܂�
	for(i=1;i<mapy-1;i++){//�����_���n�}
		for(j=1;j<mapx-1;j++){
			gmap[i][j]=rand()%20;
			if(gmap[i][j]==4)gmap[i][j]=0;
			if((gmap[i][j]>=5)&&(gmap[i][j]<=20))gmap[i][j]=1;
		}
	}
	for(i=2;i<mapx*0.8;i++){//���������l���p�̓����쐬
		gmap[5][i]=1;
	}
	for(j=5;j<mapy*0.8;j++){
		gmap[j][i]=1;
	}//�����܂�
	gmap[5][2]=1;//��l���p
	gmap[j][i]=8;//�S�[���̐ݒ�
}

//��l���Z�b�g�̊֐��쐬
int setplayer(void){
	manx=2;
	many=5;
	gmap[many][manx]=9;
}

//�}�b�v�T�C�Y�Z�b�g�̊֐��쐬
int mapsize(void){
	while(1){
		printf("�}�b�v�̉��T�C�Y�́H\n15�`128��");
		scanf("%d",&mapx);
		if((mapx>=15)&&(mapx<=128))break;
		printf("���̃T�C�Y�͖����ł�\n");
	}
	while(1){
		printf("�}�b�v�̏c�T�C�Y�́H\n15�`64��");
		scanf("%d",&mapy);
		if((mapy>=15)&&(mapy<=64))break;
		printf("���̃T�C�Y�͖����ł�\n");
	}
}
