#ifndef PECA_H
#define PECA_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "Objeto3D.h"

typedef struct Pecinha PecinhaAux;
struct Pecinha *pe=0;

Objeto3D Bloco;

struct Pecinha {
    int identificador; //nome que identifica peca
    int rotacionada; //0 para peca paralela ao eixo x, 1 para peca paralela ao eixo z
    int posmx, posmy, posmz; //posicao na matriz global de posicionamento de pecas
    int cor, tipo; //informacoes de tipo
    float transx, transy, transz; //informacoes exatas de translado relativo a distancia da origem
    int tamp; //tamanho da pecinha de lego/numero de posicoes que ocupa na matriz global de posicionamento/associacao e proporcional com o numero de pinos na parte superior
    int exibir;
    Objeto3D Obj;
};

PecinhaAux novaPeca(int , int , int , int , int , int );
PecinhaAux apagaPeca();
void atualizaCorPeca(int );
void alteraPosicao(PecinhaAux *, int , int , int );
PecinhaAux alteraTransladoPeca(float , float , float );
void pegaPosicao(PecinhaAux *, int *);
PecinhaAux rotacionaPeca(PecinhaAux * , int );
int pegaTamanho(PecinhaAux *);
void imprimirPeca(PecinhaAux );

/*informacoes do inicializador da Peca:
    nome: � sempre dado em int, pois ser� sempre um n�mero para facilitar o acesso depois
    color: � a cor, zero para preto, 1 para branco, 2 para vermelho, 3 para amarelo, 4 para verde, 5 para azul
    type: � o tipo da peca, peca pequena, grande... 0 para 1x1, 1 para 1x2, 2 para 1x4, 3 para 1x8
    size: comprimento da peca
*/

PecinhaAux novaPeca(int nome, int color, int type, int size, int exibe, int rotaciona) {
    //variavel auxiliar alocada
    struct Pecinha * auxiliarPeca = 0;
    auxiliarPeca = (struct Pecinha *) malloc (sizeof(struct Pecinha));
    //if(!auxiliarPeca) return false;
     
    auxiliarPeca->identificador = nome;
    auxiliarPeca->rotacionada = rotaciona;
    auxiliarPeca->posmx = 0;
    auxiliarPeca->posmy = 0;
    auxiliarPeca->posmz = 0;
    auxiliarPeca->cor = color;
    auxiliarPeca->tipo = type;
    auxiliarPeca->tamp = size;
    auxiliarPeca->transx = 0;
    auxiliarPeca->transy = 0;
    auxiliarPeca->transz = 0;
    auxiliarPeca->exibir = exibe;

    if(exibe==1){
	    switch(type){ //carrega o objeto correto de acordo com o tipo
	    	case 0:
				carregar(&Bloco, "Bibliotecas/Objetos/pecinha1x1.obj");
				printf("\nBloco tipo 0 carregado com sucesso");
			break;
			case 1:
				carregar(&Bloco, "Bibliotecas/Objetos/pecinha1x2.obj");
				printf("\nBloco tipo 1 carregado com sucesso");
			break;
			case 2:
				carregar(&Bloco, "Bibliotecas/Objetos/pecinha1x4.obj");
				printf("\nBloco tipo 2 carregado com sucesso");
			break;
			case 3:
				carregar(&Bloco, "Bibliotecas/Objetos/pecinha1x8.obj");
				printf("\nBloco tipo 3 carregado com sucesso");
			break;
		}
	    auxiliarPeca->Obj = Bloco;
    }
    else {
	    carregar(&Bloco, "Bibliotecas/Objetos/lixo.obj");
	    auxiliarPeca->Obj = Bloco;
    }

    pe = auxiliarPeca;
	return *pe;
}

PecinhaAux apagaPeca(){
    // variavel auxiliar alocada
    struct Pecinha * auxiliarPeca = 0;
    auxiliarPeca = (struct Pecinha *) malloc (sizeof(struct Pecinha));

    auxiliarPeca->identificador = 0;
    auxiliarPeca->rotacionada = 0;
    auxiliarPeca->posmx = 0;
    auxiliarPeca->posmy = 0;
    auxiliarPeca->posmz = 0;
    auxiliarPeca->cor = 0;
    auxiliarPeca->tipo = 0;
    auxiliarPeca->tamp = 0;
    auxiliarPeca->transx = 0;
    auxiliarPeca->transy = 0;
    auxiliarPeca->transz = 0;
    auxiliarPeca->exibir = 0;

    // carrega objeto 3D
    carregar(&Bloco, "Bibliotecas/Objetos/lixo.obj");
    auxiliarPeca->Obj=Bloco;

    pe = auxiliarPeca;

    return *pe;
}

void atualizaCorPeca(int par){
	switch(par){
		case 0:
			glColor3f(0.04f,0.01f,0.0f);
		break;
		case 1:
			glColor3f(0.92f,0.9f,0.69f);
		break;
		case 2:
			glColor3f(0.77f,0.01f,0.0f);
		break;
		case 3:
			glColor3f(0.73f,0.52f,0.06f);
		break;
		case 4:
			glColor3f(0.0f,0.1f,0.01f);
		break;
		case 5:
			glColor3f(0.0f,0.0f,0.48f);
		break;
	}
}

void alteraPosicaoMPeca(PecinhaAux *Pecinha, int posmxAux, int posmyAux, int posmzAux) {
    pe->posmx = posmxAux;
    pe->posmy = posmyAux;
    pe->posmz = posmzAux;
    
    printf("\nAlterada com sucesso a posicaox para: %d!", pe->posmx);
    printf("\nAlterada com sucesso a posicaoy para: %d!", pe->posmy);
    printf("\nAlterada com sucesso a posicaoz para: %d!", pe->posmz);
}

PecinhaAux alteraTransladoPeca(float transxAux, float transyAux, float transzAux) {
    pe->transx = transxAux;
    pe->transy = transyAux;
    pe->transz = transzAux;
    
    glTranslatef(0, 0, 0);
    glTranslatef(pe->transx, pe->transy, pe->transz);
    
    printf("\nAlterada com sucesso a transx para: %f!", pe->transx);
    printf("\nAlterada com sucesso a transy para: %f!", pe->transy);
    printf("\nAlterada com sucesso a transz para: %f!", pe->transz);
    return *pe;
}

void pegaPosicaoPeca(PecinhaAux *Pecinha, int *ArrAux) {
    ArrAux[0] = pe->posmx;
    ArrAux[1] = pe->posmy;
    ArrAux[2] = pe->posmz;
}

PecinhaAux rotacionaPeca(PecinhaAux *Pecinha, int rotaciona) {
    struct Pecinha * auxiliarPeca = Pecinha;
    auxiliarPeca->rotacionada = rotaciona;
    pe = auxiliarPeca;
    return *pe;
}

int pegaComprimentoPeca(PecinhaAux *Pecinha) {
    return (pe->tamp);
}

void imprimirPeca(PecinhaAux Pec){
    //printf("\nMentira ne");
    if(Pec.exibir==1)
    glPushMatrix();	//empilha
	atualizaCorPeca(Pec.cor);
	if(Pec.rotacionada == 1) {
	    glTranslatef(0, 0, 0);
    	glRotated(90, 0, 1, 0);
	}

	glTranslatef(Pec.transx, Pec.transy, Pec.transz);
	imprimir(Pec.Obj);
    glPopMatrix();	//empilha
}

#endif
