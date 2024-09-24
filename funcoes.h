#ifndef FUNCOES_H
#define FUNCOES_H

#define MAX 18395
#define LINHA 256

typedef struct {
    char id[20];
    char numero[20];
    char dataAjuizamento[25];
    char idClasse[10];
    char idAssunto[10];
    char anoEleicao[5];
} Processo;

void removerchaves(char *str);
int lerprocessos(Processo processos[], int max);
void contarclasses(Processo processos[], int totalProcessos);
int contarassuntos(Processo processos[], int totalProcessos);
void calctramitacao(Processo processos[], int totalProcessos);
void ordenarid(Processo processos[], int totalProcessos);
void ordenardata(Processo processos[], int totalProcessos);
void novoarquivoid(Processo processos[], int totalProcessos);
void novoarquivodata(Processo processos[], int totalProcessos);

#endif

