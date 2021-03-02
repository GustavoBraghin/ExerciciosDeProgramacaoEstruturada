#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Gustavo da Silva Braghin
//uc19201375

struct tProduto {
	int codigo; // chave de ordenação
	char descricao[30];
};

struct tNo {
	struct tProduto dado;
	struct tNo *prox;
};

struct tDescritor {
	struct tNo *ini;
	struct tNo *fim;
};

//*** MENU *******************************************************
int menu(void) {
    int op;
    printf("\n\n*** MENU ***\n\n");
    printf("1. Push\n");
    printf("2. Pop\n");
    printf("3. Listagem\n");
    printf("0. Sair\n\n");
    printf("Escolha sua opcao: ");
    scanf("%d", &op);
    return op;
}

//*** INICIALIZAR ************************************************
void inicializar(struct tDescritor *lst){
	(*lst).ini = (*lst).fim = NULL;
}

//*** Inclusao *****************************************************************
void push(struct tDescritor *lst, struct tNo *novo) {
	
	if ((*lst).ini == NULL) { // vazia/unico
		novo->prox = NULL;
		(*lst).ini = (*lst).fim = novo;
	}
	
	else { //inicio
		novo->prox = (*lst).ini;
		(*lst).ini = novo;			
	}
}

//*** LISTAR ****************************************************
void listar(struct tDescritor lst){
	
	struct tNo *p = (lst).ini;
	
	if(p == NULL){
		printf("Lista vazia!\n");
		return;
	}
	
	do{
		printf("%d - %s\n", p->dado.codigo, p->dado.descricao);
		p = p->prox;
	}while(p != NULL);
	
}

//*** EXCLUIR **********************************************
void pop(struct tDescritor *lst, int codigo){

	struct tNo *p = (*lst).ini;
		
	//lista vazia
	if(p == NULL){
		printf("Lista vazia!\n");
		return;
	}
	else{
	
		if((*lst).ini == (*lst).fim){  //Unico
		
			(*lst).ini = NULL;
			(*lst).fim = NULL;
		
		}else{//primeiro
		
			(*lst).ini = (*lst).ini->prox;					
		}
	free(p);
	printf("Excluido com sucesso!\n");	
	}
}

//*** DESTRUIR ****************************************************
void destruir(struct tDescritor *lst){
	
	struct tNo *q = (*lst).ini, *p;
	
	do{
		p = q;
		q = q->prox;
		free(p);
	}while(q != NULL);

}

main(){
	
	struct tDescritor pilha;
	struct tNo *p;
	int opcao, codigo;
	
	inicializar(&pilha);
		
	do{
		
		opcao = menu();
		
		switch (opcao){
			
			case 1:				
				 printf("\n\n*** Push (entrada) ***\n\n");
                p = (struct tNo *)malloc(sizeof(struct tNo)); // Criar um no
                printf("Digite o codigo...: ");
                scanf("%d", &(p->dado.codigo));
                printf("Digite a descricao: ");
                fflush(stdin);
                gets(p->dado.descricao);
                push(&pilha, p);
                break;
	            
	       	case 2:
	        	printf("\n\n*** Exclusao - Pop ***\n\n");
                //Excluir primeiro da lista.
                pop(&pilha,codigo);                    
	            break;               
	            
	        case 3:
	        	printf("\n\n*** Listagem ***\n\n");
                listar(pilha); // Listar (mostrar na tela) todos os produtos
	            break;	        	
		}
		
		printf("\n");
		system("pause");
		system("cls");
		
	}while(opcao != 0);
	
	destruir(&pilha);	
}
