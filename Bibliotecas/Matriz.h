#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Malha MalhaAux; //MalhaAux � uma vari�vel de tipo para uso da estrutura Malha

struct Malha *p=0;

struct Malha {
    int M[8][8][8][3]; //[eixo x com tamanho 5 posicoes][eixo y e tamanho de 5 posicoes][eixo z e tamanho de 5 posicoes][indexador 0 indica posicao ocupada, 1 indica rotacionado, 2 � identificador da peca]
};

void iniciarMalha(MalhaAux *);
void ocuparPosicao(MalhaAux *, int , int , int , int , int , int );
void esvaziaPosPeca(MalhaAux *, int );
int informaPosicao(MalhaAux *, int , int , int );
int identificaPecaPos(MalhaAux *, int , int , int );

void iniciarMalha(MalhaAux *Malha) {
    //variavel auxiliar alocada
    struct Malha * auxiliarMalha = 0;
    auxiliarMalha = (struct Malha *) malloc (sizeof(struct Malha));
    if(!auxiliarMalha) 
	return;
   
    for(int j=0; j<8; j++)
	        for(int k=0; k<8; k++)
	                for(int l=0; l<8; l++)
		                    for(int w=0; w<3; w++)
		                            auxiliarMalha->M[j][k][l][w] = 0; //atribui valor zero a cada posicao da malha, dizendo que ela esta completamente desocupada
           
    p=auxiliarMalha;
}

void ocuparPosicao(MalhaAux *Malha, int Ix, int Iy, int Iz, int tam, int rotacionado, int pecaId) {
    if(Ix > 7 || Iy > 7 || Iz > 7)
        return;    
    int i=0;
    
    //verificaExistenciaPeca();//informaPosicao()==0
    if((Ix+tam<=50) && (rotacionado==1)) {
        for(i=Ix; i>(Ix-tam); i--) {
            if(i >= 0 && Iy < 8 && Iz < 8) {
                p->M[i][Iy][Iz][0] = 1; 		// ocupa determinadas posicoes da malha indicando que ali existe uma peca
                p->M[i][Iy][Iz][1] = rotacionado;	// indica se a peca esta rotacionada
                p->M[i][Iy][Iz][2] = pecaId;		// indentificador da peca
            }
            printf("\nPosicao (%d,%d,%d) = %d", i, Iy, Iz, p->M[i][Iy][Iz][0]);
        }
    } 
    else if((Iz+tam<=50) && (rotacionado==0)) {
        for(i=Iz; i<(Iz+tam); i++) {
            if(Ix < 8 && i < 8 && Iy < 8) {
                p->M[Ix][Iy][i][0] = 1; 		// ocupa determinadas posicoes da malha indicando que ali existe uma peca
                p->M[Ix][Iy][i][1] = rotacionado;	// indica se a peca esta rotacionada
                p->M[Ix][Iy][i][2] = pecaId;		// indentificador da peca
            }
        }
    }	
	printf("\nPosicoes ocupadas com sucesso!");
}

void esvaziaPosPeca(MalhaAux *Malha, int pecaId) {
    if(pecaId == -1)
        return;    

    // Esvazia todas as informa��es de posi��es na malha relacionadas a pe�a com identificador pecaId
    for(int j=0; j<8; j++) {
        for(int k=0; k<8; k++) {
            for(int l=0; l<8; l++) {
                if(p->M[j][k][l][2] == pecaId && p->M[j][k][l][0] == 1) {
                    p->M[j][k][l][0] = 0;
                    p->M[j][k][l][1] = 0;
                    p->M[j][k][l][2] = 0;
                } 
            }
        }
    }
    printf("\nPosicoes esvaziadas com sucesso!");
}

int informaPosicao(MalhaAux *Malha, int Ix, int Iy, int Iz) {
    if(Ix > 7 || Iy > 7 || Iz > 7 || Ix < 0 || Iy < 0 || Iz < 0)
        return 0;    

    printf("\nPosicao retornada era %d!", p->M[Ix][Iy][Iz][0]);
    return p->M[Ix][Iy][Iz][0]; //retorna o estado de uma posicao desejada para informe se ali existe peça ou não
}

int identificaPecaPos(MalhaAux *Malha, int Ix, int Iy, int Iz) {
    if(p->M[Ix][Iy][Iz][0] == 1)
        return p->M[Ix][Iy][Iz][2]; //retorna o identificador da peca que consta naquela posicao
    else
        return -1;
}

#endif
