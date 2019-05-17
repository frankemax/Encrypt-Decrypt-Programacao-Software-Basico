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

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%% Cifrar a mensagem- codifica-la%%%%%%%%%%%%%%%%
    codificaMensagem(message,cifra);
    printf("Mensagem COD: %s\n", message);

    //decodificaMensagem(message,cifra);
    //printf("Mensagem DECOD: %s\n", message);

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%% alterar na imagem com os bits %%%%%%%%%%%%%%%%

    printf("\nIMG antes\n");
    for(int i=start; i<pic.height*pic.width ; i=i+intervalo)
    {
        if(i<=start+intervalo*strlen(message))
        {
            printf("[%d %d %0d] ", pic.img[i].r, pic.img[i].g, pic.img[i].b);
        }
    }

    unsigned int pix,pix2, pospix, pospix2, put, auxiliar;
    int z=0;

    printf("\n zerando os quatro ultimos e deixando certo\n");
    for(int i=start; i<pic.height*pic.width ; i=i+intervalo)
    {
        if(i<=start+intervalo*strlen(message))
        {
            pix=pic.img[i].r;
            pix2=pic.img[i].g;
            //zerei os ultimos 4 bits do red e blue
            pospix = pix & 0XF0;
            pospix2 = pix2 & 0XF0;
            //printf("pos pix = %d\n",pospix);
            pic.img[i].r=pospix;
            pic.img[i].g=pospix2;

            // colocar os ultimos 4 bits do red e blue
            auxiliar = message[z];
            pospix = (pic.img[i].r) | (message[z] >>4);
            pospix2 = (pic.img[i].g) | (auxiliar & 0X0F);

            pic.img[i].r=pospix;
            pic.img[i].g=pospix2;

            printf("[%d %d %0d] ", pic.img[i].r, pic.img[i].g, pic.img[i].b);
            //printf("entrou\n");
            z++;

        }

    }
    SOIL_save_image("saidas.jpg", SOIL_SAVE_TYPE_BMP, pic.width, pic.height, 3, pic.img);
    free(pic.img);


    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% AGORA DECRIPTADOR %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    load("saida.bmp", &pic);

    // Interacao
    char password2[100];

    printf("Digite a senha:\n ");
    scanf("%s", password2);

    printf("Senha digitada: %s\n", password2);

    //%%%%%%%%%%%%%%%%%%%%%%%%%% Designar o intervalo %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    int media2=0;
    int ascii2=0;
    for (int i =0; i< strlen(password2); i++)
    {
        ascii2=password2[i];
        //printf("valor do ascii: %d\n",ascii);
        media2=media2+ascii2;
        //printf("ASCII value of %c = %d\n", password[i], password[i]);
    }
    int intervalo2=media2/strlen(password2);
    printf("Intervalo = %d\n", intervalo2);

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%% Designar o inicio %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    int start2= password[0];
    printf("Start = %d\n", start2);

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%% Designar quantas casas a cifra irá avançar %%%%%%%%%%%%%%%%
    int cifra2= 10;
    printf("Cifra = %d\n", cifra2);

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%% Pegar na imagem a mensagem cifrada %%%%%%%%%%%%%%%%

    unsigned int pix1,pix21, pospix1;
    unsigned int valorr, valorg, valorrpos, valorgpos,valorOr;
    char message1[100];
    int posMessage=0;
    printf("\nMensagem Final\n");
    for(int i=start2; i<pic.height*pic.width ; i=i+intervalo2)
    {
        pix1 = pic.img[i].r;
        pix21 = pic.img[i].g;
        pix1 = pix1 << 4;
        pix21 = pix21 << 4;

        if(i<start2+intervalo2*100)
        {
            valorr= pic.img[i].r;
            valorr= valorr & 0X0F;
            valorrpos=valorr << 4;
            //printf("valor int do vetorr: %d \n",valorrpos);

            valorg = pic.img[i].g;
            valorg= valorg & 0X0F;
            //printf("valor int do vetorg: %d\n",valorg);

            valorOr = valorrpos | valorg;
            if(valorOr<=0)
            {
                break;
            }



            printf("%c",valorOr);
            message1[posMessage]=0;
            message1[posMessage]=valorOr;

            //printf("[%d %d %d] ", pic.img[i].r, pic.img[i].g, pic.img[i].b);


        }
    }
    //printf("\nMensagem COD: %s\n", message1);
    // printf("wtf: %d\n", message1[0]);
    //decodificaMensagem(message1,10);
    //printf("\nMensagem DECOD: %s\n", message1);















}
