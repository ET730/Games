#include<stdio.h>
#define L 8
void campo(int X[L][L]);
int vive(int X[L][L]);
int main(){
	int table[L][L]={0};
	int i, j;
	int cont=0;
	int V1,V2,M1,M2;//Conta quante pedine ci sono ancora in gioco
	
	for(j=L-1; j>=0; j--, cont++){
		for(i=0; i<L; i++){
			if(j<3){
				if(i%2==0 && cont%2==1){
					table[i][j]=1;
				}
				else if(i%2==1 && cont%2==0){
					table[i][j]=1;
				}
				else{
					table[i][j]=0;
				}
			}else if(j>4){
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
	
	
}
void campo(int X[L][L]){
	int count=0,flag=0,cont=0;
	do{
		for (int i=L-1;i>=0;i--,cont++){
			if(flag==0){
				printf(" _____  ");
			}
			if(flag==1){
				printf("|     | ");
			}
			if(flag==2){
				printf("|%3d  | ",X[i][count/4]);
			}
			if(flag==3){
				printf("|_____| ");
			}		
		
		}
		printf("\n");
		if (flag<3){
			flag++;
		} else {
			flag=0;
		}
		count++;
	}while(count<L*4);
	
}

