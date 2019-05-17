#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// Para usar strings

// SOIL é a biblioteca para leitura das imagens
#include "SOIL.h"
//https://www.thecrazyprogrammer.com/2016/11/caesar-cipher-c-c-encryption-decryption.html
void codificaMensagem(char message[], int cifra)
{
    char ch;
    int i;

    for(i = 0; message[i] != '\0'; ++i)
    {
        ch = message[i];
        if(ch >= 'a' && ch <= 'z')
        {
            ch = ch + cifra;
            if(ch > 'z')
            {
                ch = ch - 'z' + 'a' - 1;
            }
            message[i] = ch;
        }
        else if(ch >= 'A' && ch <= 'Z')
        {
            ch = ch + cifra;
            if(ch > 'Z')
            {
                ch = ch - 'Z' + 'A' - 1;
            }
            message[i] = ch;
        }
    }
}
//https://www.thecrazyprogrammer.com/2016/11/caesar-cipher-c-c-encryption-decryption.html
void decodificaMensagem(char message[], int cifra)
{
    char ch;
    int i;
    for(i = 0; message[i] != '\0'; ++i)
    {
        ch = message[i];

        if(ch >= 'a' && ch <= 'z')
        {
            ch = ch - cifra;

            if(ch < 'a')
            {
                ch = ch + 'z' - 'a' + 1;
            }

            message[i] = ch;
        }
        else if(ch >= 'A' && ch <= 'Z')
        {
            ch = ch - cifra;

            if(ch < 'A')
            {
                ch = ch + 'Z' - 'A' + 1;
            }

            message[i] = ch;
        }
    }
}

// Um pixel RGB
typedef struct
{
    unsigned char r, g, b;
} RGB;

// Uma imagem em RGB
typedef struct
{
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
    if(argc < 1)
    {
        printf("loader [img]\n");
        exit(1);
    }
    load(argv[1], &pic);


    // Interacao
    char password[100];

    printf("Digite a senha:\n ");
    scanf("%s", password);

    printf("Senha digitada: %s\n", password);

    //%%%%%%%%%%%%%%%%%%%%%%%%%% Designar o intervalo %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    int media=0;
    int ascii=0;
    for (int i =0; i< strlen(password); i++)
    {
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




    //%%%%%%%%%%%%%%%%%%%%%%%%%%%% Pegar na imagem a mensagem cifrada %%%%%%%%%%%%%%%%

    printf("\nIMG antes\n");
    for(int i=start; i<pic.height*pic.width ; i=i+intervalo){
    if((((pic.img[i].r) << 4)==0) && ((pic.img[i].g) << 4) == 0) {
        break;
    }
        if(i<start+intervalo*100)
        {
            printf("[%d %d %0d] ", pic.img[i].r, pic.img[i].g, pic.img[i].b);
        }
    }




    printf("\n");


    free(pic.img);
}
