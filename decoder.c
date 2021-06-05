#include <stdio.h>
#include <stdlib.h>


typedef struct
{
    char character;
    int pass;
}dict;



void extract(int i,int *pass)
{
    for(int j=1,b=5;j<7;j++,b--)
    {
        pass[b] = ( (i%(int)pow(10,j) - i%(int) pow(10,(j-1)) )/(int) pow(10,j-1) );
    }
}



int main(void)
{

    FILE *file = fopen("crp.txt","r");

    if(file == NULL)
    {
        printf("Dosya bulunamadi");
        return 1;
    }
    fseek(file, 0, SEEK_END);
    unsigned long int len = ftell(file);
    rewind(file);

    int dataset[len/600][10][10];

    for(int i=0;i<len/100;i++)
    {
        for(int j=0;j<10;j++)
        {
            for(int k=0;k<10;k++)
            {
                fscanf(file,"%6d",&dataset[i][j][k]);
            }
        }
    }


    dict example[64];


    for(int i=0;i<63;i++)//Yerleştirildi türkçe karakterler eklenmeli
    {
        example[i].character = (65+i);
        example[i].pass = (65+i+50);
    }
    
    example[63].character = ' ';
    example[63].pass = 300;


    int key;
    int key_array[6];
    printf("Anahtar giriniz: ");
    scanf("%d",&key);

    extract(key,&key_array);

    int en_text[6];

    extract(dataset[key_array[0]][key_array[1]][key_array[2]],&en_text);
    int counter =0;
    for(int j=0; j<=1 ;j++)
    {
        for(int i=0;i<64;i++)
        {
            if(example[i].pass == (en_text[3]*100 + en_text[4]*10 + en_text[5]))
            {
                printf("%c",example[i].character);
                break;
            }
        }

        

        if(en_text[0]*100 + en_text[1]*10 + en_text[2] == key_array[3]*100 + key_array[4]*10 + key_array[5])
        {
            counter = 1;
        }
        if(counter == 0)
        {
            j--;
        }

        extract(dataset[en_text[0]][en_text[1]][en_text[2]],&en_text);
        if(en_text[3]*100 + en_text[4]*10 + en_text[5] == 0)
        {
            printf("\nHatalı işaretçi\n");
            return 3;
        }

    }






}