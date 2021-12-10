#include<stdio.h>
typedef struct frame{

    int R;
    int M;
    int lastAcess; // tempo do último acesso.
    int lastLoad;
    int frequency;
    int indexPage; // vp
    
    
} Frame;


void run_simulator(FILE *arqE, char* type, int size_page, int size_memory);