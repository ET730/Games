#include<stdio.h>
#define L 8
void campo(int X[L][L]);
int vive(int X[L][L],int P);
int controllo(int G,int V[L][L],int X,int Y);
int controllo2(int G,int V[L][L],int X,int Y,int X1,int Y1,int D[L][L]);//ieri sera stavo introducendo il concetto damone e lo spostamento avanti indietro,usa matrice d'appoggio
int damone(int D[L][L],int X,int Y);
int mangiare(int V[L+2][L+2],int G);
int main(){
	int table[L][L]={0};
	int i, j;
	int cont=0;
	int V1=12,V2=12;//Conta quante pedine ci sono ancora in gioco
	int partita=1;//esegue la partita
	int X1,Y1,X2,Y2,X,Y,K;
	int D[L][L]={0},table_2[L+2][L+2]={3};
	
	for(j=L-1; j>=0; j--, cont++){
		for(i=0; i<L; i++){
			if(j>4){
				if(i%2==0 && cont%2==1){
					table[i][j]=1;
					table_2[i+1][j+1]=1;
				}
				else if(i%2==1 && cont%2==0){
					table[i][j]=1;
					table_2[i+1][j+1]=1;
				}
				else{
					table[i][j]=0;
					table_2[i+1][j+1]=0;
				}
			}else if(j<3){
				if(i%2==0 && cont%2==1){
					table[i][j]=2;
					table_2[i+1][j+1]=2;
				}
				else if(i%2==1 && cont%2==0){
					table[i][j]=2;
					table_2[i+1][j+1]=2;
				}
				else{
					table[i][j]=0;
					table_2[i+1][j+1]=0;
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
				do{
					printf("Giocatore %d fai la tua mossa\n",G);
					printf("Seleziona la pedina(X/Y) : ");
					scanf("%d%d",&X,&Y);
					//printf("%d%d\n",table[X-1][L-Y],controllo(G,table,X,Y));
					
				}while(controllo(G,table,X,Y));
				do{
					printf("Dove vuoi andare : ");
					scanf("%d%d",&X1,&Y1);
					
				}while(controllo2(G,table,X,Y,X1,Y1,D));// definire la funzione damone
				if (G==1 && Y1==8){
					D[X1-1][L-Y1]=1;
				}
				if (G==2 && Y1==1){
					D[X1-1][L-Y1]=1;
				}
				if (D[X-1][L-Y]==1){
					D[X-1][L-Y]==0;
					D[X1-1][L-Y1]=1;
				}
				K=mangiare(table_2,G);
				printf("%d\n",K);
				table[X-1][L-Y]=0;
				table_2[X][L-Y+1]=0;
				
				table[X1-1][L-Y1]=G;
				table_2[X1][L-Y1+1]=G;
				
				if ((X+2==X1 && Y+2==Y1)){
					table[X][L-Y-1]=0;
					table_2[X+1][L-Y]=0;
					K=0;
				} else if ((X-2==X1 && Y+2==Y1)){
					table[X-2][L-Y-1]=0;
					table_2[X-1][L-Y]=0;
					K=0;
				} else if ((X+2==X1 && Y-2==Y1)){
					table[X][L-Y+1]=0;
					table_2[X+1][L-Y+2]=0;
					K=0;
				} else if ((X-2==X1 && Y-2==Y1)){
					table[X-2][L-Y+1]=0;
					table_2[X-1][L-Y+2]=0;
					K=0;
				}
				if (K==0 && mangiare(table_2,G)){
					K=mangiare(table_2,G);
				} else if (K==1){
					for (Y2=L;Y2>0;Y2--){
						for (X2=0;X2<L;X2++){
							if (table[X2][L-Y2]==G){
								if (table[X2+1][L-Y2+1]!=0 && table[X2+1][L-Y2+1]!=G){
									if (table[X2+2][L-Y2+2]==0){
										table[X2-1][L-Y2]=0;
										table_2[X2][L-Y2+1]=0;
									}
								} else if (table[X2+1][L-Y2-1]!=0 && table[X2+1][L-Y2-1]!=G){
									if (table[X2+2][L-Y2-2]==0){
										table[X2][L-Y2]=0;
										table_2[X2+1][L-Y2+1]=0;
									}
								} else if (table[X2-1][L-Y2+1]!=0 && table[X2-1][L-Y2+1]!=G){
									if (table[X2-2][L-Y2+2]==0){
										table[X2][L-Y2]=0;
										table_2[X2+1][L-Y2+1]=0;
									}
								} else if (table[X2-1][L-Y2-1]!=0 && table[X2-1][L-Y2-1]!=G){
									if (table[X2-2][L-Y2-2]==0){
										table[X2-1][L-Y2]=0;
										table_2[X2][L-Y2+1]=0;
									}
								}							
							}
						}
					}
				
				}
				campo(table);
				mangiare(table_2,G);
				
			}while(mangiare(table_2,G));
		}
	}
}
int mangiare(int V[L+2][L+2],int G){
	for (int Y=L+2;Y>0;Y--){
		for (int X=0;X<L+2;X++){
			if (V[X][L-Y]==G){
				if (V[X+1][L-Y+1]!=0 && V[X+1][L-Y+1]!=G){
					if (V[X+2][L-Y+2]==0){
						printf("1p%d%d%d\n",X,Y,V[X][L-Y]);
						return 1;
						
					} else {
						return 0;
					}
				} else if (V[X+1][L-Y-1]!=0 && V[X+1][L-Y-1]!=G){
					if (V[X+2][L-Y-2]==0){
						printf("2p%d%d%d\n",X,Y,V[X][L-Y]);
						return 1;
						
					} else {
						return 0;
					}
				} else if (V[X-1][L-Y+1]!=0 && V[X-1][L-Y+1]!=G){
					if (V[X-2][L-Y+2]==0){
						printf("3p%d%d%d\n",X,Y,V[X][L-Y]);
						return 1;
						
					} else {
						return 0;
					}
				} else if (V[X-1][L-Y-1]!=0 && V[X-1][L-Y-1]!=G){
					if (V[X-2][L-Y-2]==0){
						printf("4p%d%d%d\n",X,Y,V[X][L-Y]);
						return 1;
						
					} else {
						return 0;
					}
				}
			}
		}
	}
	return 0;
}
int controllo2(int G,int V[L][L],int X,int Y,int X1,int Y1,int D[L][L]){//modificare il controllo, se è un damone può tornare indietro 
	if (X1>8 || X1<1 || Y1>8 || Y1<1){
		printf("Mossa non valida0\n");
		return 1;
	} else if (damone(D,X,Y)){
		if (V[X1-1][L-Y1]==0 && ((X>=X1-2 && Y>=Y1-2)||(X>=X1+2 && Y>=Y1-2)||(X>=X1-2 && Y<=Y1+2)||(X>=X1+2 && Y<=Y1+2))){
			if ((X+2==X1 && Y+2==Y1)||(X-2==X1 && Y+2==Y1)||(X-2==X1 && Y-2==Y1)||(X+2==X1 && Y-2==Y1)){
				if ((V[X][L-Y+1]!=0 && V[X][L-Y+1]!=G)||(V[X][L-Y-1]!=0 && V[X][L-Y-1]!=G)||(V[X-2][L-Y+1]!=0 && V[X-2][L-Y+1]!=G)||(V[X-2][L-Y-1]!=0 && V[X-2][L-Y-1]!=G)){
					return 0;
					
				} else {
					printf("Mossa non valida1\n");
					return 1;
				}
			} else {
				if ((X+1==X1 && Y+1==Y1)||(X-1==X1 && Y+1==Y1)||(X-1==X1 && Y-1==Y1)||(X+1==X1 && Y-1==Y1)){
					if (V[X][L-Y+1]==0||V[X][L-Y-1]==0||V[X-2][L-Y+1]==0||V[X-2][L-Y-1]==0){
						return 0;
					} else {
						printf("Mossa non valida2\n");
						return 1;
					}
				} else {
					printf("Mossa non valida3\n");
					return 1;
				}
			}
		} else {
			printf("Mossa non valida4\n");
			return 1;
		}
	} else {
		if (G==1){
			if ((Y1>Y)&&((X>=X1-2 && Y>=Y1-2)||(X>=X1+2 && Y>=Y1-2))){
				if ((X+2==X1 && Y+2==Y1)||(X-2==X1 && Y+2==Y1)){
					if ((V[X][L-Y-1]!=0 && V[X][L-Y-1]!=G)||(V[X-2][L-Y-1]!=0 && V[X-2][L-Y-1]!=G)){
						return 0;
					
					} else {
						printf("Mossa non valida5\n");
						return 1;
					}
				} else {
					if ((X+1==X1 && Y+1==Y1)||(X-1==X1 && Y+1==Y1)){
						if (V[X1][L-Y-1]==0||V[X-2][L-Y1-1]==0){
							return 0;
						} else {
							printf("Mossa non valida6\n");
							return 1;
						}
					} else {
						printf("Mossa non valida7\n");
						return 1;
					}
				}
			} else {
				printf("Mossa non valida8\n");
				return 1;
			}
		} else {
			if ((Y1<Y)&&((X>=X1-2 && Y<=Y1+2)||(X>=X1+2 && Y<=Y1+2))){
				if ((X+2==X1 && Y-2==Y1)||(X-2==X1 && Y-2==Y1)){
					if ((V[X][L-Y+1]!=0 && V[X][L-Y+1]!=G)||(V[X-2][L-Y+1]!=0 && V[X-2][L-Y+1]!=G)){
						return 0;
					
					} else {
						printf("Mossa non valida9\n");
						return 1;
					}
				} else {
					if ((X+1==X1 && Y-1==Y1)||(X-1==X1 && Y-1==Y1)){
						if (V[X][L-Y+1]==0||V[X-2][L-Y+1]==0){
							return 0;
						} else {
							printf("Mossa non valida10\n");
							return 1;
						}
					} else {
						printf("Mossa non valida11\n");
						return 1;
					}
				}
			} else {
				printf("Mossa non valida12\n");
				return 1;
			}
		}
	}
}
int controllo(int G,int V[L][L],int X,int Y){

	if (X>8 || X<1 || Y>8 || Y<1){
		printf("Cordinate non valide\n");
		//printf("%d",V[X-1][L-Y]);
		return 1;
	} else if ((V[X-1][L-Y]==0)||(V[X-1][L-Y]!=G)){
		printf("Cordinate non valide\n");
		//printf("%d",V[X-1][L-Y]);
		return 1;
	} else if (G==1){
		if (Y>1){
			if (X>1 && X<8){
				if ((V[X][L-Y+1]==G)&&(V[X][L-Y-1]==G)&&(V[X-2][L-Y+1]==G)&&(V[X-2][L-Y-1]==G)){
					printf("Cordinate non valide\n");
					//printf("%d",V[X-1][L-Y]);
					return 1;
				} else {
					return 0;
				}
			} else if (X==1){
				if ((V[X][L-Y+1]==G)&&(V[X][L-Y-1]==G)){
					printf("Cordinate non valide\n");
					//printf("%d",V[X-1][L-Y]);
					return 1;
				} else {
					return 0;
				}
			} else {
				if ((V[X-2][L-Y+1]==G)&&(V[X-2][L-Y-1]==G)){
					printf("Cordinate non valide\n");
					//printf("%d",V[X-1][L-Y]);
					return 1;
				} else {
					return 0;
				}
			}
		} else {
			if (X>1 && X<8){
				if ((V[X-2][L-Y-1]==G)&&(V[X][L-Y-1]==G)){
					printf("Cordinate non valide\n");
					//printf("%d",V[X-1][L-Y]);
					return 1;
				} else {
					return 0;
				}
			} else if (X==1){
				if ((V[X][L-Y-1]==G)){
					printf("Cordinate non valide\n");
					//printf("%d",V[X-1][L-Y]);
					return 1;
				} else {
					return 0;
				}
			} else {
				if ((V[X-2][L-Y-1]==G)){
					printf("Cordinate non valide\n");
					//printf("%d",V[X-1][L-Y]);
					return 1;
				} else {
					return 0;
				}
			}
		}
	}else if(G==2){
		if(Y<8){
			if (X>1 && X<8){
				if ((V[X][L-Y+1]==G)&&(V[X][L-Y-1]==G)&&(V[X-2][L-Y+1]==G)&&(V[X-2][L-Y-1]==G)){
					printf("Cordinate non valide\n");
					//printf("%d",V[X-1][L-Y]);
					return 1;
				} else {
					return 0;
				}
			} else if (X==1){
				if ((V[X][L-Y+1]==G)&&(V[X][L-Y-1]==G)){
					printf("Cordinate non valide\n");
					//printf("%d",V[X-1][L-Y]);
					return 1;
				} else {
					return 0;
				}
			} else {
				if ((V[X-2][L-Y+1]==G)&&(V[X-2][L-Y-1]==G)){
					printf("Cordinate non valide\n");
					//printf("%d",V[X-1][L-Y]);
					return 1;
				} else {
					return 0;
				}
			}
		} else {
			if (X>1 && X<8){
				if ((V[X-2][L-Y+1]==G)&&(V[X][L-Y+1]==G)){
					printf("Cordinate non valide\n");
					//printf("%d",V[X-1][L-Y]);
					return 1;
				} else {
					return 0;
				}
			}  else if (X==1){
				if ((V[X][L-Y+1]==G)){
					printf("Cordinate non valide\n");
					//printf("%d",V[X-1][L-Y]);
					return 1;
				} else {
					return 0;
				}
			} else {
				if ((V[X-2][L-Y+1]==G)){
					printf("Cordinate non valide\n");
					//printf("%d",V[X-1][L-Y]);
					return 1;
				} else {
					return 0;
				}
			}
		}                                  
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
	int count=4,flag=0,S;
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
					if (X[i][L-count/4]!=0){
						printf("|%3d  | ",X[i][L-count/4]);
					} else {
					 	printf("|     | ");
					}
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
int damone(int D[L][L],int X,int Y){
	if(D[X-1][L-Y]){
		return 1;
	} else { 
		return 0;
	}
}
