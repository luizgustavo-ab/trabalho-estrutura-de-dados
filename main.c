#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

//integrantes do grupo:
//luiz gustavo alves barros - uc24100270
//tiago silva coutinho - UC24101549
//nicolas oliveira de freitas 
//william de jesus

int main() {
    Processo processos[MAX];
    int totalProcessos = lerprocessos(processos, MAX);

    contarclasses(processos, totalProcessos);
    int totalassuntos = contarassuntos(processos, totalProcessos);
    calctramitacao(processos, totalProcessos);

    ordenarid(processos, totalProcessos);
    novoarquivoid(processos, totalProcessos);

    ordenardata(processos, totalProcessos);
    novoarquivodata(processos, totalProcessos);

    return 0;
}

