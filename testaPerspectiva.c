#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "Bibliotecas/Textura.h"
#include "Bibliotecas/Objeto3D.h"
#include "Bibliotecas/Seletor.h"
#include "Bibliotecas/Peca.h"

//variaveis rodar eixo da camea
int rodarx = 0; //roda no eixo x
int rodary = 0; //roda no eixo y
int rodarz = 0; //roda no eixo z

//variaveis posicao cursor
float posCursor[3] = {0,0,0}; //[0] para x, [1] para y e [2] para z

//outras variaveis
double auxfovy, auxAspect, auxZNear, auxZFar;
int tamanho = 10; //zoom
double t = 0;
double a = 0;

//Variaveis de menu
int menu = 2; //0-bem vindo, 1-menu principal, 2-jogar, 3-ajuda, 4-creditos, 5-sair
int opcao = 0;
int someseta=0; //teste sumir com ponteiro

//variaveis de começo
int jogocomecou = 0;

//variavel de luz
/*GLfloat ambiente[] = {0.2, 0.2, 0.2, 1};

GLfloat luz_posicao[]={800.0,1000.0,2000.0,1};
GLfloat luz_difusa[]={0.7, 0.7, 0.7,1};
GLfloat luz_especular[]={1,1,1,1};

GLfloat mat_ambiente[]={1,1,0.5,1};
GLfloat mat_difusa[]={0.1,0.7,0.5,1};
GLfloat mat_especular[]={1,1,0.5,1};*/

/*GLfloat luz_posicao[]={800.0,1000.0,2000.0,0.0};
GLfloat luz_difusa[]={0, 1, 0.5,1};
GLfloat luz_especular[]={0,0.05,0.2,1};

GLfloat mat_ambiente[]={0.5,0.0,0.5,1};
GLfloat mat_difusa[]={0.1,0.7,0.5,1};
GLfloat mat_especular[]={0,0,0.5,1};*/

//objetos
Objeto3D terreno; //terreno
Objeto3D Seta; //cursor de movimentacao e posicionamento de pecas
PecinhaAux MinhasPecas[240]; /*contem as pecas que poderao ser utilizadas durante o jogo, eh sua caixa de blocos de lego; as pecas estao dispostas no array da seguinte forma:
posicao 0~9: blocos 1x1 pretos
posicao 10~19: blocos 1x1 brancos
posicao 20~29: blocos 1x1 vermelhos
posicao 30~39: blocos 1x1 amarelos
posicao 40~49: blocos 1x1 verdes
posicao 50~59: blocos 1x1 azuis

posicao 60~69: blocos 1x2 pretos
posicao 70~79: blocos 1x2 brancos
posicao 80~89: blocos 1x2 vermelhos
posicao 90~99: blocos 1x2 amarelos
posicao 100~109: blocos 1x2 verdes
posicao 110~119: blocos 1x2 azuis

seguindo o padrao... e assim sucessivamente; até o maior bloco disponivel, o 1x8.
*/

//variaveis indicadoras de pecas ja adicionadas
int blocotipo0pr = 0; //1x1 preto
int blocotipo0br = 0; //1x1 branco
int blocotipo0vm = 0; //1x1 vermelho
int blocotipo0am = 0; //1x1 amarelo
int blocotipo0vd = 0; //1x1 verde
int blocotipo0az = 0; //1x1 azul
int blocotipo1pr = 0; //1x2 preto
int blocotipo1br = 0; //1x2 branco
int blocotipo1vm = 0; //1x2 vermelho
int blocotipo1am = 0; //1x2 amarelo
int blocotipo1vd = 0; //1x2 verde
int blocotipo1az = 0; //1x2 azul
int blocotipo2pr = 0; //1x4 preto
int blocotipo2br = 0; //1x4 branco
int blocotipo2vm = 0; //1x4 vermelho
int blocotipo2am = 0; //1x4 amarelo
int blocotipo2vd = 0; //1x4 verde
int blocotipo2az = 0; //1x4 azul
int blocotipo3pr = 0; //1x8 preto
int blocotipo3br = 0; //1x8 branco
int blocotipo3vm = 0; //1x8 vermelho
int blocotipo3am = 0; //1x8 amarelo
int blocotipo3vd = 0; //1x8 verde
int blocotipo3az = 0; //1x8 azul
int seguraPeca = 0;
int pecasadd = 0;

//estruturas
SetinhaAux cursor;

//gerenciamento de janela
int width=800;
int height=500;

//Cabeçalhos das funções:
void key(unsigned char , int , int );
static void rato(int , int , int , int );
void Desenhar();
void GerenciaPecas();
void relogio();
void carregarObjetos();
void logicaJogo();
void carregaMatrizPecas();

void key(unsigned char key, int x, int y)
{
    switch (key) 
    {
        case '+':
            if(menu==0)
	    menu=1;
            break;
        /*case '8':
            if(opcao>0 && opcao<4 && menu==1)
	    opcao--;
            break;
	case '2':
            if(opcao>=0 && opcao<3 && menu==1)
	    opcao++;
            break;
	case '6':
            if(opcao==0 && menu==1){
	    menu=2;
    	    
	    }
	    if(opcao==1 && menu==1)
	    menu=3;
	    if(opcao==2 && menu==1)
	    menu=4;
	    if(opcao==3 && menu==1)
	    exit(0);
            break;
	case '4':
            if(menu>1)
	    menu=1;
            break;*/
        case 'a': //ampliar zoom
            tamanho+=1;
            break;
        case 'A': //ampliar zoom
            tamanho+=1;
            break;
        case 'd': //reduzir zoom
            tamanho-=1;
            break;
        case 'D': //reduzir zoom
            tamanho-=1;
            break;
	case 'm': //rotacao extra como opcao a da funcao especial das setas do teclado
            rodary+=10;
            break;
	case 'M': //rotacao extra como opcao a da funcao especial das setas do teclado
            rodary+=10;
            break;
	case 'n': //rotacao contraria extra como opcao a da funcao especial das setas do teclado
            rodary-=10;
            break;
	case 'N': //rotacao contraria extra como opcao a da funcao especial das setas do teclado
            rodary-=10;
            break;
        case 'k': //rotacao em z 
            rodarz+=10;
            break;
        case 'K': //rotacao em z 
            rodarz+=10;
            break;
	case 'j': //rotacao em z
            rodarz-=10;
            break;
	case 'J': //rotacao em z
            rodarz-=10;
            break;
        case 'i': //rotacao em z 
            rodarx+=10;
            break;
        case 'I': //rotacao em z 
            rodarx+=10;
            break;
	case 'o': //rotacao em z
            rodarx-=10;
            break;
	case 'O': //rotacao em z
            rodarx-=10;
            break;
	case 'r': //movimento em x na matriz de posicionamento global
	    if(posCursor[0]>0 && someseta==0)
            posCursor[0]--; //"regrede" em relacao ao eixo x imaginado para matriz de seletor
            break;
	case 'R': //movimento em x na matriz de posicionamento global
	    if(posCursor[0]>0 && someseta==0)
            posCursor[0]--; //"regrede" em relacao ao eixo x imaginado para matriz de seletor
            break;
	case 't': //rotacao em x na matriz de posicionamento global
	    if(posCursor[0]<=6 && someseta==0)
            posCursor[0]++; //"avanca" em relacao ao eixo x imaginado para matriz de seletor
            break;
	case 'T': //rotacao em x na matriz de posicionamento global
	    if(posCursor[0]<=6 && someseta==0)
            posCursor[0]++; //"avanca" em relacao ao eixo x imaginado para matriz de seletor
            break;
        case 'f': //rotacao em y na matriz de posicionamento global
	    if(posCursor[1]<0 && someseta==0)
            posCursor[1]++; //"avanca" em relacao ao eixo y imaginado para matriz de seletor
            break;
        case 'F': //rotacao em y na matriz de posicionamento global
	    if(posCursor[1]<0 && someseta==0)
            posCursor[1]++; //"avanca" em relacao ao eixo y imaginado para matriz de seletor
            break;
	case 'g': //rotacao em y na matriz de posicionamento global
	    if(posCursor[1]>-7 && someseta==0)
            posCursor[1]--; //"regrede" em relacao ao eixo y imaginado para matriz de seletor
            break;
	case 'G': //rotacao em y na matriz de posicionamento global
	    if(posCursor[1]>-7 && someseta==0)
            posCursor[1]--; //"regrede" em relacao ao eixo y imaginado para matriz de seletor
            break;
        case 'c': //rotacao em z na matriz de posicionamento global
	    if(posCursor[2]<0 && someseta==0)
            posCursor[2]++; //"avanca" em relacao ao eixo z imaginado para matriz de seletor
            break;
        case 'C': //rotacao em z na matriz de posicionamento global
	    if(posCursor[2]<0 && someseta==0)
            posCursor[2]++; //"avanca" em relacao ao eixo z imaginado para matriz de seletor
            break;
	case 'v': //rotacao em z na matriz de posicionamento global
	    if(posCursor[2]>-7 && someseta==0)
            posCursor[2]--; //"regrede" em relacao ao eixo z imaginado para matriz de seletor
            break;
	case 'V': //rotacao em z na matriz de posicionamento global
	    if(posCursor[2]>-7 && someseta==0)
            posCursor[2]--; //"regrede" em relacao ao eixo z imaginado para matriz de seletor
            break;
        case 's': //selecionar peca na posicao
            selecionaPeca(&cursor, posCursor[0], posCursor[1], posCursor[2]);
            break;
        case 'S': //selecionar peca na posicao
            selecionaPeca(&cursor, posCursor[0], posCursor[1], posCursor[2]);
            break;
        case 'w': //selecionar peca na posicao
		carregar(&Seta, "Bibliotecas/Objetos/lixo.obj");
		someseta=1;
            break;
        case 'W': //selecionar peca na posicao
		carregar(&Seta, "Bibliotecas/Objetos/lixo.obj");
		someseta=1;
            break;
        /*case 'W': //selecionar peca na posicao
		carregar(&Seta, "Bibliotecas/Objetos/cursor.obj");
		someseta=0;
            break;*/
	case 'q': //sair
            exit(0);
            break;
	case 'Q': //sair
            exit(0);
            break;
	case '/':
            auxfovy--;
            break;
	case '*':
            auxfovy++;
            break;
	case '8':
            auxAspect-=0.05;
            break;
	case '9':
            auxAspect+=0.05;
            break;
	case '5':
            auxZNear--;
            break;
	case '6':
            auxZNear++;
            break;
	case '2':
            auxZFar-=100;
            break;
	case '3':
            auxZFar+=100;
            break;
	/*case 'z': //soltar peca
            if(seguraPeca==1){
		seguraPeca=0;
		cursor.pecaSel=0;
	    }
            break;
	case 'Z': //soltar peca
            if(seguraPeca==1){
		seguraPeca=0;
		cursor.pecaSel=0;
	    }
            break;*/
	/*case 'x': //teste
		 glutFullScreen();
		break;*/
    }
    //glFlush();
    glutPostRedisplay();
}

//funcao mouse
static void rato(int botao, int estado, int x, int y){
//
//adicionar peças 1x1:
//
    if(estado==GLUT_DOWN && x>=608 && x<=635 && y>=48 && y<=80 && seguraPeca==0){
//adicionar peça 1x1 preta
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 0, 0, 1, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2])*2); //blocotipo0
	pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } else if(estado==GLUT_DOWN && x>=642 && x<=670 && y>=48 && y<=80 && seguraPeca==0){
//adicionar peça 1x1 branca
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 1, 0, 1, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2])*2); //blocotipo0
        pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } else if(estado==GLUT_DOWN && x>=673 && x<=700 && y>=48 && y<=80 && seguraPeca==0){
//adicionar peça 1x1 vermelha
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 2, 0, 1, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2])*2); //blocotipo0
	pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } else if(estado==GLUT_DOWN && x>=703 && x<=730 && y>=48 && y<=80 && seguraPeca==0){
//adicionar peça 1x1 amarela
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 3, 0, 1, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2])*2); //blocotipo0
	pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } else if(estado==GLUT_DOWN && x>=734 && x<=763 && y>=48 && y<=80 && seguraPeca==0){
//adicionar peça 1x1 verde
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 4, 0, 1, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2])*2); //blocotipo0
	pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } else if(estado==GLUT_DOWN && x>=767 && x<=800 && y>=48 && y<=80 && seguraPeca==0){
//adicionar peça 1x1 azul
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 5, 0, 1, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2])*2); //blocotipo0
	pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } 
//
//adicionar peças 1x2:
//
    else if(estado==GLUT_DOWN && x>=608 && x<=635 && y>=100 && y<=128 && seguraPeca==0){
//adicionar peça 1x2 preta
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 0, 1, 2, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-0.5)*2); //blocotipo1
	pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } else if(estado==GLUT_DOWN && x>=642 && x<=670 && y>=100 && y<=128 && seguraPeca==0){
//adicionar peça 1x2 branca
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 1, 1, 2, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-0.5)*2); //blocotipo1
	pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } else if(estado==GLUT_DOWN && x>=673 && x<=700 && y>=100 && y<=128 && seguraPeca==0){
//adicionar peça 1x2 vermelha
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 2, 1, 2, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-0.5)*2); //blocotipo1
	pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } else if(estado==GLUT_DOWN && x>=703 && x<=730 && y>=100 && y<=128 && seguraPeca==0){
//adicionar peça 1x2 amarela
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 3, 1, 2, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-0.5)*2); //blocotipo1
	pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } else if(estado==GLUT_DOWN && x>=734 && x<=763 && y>=100 && y<=128 && seguraPeca==0){
//adicionar peça 1x2 verde
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 4, 1, 2, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-0.5)*2); //blocotipo1
	pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } else if(estado==GLUT_DOWN && x>=767 && x<=800 && y>=100 && y<=128 && seguraPeca==0){
//adicionar peça 1x2 azul
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 5, 1, 2, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-0.5)*2); //blocotipo1
	pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } 
//
//adicionar peças 1x4:
//
    else if(estado==GLUT_DOWN && x>=608 && x<=635 && y>=142 && y<=180 && seguraPeca==0){
//adicionar peça 1x4 preta
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 0, 2, 4, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-1.5)*2); //blocotipo2
	pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } else if(estado==GLUT_DOWN && x>=642 && x<=670 && y>=142 && y<=180 && seguraPeca==0){
//adicionar peça 1x4 branca
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 1, 2, 4, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-1.5)*2); //blocotipo2
	pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } else if(estado==GLUT_DOWN && x>=673 && x<=700 && y>=142 && y<=180 && seguraPeca==0){
//adicionar peça 1x4 vermelha
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 2, 2, 4, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-1.5)*2); //blocotipo2
	pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } else if(estado==GLUT_DOWN && x>=703 && x<=730 && y>=142 && y<=180 && seguraPeca==0){
//adicionar peça 1x4 amarela
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 3, 2, 4, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-1.5)*2); //blocotipo2
	pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } else if(estado==GLUT_DOWN && x>=734 && x<=763 && y>=142 && y<=180 && seguraPeca==0){
//adicionar peça 1x4 verde
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 4, 2, 4, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-1.5)*2); //blocotipo2
	pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } else if(estado==GLUT_DOWN && x>=767 && x<=800 && y>=142 && y<=180 && seguraPeca==0){
//adicionar peça 1x4 azul
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 5, 2, 4, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-1.5)*2); //blocotipo2
	pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } 
//
//adicionar peças 1x8:
//
    else if(estado==GLUT_DOWN && x>=608 && x<=635 && y>=190 && y<=242 && seguraPeca==0){
//adicionar peça 1x8 preta
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 0, 3, 8, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-3.5)*2); //blocotipo3
	pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } else if(estado==GLUT_DOWN && x>=642 && x<=670 && y>=190 && y<=242 && seguraPeca==0){
//adicionar peça 1x8 branca
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 1, 3, 8, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-3.5)*2); //blocotipo3
	pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } else if(estado==GLUT_DOWN && x>=673 && x<=700 && y>=190 && y<=242 && seguraPeca==0){
//adicionar peça 1x8 vermelha
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 2, 3, 8, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-3.5)*2); //blocotipo3
	pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } else if(estado==GLUT_DOWN && x>=703 && x<=730 && y>=190 && y<=242 && seguraPeca==0){
//adicionar peça 1x8 amarela
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 3, 3, 8, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-3.5)*2); //blocotipo3
	pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } else if(estado==GLUT_DOWN && x>=734 && x<=763 && y>=190 && y<=242 && seguraPeca==0){
//adicionar peça 1x8 verde
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 4, 3, 8, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-3.5)*2); //blocotipo3
	pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } else if(estado==GLUT_DOWN && x>=767 && x<=800 && y>=190 && y<=242 && seguraPeca==0){
//adicionar peça 1x8 azul
	MinhasPecas[pecasadd]=novaPeca(pecasadd, 5, 3, 8, 1);
        MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-3.5)*2); //blocotipo3
	pecasadd++;
	cursor.pecaSel=999; //modo nova peca
	seguraPeca=0;
    } 
    printf("\nPosicao do mouse: %d, %d", x, y);
    glutPostRedisplay();
}


        //MinhasPecas[blocotipo1]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-0.5)*2); //blocotipo1
        //MinhasPecas[blocotipo0]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-1.5)*2); //blocotipo2
	//MinhasPecas[blocotipo0]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-3.5)*2); //blocotipo3



void luzes()
{
	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};	   // "cor" 
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;

 	// Especifica que a cor de fundo da janela será preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a refletância do material 
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);  
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

    /*glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luz_especular);
    glLightfv(GL_LIGHT0, GL_POSITION, luz_posicao);
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambiente);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular);*/
}

void Desenhar(){
    //usa como velocidade uma divisao relativa a hora atual e armazena em constante
    /*const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;*/
    
    //LoadGLTextures("Imagens/menulateral.bmp"); //carrega textura do menu lateral
    /*                                                     */
    /*                   J   O   G    O                    */
    /*                                                     */

    glPushMatrix();	//empilha

    /**********************************************************
    *                   Iluminacao                            *
    ***********************************************************/
    /*GLfloat mat_ambiente1[]={0.5,0.0,0.5,1};
    GLfloat mat_difusa1[]={0.67,0.61,0,1};
    GLfloat mat_especular1[]={1.5699,0.9599,0.5,1};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiente1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difusa1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular1);*/

    //Fim

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);			// Enable Texture Mapping
    glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    glDisable(GL_DEPTH_TEST);			// Enables Depth Testing
    glClearColor(0,0,0,0); //Cor de fundo (preto)
    glColor3d(0,0,0); // Cor do desenho (preto)
    //glClear(GL_COLOR_BUFFER_BIT); //Limpar buffer de cor

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glViewport(0,0,width*0.75,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-800,800,-800,800,100,1500);
    //glFrustum(-10,10,-10,10,1,100);
	
	gluPerspective(auxfovy,auxAspect,auxZNear,auxZFar);

	gluLookAt(0,160,200, 0,0,0, 0,1,0);

    luzes(); //permite função luz
	//gluPerspective(90,0.75,10,1600);
    //glOrtho(-800,800,-800,800,-1500,1500); 

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpar buffer de cor

    glEnable(GL_DEPTH_TEST); //ativa zBuffer

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotated(rodarz,0,0,1);
    glRotatef(rodarx, 1, 0, 0);
    glRotatef(rodary, 0, 1, 0);

    //predefinicoes de conforto inicial na camera
    glRotated(40,1,0,0);
    glRotated(40,0,1,0);

    glScaled(tamanho,tamanho,tamanho); //zoom


    /* TERRENO           */
    /* TAMANHO 8X8       */
    glPushMatrix();	//empilha
      /*  	glEnable(GL_LIGHTING);
        	glEnable(GL_LIGHT0);*/

    glColor3f(0,1,0);
    glRotated(180,1,0,0);
    glTranslated(0, 1, 0);
    imprimir(terreno);
    glPopMatrix();	//desempilha

    /* |Fim| TERRENO     */
    /* |Fim| TAMANHO 8X8 */


    /* CURSOR DE SELECAO DE PECAS NA MATRIZ NA PEÇAS */
    if(someseta==0){ //modo esconder/mostrar seletor
    	glRotated(180,1,0,0);
    	if(jogocomecou==0){
    	glTranslated(-7, 0, 7);
    	glPushMatrix();	//empilha
        	glColor3f(0.85,0.6,0);
        	glRotated(a, 0, 1, 0);
		imprimir(Seta);
    	glPopMatrix();	//desempilha
    	}else{
    		if(moverSeta(&cursor, posCursor[0], posCursor[1], posCursor[2])==1){
    		glTranslated(-7, 0, 7);
    		glPushMatrix();	//empilha
        		glColor3f(0.85,0.6,0);
        		glTranslatef(posCursor[0]*2, posCursor[1]*2, posCursor[2]*2);
        		glRotated(a, 0, 1, 0);
			imprimir(Seta);
    		glPopMatrix();	//desempilha
    		}
    	}
    }

    /* FIM DO CURSOR DE SELECAO DE PECAS NA MATRIZ NA PEÇAS */


	// Habilita o modelo de colorização de Gouraud
/*	glShadeModel(GL_SMOOTH);

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;
	// Luz Ambiente	
	GLfloat lAmbiente[4]={0.2,0.2,0.2,1.0}; 
	GLfloat lDifusa[4]={0.7,0.7,0.7,1.0};	   // "cor" 
	GLfloat lEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
	GLfloat lposicao[4]={0.0, 50.0, 50.0, 1.0};

	// Define a refletância do material 
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, lAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, lEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, lposicao );*/

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	/*glEnable(GL_LIGHTING);  
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);*/

    GerenciaPecas();

    jogocomecou=jogocomecou+1;
    glPopMatrix();	//desempilha

    glDrawBuffer(GL_BACK); //buffer de tras

    glPushMatrix();	//empilha
    glViewport(width*0.75,0,width*0.25,height);

    glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
    gluOrtho2D(-50,50,-50,50); 
    glMatrixMode(GL_MODELVIEW);
    
    glEnable(GL_TEXTURE_2D);			// Enable Texture Mapping
    //glClearColor(1, 0, 0, 0);			// Limpa a cor de fundo para vermelho 
    //glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    //glDepthFunc(GL_LESS);			// The Type Of Depth Test To Do
    //glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
    //glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
    
    glColor3d(0,0,1); // Cor do desenho (branco)
    glClear(GL_DEPTH_BUFFER_BIT); //Limpar buffer de cor
    
    
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    /*glOrtho(-50.0, 50.0, -50.0, 50.0, -50.0, 50.0);
    glMatrixMode(GL_MODELVIEW);*/


    glBindTexture(GL_TEXTURE_2D, texture[0]);   // choose the texture to use.

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-50.0f, -50.0f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex2f( 50.0f, -50.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex2f( 50.0f,  50.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-50.0f,  50.0f);	// Top Left Of The Texture and Quad
    glEnd();


    glPopMatrix();	//desempilha

    glutSwapBuffers();

	printf("Valores Atuais: Fovy=%f, Aspect=%f, ZNear=%f, ZFar=%f.\n", auxfovy,auxAspect,auxZNear,auxZFar);
    
}

void GerenciaPecas(){ //IMPRIME AS PEÇAS QUE DEVEM SER EXIBIDAS
    for(int ax=0; ax<240; ax++){
	imprimirPeca(MinhasPecas[ax]);
    	glutPostRedisplay();
    }
}

void relogio(){ //por fator dinamico e dependencia em movimentos, utiliza-se hora para alterar variavel global responsavel para tal
    t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    a = t*90.0;
}

void carregarObjetos(){
    printf("\n Carregando objetos modelados...");
    carregar(&terreno, "Bibliotecas/Objetos/terreno8x8.obj");
    carregar(&Seta, "Bibliotecas/Objetos/cursor.obj");
    printf("\n Concluído o processo de carregar objetos modelados.");
    printf("\n Carregando texturas...");
    printf("\n Concluído o processo de carregar texturas.");
}

void logicaJogo(){
    printf("\n Carregando Bibliotecas de lógica.");
    iniciarCursor(&cursor);
    printf("\n Biblioteca Seletor.h processada com sucesso.");
    carregaMatrizPecas();
    printf("\n Balde de Lego adquirido com sucesso! :D ");
}

void carregaMatrizPecas(){
    for(int i=0; i<60; i++){ //carrega pecas do tipo 1x1 da matriz de pecas
	if(i<10) //pretas
	MinhasPecas[i]=novaPeca(i, 0, 0, 1, 0);
	else if(i>=10 && i<20) //brancas
	MinhasPecas[i]=novaPeca(i, 1, 0, 1, 0);
	else if(i>=20 && i<30) //vermelhas
	MinhasPecas[i]=novaPeca(i, 2, 0, 1, 0);
	else if(i>=30 && i<40) //amarelas
	MinhasPecas[i]=novaPeca(i, 3, 0, 1, 0);
	else if(i>=40 && i<50) //verdes
	MinhasPecas[i]=novaPeca(i, 4, 0, 1, 0);
	else if(i>=50 && i<60) //azuis
	MinhasPecas[i]=novaPeca(i, 5, 0, 1, 0);
    }
    for(int i=60; i<120; i++){ //carrega pecas do tipo 1x2 da matriz de pecas
	if(i<70) //pretas
	MinhasPecas[i]=novaPeca(i, 0, 1, 2, 0);
	else if(i>=70 && i<80) //brancas
	MinhasPecas[i]=novaPeca(i, 1, 1, 2, 0);
	else if(i>=80 && i<90) //vermelhas
	MinhasPecas[i]=novaPeca(i, 2, 1, 2, 0);
	else if(i>=90 && i<100) //amarelas
	MinhasPecas[i]=novaPeca(i, 3, 1, 2, 0);
	else if(i>=100 && i<110) //verdes
	MinhasPecas[i]=novaPeca(i, 4, 1, 2, 0);
	else if(i>=110 && i<120) //azuis
	MinhasPecas[i]=novaPeca(i, 5, 1, 2, 0);
    }
    for(int i=120; i<180; i++){ //carrega pecas do tipo 1x4 da matriz de pecas
	if(i<130) //pretas
	MinhasPecas[i]=novaPeca(i, 0, 2, 4, 0);
	else if(i>=130 && i<140) //brancas
	MinhasPecas[i]=novaPeca(i, 1, 2, 4, 0);
	else if(i>=140 && i<150) //vermelhas
	MinhasPecas[i]=novaPeca(i, 2, 2, 4, 0);
	else if(i>=150 && i<160) //amarelas
	MinhasPecas[i]=novaPeca(i, 3, 2, 4, 0);
	else if(i>=160 && i<170) //verdes
	MinhasPecas[i]=novaPeca(i, 4, 2, 4, 0);
	else if(i>=170 && i<180) //azuis
	MinhasPecas[i]=novaPeca(i, 5, 2, 4, 0);
    }
    for(int i=180; i<240; i++){ //carrega pecas do tipo 1x8 da matriz de pecas
	if(i<190) //pretas
	MinhasPecas[i]=novaPeca(i, 0, 3, 8, 0);
	else if(i>=190 && i<200) //brancas
	MinhasPecas[i]=novaPeca(i, 1, 3, 8, 0);
	else if(i>=200 && i<210) //vermelhas
	MinhasPecas[i]=novaPeca(i, 2, 3, 8, 0);
	else if(i>=210 && i<220) //amarelas
	MinhasPecas[i]=novaPeca(i, 3, 3, 8, 0);
	else if(i>=220 && i<230) //verdes
	MinhasPecas[i]=novaPeca(i, 4, 3, 8, 0);
	else if(i>=230 && i<240) //azuis
	MinhasPecas[i]=novaPeca(i, 5, 3, 8, 0);
    }
}

int main(int argc, char** argv)
{
   auxfovy = 90; 
   auxAspect = 0.75;
   auxZNear = 10;
   auxZFar = 1600;

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowSize(800,500);
    
    glutCreateWindow("Meu Lego 1.0 : Simulador");

    carregarObjetos(); //carrega objetos modelados
    logicaJogo(); //carrega estruturas do jogo

    glutKeyboardFunc(key);

    glutIdleFunc(relogio);

    glutDisplayFunc(Desenhar);

    glutMouseFunc(rato);
    //luzes();
    glutMainLoop();

}

