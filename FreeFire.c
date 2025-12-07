//Bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Código da Ilha – TORRE DE FUGA (desafio MESTRE)
#define max_componentes 20

// struct dos itens
typedef struct {
    char nome[30]; // nome do componente
    char tipo[20]; // tipo do componente
    int prioridade; // prioridade em números do componente
} COMPONENTE;

//--------------------------------------------------
//--------------- CONTADORES -----------------------
int compComparacoes = 0; // conta as comparações nos algoritmos de ordenação

//-------------------------------------------------
//-----------------FUNÇÕES VETOR ------------------
void inserirComponente(COMPONENTE torre[], int *total);
void removerComponente(COMPONENTE torre[], int *total);
void listarComponentes(COMPONENTE torre[], int total);
void bubbleSortNome(COMPONENTE torre[], int total);
void insertionSortTipo(COMPONENTE torre[], int total);
void selectionSortPrioridade(COMPONENTE torre[], int total);
void buscaBinariaPorNome(COMPONENTE torre[], int total, char chave[]);

//---------------------------------------------------------
//-------------------------MENU----------------------------
void menuTorre();

//----------------------------------------------------------
//---------- FUNÇÃO PRINCIPAL MAIN--------------------------
int main() {
    menuTorre(); // Inicia o sistema
    return 0;
}
//----------------------------------------------------------
//--------------------- MENU PRINCIPAL --------------------
void menuTorre() {
    COMPONENTE torre[max_componentes]; //vetor principal que guarda os componentes
    int total = 0; // quantidade inicial/atual de componentes
    int op; //opção do menu que será escolhida

    do { //exibe o menu abaixo
        printf("\n--- SISTEMA TORRE DE FUGA ---\n");
        printf("1 - Inserir componente\n");
        printf("2 - Remover componente\n");
        printf("3 - Listar componentes\n");
        printf("4 - Ordenar por NOME (Bubble Sort)\n");
        printf("5 - Ordenar por TIPO (Insertion Sort)\n");
        printf("6 - Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("7 - Busca binária por NOME\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &op);
        getchar();

         switch(op){
            case 1: inserirComponente(torre, &total); break; // caso queira inserir componentes
            case 2: removerComponente(torre, &total); break; // caso queira remover componentes
            case 3: listarComponentes(torre, total); break; // caso queira listar os componentes inseridos
            case 4: bubbleSortNome(torre, total); listarComponentes(torre, total); break; //colocar em ordem tipo bubble sort
            case 5: insertionSortTipo(torre, total); listarComponentes(torre, total); break; // inserir com o inserction sort
            case 6: selectionSortPrioridade(torre, total); listarComponentes(torre, total); break; // selecionar os item como prioridade com o selection sort
            case 7: {
                char chave[30];
                printf("Digite o nome do componente-chave: ");
                fgets(chave, 30, stdin);
                chave[strcspn(chave, "\n")] = '\0';
                buscaBinariaPorNome(torre, total, chave);
                break; //busca binária só funciona se o vetor já tiver sido ordenado por NOME 
            }
        }
    } while(op != 0);

}

//---------------------------------------------------------
//----------------------FUNÇÕES----------------------------
//-------------------INSERIR COMPONENTE------------------
void inserirComponente(COMPONENTE torre[], int *total) {
    if(*total >= max_componentes) {
        printf("Limite de componentes atingido!\n");
        return;
    }
    //lê o nome
    printf("Nome do Componente: ");
    fgets(torre[*total].nome, 30, stdin);
    torre[*total].nome[strcspn(torre[*total].nome, "\n")] = '\0';

    //lê o tipo
    printf("Tipo do componente: ");
    fgets(torre[*total].tipo, 20, stdin);
    torre[*total].tipo[strcspn(torre[*total].tipo, "\n")] = '\0';

    //lê a prioridade em forma de número
    printf("Prioridade (1 a 10): ");
    scanf("%d", &torre[*total].prioridade);
    getchar();

    (*total)++; // incrementa a quantidade total de componentes
}

//----------------------------------------------------------
//---------------REMOVER COMPONENTE--------------------------
void removerComponente(COMPONENTE torre[], int *total) {
    //verifica se há componentes para remover
    if(*total == 0) {
        printf("Nenhum componente para remover.\n");
        return;
    }
    char nome[30];
    printf("Nome do componente a remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    //procura o componente pelo nome
    for(int i = 0; i <*total; i++) {
        //se encontrar  o componente por nome
        if(strcmp(torre[i].nome, nome)==0){
            //desloca todos os elementos para trás
            for(int j=i; j<*total-1; j++) {
                torre[j] = torre[j+1];
            }
            (*total)--; // diminui a quantidade total
            printf("Componente removido.\n");
            return;
        }
    }
    //se chegar aqui, não encontrou nada
    printf("Componente não encontrado.\n");
}

//----------------- LISTAR COMPONENTES ------------------------
void listarComponentes(COMPONENTE torre[], int total) {
    //verifica se está vazio e avisa
    if(total==0) {
        printf("Nenhum componente cadastrado!\n");
        return;
    }
    
    //listagem de todos os itens
    printf("\n--- COMPONENTES ---\n");
    for(int i=0; i < total; i++) {
        printf("Nome: %s | Tipo: %s | Prioridade: %d\n", torre[i].nome, torre[i].tipo, torre[i].prioridade);
    }
}

//------------------ ORDENAÇÕES -------------------------------
//------------------ BUBBLE SORT NOME -------------------------
void bubbleSortNome(COMPONENTE torre[], int total) {
    compComparacoes = 0; // zera contador de comparaçoes
    clock_t inicio = clock(); // inicio do tempo

    //Bubble Sort tradicional
    for(int i = 0; i < total-1; i++){
        for(int j=0; j<total-1-i; j++){
            compComparacoes++;

          
            if(strcmp(torre[j].nome, torre[j+1].nome)>0){   //compara por nome
               
                //troca os elementos
                COMPONENTE temp = torre[j]; 
                torre[j] = torre[j+1];
                torre[j+1] = temp;
            }
        }
    }

    clock_t fim = clock(); // fim do bubble sort
    printf("Bubble Sort por NOME concluído. Comparações: %d | Tempo: %.5f s\n", 
    compComparacoes, (double)(fim-inicio)/CLOCKS_PER_SEC);
}

//------------------ INSERTION SORT TIPO -----------------------
void insertionSortTipo(COMPONENTE torre[], int total) {
    compComparacoes = 0;
    clock_t inicio = clock();

    //insertion sort tradicional
    for(int i =1; i < total; i++) {
        COMPONENTE chave = torre[i];
        int j = i-1;

        //move itens maiores para a direita
        while(j >= 0){
            compComparacoes++;

            if(strcmp(torre[j].tipo, chave.tipo)>0) { //compara por tipo(chave)
                torre[j+1] = torre[j];
                j--;
            } else break;
        }

        torre[j+1] = chave; // coloca a chave na posição correta
    }
    clock_t fim = clock(); // fim do insertion Sort
    printf("Insertion Sort por TIPO concluído! Comparações: %d | Tempo: %.5f s\n",
        compComparacoes, (double)(fim-inicio)/CLOCKS_PER_SEC);
}

//-------------------------------------------------------------------
//--------------------- SELECTION SORT PRIORIDADE -------------------
void selectionSortPrioridade(COMPONENTE torre[], int total) {
    compComparacoes = 0;
    clock_t inicio = clock();

    //selection sort tradicional
    for(int i = 0; i < total-1; i++){
        int min = i;  //índice do menor elemento

        //Procura o menor elemento no resto do vetor
        for(int j=i+1; j< total; j++) {
            compComparacoes++;

            if(torre[j].prioridade < torre[min].prioridade)
            min = j;
        }
        //se encontrou menor, troca
        if(min != i) {
            COMPONENTE temp = torre[i];
            torre[i] = torre[min];
            torre[min] = temp;
        }
    }
     clock_t fim = clock(); //fim do selection sort
    printf("Selection Sort por PRIORIDADE concluído. Comparações: %d | Tempo: %.5f s\n",
           compComparacoes, (double)(fim-inicio)/CLOCKS_PER_SEC);
}

//------------------------------------------------------------------
//------------------------- BUSCA BINARIA --------------------------
void buscaBinariaPorNome(COMPONENTE torre[], int total, char chave[]){
    int inicio = 0, fim = total-1, meio;
    int comparacoes = 0;

    while(inicio <= fim) { // enquanto houver intervalo de busca
        meio = (inicio + fim)/2; // calcula o meio
        comparacoes++;

        int cmp = strcmp(chave, torre[meio].nome);

        //se Achou imprima...
        if(cmp==0){
            printf("Componente encontrado! Nome: %s | Tipo: %s | Prioridade %d | comparações: %d\n",
                torre[meio].nome, torre[meio].tipo, torre[meio].prioridade, comparacoes);
            return;
        }
    
        else if (cmp >0) inicio = meio+1;     //chave está  depois do meio
        else fim = meio-1; //chave está antes do meio
    } 
    // se não achou imprima...
    printf("Componente não encontrado. Comparações: %d\n", comparacoes);
}


