#include <stdio.h>
#include <stdlib.h>

#include "bitmap.h"

#define abrir_arq_leitura(f, arq) if ((f = fopen(arq,"rb")) == NULL) { perror("Imp. ler arquivo"); exit(0); }	//Macro para abrir arquivo para leitura
#define abrir_arq_escrita(f, arq) if ((f = fopen(arq,"w")) == NULL) { perror("Imp. criar arquivo"); exit(0); }	//Macro para abrir arquivo para escrita


int main(int argc, char *argv[]) {
	FILE *fp, *fp_escrita;
	BitmapFileHeader fileHeader;
	BitmapInfoHeader infoHeader;
	byte *B;
	
	//Verifica quantidade de parâmetros
	if (argc < 2) {
		perror("Quantidade errada de parametros");
		exit(0);
	}
	
	abrir_arq_leitura(fp, argv[1]);
	
	//Lê cabeçalhos BMP
	leituraFileHeader(fp, &fileHeader);
	leituraInfoHeader(fp, &infoHeader);
	imprimirHeaders(fileHeader, infoHeader);
	fseek(fp, (fileHeader.offBits - 54), SEEK_CUR);	 //Pula palheta de cores
	
	//Verifica se imagem está dentro do padrão
	if (fileHeader.type != 0x4D42) {
		printf("Tipo de imagem precisa ser Bitmap\n");
		exit(0);
	}
	if (infoHeader.compression != 0) {
		printf("Imagem precisa ser sem compressao\n");
		exit(0);
	}
	if (infoHeader.bitCount != 8) {
		printf("Imagem precisa ser monocromatica\n");
		exit(0);
	}
	/*if (infoHeader.width != 320 || infoHeader.height > 240) {
		printf("Imagem precisa ter a dimensao de 320 x 240");
		exit(0);		
	}*/
	
	//Aloca matriz de cor
	B = (byte*) malloc((int) infoHeader.width * (int) infoHeader.height * sizeof(byte));
	
	//Lê cor da imagem
	leituraCor(fp, B, (int) infoHeader.width, (int) infoHeader.height);

	//Escreve valores dos pixels em um arquivo
	abrir_arq_escrita(fp_escrita, "pix.txt");
	escreveCorTXT(fp_escrita, B, infoHeader.width, infoHeader.height);

	//Libera memória das matrizes B
	free(B);

	//Fecha arquivo da imagem original
	fclose(fp);
	fclose(fp_escrita);
	
	return 0;
}

