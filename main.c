#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// Para usar strings

// SOIL é a biblioteca para leitura das imagens
#include "SOIL.h"

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
    printf("\nCarregou uma imagem de dimensoes: %d x %d x %d\n", pic->width, pic->height, chan);
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

    printf("Digite a mensagem : \n");
    gets(message);

    printf("Digite uma senha( sem espaco em branco ): \n ");
    gets(password);

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
    int cifra = password[0] - 'z' - 10;
    printf("Cifra = %d\n", cifra);

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%% Cifrar a mensagem- codifica-la%%%%%%%%%%%%%%%%
    for (int i =0; i< strlen(message); i++)
    {
        message[i] = message[i] + cifra;
    }

    printf("Mensagem COD: %s\n", message);

    //decodificaMensagem(message,cifra);
    //printf("Mensagem DECOD: %s\n", message);

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%% ALTERAR NA IMAGEM COM OS BITS %%%%%%%%%%%%%%%%%%%%%%%%%%%

    unsigned int pix,pix2, pospix, pospix2, auxiliar;
    int z=0;

    //printf("\n zerando os quatro ultimos e deixando certo\n");
    for(int i=start; i<pic.height*pic.width ; i=i+intervalo)
    {
        if(i<=start+intervalo*strlen(message))
        {
            pix=pic.img[i].r;
            pix2=pic.img[i].g;

            //zerar os ultimos 4 bits do red e blue fazendo um and com 1111 0000
            pospix = pix & 0XF0;
            pospix2 = pix2 & 0XF0;

            //printf("pos pix = %d\n",pospix);
            //guardar na imagem com os 4 ultimos bits zerados
            pic.img[i].r=pospix;
            pic.img[i].g=pospix2;

            // colocar os ultimos 4 bits do red e green:
            //      red: shiftando os 4 bits para a direita, e fazendo um or com o que esta na imagem.r
            //      green: fazendo um and com 0000 1111, zerando os 4 primeiros bits, e por fim, fazendo um or com o image.g
            auxiliar = message[z];
            pospix = (pic.img[i].r) | (message[z] >>4);
            pospix2 = (pic.img[i].g) | (auxiliar & 0X0F);

            // por fim guardar na img
            pic.img[i].r=pospix;
            pic.img[i].g=pospix2;

            //printf("[%d %d %0d] ", pic.img[i].r, pic.img[i].g, pic.img[i].b);
            //printf("entrou\n");
            z++;

        }

    }
    SOIL_save_image("saida.bmp", SOIL_SAVE_TYPE_BMP, pic.width, pic.height, 3, pic.img);
    free(pic.img);


    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% AGORA DECRIPTADOR %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    load("saida.bmp", &pic);

    // Interacao
    char password2[100];

    printf("Digite a senha:\n ");
    gets(password2);

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
    int start2= password2[0];
    printf("Start = %d\n", start2);

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%% Designar quantas casas a cifra irá avançar %%%%%%%%%%%%%%%%
    int cifra2 = password2[0] - 'z' - 10;
    printf("Cifra = %d\n", cifra2);

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%% Pegar na imagem a mensagem cifrada e "printar" %%%%%%%%%%%%%%%%

    unsigned int pix1,pix21;
    unsigned int valorR, valorRpos,valorOr,valorG;
    printf("\nMensagem Final\n");
    for(int i=start2; i<pic.height*pic.width ; i=i+intervalo2)
    {
        //passar para unsigned int
        pix1 = pic.img[i].r;
        pix21 = pic.img[i].g;

        //zerar a segunda parte dos 8 bits, ficando XXXX 0000
        pix1 = pix1 << 4;
        pix21 = pix21 << 4;

        if(i<start2+intervalo2*100)//100 pois é o limite da message
        {
            valorR= pic.img[i].r;
            valorR= valorR & 0X0F; //and com o 0000 1111 para zerar a primeira metade
            valorRpos=valorR << 4; // shift valorR para ficar XXXX 0000

            valorG = pic.img[i].g;
            valorG= valorG & 0X0F;// and com 0000 1111, para zerar a primeira metade

            valorOr = valorRpos | valorG; // or entre os dois para juntar as metades e formar o char

            if(valorOr<=0)// condicao de parada
            {
                break;
            }
            printf("%c",valorOr - cifra2);

        }
    }
}



