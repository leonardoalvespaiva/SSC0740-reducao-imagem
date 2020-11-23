#include "bitmap.h"
#include <stdlib.h>
#include <string.h>

//Lê File Header do BMP
void leituraFileHeader(FILE *fp, BitmapFileHeader* h) {
	fread(&h->type, sizeof(h->type), 1, fp);
	fread(&h->size, sizeof(h->size), 1, fp);
	fread(&h->reserved1, sizeof(h->reserved1), 1, fp);
	fread(&h->reserved2, sizeof(h->reserved2), 1, fp);
	fread(&h->offBits, sizeof(h->offBits), 1, fp);
}

//Lê Info Header do BMP
void leituraInfoHeader(FILE *fp, BitmapInfoHeader* h) {
	fread(&h->size, sizeof(h->size), 1, fp);
	fread(&h->width, sizeof(h->width), 1, fp);
	fread(&h->height, sizeof(h->height), 1, fp);
	fread(&h->planes, sizeof(h->planes), 1, fp);
	fread(&h->bitCount, sizeof(h->bitCount), 1, fp);
	fread(&h->compression, sizeof(h->compression), 1, fp);
	fread(&h->sizeImage, sizeof(h->sizeImage), 1, fp);
	fread(&h->xPixelsPerMeter, sizeof(h->xPixelsPerMeter), 1, fp);
	fread(&h->yPixelsPerMeter, sizeof(h->yPixelsPerMeter), 1, fp);
	fread(&h->colorUsed, sizeof(h->colorUsed), 1, fp);
	fread(&h->colorImportant, sizeof(h->colorImportant), 1, fp);
}

//Imprime algumas informações dos cabeçalhos
void imprimirHeaders(BitmapFileHeader fh, BitmapInfoHeader ih) {
//	printf("No. magico: %XH\n", fh.type);
	printf("Tamanho: %u\n", fh.size);
	printf("Offset dados bitmap: %u\n", fh.offBits);
	
	printf("Comprimento: %d\n", ih.width);
	printf("Altura: %d\n", ih.height);
	printf("Size image: %d\n", ih.sizeImage);
	printf("No. de cores usadas: %u\n", ih.colorUsed);
	printf("No. de bits por pixel: %u\n", ih.bitCount);
	printf("Compressao: %u\n", ih.compression);
}

//Escreve cabeçalhos BMP
void escreverHeaders(FILE *fp, BitmapFileHeader* fh, BitmapInfoHeader* ih) {
	fseek(fp, 0, SEEK_SET);
	
	//FileHeader
	fwrite(&fh->type, sizeof(fh->type), 1, fp);
	fwrite(&fh->size, sizeof(fh->size), 1, fp);
	fwrite(&fh->reserved1, sizeof(fh->reserved1), 1, fp);
	fwrite(&fh->reserved2, sizeof(fh->reserved2), 1, fp);
	fwrite(&fh->offBits, sizeof(fh->offBits), 1, fp);
	
	//InfoHeader
	fwrite(&ih->size, sizeof(ih->size), 1, fp);
	fwrite(&ih->width, sizeof(ih->width), 1, fp);
	fwrite(&ih->height, sizeof(ih->height), 1, fp);
	fwrite(&ih->planes, sizeof(ih->planes), 1, fp);
	fwrite(&ih->bitCount, sizeof(ih->bitCount), 1, fp);
	fwrite(&ih->compression, sizeof(ih->compression), 1, fp);
	fwrite(&ih->sizeImage, sizeof(ih->sizeImage), 1, fp);
	fwrite(&ih->xPixelsPerMeter, sizeof(ih->xPixelsPerMeter), 1, fp);
	fwrite(&ih->yPixelsPerMeter, sizeof(ih->yPixelsPerMeter), 1, fp);
	fwrite(&ih->colorUsed, sizeof(ih->colorUsed), 1, fp);
	fwrite(&ih->colorImportant, sizeof(ih->colorImportant), 1, fp);
}

//Lê matrizes de cores da imagem
void leituraCor(FILE *fp, byte* B, int largura, int altura) {
	int i, j;
	
	for (i = 0; i < altura; i++) {
		for (j = 0; j < largura; j++) {
			B[i*largura + j] = fgetc(fp);
		}
	}
}

//Lê matrizes de cores da imagem
void leituraCorTXT(FILE *fp, byte* B, int largura, int altura) {
	int i, j, num;
	char numero[10];
	char* linha;
	linha = (char*) malloc(1300 * sizeof(char));
	
	for (i = 0; i < altura; i++) {
		for (j = 0; j < largura; j++) {
			fscanf(fp, "%X", &num);
			B[i*largura + j] = (byte) num;
		}
	}
}

//Escreve matrizes de cores da imagem
void escreveCorTXT(FILE *fp, byte* B, int largura, int altura) {
	int i, j;
	for (i = 0; i < altura; i++) {
		for (j = 0; j < largura; j++) {
			fprintf(fp, "%X ", B[i*largura + j]);
		}
		fprintf(fp, "\n");
	}
}

//Escreve matriz de cor da imagem
void escreveCor(FILE *fp, byte* B, int largura, int altura) {
	int i, j;
	
	for (i = 0; i < altura; i++) {
		for (j = 0; j < largura; j++) {
			fputc(B[i*largura + j], fp);
		}
	}
}
