#ifndef BITMAP_H
#define BITMAP_H

#include <stdio.h>

#ifndef BYTE
#define BYTE
typedef unsigned char byte;		//Facilita a escrita e o entendimento do código
#endif

typedef struct {
	unsigned short type;			//No. mágico do arquivo
	unsigned int size;				//Tamanho do arquivo
	unsigned short reserved1;		//Reservado
	unsigned short reserved2;		//Reservado
	unsigned int offBits;			//Offset dos dados bitmap
} BitmapFileHeader;

typedef struct {
	unsigned int size;				//Tamanho do info header
	int width;						//Comprimento da imagem
	int height;						//Altura da imagem
	unsigned short planes;			//No. de planos de cor
	unsigned short bitCount;		//No. de bits por pixel
	unsigned int compression;		//Tipo de Compressão
	unsigned int sizeImage;			//Tamanho dos dados da imagem
	int xPixelsPerMeter;			//pixels X por metro
	int yPixelsPerMeter;			//pixels Y por metro
	unsigned int colorUsed;			//No. de cores usadas
	unsigned int colorImportant;	// No. de cores importantes
} BitmapInfoHeader;

void leituraFileHeader(FILE *fp, BitmapFileHeader* h); 
void leituraInfoHeader(FILE *fp, BitmapInfoHeader* h);
void imprimirHeaders(BitmapFileHeader fh, BitmapInfoHeader ih);
void escreverHeaders(FILE *fp, BitmapFileHeader* fh, BitmapInfoHeader* ih);
void leituraCor(FILE *fp, byte* B, int largura, int altura);
void leituraCorTXT(FILE *fp, byte* B, int largura, int altura);
void escreveCorTXT(FILE *fp, byte* B, int largura, int altura);
void escreveCor(FILE *fp, byte* B, int largura, int altura);

#endif
