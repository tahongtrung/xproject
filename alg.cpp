#ifndef ALG_CPP_
#define ALG_CPP_
#include "struct.h"

//UDF for graphics
#define SELECT   241//menu text color was selected
#define UNSELECT 23 //menu text color was unselected

typedef char str[31];

enum status{ UP,DOWN,LEFT,RIGHT,ENTER,BACK,EXIT,MUSIC };

	
							
str hnhap[3]={"MA LOP       :[            ]",
			  "TEN LOP      :[            ]",
		 	  "NAM NHAP HOC :[            ]"};
			   				  
str gnhap[4]={"MA MON HOC   :[            ]",
			  "TEN MON HOC  :[            ]",
		 	  "STC LY THUYET:[            ]",	
			  "STC THUC HANH:[            ]"};

str fnhap[5]={"MA SINH VIEN :[            ]",
			  "HO SINH VIEN :[            ]",
		 	  "TEN SINH VIEN:[            ]",
			  "GIOI TINH    :[            ]",
			  "SO DIEN THOAI:[            ]"};
			  
str enhap[3]={"MA MON HOC   :[            ]",
			  "LAN THI      :[            ]",
		 	  "DIEM         :[            ]"};
		 	  
void SwapSV(_sinhvien &sva, _sinhvien &svb){
	_sinhvien svtemp = sva;
	sva = svb;
	svb = svtemp;
}
void GridView(char s[],int tab,str header[4],int ck){
	int l = strlen(s);
	int x = ((70-10)/2)-(l/2)+10;
	GotoXY(x,2); printf("%s",s);
	int sp = (70-10+3)/tab;
	for(int i = 0,j = sp;i < tab;i++,j += sp){
		if(i == 0) GotoXY(j+2,4);
		else GotoXY(j,4); printf("%s",header[i]);
	}
	GotoXY(10,4); printf("%s","STT");
	for(int i = 10;i < 70;i++) {		
		GotoXY(i,3);printf("%c",char(95));
	}
	for(int i = 10;i < 70;i++) {
		GotoXY(i,5); printf("%c",char(196));
	}		
}
void Box(int x,int y,int w,int h){
	for(int i = x;i <= x+w;i++){
		for(int j = y;j <= y+h ;j++){
			if(i == x && j == y) {
				GotoXY(i,j);printf("%c",char(201)); //top left
			}
			else if(i == x && j == y+h){
				GotoXY(i,j);printf("%c",char(200)); //bot left
			}
			else if(i == x+w && j == y){
				GotoXY(i,j);printf("%c",char(187)); //
			}
			else if(i == x+w && j == y+h){
				GotoXY(x+w,y+h);printf("%c",char(188));
			}
			else if(j == y){
				GotoXY(i,j);printf("%c",char(205));
			}
			else if(j == y+h){
				GotoXY(i,j);printf("%c",char(205));
			}
			else if(i == x){
				GotoXY(i,j);printf("%c",char(186));
			}
			else if(i == x+w){				
				GotoXY(i,j);printf("%c",char(186));
			}
			else
				continue;
		}
	}
}
void TextBox(char *s, int x,int y,int w,int h){	
	int l=strlen(s);
	for(int i=x;i<=(x+w);i++){
		for(int j=y;j<=y+h;j++){
			if(i==x&&j==y) {
				GotoXY(i,j);printf("%c",char(201)); //trai tren
			}
			else if(i == x && j == y+h){
				GotoXY(i,j);printf("%c",char(200)); //trai duoi
			}
			else if(i == x+w && j == y){
				GotoXY(i,j);printf("%c",char(187));
			}
			else if(i==(x+w) &&j==(y+h)){
				GotoXY(x+w,y+h);printf("%c",char(188));
			}
			else if(j==y){//bar ngang ne
				if(i<x+l+1) continue;			
				GotoXY(i,j);
				printf("%c",char(205));				
			}
			else if(j==y+h){
				GotoXY(i,j);printf("%c",char(205));
			}
			else if(i==x){	
				GotoXY(i,j);printf("%c",char(186));
			}
			else if(i==x+w){		
				GotoXY(i,j);printf("%c",char(186));
			}
			else
				continue;
		}
	}
	GotoXY(x+1,y);
	printf("%s",s);
}

// UDF for Datastruct & Algorithms
//void InsertNodeSV(NODEPTR &T,_sinhvien sv){
//	if(T!=NULL){
//		if(T->sv.MASV > sv.MASV) 
//			return InsertNodeSV(T->left,sv);
//		else
//			if(T->sv.MASV<sv.MASV) 
//				return InsertNodeSV(T->right,sv);
//	}
//	T = (NODEPTR) malloc(sizeof(nodesv));
//	strcpy(T->sv.MASV,sv.MASV);
//	strcpy(T->sv.HO,sv.HO);
//	strcpy(T->sv.TEN,sv.TEN);
//	strcpy(T->sv.PHAI,sv.PHAI);
//	strcpy(T->sv.SODT,sv.SODT);	
//	T->left = T->right = NULL;	
//}
void insertNODEPTR(NODEPTR &p, _sinhvien sv){
	if(p == NULL){
		p = new nodesv;
		p->sv = sv;
		p->left = NULL;
		p->right = NULL;		
	}
	else{
		if(strcmp(sv.MASV,p->sv.MASV)<0)
			insertNODEPTR(p->left,sv);
		else
			insertNODEPTR(p->right,sv);
	}
}
int ExistSV(NODEPTR p,char masv[],int &i){
	if(p!=NULL){
		if(strcmp(masv,p->sv.MASV)==0) i=1;
		ExistSV(p->left,masv,i);
		ExistSV(p->right,masv,i);
	}
}
void readFileSVLOP(NODEPTR &root,char malop[]){
	char path[]="bin\\student.ini";
	FILE *fp = fopen(path,"r");
	if(fp == NULL){
		printf("Error read file!");
	}else{	
		root = NULL;		
		while(!feof(fp)){	
			char mltemp[13];
			strcpy(mltemp,"");	
			_sinhvien sv;
			strcpy(sv.MASV,"");
			strcpy(sv.HO,"");
			strcpy(sv.TEN,"");
			strcpy(sv.PHAI,"");
			strcpy(sv.SODT,"");
						
			fgets(mltemp,255,fp);
			strtok(mltemp,"\n");						
			fgets(sv.MASV,255,fp);
			strtok(sv.MASV,"\n");			
			fgets(sv.HO,255,fp);
			strtok(sv.HO,"\n");			
			fgets(sv.TEN,255,fp);
			strtok(sv.TEN,"\n");			
			fgets(sv.PHAI,255,fp);
			strtok(sv.PHAI,"\n");		
			fgets(sv.SODT,255,fp);
			strtok(sv.SODT,"\n");
			if(strcmp(strupr(malop),strupr(mltemp)) == 0)
				//InsertNodeSV(root,sv);
				insertNODEPTR(root,sv);
		}
	}
	fclose(fp);		
}

NODEPTR SearchSV(NODEPTR root,char masv[]){
	NODEPTR p;
	p=root;
	while(p!=NULL && !(strcmp(p->sv.MASV,masv)==0)){
		if(strcmp(masv,p->sv.MASV)<0)
			p=p->left;
		else
			p=p->right;
	}
	return p;
}
void readFileLop(dslop &dsl){
	char path[]="bin\\class.ini";
	FILE *fp = fopen(path,"r");
	if(fp == NULL) printf("Error read file!");
	else{

		dsl.n=0;
		while(!feof(fp)){				
			fgets(dsl.nodes[dsl.n].MALOP,225,fp);
			strtok(dsl.nodes[dsl.n].MALOP,"\n");			
			fgets(dsl.nodes[dsl.n].TENLOP,225,fp);
			strtok(dsl.nodes[dsl.n].TENLOP,"\n");
			fscanf(fp,"%d\n",&dsl.nodes[dsl.n].NAMNH);
			dsl.n++;
		}
	}
	fclose(fp);
}
void writeFileLop(char malop[],char tenlop[], int nam){
	char path[]="bin\\class.ini";
	FILE *fp = fopen(path,"w");
	if(fp == NULL) printf("Error write file!");
	else{
		for(int i=0;i<dsl.n;i++){
			fprintf(fp,"%s\n",dsl.nodes[i].MALOP);
			fprintf(fp,"%s\n",dsl.nodes[i].TENLOP);
			fprintf(fp,"%d\n",dsl.nodes[i].NAMNH);			
		}		
	}
	fclose(fp);
}
void writeFileDiem(char masv[],char mamh[],int t,float d){
	char path[]="bin\\point.ini";
	FILE *fp = fopen(path,"a+");
	if(fp == NULL) printf("Error write file!");
	else{
		fprintf(fp,"%s\n",masv);
		fprintf(fp,"%s\n",mamh);
		fprintf(fp,"%d\n",t);
		fprintf(fp,"%f\n",d);			
	}
	fclose(fp);
}
void readFileMonhoc(dsmonhoc &dsmh){
	char path[]="bin\\subject.ini";
	FILE *fp = fopen(path,"r");
	if(fp == NULL){
		printf("Error read file!");
	}else{
		while(!feof(fp)){
			fgets(dsmh.nodes[dsmh.n].MAMH,255,fp);
			strtok(dsmh.nodes[dsmh.n].MAMH,"\n");
			
			fgets(dsmh.nodes[dsmh.n].TENMH,255,fp);
			strtok(dsmh.nodes[dsmh.n].TENMH,"\n");
			
			fscanf(fp,"%d\n",&dsmh.nodes[dsmh.n].STCLT);
			fscanf(fp,"%d\n",&dsmh.nodes[dsmh.n].STCTH);
			
			dsmh.n++;
		}
	}
	fclose(fp);
}
void InsertDiem(NODE &First,_diem d){	
	NODE p;
	p=(NODE)malloc(sizeof(struct nodesv));
	p->diem=d;
	p->next = First;
	First = p;	
}
void readFileDiem(NODE &First,char masv[],NODEPTR){
	char path[]="bin\\point.ini";
	FILE *fp = fopen(path,"r");
	if(fp == NULL){
		printf("Error read file!");
		getch();
	}else{
		First = NULL;
		while(!feof(fp)){
			char sv[13];
			_diem d;			
			fgets(sv,255,fp);
			strtok(sv,"\n");
					
			fgets(d.MAMH,225,fp);
			strtok(d.MAMH,"\n");
					
			fscanf(fp,"%d\n",&d.LAN);			
			fscanf(fp,"%f\n",&d.DIEM);
			if(strcmp(strupr(sv),strupr(masv)) == 0 ||SearchSV(root,strupr(masv))!=NULL){				
				InsertDiem(First,d);
				strcpy(sv,"");
			}			
		}		
	}
	fclose(fp);
}
int readCheckFileDiem(char masv[],char mamh[]){
	char path[]="bin\\point.ini";
	FILE *fp = fopen(path,"r");
	int k = 0;
	if(fp == NULL){
		printf("Error read file!");	
		getch();	
	}else{
		while(!feof(fp)){					
			char sv[13];
			_diem d;			
			fgets(sv,255,fp);
			strtok(sv,"\n");
					
			fgets(d.MAMH,225,fp);
			strtok(d.MAMH,"\n");
					
			fscanf(fp,"%d\n",&d.LAN);			
			fscanf(fp,"%f\n",&d.DIEM);
			if(strcmp(strupr(sv),strupr(masv)) == 0 &&strcmp(strupr(d.MAMH),strupr(mamh))==0){				
				if(d.LAN>k) k=d.LAN;				
			}
			strcpy(sv,"");			
		}		
	}
	fclose(fp);
	return k;
}
void DelFirst(NODE &First){
	NODE temp = First->next;
	First = temp;
	temp=NULL;
}
void readFileDiem(NODE &First,char masv[]){
	char path[]="bin\\point.ini";
	FILE *fp = fopen(path,"r");
	if(fp == NULL){
		printf("Error read file!");	
		getch();	
	}
	else{
		First=NULL;
		while(!feof(fp)){					
			char sv[13];
			_diem d;			
			fgets(sv,255,fp);
			strtok(sv,"\n");
					
			fgets(d.MAMH,225,fp);
			strtok(d.MAMH,"\n");
					
			fscanf(fp,"%d\n",&d.LAN);			
			fscanf(fp,"%f\n",&d.DIEM);
			
			if(strcmp(sv,masv)==0){		
				InsertDiem(First,d);
				NODE p=First->next;
				while(p!=NULL){
					if(strcmp(p->diem.MAMH,d.MAMH)==0 ){
						if(d.DIEM > p->diem.DIEM){
							p->diem.LAN=d.LAN;
							p->diem.DIEM=d.DIEM;
							DelFirst(First);
							break;
						}
						else DelFirst(First);
					}	
					p=p->next;
				}
			}						
		}		
	}
	fclose(fp);	
}
void readFileDiemLOP(NODE &First,char mamh[],NODEPTR root,int times){	
	char path[]="bin\\point.ini";
	FILE *fp = fopen(path,"r");
	if(fp == NULL){
		printf("Error read file!");	
		getch();	
	}else{
		First=NULL;	
		while(!feof(fp)){					
			
			_diem d;
			char masv[13];			
			fgets(masv,255,fp);
			strtok(masv,"\n");
					
			fgets(d.MAMH,225,fp);
			strtok(d.MAMH,"\n");
					
			fscanf(fp,"%d\n",&d.LAN);			
			fscanf(fp,"%f\n",&d.DIEM);
			
			int i=0;
			int c = ExistSV(root,masv,i);		
			if((strcmp(mamh,d.MAMH) == 0) && i==1 && times==d.LAN){
				InsertDiem(First,d);		
			}
			strcpy(masv,"");	
		}		
	}
	fclose(fp);	
}


void writeFileSV(char malop[],char masv[],char ho[], char ten[], char gt[],char sdt[]){
	char path[]="bin\\student.ini";
	FILE *fp = fopen(path,"a+");
	if(fp == NULL) printf("Error write file!");
	else{
		fprintf(fp,"%s\n",malop);
		fprintf(fp,"%s\n",masv);
		fprintf(fp,"%s\n",ho);
		fprintf(fp,"%s\n",ten);
		fprintf(fp,"%s\n",gt);
		fprintf(fp,"%s\n",sdt);			
	}
	fclose(fp);
}
void readFileSinhvien(NODEPTR &root){
	char path[]="bin\\student.ini";
	FILE *fp = fopen(path,"r");
	if(fp == NULL) printf("Error read file!");
	else{	
		root=NULL;
		while(!feof(fp)){
			char mltemp[13];
			_sinhvien sv;			
			fgets(mltemp,255,fp);
			strtok(mltemp,"\n");				
			fgets(sv.MASV,255,fp);
			strtok(sv.MASV,"\n");			
			fgets(sv.HO,255,fp);
			strtok(sv.HO,"\n");			
			fgets(sv.TEN,255,fp);
			strtok(sv.TEN,"\n");			
			fgets(sv.PHAI,255,fp);
			strtok(sv.PHAI,"\n");			
			fgets(sv.SODT,255,fp);
			strtok(sv.SODT,"\n");	
			insertNODEPTR(root,sv);
			strcpy(mltemp,"");
		}
	}
	fclose(fp);		
}

void writeFileMH(char mamh[],char tenmh[],int lt,int th){
	char path[]="bin\\subject.ini";
	FILE *fp = fopen(path,"a+");
	if(fp == NULL) printf("Error write file!");
	else{
		fprintf(fp,"%s\n",mamh);
		fprintf(fp,"%s\n",tenmh);
		fprintf(fp,"%d\n",lt);
		fprintf(fp,"%d\n",th);		
	}
	fclose(fp);
}
//void InsertDiemAfter(NODE &root,_diem d){
//	NODE p;
//	if(root==NULL){		
//	}else{
//		p->diem = d;
//		p->next = root->next;
//		root->next = p;
//	}
//}

#endif
