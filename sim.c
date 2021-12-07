/*
Leonardo Trote Martins				1620572		
Ricardo Matheus de Oliveira Amaral		1621644	
*/

#include <stdio.h>
#include <stdlib.h>
#include "sim.h"

int time, nPages;


void checkInput(char* alg, int pageSize, int memSize){

    if (alg != "NRU" && alg != "FIFO2" && alg != "LFU"){
        printf("Entrada inválida");
        exit(1);
    }

    if (pageSize < 8 || pageSize > 32){
        printf("Tamanho inválido"); 
        exit(1);
    }

      if (memSize < 1 || memSize > 16){
        printf("Tamanho inválido");  
        exit(1);
    }
}


int * createPagesArray(int nPages){

    int * pages = (int * )malloc(sizeof(int)*nPages);

    for (int i = 0; i < nPages; i++){
        pages[i] = -1; //inicialmente não está na memória
    }

    return pages;

}

Info* createTablePages(int sizePage){


    int nTables = pow(2,33); //corrigir valor (n entendi)

    Info* tablePages = (Info*) malloc(sizeof(Info)*nTables);
    
    for(int i = 0; i < nTables; i++){

        //setando os valores padrao
        tablePages[i].R = 0;
        tablePages[i].R = 0;
        tablePages[i].lastAcess = -1; //ainda nao foi acessada
        tablePages[i].indexPage = -1; //ainda nao ta na memoria
    }

    return tablePages;
}

int pageNRU(Info* tablePages, int* pages, int nPages){

    int c1 = createTablePages(nPages); //não referenciada, não modificada
    int c2 = createTablePages(nPages); //não referenciada, modificada
    int c3 = createTablePages(nPages); //referenciada, não modificada
    int c4 = createTablePages(nPages); //referenciada, modificada


    



}

int pageFIFO2(){

    
}


int pageLFU(){

    
}

