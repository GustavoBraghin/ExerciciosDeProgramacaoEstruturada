#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Gustavo da Silva Braghin
//uc19201375

struct tAluno {
	int matricula;
	char nome[30];
	float nota;
};

struct tNo {
	struct tAluno dado;
	struct tNo *prox, *ant;
};

struct tDescritor {
	struct tNo *last;
};
//*** MENU *******************************************************
int menu(void) {
    int op;
    printf("\n\n*** MENU ***\n\n");
    printf("1. Inclusao\n");
    printf("2. Consulta\n");
    printf("3. Listagem\n");
    printf("4. Alteracao\n");
    printf("5. Exclusao\n");
    printf("0. Sair\n\n");
    printf("Escolha sua opcao: ");
    scanf("%d", &op);
    return op;
}

//*** INICIALIZAR ************************************************
void inicializar(struct tDescritor *lst){
	(*lst).last = NULL;
}

//*** INCLUIR ****************************************************
void incluir(struct tDescritor *lst, struct tNo *novo){
	
	struct tNo *p = (*lst).last;
	
	if(p == NULL){ //Lista vazia
		
		(*lst).last = novo;
		novo->prox = NULL;
		novo->ant = NULL;	
	}
	else{ //Inicio, meio, fim
		novo->prox = NULL;
		novo->ant = (*lst).last;
		(*lst).last = novo;
	}
}

//*** CONSULTAR ****************************************************
void consultar(struct tDescritor lst, int codigo){
	
	struct tNo *p = (lst).last;
	
	while(p!=NULL){
		
		if(p->dado.matricula == codigo){
			printf("%d - %s - %.2f\n", p->dado.matricula, p->dado.nome, p->dado.nota);
			return;
		}
		
		p = p->ant;
	}
	
	printf("Codigo nao encontrado!\n");	
}

//*** LISTAR ****************************************************
void listar(struct tDescritor lst){
	
	struct tNo *p = (lst).last;
	
	while (p != NULL) {
		printf("%d - %s - %.2f\n", p->dado.matricula, p->dado.nome, p->dado.nota);
		p = p->ant;
	}
	
}

//*** ALTERAR ****************************************************
void alterar(struct tDescritor *lst, int codigo){
	
	struct tNo *p = (*lst).last;
	
	while(p != NULL){
		
		if(p->dado.matricula == codigo){
			
			printf("Digite nova descricao: ");
			fflush(stdin);
			gets(p->dado.nome);
			
			printf("\nDescricao alterada com sucesso\n");
			return;
		}
		
		p = p->ant;
	}
	
	printf("Codigo nao encontrado!\n");	
}
/*
//*** EXCLUIR **********************************************
void excluir(struct tDescritor *lst, int codigo){

	struct tNo *p = (*lst).last, *vitima=NULL;
		
	//lista vazia
	if(p == NULL){
		printf("Lista vazia!\n");
		return;
	}
	
	//achar vítima
	while(p != NULL){
		
		if(p->dado.matricula == codigo){
			vitima = p;
		}
		
		p = p->ant;
	}
	
	//Codigo não encontrado
	if(vitima == NULL){
		printf("codigo nao encontrado!\n");
		return;
	}
	
	if(((*lst).ini == vitima) && (vitima->prox == NULL)){ 	//Unico
		(*lst).ini = NULL;
		(*lst).fim = NULL;
		(*lst).qtd = 0;
	}else{
		
		if((*lst).ini == vitima){ //primeiro
			(*lst).ini = vitima->prox;
			(*lst).ini->ant = NULL;
			
		}else{
			
			if((*lst).fim == vitima){ //Ultimo
				(*lst).fim = vitima->ant;
				(*lst).fim->prox = NULL;
				
			}else{ //MEIO
			
				vitima->ant = vitima->prox;
				vitima->prox = vitima->ant;				
			}
			
		}
		(*lst).qtd--;
	}
	free(vitima);
	printf("Excluido com sucesso!\n");	
}*/
/*
//*** DESTRUIR ****************************************************
void destruir(struct tDescritor *lst){
	
	struct tNo *p;
	
	while (lst->ini != NULL) {
		p = lst->ini;
		lst->ini = lst->ini->prox;
		free(p);
	}	
}
*/

//int qtdAlunosAcimaMedia

main(){
	
	struct tDescritor lista;
	struct tNo *p;
	int opcao, matAluno;
	
	inicializar(&lista);
		
	do{
		
		opcao = menu();
		
		switch (opcao){
			
			case 1:				
				printf("\n\n*** Inclusao ***\n\n");
                p = malloc(sizeof(struct tNo)); // Criar um no
                printf("Digite a matricula...: ");
                scanf("%d", &(p->dado.matricula));
                printf("Digite a nota...: ");
                scanf("%f", &(p->dado.nota));
                printf("Digite o nome: ");
                fflush(stdin);
                gets(p->dado.nome);
                incluir(&lista, p); // Incluir o no com produto criado na lista
	            break;
	            
	        case 2:
	        	printf("\n\n*** Consulta ***\n\n");
                printf("Digite a matricula: ");
                scanf("%d", &matAluno);
                // Pesquisar um produto com este codigo
                consultar(lista,matAluno);
	            break;                
	            
	        case 3:
	        	printf("\n\n*** Listagem ***\n\n");
                listar(lista); // Listar (mostrar na tela) todos os produtos
	            break;
	            
	        case 4:
	        	printf("\n\n*** Alteracao ***\n\n");
                // Consultar pelo codigo e, caso encontre, permitir
                printf("Digite a matricula: ");
                scanf("%d", &matAluno);
				// alterar apenas a descricao.
				// Nao a codigo, pois é chave!
				alterar(&lista,matAluno);
	            break;
	            
	        case 5:
	        	printf("\n\n*** Exclusao ***\n\n");
                // Consultar pelo codigo e, caso encontre, excluir o no da lista.
                //printf("Digite a matricula: ");
               // scanf("%d", &matAluno);
                
                //excluir(&lista,matAluno);                    
	            break;
		}
		
		printf("\n");
		system("pause");
		system("cls");
		
	}while(opcao != 0);
	
	//destruir(&lista);	
}




