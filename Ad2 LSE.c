
// Sintese
//   objetivo "LSE - Lista Simplesmente Encadeada"
//   autor "Edson F. da Fonseca"
//   data "24/03/2020"

//Aluno: Gustavo da Silva Braghin
//Matrícula: UC19201375

#include <stdio.h>
#include <stdlib.h>

//*** Declaracoes de tipos *****************************************************
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
	int qtd;
	struct tNo *fim;
};

//*** Prototipos de funcoes ****************************************************
int menu(void);
void inicializar(struct tDescritor *);
void incluir(struct tDescritor *, struct tNo *);
void consultar(struct tDescritor, int codigo);
void listar(struct tDescritor);
void alterar(struct tDescritor *, int codigo);
void excluir(struct tDescritor *, int codigo);
void destruir(struct tDescritor *);


//*** Bloco Principal **********************************************************
int main(void) {
	struct tDescritor lista;
	struct tNo *p;
	int opcao, codigo;
	
	inicializar(&lista);
	
	do {
		
        opcao = menu();
        
        switch (opcao) {
        	
               case 1: 
                    printf("\n\n*** Inclusao ***\n\n");
                    p = malloc(sizeof(struct tNo)); // Criar um no
                    printf("Digite o codigo...: ");
                    scanf("%d", &(p->dado.codigo));
                    printf("Digite a descricao: ");
                    fflush(stdin);
                    gets(p->dado.descricao);
                    incluir(&lista, p); // Incluir o no com produto criado na lista
	                break;
	           
			    case 2: 
                    printf("\n\n*** Consulta ***\n\n");
                    printf("Digite o codigo: ");
                    scanf("%d", &codigo);
                    // Pesquisar um produto com este codigo
                    consultar(lista,codigo);
	                break;                
	                
               case 3: 
                    printf("\n\n*** Listagem ***\n\n");
                    listar(lista); // Listar (mostrar na tela) todos os produtos
	                break;
	                
               case 4: 
                    printf("\n\n*** Alteracao ***\n\n");
                    // Consultar pelo codigo e, caso encontre, permitir
                    printf("Digite o codigo: ");
                    scanf("%d", &codigo);
					// alterar apenas a descricao.
					// Nao a codigo, pois é chave!
					alterar(&lista,codigo);
	                break;
	                
               case 5: 
                    printf("\n\n*** Exclusao ***\n\n");
                    // Consultar pelo codigo e, caso encontre, excluir o no da lista.
                    printf("Digite o codigo: ");
                    scanf("%d", &codigo);
                    
                    excluir(&lista,codigo);                    
	                break;
        }
        
        printf("\n");
        system("pause");
        system("cls");
        
    } while (opcao != 0);
    
    destruir(&lista);
    
	return 0;
}

//*** Inicialização ************************************************************
void inicializar(struct tDescritor *lst) {
	(*lst).ini = NULL;
	(*lst).fim = NULL;
	(*lst).qtd = 0;
}

//*** Menu *********************************************************************
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

//*** Incluir ******************************************************************
void incluir(struct tDescritor *lst, struct tNo *novo) {
	
	struct tNo *p = (*lst).ini, *q;
	
	if ((*lst).ini == NULL) { // Lista vazia
		novo->prox = NULL;
		(*lst).ini = novo;
		(*lst).fim = novo;
		(*lst).qtd++;
	}
	else { // inicio, fim ou meio
		if (novo->dado.codigo < (*lst).ini->dado.codigo) { // inicio
			novo->prox = (*lst).ini;
			(*lst).ini = novo;
			(*lst).qtd++;
		}
		else { // fim ou meio
			if (novo->dado.codigo > (*lst).fim->dado.codigo) { // fim
				(*lst).fim->prox = novo;
				(*lst).fim = novo;
				novo->prox = NULL;
				(*lst).qtd++;
			}
			else { // meio
				while (p->dado.codigo < novo->dado.codigo) {
					q = p;
					p = p->prox;
				}
				q->prox = novo;
				novo->prox = p;
			}
		}
	}
	
}

//*** Consulta *****************************************************************
void consultar(struct tDescritor lst, int codigo) {
	
	struct tNo *p = lst.ini;
	int controle=0;
	
	while(p != NULL){
		
		if(p->dado.codigo == codigo){
			
			printf("%d - %s\n", p->dado.codigo, p->dado.descricao);
			controle=1;
		}
		
		p = p->prox;		
	}
	
	if(controle != 1){
		printf("Codigo nao encontrado!\n");
	}
}

//*** Listagem *****************************************************************
void listar(struct tDescritor lst) {
	
	struct tNo *p = (lst).ini;
	
	while (p != NULL) {
		printf("%d - %s\n", p->dado.codigo, p->dado.descricao);
		p = p->prox;
	}
}

//*** Alteração *****************************************************************
void alterar(struct tDescritor *lst, int codigo){
	
	struct tNo *p = (*lst).ini;
	int controle=0;
	
	while(p != NULL){
		
		if(p->dado.codigo == codigo){
			
			printf("Digite a nova descricao: ");
			fflush(stdin);
			gets(p->dado.descricao);
			
			printf("\nDescricao alterada com sucesso\n");
			controle=1;
		}
		
		p = p->prox;		
	}
	
	if(controle != 1){
		printf("Codigo nao encontrado!\n");
	}
	
}

//*** Exclusão ******************************************************************
void excluir(struct tDescritor *lst, int codigo) {
		
	struct tNo *p = (*lst).ini, *vitima=NULL;
	
	//Achar vítima
	while(p != NULL){
		
		if(p->dado.codigo == codigo){
			vitima = p;
		}
		
		p = p->prox;
				
	}
	
	//Lista vazia
	if ((*lst).ini == NULL){
		printf("Lista Vazia\n");
		return;
	}
	
	if(vitima==NULL){
		printf("Codigo nao encontrado!\n");
		return;
	}	
		
	if (((*lst).ini == vitima) && (vitima->prox == NULL)){ // unico
		(*lst).ini = NULL;
		(*lst).fim = NULL;
		(*lst).qtd = 0;			
	}else{ // primeiro, ultimo, meio
		
		if((*lst).ini == vitima){ // primeiro
			(*lst).ini = vitima->prox;
			(*lst).qtd--;	
						
		}else{ // ultimo, meio
				
			p = (*lst).ini;
			while(p->prox != vitima){ // p no anterior ao vitima
				p = p->prox;
			}
				
			if(vitima->prox == NULL){ // ultimo
				p->prox = vitima->prox;
				(*lst).fim = p;
				(*lst).qtd--;
					
			}else{ // meio
				p->prox = vitima->prox;
				(*lst).qtd--;				
			}
		}
	}
	
	free(vitima);
	printf("Excluido com sucesso!\n");	
}	

//*** destruir lista ************************************************************
void destruir(struct tDescritor *lst){
	
	struct tNo *p;
	
	while (lst->ini != NULL) {
		p = lst->ini;
		lst->ini = lst->ini->prox;
		free(p);
	}	
}
	
//*** FIM **********************************************************************
