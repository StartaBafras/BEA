#include <stdio.h>

void extract(int i,int *pass)
{
    for(int j=1,b=5;j<7;j++,b--)
    {
        pass[b] = ( (i%(int)pow(10,j) - i%(int) pow(10,(j-1)) )/(int) pow(10,j-1) );
    }
}




int main(void)
{
     int a[6] = {0};

     extract(202151,&a);
     for(int i=0;i<6;i++)
     {
          printf("%d\n",a[i]);
     }
}