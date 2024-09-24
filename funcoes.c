#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

void removerchaves(char *str) {
    char *inicio = strchr(str, '{');
    char *fim = strchr(str, '}');
    if (inicio && fim) {
        *fim = '\0';
        strcpy(str, inicio + 1);
    }
}

int lerprocessos(Processo processos[], int max) {
    FILE *arquivo = fopen("processo_043_202409032338.csv", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }
    char linha[LINHA];
    int i = 0;
    fgets(linha, sizeof(linha), arquivo);
    while (fgets(linha, sizeof(linha), arquivo) && i < max) {
        sscanf(linha, "%[^,],%[^,],%[^,],%[^,],%[^,],%s", processos[i].id, processos[i].numero, processos[i].dataAjuizamento, processos[i].idClasse, processos[i].idAssunto, processos[i].anoEleicao);
        removerchaves(processos[i].idClasse);
        removerchaves(processos[i].idAssunto);
        i++;
    }
    fclose(arquivo);
    return i;
}

void contarclasses(Processo processos[], int totalProcessos) {
    char idclasse[10];
    int contagem = 0;
    printf("digite o id classe que deseja contar: ");
    scanf("%s", idclasse);
    for (int i = 0; i < totalProcessos; i++) {
        if (strcmp(processos[i].idClasse, idclasse) == 0) {
            contagem++;
        }
    }
    printf("\ntotal de processos com id classe %s: %d \n", idclasse, contagem);
}

int contarassuntos(Processo processos[], int totalProcessos) {
    char idAssuntos[MAX][10];
    int contador = 0;
    for (int i = 0; i < totalProcessos; i++) {
        int existe = 0;
        for (int j = 0; j < contador; j++) {
            if (strcmp(processos[i].idAssunto, idAssuntos[j]) == 0) {
                existe = 1;
                break;
            }
        }
        if (!existe) {
            strcpy(idAssuntos[contador++], processos[i].idAssunto);
        }
    }
    printf("\nTotal de id assuntos distintos: %d \n\n", contador);
    return contador;
}

void calctramitacao(Processo processos[], int totalProcessos) {
    char idBusca[9];
    int encontrado = 0;
    printf("digite a id do processo para calcular os dias em tramitacao: ");
    scanf("%s", idBusca);
    for (int i = 0; i < totalProcessos; i++) {
        if (strcmp(processos[i].id, idBusca) == 0) {
            encontrado = 1;
            int ano, mes, dia;
            sscanf(processos[i].dataAjuizamento, "%d-%d-%d", &ano, &mes, &dia);
            struct tm tm = {0};
            tm.tm_year = ano - 1900;
            tm.tm_mon = mes - 1;
            tm.tm_mday = dia;
            time_t inicio = mktime(&tm);
            time_t agora = time(NULL);
            int diastramitacao = difftime(agora, inicio) / (60 * 60 * 24);
            printf("\nDias em tramitação do processo %s: %d \n", processos[i].id, diastramitacao);
            break;
        }
    }
    if (!encontrado) {
        printf("processo com id %s não encontrado.\n", idBusca);
    }
}

void ordenarid(Processo processos[], int totalProcessos) {
    for (int i = 0; i < totalProcessos - 1; i++) {
        for (int j = i + 1; j < totalProcessos; j++) {
            if (strcmp(processos[i].id, processos[j].id) > 0) {
                Processo temp = processos[i];
                processos[i] = processos[j];
                processos[j] = temp;
            }
        }
    }
}

void ordenardata(Processo processos[], int totalProcessos) {
    for (int i = 0; i < totalProcessos - 1; i++) {
        for (int j = i + 1; j < totalProcessos; j++) {
            if (strcmp(processos[i].dataAjuizamento, processos[j].dataAjuizamento) < 0) {
                Processo temp = processos[i];
                processos[i] = processos[j];
                processos[j] = temp;
            }
        }
    }
}

void novoarquivoid(Processo processos[], int totalProcessos) {
    FILE *arquivo = fopen("processos_ordenados_id.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo \n");
        return;
    }
    fprintf(arquivo, "id,numero,dataAjuizamento,idClasse,idAssunto,anoEleicao\n");
    for (int i = 0; i < totalProcessos; i++) {
        fprintf(arquivo, "%s,%s,%s,%s,%s,%s\n", processos[i].id, processos[i].numero, processos[i].dataAjuizamento, processos[i].idClasse, processos[i].idAssunto, processos[i].anoEleicao);
    }
    fclose(arquivo);
    printf("arquivo criado com processos ordenados por ID \n\n");
}

void novoarquivodata(Processo processos[], int totalProcessos) {
    FILE *arquivo = fopen("processos_ordenados_data.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo \n");
        return;
    }
    fprintf(arquivo, "id,numero,dataAjuizamento,idClasse,idAssunto,anoEleicao\n");
    for (int i = 0; i < totalProcessos; i++) {
        fprintf(arquivo, "%s,%s,%s,%s,%s,%s\n", processos[i].id, processos[i].numero, processos[i].dataAjuizamento, processos[i].idClasse, processos[i].idAssunto, processos[i].anoEleicao);
    }
    fclose(arquivo);
    printf("arquivo criado com processos ordenados por data \n\n");
}

