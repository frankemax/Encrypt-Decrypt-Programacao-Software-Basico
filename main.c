#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// Para usar strings

// SOIL é a biblioteca para leitura das imagens
#include "SOIL.h"
//https://www.thecrazyprogrammer.com/2016/11/caesar-cipher-c-c-encryption-decryption.html
void codificaMensagem(char message[], int cifra){
    char ch;
	int i;

    for(i = 0; message[i] != '\0'; ++i){
		ch = message[i];
		if(ch >= 'a' && ch <= 'z'){
			ch = ch + cifra;
			if(ch > 'z'){
				ch = ch - 'z' + 'a' - 1;
			}
			message[i] = ch;
		}
		else if(ch >= 'A' && ch <= 'Z'){
			ch = ch + cifra;
			if(ch > 'Z'){
				ch = ch - 'Z' + 'A' - 1;
			}
			message[i] = ch;
		}
	}
}
//https://www.thecrazyprogrammer.com/2016/11/caesar-cipher-c-c-encryption-decryption.html
void decodificaMensagem(char message[], int cifra){
    char ch;
	int i;
    for(i = 0; message[i] != '\0'; ++i){
		ch = message[i];

		if(ch >= 'a' && ch <= 'z'){
			ch = ch - cifra;

			if(ch < 'a'){
				ch = ch + 'z' - 'a' + 1;
			}

			message[i] = ch;
		}
		else if(ch >= 'A' && ch <= 'Z'){
			ch = ch - cifra;

			if(ch < 'A'){
				ch = ch + 'Z' - 'A' + 1;
			}

			message[i] = ch;
		}
	}
}

// Um pixel RGB
typedef struct {
    unsigned char r, g, b;
} RGB;

// Uma imagem em RGB
typedef struct {
    int width, height;
    RGB* img;
} Img;



// Protótipos
void load(char* name, Img* pic);

// Carrega uma imagem para a struct Img
void load(char* name, Img* pic)
{
    int chan;
    pic->img = (unsigned char*) SOIL_load_image(name, &pic->width, &pic->height, &chan, SOIL_LOAD_RGB);
    if(!pic->img)
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        exit(1);
    }
    printf("Load: %d x %d x %d\n", pic->width, pic->height, chan);
}

int main(int argc, char** argv)
{
    Img pic;
    if(argc < 1) {
        printf("loader [img]\n");
        exit(1);
    }
    load(argv[1], &pic);


    // Interacao
    char message[100];
    char password[100];
    char hex[100];

    printf("Digite a mensagem: \n");
    scanf("%s", message);

    printf("Digite uma senha:\n ");
    scanf("%s", password);

    printf("Minha Mensagem: %s\n", message);
    printf("Minha Senha: %s\n", password);

    //%%%%%%%%%%%%%%%%%%%%%%%%%% Designar o intervalo %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    int media=0;
    int ascii=0;
    for (int i =0; i< strlen(password);i++){
            ascii=password[i];
        //printf("valor do ascii: %d\n",ascii);
        media=media+ascii;
        //printf("ASCII value of %c = %d\n", password[i], password[i]);

    }
    int intervalo=media/strlen(password);
    printf("Intervalo = %d\n", intervalo);
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%% Designar o inicio %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    int start= password[0];
    printf("Start = %d\n", start);
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%% Designar quantas casas a cifra irá avançar %%%%%%%%%%%%%%%%
    int cifra= 10;
    printf("Cifra = %d\n", cifra);

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%% Cifrar a mensagem- codifica-la%%%%%%%%%%%%%%%%
    codificaMensagem(message,cifra);
    printf("Mensagem COD: %s\n", message);

    //decodificaMensagem(message,cifra);
    //printf("Mensagem DECOD: %s\n", message);


     //%%%%%%%%%%%%%%%%%%%%%%%%%%%% Tranformar para binario a mensagem cifrada%%%%%%%%%%%%%%%%
    int len=strlen(message);
    len= len*8;

    int bin[len];
    for (int i = 0; i<len; i++){
        bin[i] = 0;
    }
    int y=0;


    for(int x=0; message[x]!='\0'; x++)
    {
        int val = message[x];
        while(val > 0){
            if(val % 2 == 1)
            {
                bin[y] = 1;}
            else{
                bin[y] = 0;
            }

            val = val/2;
            y++;

        }

    }
    printf("\n");
    for(int j=0; j<len; j++){
        printf("%d ",bin[j]);
    }

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%% alterar na imagem com os bits %%%%%%%%%%%%%%%%

    printf("\nIMG antes\n");
    for(int i=start; i<140000 ;i=i+intervalo){
        if(i>=start){
                if(i<start+intervalo*strlen(message)){
                    printf("[%02X %02X %02X] ", pic.img[i].r, pic.img[i].g, pic.img[i].b);
                }
        }
    }

    printf("\nzerando o Red\n");
    for(int i=start; i<140000 ;i=i+intervalo){
        if(i>=start){
                if(i<start+intervalo*strlen(message)){
                    pic.img[i].r=00;
                    printf("[%02X %02X %02X] ", pic.img[i].r, pic.img[i].g, pic.img[i].b);
                    //printf("entrou\n");
                }
        }
    }

    printf("\nalterando o RED\n");
    int j =0;
    for(int i=start; i<140000 ;i=i+intervalo){
        if(i>=start){
                if(i<start+intervalo*strlen(message)){
                    pic.img[i].r=message[j];
                    printf("[%02X %02X %02X] ", pic.img[i].r, pic.img[i].g, pic.img[i].b);
                    //printf("entrou\n");
                }
        }
        j=j+1;
    }


    // Convert text to hex.
    for (int i = 0, j = 0; i < strlen(message); ++i, j += 2)

        sprintf(hex + j, "%02x", message[i] & 0xff);

    printf("'%s' in hex is %s.\n", message, hex);



    printf("IMG depois\n");
    for(int i=start; i<140000 ;i=i+intervalo){
        if(i>=start){
                if(i<start+intervalo*strlen(message)){
                    printf("[%02X %02X %02X] ", pic.img[i].r, pic.img[i].g, pic.img[i].b);
                }
        }
    }




    printf("\nPrimeiros 10 pixels da imagem alterada:\n");
    for(int i=0; i<10; i++) {
        printf("[%02X %02X %02X] ", pic.img[i].r, pic.img[i].g, pic.img[i].b);

    }

    printf("\n");
    

    free(pic.img);
}
