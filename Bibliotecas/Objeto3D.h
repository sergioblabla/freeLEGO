#ifndef OBJETO3D_H
#define OBJETO3D_H

typedef struct ponto Ponto;
typedef struct normal Normal;
typedef struct faceT FaceT;
typedef struct faceQ FaceQ;
typedef struct objeto3D Objeto3D;

struct ponto {
    float x, y, z; // Coordenadas de um ponto no espaço
};

struct normal {
    float x, y, z; // Coordenadas de um vetor normal no espaço
};


struct faceT {
    struct ponto p1, p2, p3; // Armazena os 3 pontos que formam a face
    struct normal nl; // Armazena a normal da face
    struct faceT* prox; // Aponta para o próximo da lista encadeada
};

struct faceQ {
    struct ponto p1, p2, p3, p4; // Armazena os 4 pontos que formam a face
    struct normal nl; // Armazena a normal da face
    struct faceQ* prox; // Aponta para o próximo da lista encadeada
};

struct objeto3D {
    struct faceT *t; // Aponta para o início da lista de faces triangulares
    struct faceQ *q; // Aponta para o início da lista de faces quadriláteras
};

void carregar(Objeto3D *,char *);
void imprimir(Objeto3D);
void inserir_faceT(FaceT **, Ponto, Ponto, Ponto, Normal);
void inserir_faceQ(FaceQ **, Ponto, Ponto, Ponto, Ponto, Normal);

/* Preenche as informações de um Objeto3D com os dados presentes no arquivo */
void carregar(Objeto3D *objeto3D, char *arquivo) {

    FILE *f; // Arquivo de entrada
    fpos_t pos; // Marcador de posição
    char aux;

    int p = 0, i = 0, n = 0, k = 0; // Contadores
    int id1, id2, id3, id4, idn; // Identificadores dos pontos no vetor de pontos e do vetor de normal
    float x, y, z; // Coordenadas de um ponto

    objeto3D->t = 0;
    objeto3D->q = 0;

    f = fopen(arquivo, "r");
    if (!f) {
        printf("Nao foi possivel abrir o arquivo\n");
        return;
    }

    /* Pula as quatro linhas iniciais */
    while(fgetc(f) != '\n');
    while(fgetc(f) != '\n');
    while(fgetc(f) != '\n');
    while(fgetc(f) != '\n');

    fgetpos (f, &pos); // Armazena a posição do ponteiro de leitura

    /*Contagem dos pontos presentes no arquivo */
    while(1) {
        aux = fgetc(f);
        if(aux == 'u'){
            break;
        }
        if(aux == 'v') { // Se o caractere é 'v'
            aux = fgetc(f);
            if(aux == 'n') { // Se o caractere que segue a quebra de linha não é 'v'
                n++;
            }  
            else{
                p++;
            }
        }
    }

    fsetpos (f, &pos); // Retorna para o início da descrição dos pontos

    Ponto pontos[p]; // Criação de um vetor de pontos a partir do número de pontos lidos
    Normal normal[n]; // Criação de um vetor de vetores normais a partir do número de vn lidos

    /* Armazena todos os pontos contidos no arquivo de entrada */
    while(i != p) {
        aux = fgetc(f);
        fscanf(f, "%f %f %f\n", &pontos[i].x, &pontos[i].y, &pontos[i].z);
        i++;
    }
    
    while(k != n) {
        aux = fgetc(f);
        aux = fgetc(f);
        fscanf(f, "%f %f %f\n", &normal[k].x, &normal[k].y, &normal[k].z);
        k++;
    }

     /* Pula duas linhas */
    while(fgetc(f) != '\n');
    while(fgetc(f) != '\n');

	while(1) {
		n = 0;
		aux = fgetc(f);
		if(aux != 'f') break; // O caractere 'f' indica que se segue uma descrição de uma face

		fgetpos (f, &pos); // Armazena a posição do ponteiro de leitura
		
		while(aux != '\n') {// Enquanto não chegar ao fim da linha
			aux = fgetc(f);
			if(aux == ' ') {
				n++; // Cada caractere ' ' representa mais um ponto que compõe a face descrita na linha atual
			}
		}

		fsetpos(f, &pos); // Retorna para o início da linha

		if(n == 3) { // Caso a face seja composta por 3 pontos
			fscanf(f, "%d//%d %d//%d %d//%d\n", &id1, &idn, &id2, &idn, &id3, &idn); // Armazena os identificadores dos pontos
			inserir_faceT(&objeto3D->t, pontos[id1-1], pontos[id2-1], pontos[id3-1], normal[idn-1]); // Insere uma face triangular na lista do objeto
		}
		else { // Caso a face seja composta por 4 pontos
			fscanf(f, "%d//%d %d//%d %d//%d %d//%d\n", &id1, &idn, &id2, &idn, &id3, &idn, &id4, &idn); // Armazena os identificadores dos pontos
			inserir_faceQ(&objeto3D->q, pontos[id1-1], pontos[id2-1], pontos[id3-1], pontos[id4-1], normal[idn-1]); // Insere uma face quadrilátera na lista do objeto
		}

	}

	fclose(f);
}

void imprimir(Objeto3D objeto3D) {
    FaceT *t = objeto3D.t;
    FaceQ *q = objeto3D.q;
    
    float auxNorma = 0;

    glBegin(GL_TRIANGLES);
    while(t) {
        glNormal3f(t->nl.x, t->nl.y, t->nl.z); 
        glVertex3f(t->p1.x, t->p1.y, t->p1.z);
        glNormal3f(t->nl.x, t->nl.y, t->nl.z);
        glVertex3f(t->p2.x, t->p2.y, t->p2.z);
        glNormal3f(t->nl.x, t->nl.y, t->nl.z);
        glVertex3f(t->p3.x, t->p3.y, t->p3.z);

        t = t->prox;
    }
    glEnd();

    glBegin(GL_QUADS);
    while(q) {
        glTexCoord2f(0, 0);
        glVertex3f(q->p1.x, q->p1.y, q->p1.z);
        glTexCoord2f(0, 1);
        glVertex3f(q->p2.x, q->p2.y, q->p2.z);
        glTexCoord2f(1, 1);
        glVertex3f(q->p3.x, q->p3.y, q->p3.z);
        glTexCoord2f(1, 0); 
        glVertex3f(q->p4.x, q->p4.y, q->p4.z);

        q = q->prox;
    }
    glEnd();

}

/* Insere uma face quadrilátera na lista de um objeto */
void inserir_faceQ(FaceQ **q, Ponto p1, Ponto p2, Ponto p3, Ponto p4, Normal nl) {

    FaceQ *novo = (FaceQ *)malloc(sizeof(FaceQ));
    if(!novo) return;

    // Atibuição dos pontos à nova face
    novo->p1.x = p1.x;
    novo->p1.y = p1.y;
    novo->p1.z = p1.z;

    novo->p2.x = p2.x;
    novo->p2.y = p2.y;
    novo->p2.z = p2.z;

    novo->p3.x = p3.x;
    novo->p3.y = p3.y;
    novo->p3.z = p3.z;

    novo->p4.x = p4.x;
    novo->p4.y = p4.y;
    novo->p4.z = p4.z;

    novo->nl.x = nl.x;
    novo->nl.y = nl.y;
    novo->nl.z = nl.z;

    // Inserção no início da lista
    novo->prox = *q;
    *q = novo;

}

/* Insere uma face triangular na lista de um objeto */
void inserir_faceT(FaceT **t, Ponto p1, Ponto p2, Ponto p3, Normal nl) {

    FaceT *novo = (FaceT *)malloc(sizeof(FaceT));
    if(!novo) return;

    // Atibuição dos pontos à nova face
    novo->p1.x = p1.x;
    novo->p1.y = p1.y;
    novo->p1.z = p1.z;

    novo->p2.x = p2.x;
    novo->p2.y = p2.y;
    novo->p2.z = p2.z;

    novo->p3.x = p3.x;
    novo->p3.y = p3.y;
    novo->p3.z = p3.z;

    novo->nl.x = nl.x;
    novo->nl.y = nl.y;
    novo->nl.z = nl.z;

    // Inserção no início da lista
    novo->prox = *t;
    *t = novo;

}

#endif
