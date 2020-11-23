#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bitmap.h"

#define abrir_arq_leitura(f, arq) if ((f = fopen(arq,"rb")) == NULL) { perror("Imp. ler arquivo"); exit(0); }	//Macro para abrir arquivo para leitura
#define abrir_arq_leitura_TXT(f, arq) if ((f = fopen(arq,"r")) == NULL) { perror("Imp. ler arquivo"); exit(0); }	//Macro para abrir arquivo para leitura de TXT
#define abrir_arq_escrita(f, arq) if ((f = fopen(arq,"wb")) == NULL) { perror("Imp. criar arquivo"); exit(0); }	//Macro para abrir arquivo para escrita


int main(int argc, char *argv[]) {
	FILE *fp, *fp_escrita;
	BitmapFileHeader fileHeader;
	BitmapInfoHeader infoHeader;
	int  largura, altura, tam_paleta;
	float fator;
	byte *B;
	
	//Verifica quantidade de parâmetros
	if (argc < 4) {
		perror("Quantidade errada de parametros");
		exit(0);
	}
	
	//Abre imagem original para copiar headers
	abrir_arq_leitura(fp, argv[1]);
	
	//Lê headers BMP
	leituraFileHeader(fp, &fileHeader);
	leituraInfoHeader(fp, &infoHeader);
	imprimirHeaders(fileHeader, infoHeader);
	
	//Paleta de cores
	tam_paleta = (fileHeader.offBits - 54);
	byte* paleta = (byte*) malloc(sizeof(byte) * tam_paleta);
	fread(paleta, sizeof(byte), tam_paleta, fp);
	
	fclose(fp);
	
	//Fator de redução e novas dimensões
	fator = atof(argv[3]);
	largura = (int) infoHeader.width * fator;
	altura = (int) infoHeader.height * fator;
	//printf("\n %f %d %d", fator, largura, altura);

	//Aloca matriz de cor
	B = (byte*) malloc((int) largura * (int) altura * sizeof(byte));

	//Lê cor do arquivo TXT
	abrir_arq_leitura_TXT(fp, argv[2]);
	leituraCorTXT(fp, B, largura, altura);
	fclose(fp);
	
	//Escreve figura na saída
	abrir_arq_escrita(fp_escrita, "redux.bmp");
	
	//Atualiza header
	fileHeader.size = fileHeader.offBits + largura * altura;
	infoHeader.sizeImage = largura * altura;
	infoHeader.width = largura;
	infoHeader.height = altura;
	putchar('\n');
	imprimirHeaders(fileHeader, infoHeader);
	escreverHeaders(fp_escrita, &fileHeader, &infoHeader);		//Escreve headers
	fwrite(paleta, sizeof(byte), tam_paleta, fp_escrita);	//Escreve paleta
	escreveCor(fp_escrita, B, largura, altura); 				//Escreve cor
	
	//Fecha arquivo descompactado
	fclose(fp_escrita);
	
	//Libera memória das matriz B
	free(B);
	
	return 0;
}
