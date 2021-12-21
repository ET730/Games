 #include<stdio.h>
#define L 8
void campo(int X[L][L]);

int vive(int X[L][L],int P);
int controllo(int G,int V[L][L],int X,int Y);
int controllo2(int G,int V[L][L],int X,int Y,int X1,int Y1,int D[L+2][L+2]);//ieri sera stavo introducendo il concetto damone e lo spostamento avanti indietro,usa matrice d'appoggio
int damone(int D[L+2][L+2],int X,int Y);
int mangiare(int V[L+2][L+2],int G,int D[L+2][L+2]);
int mangX(int X,int Y,int V[L+2][L+2],int G,int D[L+2][L+2]);
int main(){
	int table[L][L]={0}; //Tavolo di gioco
	int i, j;
	int cont=0;
	int V1=12,V2=12;//Conta quante pedine ci sono ancora in gioco
	int X1,Y1,X2,Y2,X,Y,K=0,R,Sost;
	int D[L+2][L+2]={0},table_2[L+2][L+2];//tavolo dei damoni e tavolo 2 per controlli
	//Inizializzo il campo 
	for(j=L-1; j>=0; j--, cont++){
		for(i=0; i<L; i++){
			if(j>4){
				if(i%2==0 && cont%2==1){
					table[i][j]=1;
					table_2[i+1][j+1]=1;
					//printf("%d",table_2[i+1][j+1]);
				}
				else if(i%2==1 && cont%2==0){
					table[i][j]=1;
					table_2[i+1][j+1]=1;
					//printf("%d",table_2[i+1][j+1]);
				}
				else{
					table[i][j]=0;
					table_2[i+1][j+1]=0;
					//printf("%d",table_2[i+1][j+1]);
				}
			}else if(j<3){
				if(i%2==0 && cont%2==1){
					table[i][j]=2;
					table_2[i+1][j+1]=2;
					//printf("%d",table_2[i+1][j+1]);
				}
				else if(i%2==1 && cont%2==0){
					table[i][j]=2;
					table_2[i+1][j+1]=2;
					//printf("%d",table_2[i+1][j+1]);
				}
				else{
					table[i][j]=0;
					table_2[i+1][j+1]=0;
					//printf("%d",table_2[i+1][j+1]);
				}
			} else {
				table[i][j]=0;
				table_2[i+1][j+1]=0;
			}
			//printf("%d",table_2[i+1][j+1]);
		}
		//printf("\n");
	}
	for(j=L+1; j>=0; j--, cont++){
		for(i=0; i<L+2; i++){
			if (j==9 || j==0 || i==0 || i==9){
				table_2[i][j]=3;
			//	printf("%d",table_2[i][j]);
			} else {
			//	printf(" ");
			}
		}
		//printf("\n");
	}
	campo(table); //stampo il campo una prima volta
	
	while((V1>0 && V2>0)){ // inizio la partita finchè almeno uno dei giocatori non ha esaurito le pedine
		V1=vive(table,1);
		V2=vive(table,2);
		for (int G=1;G<=2;G++){
			int S=0;
			do{
				if (S==0){
					K=mangiare(table_2,G,D);
					printf("%d = controllo\n",K);
					do{			// selezione della pedina
						printf("Giocatore %d fai la tua mossa\n",G);
						printf("Seleziona la pedina(X/Y) : ");
						scanf("%d%d",&X,&Y);
						//printf("%d%d\n",table[X-1][L-Y],controllo(G,table,X,Y));
						
					}while(controllo(G,table,X,Y));
					do{			//spostamento
						printf("Dove vuoi andare : ");
						scanf("%d%d",&X1,&Y1);
						if (X1==X && Y1==Y){
							do{ 	//se inserisco le cordinate della pedina stessa richiedo le coordinate 
								printf("Giocatore %d fai la tua mossa\n",G);
								printf("Seleziona la pedina(X/Y) : ");
								scanf("%d%d",&X,&Y);
								//printf("%d%d\n",table[X-1][L-Y],controllo(G,table,X,Y));
								
							}while(controllo(G,table,X,Y));
							printf("Dove vuoi andare : ");
							scanf("%d%d",&X1,&Y1);
						}
						
					}while(controllo2(G,table,X,Y,X1,Y1,D));// definire la funzione damone
				} else if (S==1){
					X=X1;
					Y=Y1;
					do{			//spostamento
						printf("Dove vuoi andare : ");
						scanf("%d%d",&X1,&Y1);
						if (X1==X+1 || X1==X-1){
							R=0;
							X1=X;
							Y1=Y;
						} else {
							R=controllo2(G,table,X,Y,X1,Y1,D);
						}
					}while(R);
				}
				
				
				
				
				if ((X+2==X1 && Y+2==Y1)){
					table[X][L-Y-1]=0;
					table_2[X+1][L-Y]=0;
					D[X+1][L-Y]=0;
					K=0;
					S=1;
				} else if ((X-2==X1 && Y+2==Y1)){
					table[X-2][L-Y-1]=0;
					table_2[X-1][L-Y]=0;
					D[X-1][L-Y]=0;
					K=0;
					S=1;
				} else if ((X+2==X1 && Y-2==Y1)){
					table[X][L-Y+1]=0;
					table_2[X+1][L-Y+2]=0;
					D[X+1][L-Y+2]=0;
					K=0;
					S=1;
				} else if ((X-2==X1 && Y-2==Y1)){
					table[X-2][L-Y+1]=0;
					table_2[X-1][L-Y+2]=0;
					D[X-1][L-Y+2]=0;
					K=0;
					S=1;
				}
				if (K==1 && S==0){
					for (Y2=L-1;Y2>=0;Y2--){
						for (X2=0;X2<L;X2++){
							if (table[X2][Y2]==G){
								if (table[X2+1][Y2+1]!=0 && table[X2+1][Y2+1]!=G && table[X2+1][Y2+1]!=3 && K==1){
									if (table[X2+2][Y2+2]==0){
										table[X2][Y2]=0;
										table_2[X2+1][Y2+1]=0;
										D[X2+1][Y2+1]=0;
										K=0;
									}
								}
								else if (table[X2-1][Y2-1]!=0 && table[X2-1][Y2-1]!=G && table[X2-1][Y2-1]!=3 && K==1){
									if (table[X2-2][Y2-2]==0){
										table[X2][Y2]=0;
										table_2[X2+1][Y2+1]=0;
										D[X2+1][Y2+1]=0;
										K=0;
									}
								}
								else if (table[X2-1][Y2+1]!=0 && table[X2-1][Y2+1]!=G && table[X2-1][Y2+1]!=3 && K==1){
									if (table[X2-2][Y2+2]==0){
										table[X2][Y2]=0;
										table_2[X2+1][Y2+1]=0;
										D[X2+1][Y2+1]=0;
										K=0;
									}
								}
								else if (table[X2+1][Y2-1]!=0 && table[X2+1][Y2-1]!=G && table[X2+1][Y2-1]!=3 && K==1){
									if (table[X2+2][Y2-2]==0){
										table[X2][Y2]=0;
										table_2[X2+1][Y2+1]=0;
										D[X2+1][Y2+1]=0;
										K=0;
									}
								}
							}
						}
					}
				}
				if (X1!=X && Y1!=Y){
					table[X1-1][L-Y1]=table[X-1][L-Y];
					table_2[X1][L-Y1+1]=table_2[X][L-Y+1];
					table[X-1][L-Y]=0;
					table_2[X][L-Y+1]=0;
				}
				if (G==1 && Y1==8){		//creo i damoni
					D[X1][L-Y1+1]=G;
				}
				if (G==2 && Y1==1){
					D[X1][L-Y1+1]=G;
				}
				if (D[X][L-Y+1]!=0){		// se la pedina selezionata è un damone la sposto
					D[X1][L-Y1+1]=D[X][L-Y+1];
					D[X][L-Y+1]=0;
				}
				if (S==1){
					K=mangX(X1,9-Y1,table_2,G,D);
				}
				printf("\n");
				//campo(D);
				campo(table);
				
				
			}while(K);
		
		printf("%d\n",K);
		}
	}
	return 0;
}
int mangX(int X,int Y,int V[L+2][L+2],int G,int D[L+2][L+2]){
	int K;
	K=damone(D,X,Y);
	if (K==1){
		if (V[X][Y]==G){
			if (V[X+1][Y-1]!=0 && V[X+1][Y-1]!=G && V[X+1][Y-1]!=3){
				if (V[X+2][Y-2]==0){
					
					return 1;
				} else {return 0;}
			} else if (V[X-1][Y+1]!=0 && V[X-1][Y+1]!=G && V[X-1][Y+1]!=3){
				if (V[X-2][Y+2]==0){
					
					return 1;
				} else {return 0;}
			} else if (V[X-1][Y-1]!=0 && V[X-1][Y-1]!=G && V[X-1][Y-1]!=3){
				if (V[X-2][Y-2]==0){
					
					return 1;
				} else {return 0;}
			} else if (V[X+1][Y+1]!=0 && V[X+1][Y+1]!=G && V[X+1][Y+1]!=3){
				if (V[X+2][Y+2]==0){
					
					return 1;
				} else {return 0;}
			}
		}
	} else {
		if (G==1){
			if (V[X][Y]==G){
				if (V[X+1][Y-1]!=0 && V[X+1][Y-1]!=G && V[X+1][Y-1]!=3 && D[X+1][Y-1]==0){
					if (V[X+2][Y-2]==0){
						return 1;
					} else {return 0;}
				} else if (V[X-1][Y-1]!=0 && V[X-1][Y-1]!=G && V[X-1][Y-1]!=3 && D[X-1][Y-1]==0){
					if (V[X-2][Y-2]==0){
						return 1;
					} else {return 0;}
				} else {return 0;}
			}
		} else {
			if(V[X][Y]==G){
				if (V[X-1][Y+1]!=0 && V[X-1][Y+1]!=G && V[X-1][Y+1]!=3 && D[X-1][Y+1]==0){
					if (V[X-2][Y+2]==0){
						return 1;
					} else {return 0;}
				}  else if (V[X+1][Y+1]!=0 && V[X+1][Y+1]!=G && V[X+1][Y+1]!=3 && D[X+1][Y+1]==0){
					if (V[X+2][Y+2]==0){
						return 1;
					} else {return 0;}
				} else {return 0;}
			}
		}
	}
	return 0;
}
int mangiare(int V[L+2][L+2],int G,int D[L+2][L+2]){
	int K;
	for (int Y=L;Y>0;Y--){
		for (int X=1;X<L+1;X++){
			K=damone(D,X,Y);
			if (K==1){
				if (V[X][Y]==G){
					if (V[X+1][Y-1]!=0 && V[X+1][Y-1]!=G && V[X+1][Y-1]!=3){
						if (V[X+2][Y-2]==0){
							return 1;
						} else {continue;}
					} else if (V[X-1][Y+1]!=0 && V[X-1][Y+1]!=G && V[X-1][Y+1]!=3){
						if (V[X-2][Y+2]==0){
							return 1;
						} else {continue;}
					} else if (V[X-1][Y-1]!=0 && V[X-1][Y-1]!=G && V[X-1][Y-1]!=3){
						if (V[X-2][Y-2]==0){
							return 1;
						} else {continue;}
					} else if (V[X+1][Y+1]!=0 && V[X+1][Y+1]!=G && V[X+1][Y+1]!=3){
						if (V[X+2][Y+2]==0){
							return 1;
						} else {continue;}
					}
				}
			} else {
				if (G==1){
					if (V[X][Y]==G){
						
						if ((V[X+1][Y-1]!=0 && V[X+1][Y-1]!=G) && (V[X+1][Y-1]!=3 && D[X+1][Y-1]==0)){
							if (V[X+2][Y-2]==0){
								return 1;
							} else { continue;}
						} else if (V[X-1][Y-1]!=0 && V[X-1][Y-1]!=G && V[X-1][Y-1]!=3 && D[X-1][Y-1]==0){
							if (V[X-2][Y-2]==0){
								return 1;
							} else { continue;}
						}else { continue;}
					}
				} else {
					if(V[X][Y]==G){
						if (V[X-1][Y+1]!=0 && V[X-1][Y+1]!=G && V[X-1][Y+1]!=3 && D[X-1][Y+1]==0){
							if (V[X-2][Y+2]==0){
								return 1;
							} else {continue;}
						}  else if (V[X+1][Y+1]!=0 && V[X+1][Y+1]!=G && V[X+1][Y+1]!=3 && D[X+1][Y+1]==0){
							if (V[X+2][Y+2]==0){
								return 1;
							} else {continue;}
						} else {continue;}
					}
				}
			}
		}
	}
	return 0;
}
int controllo2(int G,int V[L][L],int X,int Y,int X1,int Y1,int D[L+2][L+2]){//modificare il controllo, se è un damone può tornare indietro 
	if (X1>8 || X1<1 || Y1>8 || Y1<1){
		printf("Mossa non valida0\n");
		return 1;
	} else if (damone(D,X,L-Y+1)){
		if (V[X1-1][L-Y1]==0 && ((X>=X1-2 && Y>=Y1-2)||(X>=X1+2 && Y>=Y1-2)||(X>=X1-2 && Y<=Y1+2)||(X>=X1+2 && Y<=Y1+2))){
			if ((X+2==X1 && Y+2==Y1)&&(V[X1-1][L-Y1]==0)){
				if ((V[X][L-Y-1]!=0 && V[X][L-Y-1]!=G)){
					return 0;
					
				} else {
					printf("Mossa non valida1\n");
					return 1;
				}
			} else if ((X-2==X1 && Y+2==Y1)&&(V[X1-1][L-Y1]==0)){
				if ((V[X-2][L-Y-1]!=0 && V[X-2][L-Y-1]!=G)){
					return 0;
					
				} else {
					printf("Mossa non valida1\n");
					return 1;
				}
			} else if ((X-2==X1 && Y-2==Y1)&&(V[X1-1][L-Y1]==0)){
				if ((V[X-2][L-Y+1]!=0 && V[X-2][L-Y+1]!=G)){
					return 0;
					
				} else {
					printf("Mossa non valida1\n");
					return 1;
				}
			} else if ((X+2==X1 && Y-2==Y1)&&(V[X1-1][L-Y1]==0)){
				if ((V[X][L-Y+1]!=0 && V[X][L-Y+1]!=G)){
					return 0;
					
				} else {
					printf("Mossa non valida1\n");
					return 1;
				}
			} else {
				if ((X+1==X1 && Y+1==Y1)){
					if ((V[X][L-Y-1]==0)){
						return 0;
					} else {
						printf("Mossa non valida2\n");
						return 1;
					}
				} else if (X-1==X1 && Y+1==Y1){
					if ((V[X-2][L-Y-1]==0)){
						return 0;
					} else {
						printf("Mossa non valida2-\n");
						return 1;
					}
				} else if (X-1==X1 && Y-1==Y1){
					if ((V[X-2][L-Y+1]==0)){
						return 0;
					} else {
						printf("Mossa non valida2--\n");
						return 1;
					}
				} else if (X+1==X1 && Y-1==Y1){
					if ((V[X][L-Y+1]==0)){
						return 0;
					} else {
						printf("Mossa non valida2---\n");
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
				if ((X+2==X1 && Y+2==Y1)&&(V[X1-1][L-Y1]==0)){
					if ((V[X][L-Y-1]!=0 && V[X][L-Y-1]!=G && D[X+1][L-Y]==0)){
						return 0;
					
					} else {
						printf("Mossa non valida5\n");
						return 1;
					}
				} else if ((X-2==X1 && Y+2==Y1)&&(V[X1-1][L-Y1]==0)){
					if ((V[X-2][L-Y-1]!=0 && V[X-2][L-Y-1]!=G && D[X-1][L-Y]==0)){
						return 0;
					
					} else {
						printf("Mossa non valida5-\n");
						return 1;
					}
				} else {
					if ((X+1==X1 && Y+1==Y1)){
						if (V[X][L-Y-1]==0){
							return 0;
						} else {
							printf("Mossa non valida6\n");
							return 1;
						}
					} else if (X-1==X1 && Y+1==Y1){
						if (V[X-2][L-Y-1]==0){
							return 0;
						} else {
							printf("Mossa non valida6-\n");
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
				if ((X-2==X1 && Y-2==Y1)&&(V[X1-1][L-Y1]==0)){
					if ((V[X-2][L-Y+1]!=0 && V[X-2][L-Y+1]!=G && D[X-1][L-Y+2]==0)){
						return 0;
					
					} else {
						printf("Mossa non valida9\n");
						return 1;
					}
				} else if ((X+2==X1 && Y-2==Y1)&&(V[X1-1][L-Y1]==0)){
					if ((V[X][L-Y+1]!=0 && V[X][L-Y+1]!=G && D[X+1][L-Y+2]==0)){
						return 0;
					
					} else {
						printf("Mossa non valida9-\n");
						return 1;
					}
				} else {
					if ((X+1==X1 && Y-1==Y1)){
						if (V[X][L-Y+1]==0){
							return 0;
						} else {
							printf("Mossa non valida10\n");
							return 1;
						}
					} else if(X-1==X1 && Y-1==Y1){
						if (V[X-2][L-Y+1]==0){
							return 0;
						} else {
							printf("Mossa non valida10-\n");
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

int damone(int D[L+2][L+2],int X,int Y){
	if(D[X][Y]!=0){
		return 1;
	} else { 
		return 0;
	}
}
/*#include <stdio.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

int main()
{
    printf("%sred\n", KRED);
    printf("%sgreen\n", KGRN);
    printf("%syellow\n", KYEL);
    printf("%sblue\n", KBLU);
    printf("%smagenta\n", KMAG);
    printf("%scyan\n", KCYN);
    printf("%swhite\n", KWHT);
    printf("%snormal\n", KNRM);

    return 0;
}*/

