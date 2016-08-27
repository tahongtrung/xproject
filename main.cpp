/************************************
*DE TAI:QUAN LY DIEM SINH VIEN      *
*GVHD  :LUU NGUYEN KI THU           *
*SVTH  :-TA HONG TRUNG   N13DCCN213 *
*	     -TRAN CAM TRUONG N13DCCN216*
************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "alg.cpp" 

status key(int z){
	if(z == 224){
		char c = getch();
		if (c == 72) return UP;
		if (c == 80) return DOWN;
		if (c == 77) return RIGHT;
		if (c == 75) return LEFT;
	}
	else{
		if (z == 32) return MUSIC;
		if (z == 27) return EXIT;
		if (z == 13)
			return ENTER;
		else
			return BACK;
	}
}
char ol[4],osv[13],lp[13];
int times,m=0;
int Menu(int n,int &out,int &pos){
	
	str smenu[9]= { " NHAP LOP             !", 
					" IN DANH SACH LOP     !",
					" NHAP SINHVIEN        !",
					" IN DANH SACH SINHVIEN!",
					" NHAP MON HOC         !",
					" IN DANH SACH MON HOC !",
					" NHAP DIEM            !",
					" IN BANG DIEM LOP     !",
					" PHIEU DIEM SV        !"};
								
	int *color = (int*)malloc(n*sizeof(int));
	for(int i = 0;i < n;i++){
		color[i] = UNSELECT;
	}
	int x = pos;
	color[x]=SELECT;
	while(1){
		Clear();
		if (m == 1) MessageBeep(0);
		for(int i = 0;i < n;i++){
			TextColor(color[i]);
			if(i == pos){
				GotoXY(26,3+i);
				printf("%d %c%s \n",i+1,char(16),smenu[i]);
			}else{
				GotoXY(26,3+i);
				printf("%d   %s\n",i+1,smenu[i]);
			}
		}
		TextColor(23);
		GotoXY(00,15); printf("[SELECT:ENTER]");
		GotoXY(20,15); printf("[MUSIC%c:SPACE]",char(14));
		GotoXY(38,15); printf("[EXIT:ESC]");
		GotoXY(55,15); printf("[UP:%c/%c]",char(30),char(17));
		GotoXY(70,15); printf("[DOWN:%c/%c]",char(31),char(16));
		Box(25,2,28,10);
		
		int z = getch();
		status stt = key(z);
		switch(stt){
			case UP   : case LEFT : {								
				(pos == 0)? pos = n-1:pos--;
				break;
			};
			case DOWN : case RIGHT: {				
				(pos == n-1)? pos = 0:pos++;
				break;
			}	
			case ENTER: return pos;
			case BACK : break;
			case EXIT : {
				out = 1;
				return pos;			
			}
			case MUSIC : {
				(m == 1)? m = 0:m = 1;
				break;
			}
		}
		for(int i = 0;i < n;i++)
			color[i] = UNSELECT;
		color[pos] = SELECT;	 			
	}//end while 
}

void Notify(int x,int y,int c1,int c2,char s[],int sec){
	if (m == 1) MessageBeep(0x00000010L);
	TextColor(c1);
	GotoXY(x,y);
	printf("%s",s);
	Sleep(sec);
	for(int i=0;i<strlen(s);i++) s[i]=' ';
	GotoXY(x,y);
	printf("%s",s);
	TextColor(c2);
}
int checkFull(str stemp[],int n){
	for(int i=0;i<n;i++){
		if(strlen(stemp[i])==0) return 0;
	}
	return 1;
}
int IsDigital(char A[]){
	int l=strlen(A);
	for(int i=0;i<l;i++)
		if(!isdigit(A[i])) return 0;
	return 1;
}
int checkMaMH(char token[]){
	//readFileMonhoc(dsmh);
	for(int i=0;i<dsmh.n;i++)
		if(strcmp(dsmh.nodes[i].MAMH,token)==0) return 0;
	return 1;
}
int checkMalop(char stemp[]){
	//dsl.n=0;
	//readFileLop(dsl);
	for(int i=0;i<dsl.n;i++)
		if(strcmp(strlwr(dsl.nodes[i].MALOP),strlwr(stemp)) == 0) return i;//giong nhau
	return -1;
}

int checkDiem(char A[]){
	int c=0;
	if(atof(A) > 10 || atof(A) < 0) return 0;
	for(int i = 0;i < strlen(A);i++) 
		if(!isdigit(A[i])) 
			if(A[i] == '.') c++;
			else return 0;
	if (c > 1) return 0;
	return 1;
}

int ck,tt =1;
int k=0;
str stemp[5];int dung=0;
int KeyPressed(str stemp[],int dung,int n,int ck){
	int l, max;
	(ck == 1 )? max = 3 : max = 11;
	AGAIN:
	l = strlen(stemp[k]);	
	if(kbhit()){	
		int key = getch();		
		switch(key){
			case 27: return -2; 
			case 13:{
				if(tt==n || strlen(stemp[k+1]) > 0){//enter len xg d
					if(checkFull(stemp,n)){
						if(ck==0){ //dang nhap lop
							if(checkMalop(stemp[0])!=-1){
								char s[]="Lop bi trung!";
								Notify(30,10,28,31,s,1000);
								tt=1;k=0;
								GotoXY(40 +strlen(stemp[k]),tt+3);
								goto AGAIN;
							}							
							if(!IsDigital(stemp[2])||strlen(stemp[2])<4){
								char s[]="Nam khong hop le!";
								Notify(30,10,28,31,s,1000);
								tt=3,k=2;
								GotoXY(40+strlen(stemp[2]),2+4);
								goto AGAIN;
							}
							//writeFileLop(strupr(stemp[0]),strupr(stemp[1]),atoi(stemp[2]));
						}
						if(ck==1) {//inds lop
							strcpy(ol,stemp[0]); //k can dong nay kt truc tiep
							if(l<4 || !IsDigital(stemp[0])){ 
								char s[]="Nam khong hop le!";
								Notify(30,10,28,31,s,1000);
								k=0;tt=1;
								GotoXY(40+strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							//readFileLop(dsl);
							int dc=0;
							for(int i=0;i<dsl.n;i++){
								if(dsl.nodes[i].NAMNH==atoi(stemp[0])){				
									dc++;
								}
							}
							if(dc==0){
								char t[]="Nien khoa khong ton tai!";
								Notify(27,10,28,31,t,1000);							
								GotoXY(40+strlen(stemp[k]),k+1+3);
								goto AGAIN;
							}							
						}
						if(ck==-2){
							//readFileSinhvien(root);
							NODEPTR q = SearchSV(root,strupr(stemp[0]));	
							if(q!=NULL){
								char s[]="Ma sinh vien ton tai!";
								Notify(30,10,28,31,s,1000);
								k=0,tt=1;
								GotoXY(40+strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							if(!IsDigital(stemp[4]) || strlen(stemp[4])<10){
								char s[]="SDT khong hop le!";
								Notify(30,10,28,31,s,1000);
								k=4,tt=5;
								GotoXY(40+strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							//writeFileSV(strupr(lp),strupr(stemp[0]),strupr(stemp[1]),strupr(stemp[2]),strupr(stemp[3]),strupr(stemp[4]));
						}
						if(ck == 2){ 
							if(checkMalop(stemp[0]) == -1){
								char t[]="Lop khong ton tai!";
								Notify(30,10,28,31,t,1000);
								k=0;tt=1;
								GotoXY(40+strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							strcpy(lp,stemp[0]);
						}
						if(ck==3){	
							strcpy(lp,stemp[0]);		
							if(checkMalop(stemp[0])==-1){
								char f[]="Lop khong ton tai!";
								Notify(30,10,28,31,f,1000);
								k=0,tt=1;								
								GotoXY(40+strlen(stemp[k]),tt+3);
								goto AGAIN;
							}				
							//readFileSVLOP(root,lp);
							if(root==NULL){
								char f[]="Lop khong co sinh vien!";
								Notify(27,10,28,31,f,1000);
								k=0,tt=1;								
								GotoXY(40+strlen(stemp[k]),tt+3);
								root=NULL;
								goto AGAIN;
							}						
						}
						if(ck==4){
							if(checkMaMH(stemp[0])==0){
								char s[]="Mon hoc bi trung!";
								Notify(30,10,28,31,s,1000);
								tt=1;k=0;
								GotoXY(40 +strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							if(!IsDigital(stemp[2])){
								char s[]="STC khong hop le!";
								Notify(30,10,28,31,s,1000);
								tt=3;k=2;
								GotoXY(40 +strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							if(!IsDigital(stemp[3])){
								char s[]="STC khong hop le!";
								Notify(30,10,28,31,s,1000);
								tt=4;k=3;
								GotoXY(40 +strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							//writeFileMH(strupr(stemp[0]),strupr(stemp[1]),atoi(stemp[2]),atoi(stemp[3]));	
						}
						if(ck==-6){
							if(checkMaMH(stemp[0])){
								char s[]="Mon hoc khong ton tai!";
								Notify(30,10,28,31,s,1000);
								tt=1;k=0;
								GotoXY(40 +strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							if(!IsDigital(stemp[1])){
								char s[]="So lan thi khong hop le";
								Notify(30,10,28,31,s,1000);
								tt=2;k=1;
								GotoXY(40 +strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							int w;///=readCheckFileDiem(osv,stemp[0]);
							if(w>=0){
								if(atoi(stemp[1])!= w+1){
									char s[]="Lan thi tiep theo phai lien sau";
									Notify(24,10,28,31,s,1000);
									tt=2;k=1;
									GotoXY(40 +strlen(stemp[k]),tt+3);
									goto AGAIN;
								}
							}
							if(!checkDiem(stemp[2])){
								char s[]="Diem khong hop le";
								Notify(30,10,28,31,s,1000);
								tt=3;k=2;
								GotoXY(40 +strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							//writeFileDiem(osv,stemp[0],atoi(stemp[1]),atof(stemp[2]));
						}
						if(ck==6){
							//readFileSinhvien(root);
							NODEPTR q = SearchSV(root,stemp[0]);
							if(q==NULL){
								char s[]="Ma sinh vien khong ton tai!";
								Notify(26,10,28,31,s,1000);
								k=0,tt=1;
								GotoXY(40+strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							strcpy(osv,strupr(stemp[0]));
						}
						if(ck==7){
							if(checkMalop(stemp[0])==-1){
								char y[]="Lop khong ton tai!";
								Notify(30,10,28,31,y,1000);
								k=0,tt=1;
								GotoXY(40+strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							strcpy(lp,strupr(stemp[0]));
							if(checkMaMH(stemp[1])){
								char y[]="Mon hoc khong ton tai!";
								Notify(30,10,28,31,y,1000);
								k=1;tt=2;
								GotoXY(40+strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							strcpy(osv,strupr(stemp[1]));
							if(!IsDigital(stemp[2]) || atoi(stemp[2])==0){
								char s[]="So lan thi khong hop le!";
								Notify(30,10,28,31,s,1000);
								tt=3;k=2;
								GotoXY(40 +strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							times=atoi(stemp[2]);
																				
						}
						if(ck==8){
							//readFileSinhvien(root);											
							NODEPTR q = SearchSV(root,stemp[0]);
							if(q==NULL){
								char s[]="Ma sinh vien khong ton tai!";
								Notify(26,10,28,31,s,1000);
								k=0,tt=1;
								GotoXY(40+strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
							strcpy(osv,stemp[0]);//lay dc masv
							//readFileDiem(First,osv);
							if(First==NULL){
								char s[]="Sinh vien chua co diem!";
								Notify(26,10,28,31,s,1000);
								k=0,tt=1;
								GotoXY(40+strlen(stemp[k]),tt+3);
								goto AGAIN;
							}
						}
						return -1;//da nhap du field
					}
					else{
						for(int i=0;i<n;i++){
							if(strlen(stemp[i])==0){
								tt=i+1;k=i;break;
							}
						}
						char s[]="Error Data!";						
						Notify(25,10,28,31,s,1000);	
						GotoXY(40+strlen(stemp[k]),tt+3);	
						goto AGAIN;	
					}
				}else{
					if(tt==n) tt=1; else tt++;						
					if(k==n-1) k=0; else k++;	
					if(strlen(stemp[k])!=0){
						for(int i=0;i<n;i++){
							if(strlen(stemp[i])==0){	
								tt=i+1;k=i;break;
							}
						}
					}																				
					GotoXY(40+strlen(stemp[k]),tt+3);	
					goto AGAIN;
				}		
			}
			case 8:{/*  BACKSPACE KEY: dell a char	*/											
				stemp[k][strlen(stemp[k])-1] ='\0';
				if(l > 0){
					GotoXY(40+l,tt+3);
					printf("\b");				
					printf(" ");		
					printf("\b");
				}
				goto AGAIN;	
			}		
			case 224:{/*  VK KEY: move direction,up,down  */
				key = getch();
				switch(key){	
					case 75: case 72:{/* VK_UP,VK_LEFT: up*/													
						(tt==1)? tt=n:tt--;
						(k==0)? k=n-1:k--;
						GotoXY(40 +strlen(stemp[k]),tt+3);
						goto AGAIN;
					}
					case 77: case 80:{/* VK_DOWN,VK_RIGHT: down*/
						(tt==n)? tt=1:tt++;						
						(k==n-1)? k=0: k++;
						GotoXY(40 +strlen(stemp[k]),tt+3);	
						goto AGAIN;
					}	
				}
				break;
			}																
			default:{
				if(ck == 0 && k == 2 ) max = 3;
				if(l > max){
					char s[] = "Vuot qua so ki tu";
					Notify(30,10,28,31,s,1000);
					GotoXY(40+strlen(stemp[k]),k+1+3);
				}else{
					GotoXY(40+strlen(stemp[k]),k+1+3);																	
					printf("%c",toupper(key));
					stemp[k][l] = toupper(key);
					stemp[k][++l] = '\0';
					goto AGAIN;
				}							
			}
		}
	}	
}

void InputUI(int rong,char* s,str menumh[],int n,int ck){
	
	TextBox(s,24,3,29,3+n-2);		
	GotoXY(00,15); printf("[BACK:ESC]");
	GotoXY(22,15); printf("[INSERT:ENTER]");
	GotoXY(50,15); printf("[UP:%c/%c]",char(30),char(17));
	GotoXY(70,15); printf("[DOWN:%c/%c]",char(31),char(16));
	for(int i = 4;i < n+4 ;i++){
		GotoXY(25,i); printf(menumh[i-4]);
	}
	TextColor(31);
	
	GotoXY(40,4);
	int k;
	do{	
		k = KeyPressed(stemp,dung,n,ck);		
	}while(k != -1 && k != -2 && k != -3);
	dung = k;
}
void InputCheck(int n,char* s,str menumh[8],int ck){
	//Clear();
	TextColor(23);
	int c;
	do{
		Clear();
		tt=1,c=0,k=0; //reset global variable
		for(int i=0;i<n;i++){
			memset(stemp[i],0,255);
		}

		InputUI(dung,s,menumh,n,ck);
		
		if(ck==2 && lp != NULL) break;
		if(ck==1||ck==3||ck==8) break;
		else{
			TextColor(23);
			for(int i=0;i<n;i++){
				GotoXY(40,i+1+3); printf("%s",stemp[i]);
			}
			if(dung == -3) break ;
			
			if(dung == -1) {
				switch(ck) {
					case 5: {
						TextColor(31);
						return;
					}
					case 2:	break;
					case 4:	break;
					case 6: {
						c=0; continue;
						break;
					}
					case 7: {
						TextColor(31);
						return ;
					}
				}
				GotoXY(25,10);
				TextColor(26);
				printf("THEM THANH CONG!");
				GotoXY(25,11);
				printf("ENTER DE TIEP TUC, PHIM BAT KI DE THOAT!");
				TextColor(23);
			}else
				break;
			c = getch();
		}									
	}while(c == 13 || c == 13);
}

///void Preorder(NODEPTR p,int &i,struct dssinhvien &dssv)
void PrintListSV(NODEPTR &root){
	struct dssinhvien {
		int n;
		_sinhvien nodes[MAXLIST];
	};
	struct dssinhvien dssv;
	int i;
	//Preorder(root,i,dssv);
	//order list sv
	for(int i=1;i<dssv.n;i++){
		for(int j=dssv.n-1;j>=i;j--){
			if(strcmp(dssv.nodes[j-1].TEN,dssv.nodes[j].TEN)==0){
				if(strcmp(dssv.nodes[j-1].HO,dssv.nodes[j].HO)>0){
					SwapSV(dssv.nodes[j-1],dssv.nodes[j]);
				}
			}
			if(strcmp(dssv.nodes[j-1].TEN,dssv.nodes[j].TEN)>0){	
				SwapSV(dssv.nodes[j-1],dssv.nodes[j]);
			}
		}
	}
	for(int i=0;i<dssv.n;i++){
		GotoXY(10,i+6);printf("%d",i);		
		GotoXY(14,i+6);printf("%s",dssv.nodes[i].MASV);
		GotoXY(24,i+6);printf("%s",dssv.nodes[i].HO);
		GotoXY(36,i+6);printf("%s",dssv.nodes[i].TEN);
		GotoXY(48,i+6);printf("%s",dssv.nodes[i].PHAI);
		GotoXY(60,i+6);printf("%s",dssv.nodes[i].SODT);
	}
}
void Preorder(NODEPTR p,int &i,struct dssinhvien &dssv){
	if(p!=NULL){
	/*	
		strcpy(dssv.nodes[i].HO,p->sv.HO);
		strcpy(dssv.nodes[i].MASV,p->sv.MASV);
		strcpy(dssv.nodes[i].TEN,p->sv.TEN);
		strcpy(dssv.nodes[i].PHAI,p->sv.PHAI);
		strcpy(dssv.nodes[i].SODT,p->sv.SODT);*/
/*		
		GotoXY(10,i+6);printf("%d",i);
		GotoXY(13,i+6);printf("%s",dssv.nodes[i].MASV);
		GotoXY(24,i+6);printf("%s",dssv.nodes[i].HO);
		GotoXY(36,i+6);printf("%s",dssv.nodes[i].TEN);
		GotoXY(48,i+6);printf("%s",dssv.nodes[i].PHAI);
		GotoXY(60,i+6);printf("%s",dssv.nodes[i].SODT);
		*/
		i++;
		//dssv.n++;
		Preorder(p->left,i,dssv);
		Preorder(p->right,i,dssv);
	}
}

void indslk(NODE First){
	ShowCur(false);
	NODE q = First;
	if(q == NULL) printf("Danh sach rong!");
	int i = 0;
	while(q != NULL){
		GotoXY(10,i+6); printf("%d",i);
		GotoXY(23,i+6); printf("%s",q->diem.MAMH);
		GotoXY(42,i+6); printf("%d",q->diem.LAN);
		GotoXY(64,i+6); printf("%3.1f",q->diem.DIEM);
		q = q->next;
		i++;
	}
}
void ReadFile(){
	readFileMonhoc(dsmh);
	readFileLop(dsl);
}
void WriteFile(){
	//writeFileMH();
}
int main(){	
	ReadFile();
	//global var
	/*
	struct dssinhvien {
		int n;
		_sinhvien nodes[MAXLIST];
	};*/
	//struct dssinhvien dssv;
	
	SetConsoleTitle("QUAN LI DIEM SINH VIEN");
	SetConsolePos(350,100);
	
	int out=0,pos=0;
	MENU:
	ShowCur(false);
	TextColor(23);
	
	ck = Menu(9,out,pos);
	TextColor(31);
	if (out == 1) {
		Clear();
		if (m == 1) MessageBeep(0x00000010L);
		char a[] = " THONG BAO ";
		TextBox(a,20,5,40,7);
		TextColor(31);
		GotoXY(31,7);printf("THOAT CHUONG TRINH?");
		GotoXY(26,8);printf("PHIEN LAM VIEC DA DUOC LUU LAI");
		TextColor(23);
		GotoXY(48,10);printf("ENTER:THOAT");
		GotoXY(22,10);printf("ESC:QUAY LAI");

		int c = getch();
		if (c == 13) //ENTER TO EXIT
			return 1;
		else 
			goto MENU;
	}
	ShowCur(true);
	Clear();
	switch(ck){
		case 0: {
			char s[]=" NHAP LOP ";
			GotoXY(0,0);
			InputCheck(3,s,hnhap,ck);
			goto MENU;
		}
		case 1: {
			strcpy(ol,"");
			str t[1]={"NIEN KHOA    :[            ]"};
			char s[]=" DS LOP THEO KHOA ";

			InputCheck(1,s,t,ck);
			if(dung==-2) goto MENU;
			Clear();
			int tab=3;
			str header[3]={"MA LOP","TEN LOP","NAM NH"};
			char ti[]="DANH SACH LOP";
			ShowCur(false);
			int sp=(70-10+3)/tab;
			if(dung == -2) goto MENU;
			int dc=0;
			GridView(ti,tab,header,ck);
			for(int i = 0;i < dsl.n;i++) {
				if(dsl.nodes[i].NAMNH == atoi(ol)){
					GotoXY(10,dc+6);printf("%d",dc+1);		
					GotoXY(sp+2,dc+6); printf("%s",dsl.nodes[i].MALOP);
					GotoXY(sp+sp,dc+6); printf("%s",dsl.nodes[i].TENLOP);
					GotoXY(sp+sp+sp,dc+6); printf("%d",dsl.nodes[i].NAMNH);
					dc++;
				}
			}
			getch();
			goto MENU;
		}
		case 2:{
			strcpy(lp,"");
			char s[]=" NHAP SINH VIEN CHO LOP ";
			str t[1]={"MA LOP       :[            ]"};
			InputCheck(1,s,t,ck);
			if( dung == -2) goto MENU;
			ck=-2;
			char c[]=" NHAP SINH VIEN ";
			InputCheck(5,s,fnhap,ck);
			if( dung == -2) goto MENU;
			ck=2;
			goto MENU;
		}
		case 3:{
			strcpy(lp,"");
			char s[]=" DS SINH VIEN CUA LOP ";
			str t[1]={"MA LOP       :[            ]"};		
			InputCheck(1,s,t,ck);
			readFileLop(dsl);
			if( dung == -2) goto MENU;
			Clear();
			int tab=5;
			str header[5]={"MASV","HO","TEN","PHAI","SDT"};
			char ti[]="DANH SACH SINH VIEN LOP ";
			char *nameClass=strcat(ti,lp);
			
			int n=checkMalop(lp);
			readFileSVLOP(dsl.nodes[n].ptrdssv,lp);
				
			ShowCur(false);
			int i=0;
			//dssv.n=0;
			//Preorder(root,i,dssv);
			Clear();
			//indssv(dssv);

			int sp=(70-10+3)/tab;
			GridView(nameClass,tab,header,ck);
			getch();
			goto MENU;
		}
		case 4:{
			int n=4;
			char s[]=" NHAP MON HOC ";
			InputCheck(n,s,gnhap,ck);
			goto MENU;
		}
		case 5:{
	
			int tab=4;
			str header[4]={"MAMH","TENMH","STCLT","STCTH"};
			char s[]="DANH SACH MON HOC";
			//readFileMonhoc(dsmh);

			GridView(s,tab,header,ck);
			
			int sp=(70-10+3)/tab;
			for(int i=0;i<dsmh.n;i++){	
				GotoXY(10,i+6);printf("%d",i+1);		
				GotoXY(sp,i+6); printf("%s",dsmh.nodes[i].MAMH);
				GotoXY(sp+sp,i+6); printf("%s",dsmh.nodes[i].TENMH);
				GotoXY(sp+sp+sp,i+6); printf("%d",dsmh.nodes[i].STCLT);
				GotoXY(sp+sp+sp+sp,i+6); printf("%d",dsmh.nodes[i].STCTH);		
			}
			GotoXY(0,0);ShowCur(false);
			getch();
			goto MENU;
		}
		case 6:{
			strcpy(osv,"");
			char sv[]="NHAP DIEM CHO SINH VIEN";
			str tit[1]={"MA SINH VIEN :[            ]"};
			InputCheck(1,sv,tit,ck);
			ck=-6;
			if(dung == -2) goto MENU;
			char s[]=" NHAP DIEM ";
			InputCheck(3,s,enhap,ck);
			ck=6;
			goto MENU;
		}
		case 7:{
			times=0;
			memset(osv,0,13*sizeof(char));
			memset(lp,0,13*sizeof(char));
			char lop[]= " BANG DIEM CUA LOP ";
			str tit[3]={" MA LOP      :[            ]",
						" MA MON HOC  :[            ]",
						" LAN THI     :[            ]"};
			InputCheck(3,lop,tit,ck);
			if(dung == -2) goto MENU;
			
			int n=checkMalop(lp);
			readFileSVLOP(dsl.nodes[n].ptrdssv,lp);	
			
			//readFileSVLOP(root,lp);	
			readFileDiemLOP(First,osv,dsl.nodes[n].ptrdssv,times);
			
			Clear();		
			if(First!=NULL) indslk(First);
			str header[3]={"MAMH","LAN THI","DIEM"};
			char s[]="BANG DIEM CUA LOP ";
			char *v = strcat(s,lp);	
			GridView(v,3,header,ck);
			
			GotoXY(0,0);getch();
			goto MENU;
		}
		case 8:{
			strcpy(osv,"");
			char sv[]=" PHIEU DIEM SINH VIEN ";
			str tit[1]={"MA SINH VIEN :[            ]"};
			InputCheck(1,sv,tit,ck);
			if(dung == -2) goto MENU;
			
			readFileSinhvien(root);
			NODEPTR q = SearchSV(root,osv);
			readFileDiem(q->sv.ptrdsd,osv);
			
			Clear();
			indslk(q->sv.ptrdsd);
				
			str header[3]={"MAMH","LAN THI","DIEM"};
			char s[]="PHIEU DIEM CUA SV ";
			char *v = strcat(s,osv);	
			GridView(v,3,header,ck);
			GotoXY(0,0);getch();
			goto MENU;
		}
	}
	return 0;
}
