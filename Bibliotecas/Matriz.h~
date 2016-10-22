#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Malha MalhaAux; //MalhaAux é uma variável de tipo para uso da estrutura Malha
//typedef struct EixoX EixoXAux;
//typedef struct EixoY EixoYAux;
//typedef struct EixoZ EixoZAux;
struct Malha *p=0;

struct Malha {
    int M[8][8][8][2]; //[eixo x com tamanho 5 posicoes][eixo y e tamanho de 5 posicoes][eixo z e tamanho de 5 posicoes][posicao 1 indica identificador da peca]
};

/*struct EixoX {
    int eixo[10]; //eixo x e tamanho de 10 posicoes
};

struct EixoY {
    EixoX *eixoy[10]; //eixo y e tamanho de 10 posicoes
};

struct EixoZ {
    EixoY *eixoz[5]; //eixo z e tamanho de 5 posicoes
};*/

void iniciarMalha(MalhaAux *);
void ocuparPosicao(MalhaAux *, int , int , int , int , int );
void esvaziaPosicao(MalhaAux *, int , int , int , int , int );
int informaPosicao(MalhaAux *, int , int , int );
int identificaPecaPos(MalhaAux *, int , int , int );

void iniciarMalha(MalhaAux *Malha) {
     //variavel auxiliar alocada
     struct Malha * auxiliarMalha = 0;
     auxiliarMalha = (struct Malha *) malloc (sizeof(struct Malha));
     if(!auxiliarMalha) return;
    
    printf("\nlindo");
    int aux=0;
    for(int j=0; j<8; j++)
	        for(int k=0; k<8; k++)
	                for(int l=0; l<8; l++)
		                    for(int w=0; w<2; w++)
		                            auxiliarMalha->M[j][k][l][w] = 0; //atribui valor zero a cada posicao da malha, dizendo que ela esta completamente desocupada
           
    p=auxiliarMalha;
    /*for(int j=0; j<10; j++)
	for(int k=0; k<10; k++)
	    for(int l=0; l<5; l++)
		p->M->eixoz[l]->eixoy[k].eixo[j] = 0; //atribui valor zero a cada posicao da malha, dizendo que ela esta completamente desocupada*/
}

void ocuparPosicao(MalhaAux *Malha, int Ix, int Iy, int Iz, int tam, int rotacionado) {
     //variavel auxiliar alocada
    /* struct Malha * auxiliarMalha = 0;
     auxiliarMalha = (struct Malha *) malloc (sizeof(struct Malha));
     if(!auxiliarMalha) return;*/
     
    int i=0;
    //verificaExistenciaPeca();//informaPosicao()==0
    if((Ix+tam<=50) && (rotacionado==0))
    for(i=Ix-1; i<tam; i++)
	p->M[i][Iy-1][Iz-1][0] = 1; //ocupa determinadas posicoes da malha indicando que ali existe uma peca
    else if((Iy+tam<=50) && (rotacionado==1))
    for(i=Iy-1; i<tam; i++)
	p->M[Ix-1][i][Iz-1][0] = 1; //ocupa determinadas posicoes da malha indicando que ali existe uma peca
	
	//p=auxiliarMalha;
	
	printf("\nPosicoes ocupadas com sucesso!");
}

void esvaziaPosicao(MalhaAux *Malha, int Ix, int Iy, int Iz, int tam, int rotacionado) {
     if(rotacionado==0)
    for(int i=Ix-1; i<tam; i++)
	p->M[i][Iy-1][Iz-1][0] = 0; //desocupa determinadas posicoes da malha "removendo a existencia de peca ali"
     else if(rotacionado==1)
    for(int i=Iy-1; i<tam; i++)
	p->M[Ix-1][i][Iz-1][0] = 0; //desocupa determinadas posicoes da malha "removendo a existencia de peca ali"
	
	printf("\nPosicoes esvaziadas com sucesso!");
}

int informaPosicao(MalhaAux *Malha, int Ix, int Iy, int Iz) {
    printf("\nPosicao retornada era %d!", p->M[Ix-1][Iy-1][Iz-1][0]);
    
    return p->M[Ix-1][Iy-1][Iz-1][0]; //retorna o estado de uma posicao desejada para informe se ali existe peÃ§a ou nÃ£o
}

int identificaPecaPos(MalhaAux *Malha, int Ix, int Iy, int Iz) {
    return p->M[Ix-1][Iy-1][Iz-1][1]; //retorna o identificador da peca que consta naquela posicao
}

#endif
