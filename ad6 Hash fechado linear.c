#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Gustavo da Silva Braghin
//uc19201375

struct tabelaHash {
	int codigo; // chave de ordenação
	char descricao[30];
}hash[10];


//*** MENU *******************************************************
int menu(void) {
    int op;
    printf("\n\n*** MENU ***\n\n");
    printf("1. inserir\n");
    printf("2. excluir\n");
    printf("3. consultar\n");
    printf("4. listar\n");
    printf("0. Sair\n\n");
    printf("Escolha sua opcao: ");
    scanf("%d", &op);
    return op;
}

void inicializar(){
	int i;
	
	for(i=0; i<=10; i++){
		hash[i].codigo = -1;
	}
}

int hashIncluir(int key){
	
	if(hash[key%10].codigo<0){
		return (key%10);
	}else{
		return hashIncluir(key+1);	
	}
}

int hashExcluir(int key, int cod){
	
	if(hash[key%10].codigo == cod){
		return key%10;
	}else{
		if(hash[key%10].codigo == -1){
			return -3;
		}else{
			return hashExcluir(key+1, key);
		}
	}
}

void excluir(int key){
	
	if(key == -3){
        printf("CODIGO NAO ENCONTRADO");
	}else{
		hash[key].codigo = -2;
		strcpy(hash[key].descricao, "");
		printf("Exclusao concluida");
	}
	
}
void consulta(int key){
	
	if(key == -3){
       	printf("CODIGO NAO ENCONTRADO");
	}else{
		printf("\nPosicao: %i\n", key);
        printf("CODIGO: %i   DESCRICAO: %s\n", hash[key].codigo, hash[key].descricao);
	}
}

void listar(){
	int i;
	
	for(i=0; i<10; i++){
		
		printf("Posicao: %i\n",i);
		if(hash[i].codigo >= 0){
			printf("codigo: %i   descricao: %s\n\n", hash[i].codigo, hash[i].descricao);
		}else{
			if(hash[i].codigo == -1){
				printf("VAZIO\n\n");
			}else{
				printf("DELETADO\n\n");
			}
		}
	}
}

main(){
	
	int opcao, codigo, key;
	char descricao[30];
	
	inicializar();
	
	do{
		
		opcao = menu();
		
		switch (opcao){
			
			case 1:				
				printf("\n\n*** Inclusao ***\n\n");
                printf("Digite o codigo...: ");
                scanf("%d", &codigo);
                printf("Digite a descricao: ");
                fflush(stdin);
                gets(descricao);
                
                key = hashIncluir(codigo); //gerar key do vetor e passar os dados para o vetor
				hash[key].codigo = codigo;
				strcpy(hash[key].descricao, descricao);
				printf("Inclusao concluida\n");		
	            break;
	            
	       	case 2:
	       		printf("\n\n*** Exclusao ***\n\n");
                // Consultar pelo codigo e, caso encontre, excluir o no da lista.
                printf("Digite o codigo: ");
                scanf("%d", &codigo);
				            
                key = hashExcluir(codigo,codigo);
				excluir(key);	        	
	            break;
				   
	        case 3:
                printf("\n\n*** Consulta ***\n\n");
                printf("Digite o codigo: ");
                scanf("%d", &codigo);
                // Pesquisar um produto com este codigo
                key = hashExcluir(codigo, codigo);
                consulta(key);
	            break;
	            
	        case 4:
	        	printf("\n\n*** Listagem ***\n\n");
	        	listar();
	            break;
		}
		
		printf("\n");
		system("pause");
		system("cls");
		
	}while(opcao != 0);	
	
}
