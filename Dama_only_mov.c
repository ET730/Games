#include<stdio.h>
#define L 8
void campo(int X[L][L]);
int vive(int X[L][L],int P);
int controllo(int G,int V[L][L],int X,int Y);
int controllo2(int G,int V[L][L],int X,int Y,int X1,int Y1,int D);//ieri sera stavo introducendo il concetto damone e lo spostamento avanti indietro,usa matrice d'appoggio
int main(){
	int table[L][L]={0};
	int i, j;
	int cont=0;
	int V1=12,V2=12;//Conta quante pedine ci sono ancora in gioco
	int partita=1;//esegue la partita
	int X1,Y1,X2,Y2,X,Y;
	
	for(j=L-1; j>=0; j--, cont++){
		for(i=0; i<L; i++){
			if(j>4){
				if(i%2==0 && cont%2==1){
					table[i][j]=1;
				}
				else if(i%2==1 && cont%2==0){
					table[i][j]=1;
				}
				else{
					table[i][j]=0;
				}
			}else if(j<3){
				if(i%2==0 && cont%2==1){
					table[i][j]=2;
				}
				else if(i%2==1 && cont%2==0){
					table[i][j]=2;
				}
				else{
					table[i][j]=0;
				}
			}
		}
	}
	campo(table);
	while(partita && (V1!=0 && V2!=0)){
		V1=vive(table,1);
		V2=vive(table,2);
		for (int G=1;G<=2;G++){
			do{
				printf("Giocatore %d fai la tua mossa\n",G);
				printf("Seleziona la pedina(X/Y) : ");
				scanf("%d%d",&X,&Y);
				
			}while(controllo(G,table,X,Y));
			do{
				printf("Dove vuoi andare : ");
				scanf("%d%d",&X1,&Y1);
				
			}while(controllo2(G,table,X,Y,X1,Y1,D));// definire la funzione damone
			
			/*
			table[X-1][L-Y]=0;
			
			table[X1-1][L-Y1]=G;
			
			campo(table);
			*/
		}
	}
}
int controllo2(int G,int V[L][L],int X,int Y,int X1,int Y1,int D){//modificare il controllo, se è un damone può tornare indietro 
	if (X1>8 || X1<1 || Y1>8 || Y1<1){
		printf("Mossa non valida0\n");
		return 1;
	} else {
		if (V[X1-1][L-Y1]==0 && ((X<X1-2 && Y<Y1-2)||(X<X1+2 && Y<Y1-2)||(X<X1+2 && Y<Y1+2)||(X<X1-2 && Y<Y1+2))){
			if ((X+2==X1 && Y+2==Y1)||(X-2==X1 && Y+2==Y1)||(X-2==X1 && Y-2==Y1)||(X+2==X1 && Y-2==Y1)){
				if ((V[X][L-Y+1]!=0 && V[X][L-Y+1]!=G)||(V[X][L-Y-1]!=0 && V[X][L-Y-1]!=G)||(V[X-2][L-Y+1]!=0 && V[X-2][L-Y+1]!=G)||(V[X-2][L-Y-1]!=0 && V[X-2][L-Y-1]!=G)){
					return 0;
					
				} else {
					printf("Mossa non valida\n");
					return 1;
				}
			} else {
				return 0;
			}
		} else {
			printf("Mossa non valida\n");
			return 1;
		}
	}
}
int controllo(int G,int V[L][L],int X,int Y){

	if (X>8 || X<1 || Y>8 || Y<1){
		printf("Cordinate non valide\n");
		//printf("%d",V[X-1][L-Y]);
		return 1;
	} else if (V[X-1][L-Y]==G){
		//printf("%d",V[X-1][L-Y]);
		return 0;
	} else {
		printf("Cordinate non valide\n");
		//printf("%d",V[X-1][L-Y]);
		return 1;
	}
}
int vive(int X[L][L],int P){
	int vive=0;
	for(int j=L-1; j>=0; j--){
		for(int i=0; i<L; i++){
			if (X[j][i]==P){
				vive++;
			}
		}
	}
	return vive;
}
	
void campo(int X[L][L]){
	int count=4,flag=0;
	do{
		
				if(flag==0){
					printf("        ");
				}
				if(flag==1){
					printf("        ");
				}
				if(flag==2){
					printf("        ");
				}
				if(flag==3){
					printf("  %3d   ",count/4);
				}
				if(flag==4){
					printf("        ");
				}
		for (int i=0;i<L;i++){
			
			
				if(flag==0){
					printf(" %3d    ",i+1);
				}
				if(flag==1){
					printf(" _____  ");
				}
				if(flag==2){
					printf("|     | ");
				}
				if(flag==3){
					printf("|%3d  | ",X[i][L-count/4]);
				}
				if(flag==4){
					printf("|_____| ");
				}
				
		
		}
		printf("\n");
		if (flag<4){
			flag++;
		} else {
			flag=1;
		}
		count++;
	}while(count<L*4+5);
	
}

