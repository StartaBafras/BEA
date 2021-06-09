#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


typedef struct
{
    char character;
    int pass;
}dict;


int find_size(int i)//Sayıların basamak sayısını bulur
{
    int counter = 1;
    int temp = i;
    for(;;counter++)
    {
        temp = (int) temp/10;
        if(temp<1)
        {
            break;
        }
    }
    return counter;
}

void extract(int i,int *pass)
{
    for(int j=1,b=5;j<7;j++,b--)
    {
        pass[b] = ( (i%(int)pow(10,j) - i%(int) pow(10,(j-1)) )/(int) pow(10,j-1) );
    }
}



int combine(int i,int j)// 2 sayıyı yan yana yazar
{
    int counter = 1;
    int temp = j;
    for(;;counter++)
    {
        temp = (int) temp/10;
        if(temp<1)
        {
            break;
        }
    }

    return ((pow(10,counter)*i)+j);
}
//aabbcc


int main(void)
{
    char input2[500];
    int size = 0;
    dict example[64]; //define öğrenilmeli
    int key[6] = {0};
    
    FILE *file = fopen("crp.txt","w");
    
    for(int i=0;i<63;i++)//Yerleştirildi türkçe karakterler eklenmeli
    {
        example[i].character = (65+i);
        example[i].pass = (65+i+50);
    }
    example[63].character = ' ';
    example[63].pass = 300;


    srand(time(NULL));

    printf("Text: ");
    //fscanf(stdin,"%s",input2);
    fgets(input2,500,stdin);

    char input[500];

    for(int i=0;input2[i] != '\n';i++)
    {
        input[i] = input2[i];
    }



    for(int i=0;input[i] != '\0';i++) // Girilen metnin karakter sayısı belirleniyor
    {
        size++;
    }

    int old_location[size+1];
    int *ol = old_location;
    for(int i=0;i<size+1;i++,ol++)// Kayıtların tutulacağı ve birbiriyle kıyaslanacağı dizi oluşturuldu
    {
        *ol = -1;
    }

    int random_n = rand()%size; //random_n 1 eksende kaç harf yazılacağını belirliyor

    while(random_n == 0)
    {
        random_n = rand()%size; //random_n 1 eksende kaç harf yazılacağını belirliyor
    }


    int block = (int) size/random_n; //bütün dizi için sabit bölümleme yapıyor plana göre değiştirilmeli 
    int dataset[block][10][10];


    int *p = &dataset;
    for(int i=0;i<block*100;i++,p++) // veriler sıfırlandı
    {
        *p = 0;
    }



    int cp = 0;
    char *c = input;
    int random_location[6] = {rand()%block,rand()%10,rand()%10,rand()%block,rand()%10,rand()%10}; //Rastgele yazılacak yer belirleniyor

    key[0] = random_location[0];
    key[1] = random_location[1];
    key[2] = random_location[2];

    old_location[0] = combine(random_location[0],combine(random_location[1],random_location[2]));

    if(block == 1)// tek blok oluştuysa blok başına düşen karakter sayısı bütün karakter sayısına eşit olalı
    {
        random_n = size;
    }

    for(int i=0;i<size;i++)
    {
        
        
        random_location[3] = rand()%block;//Gelecek kordinatlar belirleniyor
        random_location[4] = rand()%10;
        random_location[5] = rand()%10;

        for(int j=0;old_location[j] != -1;j++)//Oluşturulan kordinatların eski oluşturulan kordinatlarla çakışıp çakışmadığı kontrol ediliyor
        {
            if(old_location[j] == combine(random_location[3],combine(random_location[4],random_location[5])))
            {
                random_location[3] = rand()%block;//Çakışma varsa kordinatlar tekrar oluşturuluyor anca tekrar kontrol edilmeleri lazımken edilmiyorlar
                random_location[4] = rand()%10;
                random_location[5] = rand()%10;
            }
        }

        old_location[i+1] = combine(random_location[3],combine(random_location[4],random_location[5]));// yeni kordinatlar kayıt ediliyor


        


            
        for(int k=0;k<64;k++)
        {
            if(*c == (example[k].character)) // sözlük karakter eşleşmesi
            {
                cp = example[k].pass;//karakterin şifresi alınıyor
                break;
            }
        }
        c++; // işaretçi bir sonraki karaktere işaret ediyor

        
        dataset[random_location[0]][random_location[1]][random_location[2]] = combine(random_location[3],combine(combine(random_location[4],random_location[5]),cp));
        

            
            
        //printf("%d,%d,%d\n",random_location[0],random_location[1],random_location[2]);

        key[3] = random_location[0];
        key[4] = random_location[1];
        key[5] = random_location[2];

        random_location[0] = random_location[3];//kordinatlar kaydırılıyor bunlar bir sornaki karakterin yazılacağı konumlar
        random_location[1] = random_location[4];
        random_location[2] = random_location[5];

            
    }

    size-random_n; //Eğer 3 karakter girilir ve her bloğa 2 karakter eklenirse 2. eşleme işleminde 1 karakter kaldığından for döngüsü çalışacak ancak-
    if(size<random_n)//Hata verecektir kalan eleman sayısı her blokta olacak olan sayıdan küçük olursa son kalan bloğa kalan eleman sayısı kadar yazılır.
    {
            random_n = size;
    }
    
    
    
    p = &dataset;
    int rng=0;
    for(int i=0;i<block*100;i++,p++) // veriler tanınamaz hale getirildi
    {
        if(*p == 0)
        {
            rng = rand()%block;//blok sayısı 1 olduğunda 0 ve 1 yerleştirilmeli sadece 1 yerleştiriliyor
            rng = combine(rng,99999);//tek boyutlu şifreleme yapıldığında 0 karakterleri çok ortada
            *p = rand()%100000+rng;
        }
    }
    
    
    
    



    p = &dataset;//Dosyaya yazdırılıyor
    int smalls[6];
    for(int i=0;i<block*100;i++,p++)
    {
        if(find_size(*p) < 7)// sayılar 6 karakterden oluşmayabilir başlarına 0 yazmak için bu bölüm var
        {
            extract(*p,&smalls);
            fprintf(file,"%d%d%d%d%d%d",smalls[0],smalls[1],smalls[2],smalls[3],smalls[4],smalls[5]);
            continue;
        }
        fprintf(file,"%d",*p);
    }
    
    printf("\nKey: ");

    for(int i=0;i<6;i++)
    {
        printf("%d",key[i]);
    }
    
}