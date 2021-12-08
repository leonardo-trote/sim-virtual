/*
Leonardo Trote Martins				1620572		
Ricardo Matheus de Oliveira Amaral		1621644	
*/

#include <stdio.h>
#include <stdlib.h>
#include "sim.h"

int time = 0, nPages;


void checkInput(char* alg, int pageSize, int memorySize){

    if (strcmp(alg,"NRU") != 0 && strcmp(alg,"FIFO2") != 0 && strcmp(alg,"LFU") != 0){
        printf("Algoritmo inválido. Deve ser NRU, FIFO2 ou LFU\n");
        exit(1);
    }

    if (pageSize < 8 || pageSize > 32){
        printf("Tamanho de página inválido. Deve ser um valor inteiro entre 8 e 32\n"); 
        exit(1);
    }

      if (memorySize < 1 || memorySize > 16){
        printf("Tamanho de memória inválido. Deve ser um valor inteiro entre 1 e 16");  
        exit(1);
    }
}


int * createPages(int nPages){

    int * pages = (int * )malloc(sizeof(int)*nPages);

    // - 1 | -1 | -1 | -1 |
    for (int i = 0; i < nPages; i++){
        pages[i] = -1; //inicialmente não está na memória
    }

    return pages;

}

Frame * createTable(int pageSize){

    int offset = (int)(ceil(log2(pageSize*1000)));
    int nTables = pow(2,32 - offset); 

    Frame* tbps = (Frame*) malloc(sizeof(Frame)*nTables);
    
    for(int i = 0; i < nTables; i++){

        //setando os valores padrao
        tbps[i].R = 0;
        tbps[i].M = 0;
        tbps[i].lastAcess = -1; //ainda nao foi acessada
        tbps[i].indexPage = -1; //ainda nao ta na memoria
    }

    return tbps;
}

//retorna a pagina que nao foi usada recentemente
int NRU(Frame* tablePages, int* pages, int nPages){

    int c0_index = 0, c1_index = 0, c2_index = 0, c3_index = 0;


    int *c0 = createPages(nPages); //classe 1 - não referenciada, não modificada (00)
    int * c1 = createPages(nPages); //classe 2 - não referenciada, modificada (01)
    int * c2 = createPages(nPages); //classe 3 - referenciada, não modificada (10)
    int * c3 = createPages(nPages); //classe 4 - referenciada, modificada (11)

    //preenchendo os vetores de acordo com a classe
    for (int i = 0; i < nPages; i++){
        
        int current_page = pages[i];
        
        if (tablePages[current_page].R == 0 && tablePages[current_page].M == 0){ //c0 (r = 0, m = 0)
            c0[c1_index] = i; //coloca o indice emento na lista da classe 1
            c0_index++;
           
        }

        else if (tablePages[current_page].R == 0 && tablePages[current_page].M == 1){ //c1 (r = 0, m = 1)
            c1[c1_index] = i; //coloca o indice emento na lista da classe 2
            c1_index++;
            
        }

        else if (tablePages[current_page].R == 1 && tablePages[current_page].M == 0){ //c2 (r = 1, m = 0)
            c2[c2_index] = i; //coloca o indice emento na lista da classe 2
            c2_index++;
              
        }
        else{ //c3 (r = 1, m = 1)
            c3[c3_index] = i; //coloca o indice emento na lista da classe 2
            c3_index++;  
            
        }
    
        


    
    
    
    }
    





}

int pageFIFO2(){

    
}


int pageLFU(){

    
}

