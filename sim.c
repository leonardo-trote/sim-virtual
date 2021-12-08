/*
Leonardo Trote Martins				1620572		
Ricardo Matheus de Oliveira Amaral		1621644	
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "sim.h"

#define N 32 // leituras para zerar o bit no NRU.

int t_time = 0, nPages;


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

//verifica se a lista de páginas está vazia.
int emptyPages(int *pages){
    if (pages[0] == -1){
        return 1;
    }
    return 0;
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
        tbps[i].lastLoad = -1; //tempo que foi colocado na memoria
        tbps[i].frequency = 0; //frequencia de acesso
    }

    return tbps;
}

//Retorna um index aleatorio
int indexRandom(int n){
    srand(time(NULL));
    return rand() % n;
}

//retorna o index da pagina da classe menos 'importante' de forma aleatória
int search_index_NRU(Frame* tablePages, int* pages, int nPages){

    int c0_index = 0, c1_index = 0, c2_index = 0, c3_index = 0; // tamanho dos vetores.


    int *c0 = createPages(nPages); //classe 1 - não referenciada, não modificada (00)
    int *c1 = createPages(nPages); //classe 2 - não referenciada, modificada (01)
    int *c2 = createPages(nPages); //classe 3 - referenciada, não modificada (10)
    int *c3 = createPages(nPages); //classe 4 - referenciada, modificada (11)

    //preenchendo os vetores de acordo com a classe
    for (int i = 0; i < nPages; i++){
        
        int current_page = pages[i];
        
        if (tablePages[current_page].R == 0 && tablePages[current_page].M == 0){ //c0 (r = 0, m = 0)
            c0[c1_index] = i; //coloca o indice emento na lista da classe 0
            c0_index++;
        }

        else if (tablePages[current_page].R == 0 && tablePages[current_page].M == 1){ //c1 (r = 0, m = 1)
            c1[c1_index] = i; //coloca o indice emento na lista da classe 1
            c1_index++;
        }

        else if (tablePages[current_page].R == 1 && tablePages[current_page].M == 0){ //c2 (r = 1, m = 0)
            c2[c2_index] = i; //coloca o indice emento na lista da classe 2
            c2_index++;
        }

        else{ //c3 (r = 1, m = 1)
            c3[c3_index] = i; //coloca o indice emento na lista da classe 3
            c3_index++;  
        }
    }

    //Escolhendo a categoria da página que vai ser retirada
    int *vet;
    int size_index;
    if (!emptyPages(c0)){
        vet = c0;
        size_index = c0_index;
    }
    else if (!emptyPages(c1)){
        vet = c1;
        size_index = c0_index;
    }
    else if (!emptyPages(c2)){
        vet = c2;
        size_index = c2_index;
    }
    else{
        vet = c3;
        size_index = c3_index;
    }
    //A página que vai ser retirada.
    int pos;
    pos = indexRandom(size_index);
    return vet[pos];
}

int pageFIFO2(Frame* tablePages, int* pages, int nPages){

    //o bit R do primeiro (mais antigo) indice da lista é 0, entao remove esse mesmo
    if (tablePages[pages[0]].R == 0){
        return 0; //esse é o indice da pagina que vai ser removid0
    }    

    //se for 1, então limpa e coloca no final
    for (int i = 0; i< nPages; i++){

        int current_page = pages[i];
        if (tablePages[current_page].R == 1){


        }



    }
}







int pageLFU(Frame* tablePages, int* pages, int nPages){

    int smallerFrequency = -1;
    int smallerIndex = 0;

    //percote todas as paginas e retorna o index da que tem menor frequencia
    for(int i = 0; i < nPages; i++){
        
        int current_page = pages[i];

        if (tablePages[current_page].frequency < smallerFrequency){

            smallerFrequency = tablePages[current_page].frequency;
            smallerIndex = i;
        }
    }
    return smallerIndex;
}

void reset_bits(Frame* tablePages, int * pages, int nPages){
    int index_TPage;
    for (int i = 0; i < nPages; i++){
        index_TPage = pages[i];
        if (index_TPage != -1){
            tablePages[index_TPage].R = 0;
        }
    }
}
void remove_page(Frame* tablePages, int * pages, int index_Tpage, int index_Vpage){
    tablePages[pages[index_Vpage]].R = 0;
    tablePages[pages[index_Vpage]].M = 0;
    tablePages[pages[index_Vpage]].lastLoad = -1;
    tablePages[index_Tpage].indexPage = pages[index_Vpage];
    pages[index_Vpage] = index_Tpage;
}

void run_simulator(FILE *arqE, char* type, int size_page, int size_memory){
    //n_pages = Quantidade de páginas.
    int index_Tpage, 
        n_pages,
        in_memory,
        offset = (int)(ceil(log2(size_page * 1024))), // 1 MB = 1024KB
        time_zeroBits = 0,
        n_pos = 0,
        runtime = 0,
        n_missingPages = 0,
        n_writtenPages = 0;
    unsigned int addr;
	char rw;
    int* pages;
    Frame* tablePages;

    n_pages = (size_memory * 1024) / size_page;
    tablePages = createTable(size_page);
    pages = createPages(n_pages);

    while(fscanf(arqE, "%x %c", &addr, &rw) != EOF) {
        if (!strcmp(type,"NRU") && time_zeroBits == N){
            reset_bits(tablePages, pages, n_pages);
            time_zeroBits = 0;
        }
        index_Tpage = addr >> offset;
        in_memory = tablePages[index_Tpage].indexPage; // -1 não está na memoria, -1 -> falta página
        if (in_memory == -1){
            n_missingPages++;
            //Verifica se precisamos remover uma página.
            if (n_pos < n_pages){//ñ precisa remover
                pages[n_pos] = index_Tpage;
                tablePages[index_Tpage].indexPage = n_pos;
                n_pos++;
            }
            else{ // precisa remover
                int index_Vpage;
                if (!strcmp(type, "LFU")){
                    index_Vpage = pageLFU(tablePages, pages, n_pages);
                }
                int aux = pages[index_Vpage];
                if (tablePages[aux].M == 1){
                    n_writtenPages++;
                }
                remove_page(tablePages, pages, index_Tpage, index_Vpage); 
            }
        }
        tablePages[index_Tpage].R = 1;
        tablePages[index_Tpage].frequency++;

        if (rw == 'W'){
            tablePages[index_Tpage].M = 1;
        } 
        
        tablePages[index_Tpage].lastAcess = runtime;
        time_zeroBits++;
        runtime++;
    }
    //printar informações necessárias para o trabalho.
    printf("Número de Faltas de Páginas: %d\n", n_missingPages);
    printf("Número de Páginas Escritas: %d\n", n_writtenPages);
    //3free(pages);
    free(tablePages);
     //Ta dando erro aqui mas não sei o porquê.
}

int main(int argc, char *argv[]) {
	
	FILE *arqE;
	char type[4], caminho[50] = "testes/";
	int size_page, size_memory;

	if(argc < 5) {
		printf("Quantidade inválida de parâmetros!\n");
		printf("Exemplo: sim-virtual LFU arquivo.log 8 16\n");
		exit(1);
	}

	strcpy(type, argv[1]);
	size_page = atoi(argv[3]); 
	size_memory = atoi(argv[4]);
	strcat(caminho, argv[2]);
	arqE = fopen(caminho,"r");
    printf("%s\n",caminho);
	if (!arqE) {
    	printf("Erro ao abrir arquivo!\n");
    	exit(1);
	}
	
	checkInput(type, size_page, size_memory);

	printf("\nExecutando o simulador...\n");
	printf("Arquivo de entrada: %s\n", argv[2]);
	printf("Tamanho da memória física: %d MB\n", size_memory);
	printf("Tamanho das páginas: %d KB\n", size_page);
	printf("Algoritmo de substituição: %s\n", type);
    	
	//executaSimuladorVirtual(arq, tipoAlg, tamPagina, tamMemFis);
    run_simulator(arqE, type, size_page, size_memory);
	fclose(arqE);
	
	return 0;

}