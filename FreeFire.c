//Bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
#define max_itens 10

// struct dos itens
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
}Item;

//-------------------------------------------------
//------------- LISTA ENCADEADA --------------------
typedef struct No {
    Item dados;
    struct No *proximo;
    } No;
    
//----------------------------------------------------
//-------------------CONTADORES----------------------
int compSequencial = 0;
int compBinario = 0;

//--------------------------------------------------
//-------------- FUNÇÕES VETOR ---------------------
void inserirItemVetor(Item mochila[], int *total); // função para inserir os itens na mochila
void removerItemVetor(Item mochila[], int *total); // função para remover itens da mochila
void listarItensVetor(Item mochila[], int total); // listar os itens da mochila
void buscarSequencialVetor(Item mochila[], int total); //procurar itens
void ordenarVetor(Item mochila[], int total); //ordenar itens
void buscarBinarioVetor(Item mochila[], int total);

//--------------------------------------------------------------
//--------------------FUNÇÕES LISTA ---------------------------
void inserirItemLista(No **lista);
void removerItemLista(No **lista);
void listarItensLista(No *lista);
void buscarSequencialLista(No *lista);

//---------------------------------------------------------
//-------------------------MENU----------------------------
void menuVetor();
void menuLista();

//----------------------------------------------------------
//---------- FUNÇÃO PRINCIPAL MAIN--------------------------
int main() {
    int escolha;

    do {
        printf("\n-------------------------------\n");
        printf("-------- SISTEMA DE MOCHILA --------\n");
        printf("--------------------------------\n");
        printf("1 - Usar mochila com VETOR\n");
        printf("2 - Usar mochila com LISTA ENCADEADA\n");
        printf("0 - SAIR\n");
        printf("\n------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        getchar(); // limpa o restante

        switch(escolha) {
            case 1: menuVetor(); break;
            case 2: menuLista(); break;
            case 0: printf("Saindo...\n"); break;
           default: printf("Opção invalida!\n");    
        }
    }while (escolha != 0);

    return 0;

}
//----------------------------------------------------------
//--------------------- MENU VETOR -------------------------
void menuVetor() {
    Item mochila[max_itens];
    int total = 0;
    int op;

    do {
        printf("\n--- MENU VETOR---\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Busca sequencial\n");
        printf("5 - Ordenar (Bubble) + Busca Binária\n");
        printf("0 - Voltar\n");
        printf("Opção: ");
        scanf("%d", &op); 
        getchar();       

        switch (op) {
            case 1: inserirItemVetor(mochila, &total); break;
            case 2: removerItemVetor(mochila, &total); break;
            case 3: listarItensVetor(mochila, total); break;
            case 4: buscarSequencialVetor(mochila, total); break;
            case 5: ordenarVetor(mochila, total);buscarBinarioVetor(mochila, total); break;
        }
    } while (op != 0);
}
//--------------------------------------------------------------------
//------------------------ MENU LISTA -----------------------------
void menuLista() {
    No *lista = NULL;
    int op;

    do {
        printf("\n--- MENU LISTA ---\n");
        printf("1 - Inserir item\n");            
        printf("2 - Remover item\n");        
        printf("3 - Listar itens\n");        
        printf("4 - Busca Sequencial\n");        
        printf("0 - VOLTAR\n");   
        printf("Opção: ");
        scanf("%d", &op);
        getchar();
        
        switch (op){
            case 1: inserirItemLista (&lista); break;
            case 2: removerItemLista(&lista); break;
            case 3: listarItensLista(lista); break;
            case 4: buscarSequencialLista(lista); break;
        }
    } while (op != 0);
    
}
//-----------------------------------------------------------------
//---------------------- FUNÇÕES VETOR ---------------------------
void inserirItemVetor(Item mochila[], int *total) {
    if (*total >= max_itens) {
        printf("\n Mochila cheia!\n");
        return;
    }

    int c;
    ((c = getchar()) != '\n' && c != EOF); //limpa buffer

    printf("Nome do item: ");
    fgets(mochila[*total].nome, 30, stdin);
    mochila[*total].nome[strcspn(mochila[*total].nome, "\n")] = '\0';

    printf("Tipo do item: ");
    fgets(mochila[*total].tipo, 20, stdin);
    mochila[*total].tipo[strcspn(mochila[*total].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);
    getchar();

    (*total)++;
}

void removerItemVetor(Item mochila[], int *total) {
    if(*total == 0) {
        printf("\nMochila VAZIA!\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item a remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *total; i++) {
        if(strcmp(mochila[i].nome, nome) == 0) {

            //deslocamento de itens para esquerda
            for (int j =i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;
            printf("Item removido com sucesso! \n");
            return;
        }
    }

    printf("Item não encontrado!\n");
}

void listarItensVetor(Item mochila[], int total) {
    if (total == 0) {
        printf("Vazio!\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);        
    }
}

void buscarSequencialVetor(Item mochila[], int total) {
    char nome[30];
    printf("Buscar por nome: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    compSequencial = 0;

    for (int i = 0; i < total; i++) {
        compSequencial++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\nItem encontrado! Comparações: %d\n", compSequencial);
            return;
        }
    }
    printf("Item não encontrado! Comparações: %d\n", compSequencial);

    }

    void ordenarVetor(Item mochila[], int total) {
        for (int i = 0; i < total - 1; i++) {
            for(int j = 0; j < total - 1 - i; j++) {
                if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                 Item temp = mochila[j];
                mochila[j] = mochila[j+1];
                mochila[j+1] = temp; 
                }
            }
        }
        printf("Ordenado!\n");
    }

    void buscarBinarioVetor(Item mochila[], int total) {
    char nome[30];
    printf("Nome para busca binária: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int inicio = 0, fim = total - 1;
    compBinario = 0;

    while (inicio <= fim) {
        compBinario++;
        int meio = (inicio + fim) / 2;

        int cmp = strcmp(nome, mochila[meio].nome);

        if (cmp == 0) {
            printf("Encontrado! Comparações (binário): %d\n", compBinario);
            return;
        }
        else if (cmp > 0) 
            inicio = meio + 1;
        else
            fim = meio - 1;
         
    }

    printf("Não encontrado! Comparações (binário): %d\n", compBinario);
}

// ------------------------------------------------------------
// -------------------- FUNÇÕES LISTA -----------------------------

void inserirItemLista(No **lista) {
    No *novo = malloc(sizeof(No));

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Nome: ");
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();

    novo->proximo = *lista;
    *lista = novo;
}

void removerItemLista(No **lista) {
    if (*lista == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    char nome[30];
    printf("Nome para remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No *atual = *lista;
    No *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL)
                *lista = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            free(atual);
            printf("Removido!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Item não encontrado!\n");
}

void listarItensLista(No *lista) {
    if (lista == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    No *aux = lista;
    while (aux != NULL) {
        printf("\nNome: %s\n", aux->dados.nome);
        printf("Tipo: %s\n", aux->dados.tipo);
        printf("Quantidade: %d\n", aux->dados.quantidade);
        aux = aux->proximo;
    }
}

void buscarSequencialLista(No *lista) {
    char nome[30];
    printf("Nome para buscar: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    compSequencial = 0;

    No *aux = lista;

    while (aux != NULL) {
        compSequencial++;
        if (strcmp(aux->dados.nome, nome) == 0) {
            printf("Encontrado! Comparações: %d\n", compSequencial);
            return;
        }
        aux = aux->proximo;
    }

    printf("Não encontrado! Comparações: %d\n", compSequencial);
}
