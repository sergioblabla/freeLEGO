#ifndef TEXTURA_H
#define TEXTURA_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

int texture[1];

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};
typedef struct Image Image;

int ImageLoad(char *filename, Image *image) {
    FILE *file;
    unsigned long size;                 // size of the image in bytes.
    unsigned long i;                    // standard counter.
    unsigned short int planes;          // number of planes in image (must be 1) 
    unsigned short int bpp;             // number of bits per pixel (must be 24)
    char temp;                          // temporary color storage for bgr-rgb conversion.

    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL){
    	printf("File Not Found : %s\n",filename);
    	return 0;
    } 
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
    	printf("Error reading width from %s.\n", filename);
    	return 0;
    }
    if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
    	printf("Error reading height from %s.\n", filename);
    	return 0;
    }
    size = image->sizeX * image->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
    	printf("Error reading planes from %s.\n", filename);
    	return 0;
    }
    if (planes != 1) {
    	printf("Planes from %s is not 1: %u\n", filename, planes);
    	return 0;
    }
    // read the bpp
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
    	printf("Error reading bpp from %s.\n", filename);
    	return 0;
    }
    if (bpp != 24) {
    	printf("Bpp from %s is not 24: %u\n", filename, bpp);
    	return 0;
    }
    // seek past the rest of the bitmap header.
    fseek(file, 24, SEEK_CUR);
    // read the data. 
    image->data = (char *) malloc(size);
    if (image->data == NULL) {
    	printf("Error allocating memory for color-corrected image data (Erro enquanto aloca memória para uma informação de correção de cor da imagem)");
    	return 0;	
    }
    if ((i = fread(image->data, size, 1, file)) != 1) {
    	printf("Error reading image data from %s.\n (Erro ao ler informações da imagem)", filename);
    	return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
    	temp = image->data[i];
    	image->data[i] = image->data[i+2];
    	image->data[i+2] = temp;
    }
    return 1;
}

void LoadGLTextures(char *imagem) {	
    // Load Texture
    Image *image1;
    
    // allocate space for texture
    image1 = (Image *) malloc(sizeof(Image));
    if (image1 == NULL) {
    	printf("Error allocating space for image");
    	exit(0);
    }
    if (!ImageLoad(imagem, image1)) {
	   exit(1);
    }        
    // Create Texture	
    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2d texture (x and y size)
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);
};

#endif
