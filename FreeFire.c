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

//-------------- FUNÇÕES ------------
void inserirItem(Item mochila[], int *total); // função para inserir os itens na mochila
void removerItem(Item mochila[], int *total); // função para remover itens da mochila
void listarItens(Item mochila[], int total); // listar os itens da mochila
void buscarItem(Item mochila[], int total); //procurar itens


//---------- função principal MAIN----------
int main() {
    Item mochila[max_itens];
    int total = 0;
    int opcao;

    do {
        printf("\n-------------------------------\n");
        printf("------------ INVENTÁRIO ----------\n");
        printf("\n--------------------------------\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - SAIR\n");
        printf("\n------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa o restante

        switch(opcao) {
            case 1: inserirItem (mochila, &total); break;
            case 2: removerItem (mochila, &total); break;
            case 3: listarItens (mochila, total); break;
            case 4: buscarItem (mochila, total); break;
            case 0: printf("Saindo...\n"); break;
           default: printf("Opcao invalida!\n");    
        }
    }while (opcao != 0);

    return 0;

}
//-----------------------------------------------
// inserir item no vetor
void inserirItem(Item mochila[], int *total) {
    if (*total >= max_itens) {
        printf("\n Mochila cheia! (max 10 itens)\n");
        return;
    }

    printf("\n--- Inserir novo item ---\n");

    printf("Nome do item: ");
    fgets(mochila[*total].nome, 30, stdin);
    mochila[*total]. nome[strcspn(mochila[*total].nome, "\n")] = '\0';

    printf("Tipo do item (arma/municao/cura): ");
    fgets(mochila[*total].tipo, 20, stdin);
    mochila[*total].tipo[strspn(mochila[*total].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);
    getchar();

    (*total)++;

    printf("\nItem cadastrado com sucesso!\n");
}
//----------------------------------------------------------
//------------------ REMOÇÃO DE ITEM -----------------------
void removerItem(Item mochila[], int *total) {
    char nomeBuscado[30];
    int i, j;

    // verificando se a mochila está vazia
    if(*total == 0) {
        printf("\nMochila VAZIA!\n");
        return;
    }

    printf("\n--- Remover item ---\n");
    printf("Digite o nome do item a remover: ");

    fgets(nomeBuscado, 30, stdin);
    nomeBuscado[strcspn(nomeBuscado, "\n")] = '\0';

    for (i = 0; i < *total; i++) {
        if(strcmp(mochila[i].nome, nomeBuscado) == 0) {

            //deslocamento de itens para esquerda
            for (j =i; j < *total -1; j++) {
                mochila[j] = mochila[j+1];
            }
            (*total)--;

            printf("Item '%s' removido com sucesso! \n", nomeBuscado);
            return;
        }
    }

    printf("Item não encontrado!\n");
}
//----------------------------------------------------------------------
//---------------------------- LISTAGEM DOS ITENS ----------------------
void listarItens(Item mochila[], int total) {
    int i;

    printf("\n--- Itens na mochila ---\n");

    //verificando se algum item foi registrado
    if (total == 0) {
        printf("Nenhum item registrado.\n");
        return;
    }

    for (i = 0; i < total; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("Nome: %s\n",mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade %d\n", mochila[i].quantidade);        
    }
}
//--------------------------------------------------------------------
//-------------------BUSCA SEQUENCIAL PELO NOME ----------------------
void buscarItem(Item mochila[], int total) {
    char nomeBuscado[30];
    int i;

    printf("\n--- Buscar item ---\n");
    printf("Nome do item: ");
    fgets(nomeBuscado, 30, stdin);
    nomeBuscado[strcspn(nomeBuscado, "\n")] = '\0';

    for (i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBuscado) == 0){
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }
    printf("Item nao encontrado!\n");
}