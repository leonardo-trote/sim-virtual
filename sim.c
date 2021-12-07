/*
Leonardo Trote Martins				1620572		
Ricardo Matheus de Oliveira Amaral		1621644	
*/

#include <stdio.h>
#include <stdlib.h>
#include "sim.h"

int time, nPages;


void checkInput(char* alg, int pageSize, int memorySize){

    if (alg != "NRU" && alg != "FIFO2" && alg != "LFU"){
        printf("Algoritmo inválido");
        exit(1);
    }

    if (pageSize < 8 || pageSize > 32){
        printf("Tamanho de página inválido"); 
        exit(1);
    }

      if (memorySize < 1 || memorySize > 16){
        printf("Tamanho de memória inválido");  
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

pageTable* createTablePages(int pageSize){


    int nTables = pow(2,33); //corrigir valor (n entendi)

    pageTable* tbps = (pageTable*) malloc(sizeof(pageTable)*nTables);
    
    for(int i = 0; i < nTables; i++){

        //setando os valores padrao
        tbps[i].R = 0;
        tbps[i].R = 0;
        tbps[i].lastAcess = -1; //ainda nao foi acessada
        tbps[i].indexPage = -1; //ainda nao ta na memoria
    }

    return tbps;
}


void deletePage(pageTable* tablePages, int* pages, indexPage, indexTable){

    


}



int pageNRU(pageTable* tablePages, int* pages, int nPages){

    int c1_index = 0; 
    int c2_index = 0;
    int c3_index = 0;
    int c4_index = 0;


    int c1 = createTablePages(nPages); //classe 1 - não referenciada, não modificada
    int c2 = createTablePages(nPages); //classe 2 - não referenciada, modificada
    int c3 = createTablePages(nPages); //classe 3 - referenciada, não modificada
    int c4 = createTablePages(nPages); //classe 4 - referenciada, modificada

    for (int i = 0; i < nPages; i++){
        
        int current_page = pages[i];
        
        if (tablePages[current_page].R == 0 && tablePages[current_page].M == 0){ //c1 (r = 0, m = 0)
            c1[c1_index] = i;
            c1_index++;
        }

        else if (tablePages[current_page].R == 0 && tablePages[current_page].M == 1){ //c1 (r = 0, m = 1)
            c2[c2_index] = i;
            c2_index++;
        }

        else if (tablePages[current_page].R == 1 && tablePages[current_page].M == 0){ //c1 (r = 1, m = 0)
            c3[c3_index] = i;
            c3_index++;   
        }

        else{ //c1 (r = 1, m = 1)
            c4[c4_index] = i;
            c4_index++;
        }
    }
    
    //o que vem depois eu nao entendi direito




    //aqui tem que fazer a remoção 

}

int pageFIFO2(){

    
}


int pageLFU(){

    
}

