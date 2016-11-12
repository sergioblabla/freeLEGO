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
    int M[8][8][8][3]; //[eixo x com tamanho 5 posicoes][eixo y e tamanho de 5 posicoes][eixo z e tamanho de 5 posicoes][indexador 0 indica posicao ocupada, 1 indica rotacionado, 2 é identificador da peca]
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
void ocuparPosicao(MalhaAux *, int , int , int , int , int , int );
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
		                    for(int w=0; w<3; w++)
		                            auxiliarMalha->M[j][k][l][w] = 0; //atribui valor zero a cada posicao da malha, dizendo que ela esta completamente desocupada
           
    p=auxiliarMalha;
    /*for(int j=0; j<10; j++)
	for(int k=0; k<10; k++)
	    for(int l=0; l<5; l++)
		p->M->eixoz[l]->eixoy[k].eixo[j] = 0; //atribui valor zero a cada posicao da malha, dizendo que ela esta completamente desocupada*/
}

void ocuparPosicao(MalhaAux *Malha, int Ix, int Iy, int Iz, int tam, int rotacionado, int pecaId) {
     //variavel auxiliar alocada
    /* struct Malha * auxiliarMalha = 0;
     auxiliarMalha = (struct Malha *) malloc (sizeof(struct Malha));
     if(!auxiliarMalha) return;*/
    if(Ix > 7 || Iy > 7 || Iz > 7)
        return;    
    int i=0;
    //verificaExistenciaPeca();//informaPosicao()==0
    if((Ix+tam<=50) && (rotacionado==1)) {
        for(i=Ix; i>(Ix-tam); i--){
	    if(i > 0 && Iy < 8 && Iz < 8) {
	        p->M[i][Iy][Iz][0] = 1; 		// ocupa determinadas posicoes da malha indicando que ali existe uma peca
		p->M[i][Iy][Iz][1] = rotacionado;	// indica se a peca esta rotacionada
		p->M[i][Iy][Iz][2] = pecaId;		// indentificador da peca
	    }

	//printf("\nPosicao (%d,%d,%d) = %d", i, Iy, Iz, p->M[i][Iy][Iz][0]);
	}
    } else if((Iz+tam<=50) && (rotacionado==0)) {
        for(i=Iz; i<(Iz+tam); i++)
	    if(Ix < 8 && i < 8 && Iy < 8)
	        p->M[Ix][Iy][i][0] = 1; 		// ocupa determinadas posicoes da malha indicando que ali existe uma peca
		p->M[Ix][Iy][i][1] = rotacionado;	// indica se a peca esta rotacionada
		p->M[Ix][Iy][i][2] = pecaId;		// indentificador da peca

//printf("\nPosicao (%d,%d,%d) = %d", Ix, Iy, i, p->M[Ix][Iy][i][0]);
    }
	//p=auxiliarMalha;
	
	printf("\nPosicoes ocupadas com sucesso!");
}

void esvaziaPosicao(MalhaAux *Malha, int Ix, int Iy, int Iz, int tam, int rotacionado) {
    if(Ix > 7 || Iy > 7 || Iz > 7)
        return;    

     if(rotacionado==0)
    for(int i=Ix; i<tam; i++)
	p->M[i][Iy][Iz][0] = 0; //desocupa determinadas posicoes da malha "removendo a existencia de peca ali"
     else if(rotacionado==1)
    for(int i=Iy; i<tam; i++)
	p->M[Ix][i][Iz][0] = 0; //desocupa determinadas posicoes da malha "removendo a existencia de peca ali"
	
	printf("\nPosicoes esvaziadas com sucesso!");
}

int informaPosicao(MalhaAux *Malha, int Ix, int Iy, int Iz) {
    if(Ix > 7 || Iy > 7 || Iz > 7)
        return 0;    

    printf("\nPosicao retornada era %d!", p->M[Ix][Iy][Iz][0]);
    
    return p->M[Ix][Iy][Iz][0]; //retorna o estado de uma posicao desejada para informe se ali existe peÃ§a ou nÃ£o
}

int identificaPecaPos(MalhaAux *Malha, int Ix, int Iy, int Iz) {
    return p->M[Ix][Iy][Iz][2]; //retorna o identificador da peca que consta naquela posicao
}

#endif
