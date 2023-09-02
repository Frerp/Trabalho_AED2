#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Definição das Structs usadas no programa
typedef struct{
    int id;
    int idade;
    char nome[50];
    char planeta_origem[30];
}Passageiro;

typedef struct{
    char nome[15];
    int qtd;
}Recurso;

typedef struct{
    int id;
    int prioridade;
    Passageiro passageiros[5]; //no máximo cada espaçonave possui 5 passageiros
    Recurso recursos[3]; //no máximo cada espaçonave possui 3 recursos
}Espaconave;


//Função para inserir nave na heap
void inserir(Espaconave *naves, int *pont_tamanho_heap){
    int tamanho_heap = *pont_tamanho_heap;
    printf("\n\n---------------DADOS DA NAVE %d---------------", tamanho_heap +1);
    naves[tamanho_heap].id = tamanho_heap + 1;
    printf("\nDigite a prioridade da nave: ");
    scanf("%d", &naves[tamanho_heap].prioridade);
    fflush(stdin);

    for(int j=0; j<5; j++){
        printf("\n");
        printf("Digite o id do passageiro: ");
        scanf("%d", &naves[tamanho_heap].passageiros[j].id);
        fflush(stdin);

        printf("Digite o nome do passageiro: ");
        fgets(&naves[tamanho_heap].passageiros[j].nome, 40, stdin);
        fflush(stdin);

        printf("Digite a idade do passageiro: ");
        scanf("%d", &naves[tamanho_heap].passageiros[j].idade);
        fflush(stdin);

        printf("Digite o planeta de origem do passageiro: ");
        fgets(&naves[tamanho_heap].passageiros[j].planeta_origem, 40, stdin);
        fflush(stdin);
    }

    for(int j=0; j<3; j++){
        printf("\n");
        printf("Digite o nome do recurso: ");
        fgets(&naves[tamanho_heap].recursos[j].nome, 40, stdin);
        fflush(stdin);
    }
    *pont_tamanho_heap += 1;

/*Depois de inserir a nave no final da lista, será necessário chamar subir()/descer()
para que a nova nave fique na posição correta*/
}


//Função para exibir as naves da heap
void exibir(Espaconave *naves, int tamanho_heap){
    for(int i=0; i<tamanho_heap; i++){
        printf("\n\n---------------DADOS DA NAVE %d---------------", naves[i].id);
        printf("\nId da nave: %d", naves[i].id);
        printf("\nPrioridade: %d", naves[i].prioridade);
        for(int j=0; j<5; j++){
            printf("\n\n");
            printf("Id do passageiro: %d", naves[i].passageiros[j].id);
            printf("\nNome do passageiro: %s", naves[i].passageiros[j].nome);
            printf("Idade do passageiro: %d", naves[i].passageiros[j].idade);
            printf("\nPlaneta de origem do passageiro: %s", naves[i].passageiros[j].planeta_origem);
        }

        for(int j=0; j<3; j++){
            printf("\nNome do recurso: %s", naves[i].recursos[j].nome);
        }
    }
}

int main()
{
//Leitura do csv de Naves
    Espaconave *naves;
    naves = malloc(100*sizeof(Espaconave));
    int tamanho_heap = 0;
    int *pont_tamanho_heap = &tamanho_heap;
    char *nave_csv[10];
    char *ptr;
    FILE *fptr;
    fptr = fopen("Dados_naves.csv", "r");
    while(EOF != fscanf(fptr, "%[^\n]\n", nave_csv)){
        ptr = strtok(nave_csv, ",");
        int contador_2 = 0;
        while( ptr != NULL){
            if (contador_2 == 0){
                naves[tamanho_heap].id = atoi(ptr);
            }else if (contador_2 == 1){
                naves[tamanho_heap].prioridade = atoi(ptr);
            }
            ptr = strtok(NULL, ",");
            contador_2++;
        }
        tamanho_heap++;
    }
    fclose(fptr);

    inserir(naves, pont_tamanho_heap);
    exibir(naves, tamanho_heap);
    free(naves);
    naves = NULL;
}
