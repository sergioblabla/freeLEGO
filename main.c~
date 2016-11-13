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
int tamanho = 10; //zoom
double t = 0;
double a = 0;

//Variaveis de menu
int menu = 0; //0:bem vindo, -1:menu principal sem opcoes selecionadas, 1:menu principal, 2:jogar, 3:ajuda, 4:creditos, 5:sair
int opcao = 0;
int someseta=0; //teste sumir com ponteiro

//variaveis de começo
int jogocomecou = 0;

//variavel de luz
GLfloat ambiente[] = {1, 1, 1, 0.5};

GLfloat luz_posicao[]={800.0,800.0,800.0,0.0};
GLfloat luz_difusa[]={1, 1, 0.5,1};
GLfloat luz_especular[]={0,0.05,0.2,1};

GLfloat mat_ambiente[]={0.5,0.0,0.5,1};
GLfloat mat_difusa[]={0.1,0.7,0.5,1};
GLfloat mat_especular[]={0,0,0.5,1};

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
int delPecaId = -1;
int girarPeca = -1;

//estruturas
SetinhaAux cursor;

//gerenciamento de janela
int width=800;
int height=500;

//Cabeçalhos das funções:
void key(unsigned char , int , int );
void specialKeys(int , int , int );
static void rato(int , int , int , int );
void Desenhar();
void GerenciaPecas();
void relogio();
void carregarObjetos();
void logicaJogo();
void carregaMatrizPecas();

void specialKeys(int key, int x, int y)
{
    	// Exibe inicialmente um menu sem opções selecionadas
    	if(menu==-1)
	    menu = 1;

	switch(key)
	{

    /**********************************************************
    *                Menu Acesso Operações                    *
    ***********************************************************/
	    case GLUT_KEY_UP:
		if(opcao>0 && opcao<4 && menu==1)
	            opcao--;
		break;
	    case GLUT_KEY_DOWN:
		if(opcao>=0 && opcao<3 && menu==1)
	            opcao++;
		break;
	    case GLUT_KEY_RIGHT:
		if(opcao==0 && menu==1){
	            menu=2;
	            LoadGLTextures("Imagens/menulateral.bmp"); //carrega textura do menu lateral
	        }
	        if(opcao==1 && menu==1)
	            menu=3;
	        if(opcao==2 && menu==1)
	            menu=4;
	        if(opcao==3 && menu==1)
	            exit(0);
		break;
	    case GLUT_KEY_LEFT:
		if(menu>1)
	            menu=1;
		break;
	}

        glutPostRedisplay();
}
void key(unsigned char key, int x, int y)
{
    // Exibe inicialmente um menu sem opções selecionadas
    if(menu==-1)
	menu = 1;
    switch (key) 
    {
	
    /**********************************************************
    *                Menu Acesso Operações                    *
    ***********************************************************/
        case '+':
            if(menu==0)
	        menu=-1;
	    break;
        case '8':
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
	        LoadGLTextures("Imagens/menulateral.bmp"); //carrega textura do menu lateral
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
            break;
    /**********************************************************
    *             Tela de Partida Zoom Operações              *
    ***********************************************************/
        case 'a': //ampliar zoom
	    if(tamanho < 61 && menu==2)
                tamanho+=1;
            break;
        case 'A': //ampliar zoom
	    if(tamanho < 61 && menu==2)
                tamanho+=1;
            break;
        case 'd': //reduzir zoom
	    if(tamanho > 1 && menu==2)
                tamanho-=1;
            break;
        case 'D': //reduzir zoom
	    if(tamanho > 1 && menu==2)
                tamanho-=1;
            break;

    /**********************************************************
    *           Tela de Partida Câmera Operações              *
    ***********************************************************/
	case 'm': //rotacao extra como opcao a da funcao especial das setas do teclado
	    if(menu==2)
            	rodary+=10;
            break;
	case 'M': //rotacao extra como opcao a da funcao especial das setas do teclado
	    if(menu==2)
            	rodary+=10;
            break;
	case 'n': //rotacao contraria extra como opcao a da funcao especial das setas do teclado
	    if(menu==2)
            	rodary-=10;
            break;
	case 'N': //rotacao contraria extra como opcao a da funcao especial das setas do teclado
	    if(menu==2)
            	rodary-=10;
            break;
        case 'k': //rotacao em z 
	    if(menu==2)
            	rodarz+=10;
            break;
        case 'K': //rotacao em z 
	    if(menu==2)
            	rodarz+=10;
            break;
	case 'j': //rotacao em z
	    if(menu==2)
            	rodarz-=10;
            break;
	case 'J': //rotacao em z
	    if(menu==2)
            	rodarz-=10;
            break;
        case 'i': //rotacao em z 
	    if(menu==2)
            	rodarx+=10;
            break;
        case 'I': //rotacao em z 
	    if(menu==2)
            	rodarx+=10;
            break;
	case 'o': //rotacao em z
	    if(menu==2)
            	rodarx-=10;
            break;
	case 'O': //rotacao em z
	    if(menu==2)
            	rodarx-=10;
            break;

    /**********************************************************
    *        Tela de Partida Cursor de Peças Operações        *
    ***********************************************************/
	case 'r': //movimento em x na matriz de posicionamento global
	    if(posCursor[0]>0 && someseta==0 && menu==2)
            	posCursor[0]--; //"regrede" em relacao ao eixo x imaginado para matriz de seletor
            break;
	case 'R': //movimento em x na matriz de posicionamento global
	    if(posCursor[0]>0 && someseta==0 && menu==2)
            	posCursor[0]--; //"regrede" em relacao ao eixo x imaginado para matriz de seletor
            break;
	case 't': //rotacao em x na matriz de posicionamento global
	    if(posCursor[0]<=6 && someseta==0 && menu==2)
            	posCursor[0]++; //"avanca" em relacao ao eixo x imaginado para matriz de seletor
            break;
	case 'T': //rotacao em x na matriz de posicionamento global
	    if(posCursor[0]<=6 && someseta==0 && menu==2)
            	posCursor[0]++; //"avanca" em relacao ao eixo x imaginado para matriz de seletor
            break;
        case 'f': //rotacao em y na matriz de posicionamento global
	    if(posCursor[1]<0 && someseta==0 && menu==2)
            	posCursor[1]++; //"avanca" em relacao ao eixo y imaginado para matriz de seletor
            break;
        case 'F': //rotacao em y na matriz de posicionamento global
	    if(posCursor[1]<0 && someseta==0 && menu==2)
	        posCursor[1]++; //"avanca" em relacao ao eixo y imaginado para matriz de seletor
            break;
	case 'g': //rotacao em y na matriz de posicionamento global
	    if(posCursor[1]>=-6 && someseta==0 && menu==2)
            	posCursor[1]--; //"regrede" em relacao ao eixo y imaginado para matriz de seletor
            break;
	case 'G': //rotacao em y na matriz de posicionamento global
	    if(posCursor[1]>=-6 && someseta==0 && menu==2)
            	posCursor[1]--; //"regrede" em relacao ao eixo y imaginado para matriz de seletor
            break;
        case 'c': //rotacao em z na matriz de posicionamento global
	    if(posCursor[2]<0 && someseta==0 && menu==2)
            	posCursor[2]++; //"avanca" em relacao ao eixo z imaginado para matriz de seletor
            break;
        case 'C': //rotacao em z na matriz de posicionamento global
	    if(posCursor[2]<0 && someseta==0 && menu==2)
            	posCursor[2]++; //"avanca" em relacao ao eixo z imaginado para matriz de seletor
            break;
	case 'v': //rotacao em z na matriz de posicionamento global
	    if(posCursor[2]>=-6 && someseta==0 && menu==2)
            	posCursor[2]--; //"regrede" em relacao ao eixo z imaginado para matriz de seletor
            break;
	case 'V': //rotacao em z na matriz de posicionamento global
	    if(posCursor[2]>=-6 && someseta==0 && menu==2)
            	posCursor[2]--; //"regrede" em relacao ao eixo z imaginado para matriz de seletor
            break;

    /**********************************************************
    *           Tela de Partida Pecinhas Operações            *
    ***********************************************************/
	// Delete
        case 127: { // remover pecinhas
	    delPecaId = identificaPecaPosicao(&cursor, posCursor[0], posCursor[1], posCursor[2]);

	    if(delPecaId != -1) {
	   	deletarPeca(&cursor, delPecaId);
            	MinhasPecas[delPecaId] = apagaPeca();
		delPecaId = -1;
	    }
            break;
	}
	// Rodar Pecinha
	case 13: {
	    // Pega ID da pecinha naquela posicao
	    girarPeca = identificaPecaPosicao(&cursor, posCursor[0], posCursor[1], posCursor[2]);
	    
	    // Se não há peça alguma naquela posição, não faz nada
	    if(girarPeca == -1) {
	    } else {
		// Se pecinha tem comprimento 1, ou seja, é 1x1, não faz nada
		if(MinhasPecas[girarPeca].tamp == 1) {
		} else {
		    // Verifica se pecinha já estava rotacionada
			printf("\nRotacionada = %d\n", MinhasPecas[girarPeca].rotacionada);
		    if(MinhasPecas[girarPeca].rotacionada == 1) {
			// Verifica se há espaço naquela direção para a pecinha ser rotacionada
			if(verificaPosMatriz(&cursor, posCursor[0]+1, posCursor[1], posCursor[2], MinhasPecas[girarPeca].tamp-1, 0) == 0) { 
			    printf("\n\nOHO\n\n");

			    MinhasPecas[girarPeca] = rotacionaPeca(&MinhasPecas[girarPeca], 0);

			    switch(MinhasPecas[girarPeca].tamp) {
			    	case 2:
				    MinhasPecas[girarPeca] = alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2])*2-1);
				    break;
			    	case 4:
				    MinhasPecas[girarPeca] = alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2])*2-3);
				    break;
			    	case 8:
				    MinhasPecas[girarPeca] = alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2])*2-7);
				    break;
			    }

	   		    deletarPeca(&cursor, girarPeca);

			    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], MinhasPecas[girarPeca].tamp, 0, girarPeca);

			}
		    } else {
		    // Não estava rotacionada
			if(verificaPosMatriz(&cursor, posCursor[0]-1, posCursor[1], posCursor[2], MinhasPecas[girarPeca].tamp-1, 1) == 0) { 
			    printf("\n\nYEY\n\n");

			    MinhasPecas[girarPeca] = rotacionaPeca(&MinhasPecas[girarPeca], 1);

			    switch(MinhasPecas[girarPeca].tamp) {
			    	case 2:
				    MinhasPecas[girarPeca] = alteraTransladoPeca(-(posCursor[2])*2, (posCursor[1]+0.25)*2, (posCursor[0])*2-1);
				    break;
			    	case 4:
				    MinhasPecas[girarPeca] = alteraTransladoPeca(-(posCursor[2])*2, (posCursor[1]+0.25)*2, (posCursor[0])*2-3);
				    break;
			    	case 8:
				    MinhasPecas[girarPeca] = alteraTransladoPeca(-(posCursor[2])*2, (posCursor[1]+0.25)*2, (posCursor[0])*2-7);
				    break;
			    }

	   		    deletarPeca(&cursor, girarPeca);

			    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], MinhasPecas[girarPeca].tamp, 1, girarPeca);
			}
		    }
		}
	    //printf("\nGirarPeca=%d, Pecasadd=%d\n", girarPeca, pecasadd);
		girarPeca = -1;
	    }
	    //printf("\nPosicao Trans: (%.3f,%.3f,%.3f)\n", (posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2])*2);
	    break;
	}
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

    /**********************************************************
    *                 Jogo: Extra Operações                   *
    ***********************************************************/
	case 'q': //sair
            exit(0);
            break;
	case 'Q': //sair
            exit(0);
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
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 1, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 1, 0, pecasadd);
            MinhasPecas[pecasadd]=novaPeca(pecasadd, 0, 0, 1, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2])*2); //blocotipo0
	    pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } else if(estado==GLUT_DOWN && x>=642 && x<=670 && y>=48 && y<=80 && seguraPeca==0){
//adicionar peça 1x1 branca
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 1, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 1, 0, pecasadd);
	    MinhasPecas[pecasadd]=novaPeca(pecasadd, 1, 0, 1, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2])*2); //blocotipo0
            pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } else if(estado==GLUT_DOWN && x>=673 && x<=700 && y>=48 && y<=80 && seguraPeca==0){
//adicionar peça 1x1 vermelha
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 1, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 1, 0, pecasadd);
	    MinhasPecas[pecasadd]=novaPeca(pecasadd, 2, 0, 1, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2])*2); //blocotipo0
	    pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } else if(estado==GLUT_DOWN && x>=703 && x<=730 && y>=48 && y<=80 && seguraPeca==0){
//adicionar peça 1x1 amarela
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 1, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 1, 0, pecasadd);
	    MinhasPecas[pecasadd]=novaPeca(pecasadd, 3, 0, 1, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2])*2); //blocotipo0
	    pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } else if(estado==GLUT_DOWN && x>=734 && x<=763 && y>=48 && y<=80 && seguraPeca==0){
//adicionar peça 1x1 verde
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 1, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 1, 0, pecasadd);
	    MinhasPecas[pecasadd]=novaPeca(pecasadd, 4, 0, 1, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2])*2); //blocotipo0
	    pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } else if(estado==GLUT_DOWN && x>=767 && x<=800 && y>=48 && y<=80 && seguraPeca==0){
//adicionar peça 1x1 azul
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 1, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 1, 0, pecasadd);
	    MinhasPecas[pecasadd]=novaPeca(pecasadd, 5, 0, 1, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2])*2); //blocotipo0
	    pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } 
//
//adicionar peças 1x2:
//
    else if(estado==GLUT_DOWN && x>=608 && x<=635 && y>=100 && y<=128 && seguraPeca==0){
//adicionar peça 1x2 preta
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 2, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 2, 0, pecasadd);
	    MinhasPecas[pecasadd]=novaPeca(pecasadd, 0, 1, 2, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-0.5)*2); //blocotipo1
	    pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } else if(estado==GLUT_DOWN && x>=642 && x<=670 && y>=100 && y<=128 && seguraPeca==0){
//adicionar peça 1x2 branca
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 2, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 2, 0, pecasadd);
	    MinhasPecas[pecasadd]=novaPeca(pecasadd, 1, 1, 2, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-0.5)*2); //blocotipo1
	    pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } else if(estado==GLUT_DOWN && x>=673 && x<=700 && y>=100 && y<=128 && seguraPeca==0){
//adicionar peça 1x2 vermelha
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 2, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 2, 0, pecasadd);
	    MinhasPecas[pecasadd]=novaPeca(pecasadd, 2, 1, 2, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-0.5)*2); //blocotipo1
	    pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } else if(estado==GLUT_DOWN && x>=703 && x<=730 && y>=100 && y<=128 && seguraPeca==0){
//adicionar peça 1x2 amarela
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 2, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 2, 0, pecasadd);
	    MinhasPecas[pecasadd]=novaPeca(pecasadd, 3, 1, 2, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-0.5)*2); //blocotipo1
	    pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } else if(estado==GLUT_DOWN && x>=734 && x<=763 && y>=100 && y<=128 && seguraPeca==0){
//adicionar peça 1x2 verde
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 2, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 2, 0, pecasadd);
	    MinhasPecas[pecasadd]=novaPeca(pecasadd, 4, 1, 2, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-0.5)*2); //blocotipo1
	    pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } else if(estado==GLUT_DOWN && x>=767 && x<=800 && y>=100 && y<=128 && seguraPeca==0){
//adicionar peça 1x2 azul
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 2, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 2, 0, pecasadd);
	    MinhasPecas[pecasadd]=novaPeca(pecasadd, 5, 1, 2, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-0.5)*2); //blocotipo1
	    pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } 
//
//adicionar peças 1x4:
//
    else if(estado==GLUT_DOWN && x>=608 && x<=635 && y>=142 && y<=180 && seguraPeca==0){
//adicionar peça 1x4 preta
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 4, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 4, 0, pecasadd);
	    MinhasPecas[pecasadd]=novaPeca(pecasadd, 0, 2, 4, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-1.5)*2); //blocotipo2
	    pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } else if(estado==GLUT_DOWN && x>=642 && x<=670 && y>=142 && y<=180 && seguraPeca==0){
//adicionar peça 1x4 branca
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 4, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 4, 0, pecasadd);
	    MinhasPecas[pecasadd]=novaPeca(pecasadd, 1, 2, 4, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-1.5)*2); //blocotipo2
	    pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } else if(estado==GLUT_DOWN && x>=673 && x<=700 && y>=142 && y<=180 && seguraPeca==0){
//adicionar peça 1x4 vermelha
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 4, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 4, 0, pecasadd);
	    MinhasPecas[pecasadd]=novaPeca(pecasadd, 2, 2, 4, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-1.5)*2); //blocotipo2
	    pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } else if(estado==GLUT_DOWN && x>=703 && x<=730 && y>=142 && y<=180 && seguraPeca==0){
//adicionar peça 1x4 amarela
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 4, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 4, 0, pecasadd);
	    MinhasPecas[pecasadd]=novaPeca(pecasadd, 3, 2, 4, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-1.5)*2); //blocotipo2
	    pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } else if(estado==GLUT_DOWN && x>=734 && x<=763 && y>=142 && y<=180 && seguraPeca==0){
//adicionar peça 1x4 verde
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 4, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 4, 0, pecasadd);
	    MinhasPecas[pecasadd]=novaPeca(pecasadd, 4, 2, 4, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-1.5)*2); //blocotipo2
	    pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } else if(estado==GLUT_DOWN && x>=767 && x<=800 && y>=142 && y<=180 && seguraPeca==0){
//adicionar peça 1x4 azul
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 4, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 4, 0, pecasadd);
	    MinhasPecas[pecasadd]=novaPeca(pecasadd, 5, 2, 4, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-1.5)*2); //blocotipo2
	    pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } 
//
//adicionar peças 1x8:
//
    else if(estado==GLUT_DOWN && x>=608 && x<=635 && y>=190 && y<=242 && seguraPeca==0){
//adicionar peça 1x8 preta
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 8, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 8, 0, pecasadd);
	    MinhasPecas[pecasadd]=novaPeca(pecasadd, 0, 3, 8, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-3.5)*2); //blocotipo3
	    pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } else if(estado==GLUT_DOWN && x>=642 && x<=670 && y>=190 && y<=242 && seguraPeca==0){
//adicionar peça 1x8 branca
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 8, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 8, 0, pecasadd);
	    MinhasPecas[pecasadd]=novaPeca(pecasadd, 1, 3, 8, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-3.5)*2); //blocotipo3
	    pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } else if(estado==GLUT_DOWN && x>=673 && x<=700 && y>=190 && y<=242 && seguraPeca==0){
//adicionar peça 1x8 vermelha
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 8, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 8, 0, pecasadd);
	    MinhasPecas[pecasadd]=novaPeca(pecasadd, 2, 3, 8, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-3.5)*2); //blocotipo3
	    pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } else if(estado==GLUT_DOWN && x>=703 && x<=730 && y>=190 && y<=242 && seguraPeca==0){
//adicionar peça 1x8 amarela
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 8, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 8, 0, pecasadd);
	    MinhasPecas[pecasadd]=novaPeca(pecasadd, 3, 3, 8, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-3.5)*2); //blocotipo3
	    pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } else if(estado==GLUT_DOWN && x>=734 && x<=763 && y>=190 && y<=242 && seguraPeca==0){
//adicionar peça 1x8 verde
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 8, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 8, 0, pecasadd);
	    MinhasPecas[pecasadd]=novaPeca(pecasadd, 4, 3, 8, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-3.5)*2); //blocotipo3
	    pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } else if(estado==GLUT_DOWN && x>=767 && x<=800 && y>=190 && y<=242 && seguraPeca==0){
//adicionar peça 1x8 azul
	if(verificaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 8, 0) == 0) { 
	    ocupaPosMatriz(&cursor, posCursor[0], posCursor[1], posCursor[2], 8, 0, pecasadd);
	    MinhasPecas[pecasadd]=novaPeca(pecasadd, 5, 3, 8, 1, 0);
            MinhasPecas[pecasadd]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-3.5)*2); //blocotipo3
	    pecasadd++;
	    cursor.pecaSel=999; //modo nova peca
	    seguraPeca=0;
	}
    } 
    printf("\nPosicao do mouse: %d, %d", x, y);
    glutPostRedisplay();
}


        //MinhasPecas[blocotipo1]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-0.5)*2); //blocotipo1
        //MinhasPecas[blocotipo0]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-1.5)*2); //blocotipo2
	//MinhasPecas[blocotipo0]=alteraTransladoPeca((posCursor[0])*2, (posCursor[1]+0.25)*2, (posCursor[2]-3.5)*2); //blocotipo3

void Desenhar(){
    //usa como velocidade uma divisao relativa a hora atual e armazena em constante
    /*const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;*/

    switch (menu) {
    case 0: //primeira tela ao abrir jogo
    glPushMatrix();	//desempilha
    LoadGLTextures("Imagens/bemvindo.bmp");				// Load The Texture(s) 
    glEnable(GL_TEXTURE_2D);			// Enable Texture Mapping
    glClearColor(0, 0, 0, 0);			// Limpa a cor de fundo para preto 
    glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);			// The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
    glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
    
    glColor3d(1,1,1); // Cor do desenho (branco)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpar buffer de cor
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50,50,-50,50); 
    glMatrixMode(GL_MODELVIEW);

    glBindTexture(GL_TEXTURE_2D, texture[0]);   // choose the texture to use.

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-50.0f, -50.0f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex2f( 50.0f, -50.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex2f( 50.0f,  50.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-50.0f,  50.0f);	// Top Left Of The Texture and Quad
    glEnd();
    break;
    case -1://exibe um menu sem opcoes selecionadas
    glPushMatrix();	//desempilha
    LoadGLTextures("Imagens/mp.bmp");				// Load The Texture(s) 
    glEnable(GL_TEXTURE_2D);			// Enable Texture Mapping
    glClearColor(0, 0, 0, 0);			// Limpa a cor de fundo para preto 
    glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);			// The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
    glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
    
    glColor3d(1,1,1); // Cor do desenho (branco)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpar buffer de cor
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50,50,-50,50); 
    glMatrixMode(GL_MODELVIEW);

    glBindTexture(GL_TEXTURE_2D, texture[0]);   // choose the texture to use.

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-50.0f, -50.0f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex2f( 50.0f, -50.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex2f( 50.0f,  50.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-50.0f,  50.0f);	// Top Left Of The Texture and Quad
    glEnd();
    break;
    case 1: 
    /*                                                     */
    /*            M E N U    P R I N C I P A L             */
    /*                                                     */

	switch(opcao){
    	case 0:
		LoadGLTextures("Imagens/mp1.bmp");				// Load The Texture(s)
		break;
    	case 1:
		LoadGLTextures("Imagens/mp2.bmp");				// Load The Texture(s)
		break;
    	case 2:
		LoadGLTextures("Imagens/mp3.bmp");				// Load The Texture(s)
		break;
    	case 3:
		LoadGLTextures("Imagens/mp4.bmp");				// Load The Texture(s)
		break;
	}

	glEnable(GL_TEXTURE_2D);			// Enable Texture Mapping
    	glClearColor(0, 0, 0, 0);			// Limpa a cor de fundo para preto 
    	glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    	glDepthFunc(GL_LESS);			// The Type Of Depth Test To Do
    	glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
    	glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
    
    	glColor3d(1,1,1); // Cor do desenho (branco)
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpar buffer de cor
    
    	glViewport(0,0,width,height);

    	glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
    	gluOrtho2D(-50,50,-50,50); 
    	glMatrixMode(GL_MODELVIEW);

	// Luz Ambiente	
	GLfloat ambiente[4]={1.0,1.0,1.0,1.0}; 
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente); 

    	glBindTexture(GL_TEXTURE_2D, texture[0]);   // choose the texture to use.

    	glBegin(GL_QUADS);
    		glTexCoord2f(0.0f, 0.0f); glVertex2f(-50.0f, -50.0f);	// Bottom Left Of The Texture and Quad
    		glTexCoord2f(1.0f, 0.0f); glVertex2f( 50.0f, -50.0f);	// Bottom Right Of The Texture and Quad
    		glTexCoord2f(1.0f, 1.0f); glVertex2f( 50.0f,  50.0f);	// Top Right Of The Texture and Quad
    		glTexCoord2f(0.0f, 1.0f); glVertex2f(-50.0f,  50.0f);	// Top Left Of The Texture and Quad
    	glEnd();
    glPopMatrix();	//desempilha
	break; //fim do menu principal
    case 2:
    /*                                                     */
    /*                   J   O   G    O                    */
    /*                                                     */


    glPushMatrix();	//empilha

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpar buffer de cor
    glClearColor(0,0,0,0); //Cor de fundo (preto)
    glColor3d(0,0,0); // Cor do desenho (preto)

    /**********************************************************
    *                   Iluminacao                            *
    ***********************************************************/
	// Luz Ambiente	
	GLfloat lAmbiente[4]={0.2,0.2,0.2,1.0}; 

	GLfloat lDifusa[4]={0.7,0.7,0.7,1.0};	   // "cor" 
	GLfloat lEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
	GLfloat lposicao[4]={-460, -500, 400, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;

	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a refletância do material 
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS, especMaterial);

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, lAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, lEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, lposicao );

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);  
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST); //ativa zBuffer

    //Fim
/*
    //glEnable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);			// Enable Texture Mapping
    glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    //glDisable(GL_DEPTH_TEST);			// Enables Depth Testing
    glClear(GL_COLOR_BUFFER_BIT); //Limpar buffer de cor

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();*/

    glViewport(0,0,width*0.75,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-800,800,-800,800,100,1500);
    //glFrustum(-10,10,-10,10,1,100);
    //glOrtho(-800,800,-800,800,-1500,1500); 
    // Ativa Projeção Perspectiva
    gluPerspective(90, 0.75, 10, 1600);
    //Posiciona a Câmera
    gluLookAt(0,160,200, 0,0,0, 0,1,0);
/*
    //glEnable(GL_DEPTH_TEST); //ativa zBuffer

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();*/

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
    glColor3d(0,1,0);
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

    GerenciaPecas();

    jogocomecou=jogocomecou+1;
    glPopMatrix();	//desempilha

    glDrawBuffer(GL_BACK); //buffer de tras

    glPushMatrix();	//empilha
    glViewport(width*0.75,0,width*0.25,height);

    // A textura do Menu Lateral deve ser exibida sem efeitos de luz
    // Assim, a luz ambiente deve emitir 100% de intensidade	
    lAmbiente[0] = lAmbiente[1] = lAmbiente[2] = lAmbiente[3] = 1.0;
    glLightfv(GL_LIGHT0, GL_AMBIENT, lAmbiente); 

    glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
    gluOrtho2D(-50,50,-50,50); 
    glMatrixMode(GL_MODELVIEW);
    
    glEnable(GL_TEXTURE_2D);			// Enable Texture Mapping
    //glClearColor(1, 0, 0, 0);			// Limpa a cor de fundo para vermelho 
    //glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);			// The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
    glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
    
    glColor3d(1,1,1); // Cor do desenho (branco)
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
    break;
    case 3:
    glPushMatrix();	//empilha
    LoadGLTextures("Imagens/legopc2.bmp");				// Load The Texture(s) 
    glEnable(GL_TEXTURE_2D);			// Enable Texture Mapping
    glClearColor(0, 1, 0, 0);			// Limpa a cor de fundo para verde 
    glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);			// The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
    glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
    
    glColor3d(1,1,1); // Cor do desenho (branco)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpar buffer de cor
    
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
    gluOrtho2D(-50,50,-50,50); 
    glMatrixMode(GL_MODELVIEW);

    glBindTexture(GL_TEXTURE_2D, texture[0]);   // choose the texture to use.

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-50.0f, -50.0f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex2f( 50.0f, -50.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex2f( 50.0f,  50.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-50.0f,  50.0f);	// Top Left Of The Texture and Quad
    glEnd();    
    glPopMatrix();	//desempilha
    break;
    case 4:
    glPushMatrix();	//desempilha
    LoadGLTextures("Imagens/legopc3.bmp");				// Load The Texture(s) 
    glEnable(GL_TEXTURE_2D);			// Enable Texture Mapping
    glClearColor(1, 0, 0, 0);			// Limpa a cor de fundo para vermelho 
    glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);			// The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
    glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
    
    glColor3d(1,1,1); // Cor do desenho (branco)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpar buffer de cor
    
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
    gluOrtho2D(-50,50,-50,50); 
    glMatrixMode(GL_MODELVIEW);

    glBindTexture(GL_TEXTURE_2D, texture[0]);   // choose the texture to use.

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-50.0f, -50.0f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex2f( 50.0f, -50.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex2f( 50.0f,  50.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-50.0f,  50.0f);	// Top Left Of The Texture and Quad
    glEnd();
    glPopMatrix();	//desempilha
    break;
 }
glutSwapBuffers();

    //printf("\nPosição do Mouse Atual: (%.0f,%.0f,%.0f)", posCursor[0], -posCursor[1], -posCursor[2]);
}

void GerenciaPecas(){ //IMPRIME AS PEÇAS QUE DEVEM SER EXIBIDAS
    for(int ax=0; ax<240; ax++) {
	if(MinhasPecas[ax].exibir == 1) {
	    imprimirPeca(MinhasPecas[ax]);
	}
    }

    glutPostRedisplay();
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
    //carregaMatrizPecas();
    printf("\n Balde de Lego adquirido com sucesso! :D ");
}

void carregaMatrizPecas(){
    for(int i=0; i<60; i++){ //carrega pecas do tipo 1x1 da matriz de pecas
	if(i<10) //pretas
	MinhasPecas[i]=novaPeca(i, 0, 0, 1, 0, 0);
	else if(i>=10 && i<20) //brancas
	MinhasPecas[i]=novaPeca(i, 1, 0, 1, 0, 0);
	else if(i>=20 && i<30) //vermelhas
	MinhasPecas[i]=novaPeca(i, 2, 0, 1, 0, 0);
	else if(i>=30 && i<40) //amarelas
	MinhasPecas[i]=novaPeca(i, 3, 0, 1, 0, 0);
	else if(i>=40 && i<50) //verdes
	MinhasPecas[i]=novaPeca(i, 4, 0, 1, 0, 0);
	else if(i>=50 && i<60) //azuis
	MinhasPecas[i]=novaPeca(i, 5, 0, 1, 0, 0);
    }
    for(int i=60; i<120; i++){ //carrega pecas do tipo 1x2 da matriz de pecas
	if(i<70) //pretas
	MinhasPecas[i]=novaPeca(i, 0, 1, 2, 0, 0);
	else if(i>=70 && i<80) //brancas
	MinhasPecas[i]=novaPeca(i, 1, 1, 2, 0, 0);
	else if(i>=80 && i<90) //vermelhas
	MinhasPecas[i]=novaPeca(i, 2, 1, 2, 0, 0);
	else if(i>=90 && i<100) //amarelas
	MinhasPecas[i]=novaPeca(i, 3, 1, 2, 0, 0);
	else if(i>=100 && i<110) //verdes
	MinhasPecas[i]=novaPeca(i, 4, 1, 2, 0, 0);
	else if(i>=110 && i<120) //azuis
	MinhasPecas[i]=novaPeca(i, 5, 1, 2, 0, 0);
    }
    for(int i=120; i<180; i++){ //carrega pecas do tipo 1x4 da matriz de pecas
	if(i<130) //pretas
	MinhasPecas[i]=novaPeca(i, 0, 2, 4, 0, 0);
	else if(i>=130 && i<140) //brancas
	MinhasPecas[i]=novaPeca(i, 1, 2, 4, 0, 0);
	else if(i>=140 && i<150) //vermelhas
	MinhasPecas[i]=novaPeca(i, 2, 2, 4, 0, 0);
	else if(i>=150 && i<160) //amarelas
	MinhasPecas[i]=novaPeca(i, 3, 2, 4, 0, 0);
	else if(i>=160 && i<170) //verdes
	MinhasPecas[i]=novaPeca(i, 4, 2, 4, 0, 0);
	else if(i>=170 && i<180) //azuis
	MinhasPecas[i]=novaPeca(i, 5, 2, 4, 0, 0);
    }
    for(int i=180; i<240; i++){ //carrega pecas do tipo 1x8 da matriz de pecas
	if(i<190) //pretas
	MinhasPecas[i]=novaPeca(i, 0, 3, 8, 0, 0);
	else if(i>=190 && i<200) //brancas
	MinhasPecas[i]=novaPeca(i, 1, 3, 8, 0, 0);
	else if(i>=200 && i<210) //vermelhas
	MinhasPecas[i]=novaPeca(i, 2, 3, 8, 0, 0);
	else if(i>=210 && i<220) //amarelas
	MinhasPecas[i]=novaPeca(i, 3, 3, 8, 0, 0);
	else if(i>=220 && i<230) //verdes
	MinhasPecas[i]=novaPeca(i, 4, 3, 8, 0, 0);
	else if(i>=230 && i<240) //azuis
	MinhasPecas[i]=novaPeca(i, 5, 3, 8, 0, 0);
    }
}

int main(int argc, char** argv)
{
   
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowSize(width,height);

    glutCreateWindow("free LEGO 1.0 : Simulador");

    carregarObjetos(); //carrega objetos modelados
    logicaJogo(); //carrega estruturas do jogo

    glutKeyboardFunc(key);
    glutSpecialFunc(specialKeys);

    glutIdleFunc(relogio);
    glutDisplayFunc(Desenhar);

    glutMouseFunc(rato);

    glutMainLoop();

}

