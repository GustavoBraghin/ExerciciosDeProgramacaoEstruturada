//ATIVIDADE DOMÉSTICA 18/11
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void inicializar(int m[][4]){
	int i,j;
	
	for(i=0; i<5; i++){
		for(j=0; j<5; j++){
			m[i][j] = 0;
		}
	}
}

void apresentaN(int m[][4]){
	int i,j,x;
	printf("  ");
	for(i=0; i<5; i++){
		printf("%i ", i);
	}
	printf("\n");
	for(j=0; j<5; j++){
		printf("%i ", j);
		for(i=0; i<5; i++){
			if(m[i][j] == 1){
				printf("1 ");
			}else{
				printf("0 ");
			}
		}
	printf("\n");
	}
}


main(){
	
	int matriz[4][4];
	int i,j, z=0;
	char saida;
	
	inicializar(matriz);
	
	do{
	
		do{
			printf("Tendo os numeros de 0 a 4, digite o numero de onde a aresta sai: ");
			scanf("%i", &i);
		}while(i<0 || i>4);
		do{
			printf("Tendo os numeros de 0 a 4, digite o numero para onde a aresta chega: ");
			scanf("%i", &j);
		}while(j<0 || j>4);
		
		z++;
		matriz[i][j] = 1;
		
	}while(z<5);
	apresentaN(matriz);
}
