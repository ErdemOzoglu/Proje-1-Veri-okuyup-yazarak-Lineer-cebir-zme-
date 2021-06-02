#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
// sadece binary tipteki dosyada noktalarin kontrolünü yapmiyor. yani alan xyz ise noktalarda buna göre ayarlanmistir kusur yoktur.
int rgbolmayanlar[20];
int h=0;
/* Kup Koordinat */
typedef struct
{
  double x;
  double y;
  double z;
}KupKoordinat;
/* nokta struct tipi */
typedef struct
{
    double x;
    double y;
    double z;
    int r;
    int g;
    int b;

} Nokta;
/*dosya struct tipi */
typedef struct
{
    int version;
    int alanlar;
    int noktalar;
    int data;
    Nokta *veriler;
} Dosya;
int rgbsatirkontrol(int m,int *rgbolmayanlar,int h)
{
    int k;
    k=h;
    while(k>0)
  {
      if(rgbolmayanlar[k-1]==m+1)
      {
          return 0;
      }
      k--;
  }
  return 1;

}
void DosyaNoktaKontrol_1(FILE *fp,Dosya *dosya,long noktasayisii)   // dosyadaki her satirdaki  xyz rgb degerlerini kontrol eder sadece ascii
{
    h=0;
char karakter;
int j=0,bosluk=0,m=1,satir=0;
 if(dosya->data == 0 && dosya->alanlar==1)
 {  karakter=fgetc(fp);
    while(satir<5)
    {
        while(karakter != '\n')
        {
            karakter=fgetc(fp);
        }
        karakter=fgetc(fp);
        satir++ ;
    }

    while(karakter != EOF)
    {
        while(karakter != '\n'){

        if(karakter == ' ')
        {
            bosluk++;
        }
        karakter=fgetc(fp);
        }
        if(bosluk == 2)
        {
            rgbolmayanlar[j]=m;
            j++;
            h=j;
        }
    karakter = fgetc(fp);
    bosluk=0;
    m++;
    if(m > noktasayisii-1)
    {
        break;
    }
    }

 }

}
void DosyaNoktaKontrol_2(FILE *fp,Dosya *dosya,long noktasayisii)  // dosya xyzrgb ascii seklindeyse dosyada verilemeyn rgb degerlerinin satirini yazar.
{

char karakter;
int j=0,bosluk=0,m=0,satir=0;

    karakter=fgetc(fp);
    while(satir<5)
    {
        while(karakter != '\n')
        {
            karakter=fgetc(fp);
        }
        satir++ ;
        if(satir==5)
        {
            break;
        }
        karakter=fgetc(fp);

    }
    while(karakter != EOF)
    {
        while(karakter != '\n'){

        if(karakter == ' ')
        {
            bosluk++;
        }
        karakter=fgetc(fp);
        }
        if(bosluk == 2)
        {
            printf("\n %d. noktanin R G B bilgileri verilmemistir.\n",m);
        }
    karakter = fgetc(fp);
    bosluk=0;
    m++;
    if(m > noktasayisii-1)
    {
        break;
    }
    }
 }
void DosyaBilgiOku(FILE *fp,Dosya *dosya)  // dosyadan ilk 5 satiri okuyarak degerleri dosya tipindeki referansa aktarir.
{
    char karak;
    int i=0;
        if(i==0)
        {
            while(karak != '\n')
            {
                karak=fgetc(fp);
                printf("%c",karak);
            }
            i++;
        }
        printf("\n");
        if(i==1)
        {
            char karakter1[20];
            fscanf(fp,"%s %d",karakter1,&(dosya->version));
            i++;

        }

        if(i==2)
        {
            int l=1;

            karak=fgetc(fp);

            karak=fgetc(fp);

            while(karak != '\n')
            {
                l++;
                karak=fgetc(fp);
            }
            if(l == 20)
            {
                dosya->alanlar=1;
                i++;
            }
            else if(l==14)
            {
                dosya->alanlar=0;
                i++;

            }
            else
            {
                dosya->alanlar=2;
                i++;
            }
        }

        if(i==3)
        {

            char karakter1[20];
            fscanf(fp,"%s %d",karakter1,&(dosya->noktalar));
            i++;

        }

        if(i==4)
        {

            char karakter1[20];
            char karakter2[20];
            fscanf(fp,"%s %s",karakter1,karakter2);


            if(strcmp(karakter2,"ascii")==0)
            {

                printf("Dosyadaki veriler ASCii seklindedir.\n");


                dosya->data=0;
                i++;

            }
            if(strcmp(karakter2,"binary")==0)
            {
                printf("Dosyadaki veriler BINARY seklindedir.\n");
                dosya->data=1;
                i++;
            }
        }

}
long NoktaSayisi(FILE *fp,Dosya *dosya)           // dosyadaki nokta sayisini tespit eder.
{
    long i=0;
    char karakter;
    float buffer;
    int tutucu;

      if(dosya->data==0)
   {

    if (fp == NULL)
    {
        printf("dosya acilamadi.");
        return 1;
    }

    else
    {   karakter=fgetc(fp);
        while(1)
       {   while(karakter!='\n')
        {
            karakter=fgetc(fp);
        }
           if(karakter == '\n')
            {
                i++;
            }

            if(i==5)
            {
                break;

            }
            karakter=fgetc(fp);
       }
        i=0;
        while(karakter != EOF)
        {
            if(karakter == '\n')
            {
                i++;
            }
            karakter=fgetc(fp);

        }
    }
    return i;}

      if(dosya->data==1 && dosya->alanlar==1)
   {  i=0;

    if (fp == NULL)
    {
        printf("dosya acilamadi.");
        return 1;
    }

    else
    {

        karakter=fgetc(fp);
        while(i<5){
        while(karakter !='\n')
        {
            karakter=fgetc(fp);
        }
        i++;

        if(i==5)
        {
            break;
        }
        karakter=fgetc(fp);
        }
        i=-1;
        while(!feof(fp))
        {

           fread(&buffer,sizeof(float),1,fp);

           fread(&buffer,sizeof(float),1,fp);

           fread(&buffer,sizeof(float),1,fp);


           fread(&tutucu,sizeof(int),1,fp);

           fread(&tutucu,sizeof(int),1,fp);

           fread(&tutucu,sizeof(int),1,fp);


          i++;

        }

    }
    return i;}
    if(dosya->data==1 && dosya->alanlar==0)
   {  i=0;

    if (fp == NULL)
    {
        printf("dosya acilamadi.");
        return 1;
    }

    else
    {

        karakter=fgetc(fp);
        while(i<5){
        while(karakter !='\n')
        {
            karakter=fgetc(fp);
        }
        i++;

        if(i==5)
        {
            break;
        }
        karakter=fgetc(fp);
        }
        i=-1;
        while(!feof(fp))
        {

           fread(&buffer,sizeof(float),1,fp);

           fread(&buffer,sizeof(float),1,fp);

           fread(&buffer,sizeof(float),1,fp);

          i++;

        }

    }
    return i;}
}
int DosyaNoktaSayisiKontrol(FILE *fp,Dosya *dosya,long noktasayisii)
{
    if(dosya->noktalar == noktasayisii)
    {
        printf("\nDosyadaki nokta sayisi belirtilen nokta sayisi ile ayni..\n");
        return 1;
    }
    else
    {
        printf("\nDosyadaki nokta sayisi belirtilen nokta sayisi ile ayni degil ..\n");
        printf("dosyada belirtilen nokta miktari ..%d\n",dosya->noktalar);
        printf("dosyadaki nokta miktari %d\n",NoktaSayisi(fp,dosya));
        return 0;
    }
}
void EkranCiktisi(FILE *fp,Dosya *dosya,long noktasayisii)   // dosya ascii seklindeyse cikti alir . binary sekli yazilacak.
{
    FILE *p ;
    int i;
    char karakter;
    float buffer;
    int tutucu;
    p=fp;

   if(dosya->data==0)
   {
       if (p == NULL)
    {
        printf("dosya acilamadi.");
    }

    else
    {
        karakter = fgetc(p);
        int   i=0;
        while(karakter != EOF)
        {
            fputc(karakter,stdout);
            if(karakter == '\n' )
            {
               // printf("%d . satir ...",i+1);
                i++;
            }
            karakter=fgetc(p);
        }
    }
    }
    i=0;
    if(dosya->data==1 && dosya->alanlar==1)
    {
                karakter=fgetc(fp);
        while(i<5){
        while(karakter !='\n')
        {
            karakter=fgetc(fp);
        }
        i++;

        if(i==5)
        {
            break;
        }
        karakter=fgetc(fp);
        }
        printf("\n");
        i=0;
        while(!feof(fp))
        {
            if(i==noktasayisii)
            {
                break;
            }

           fread(&buffer,sizeof(float),1,fp);
           printf("%f ",buffer);
           fread(&buffer,sizeof(float),1,fp);
           printf("%f ",buffer);
           fread(&buffer,sizeof(float),1,fp);
           printf("%f ",buffer);
           fread(&tutucu,sizeof(int),1,fp);
           printf("%d ",tutucu);
           fread(&tutucu,sizeof(int),1,fp);
            printf("%d ",tutucu);
           fread(&tutucu,sizeof(int),1,fp);
          printf("%d ",tutucu);

          i++;
          printf("\n");

        }
    }
    i=0;
    if(dosya->data==1 && dosya->alanlar==0)
    {
                karakter=fgetc(fp);
        while(i<5){
        while(karakter !='\n')
        {
            karakter=fgetc(fp);
        }
        i++;

        if(i==5)
        {
            break;
        }
        karakter=fgetc(fp);
        }
        printf("\n");
        i=0;
        while(!feof(fp))
        {
            if(i==noktasayisii)
            {
                break;
            }

           fread(&buffer,sizeof(float),1,fp);
           printf("%f ",buffer);
           fread(&buffer,sizeof(float),1,fp);
           printf("%f ",buffer);
           fread(&buffer,sizeof(float),1,fp);
           printf("%f ",buffer);

          i++;
          printf("\n");

        }
    }

}
int DosyaBaslikBilgileri(FILE *fp,Dosya *dosya) // dosyanin ilk 5 satirini okur ve dosya formatina aykiriysa hata verir.
{
    char karak;
    int i=0;
    char karakterler_1[10];

    while(!feof(fp)){
        if(i==0)
        {
            char karakterler_2[10];
            char karakterler_3[10];
            char karakterler_4[10];
            fscanf(fp,"%s %s %s %s",karakterler_1,karakterler_2,karakterler_3,karakterler_4);
            if(strcmp(karakterler_1,"#")!=0 || strcmp(karakterler_2,"Noktalar")!=0  || strcmp(karakterler_3,"dosya") != 0 || strcmp(karakterler_4,"format")!= 0)
            {
             printf("%d .satir dosya formati uygun degil..\n",i+1);
             return 0;
            }
            else
            {
             printf("%d . satir uygun\n",i+1);
            }

        }
        if(i==1)
        {   char karakter1[20];
            char karakter2[20];
            int c;
            fscanf(fp,"%s %s",karakter1,karakter2);;
            c=atoi(karakter2);
            if(strcmp(karakter1,"VERSION")!=0 || c<0==1|| c>1000==1 )
            {
                 printf("%d .satir dosya formati uygun degil..\n",i+1);
                 return 0;
            }
            else
            {
                printf("%d . satir uygun\n",i+1);
            }

        }

        if(i==2)
        {
            int l=1;
            char t_1[3];
            char t_2[3];
            char t_3[3];
            char t_4[3];
            char t_5[3];
            char t_6[3];
             if(dosya->alanlar==1)
             {

              fscanf(fp,"%s %s %s %s %s %s %s",karakterler_1,t_1,t_2,t_3,t_4,t_5,t_6);
              if(strcmp(karakterler_1,"ALANLAR" )!=0 || strcmp(t_1,"x")!=0 || strcmp(t_2,"y")!=0 || strcmp(t_3,"z")!=0 || strcmp(t_4,"r")!=0 || strcmp(t_5,"g")!=0 || strcmp(t_6,"b")!=0)
              {
                 printf("%d .satir dosya formati uygun degil..\n",i+1);
                 return 0;
              }
              else
              {
                printf("%d . satir uygun\n",i+1);
              }
             }

             if(dosya->alanlar==0)
             {

              fscanf(fp,"%s %s %s %s",karakterler_1,t_1,t_2,t_3);
              if(strcmp(karakterler_1,"ALANLAR" )!=0 || strcmp(t_1,"x")!=0 || strcmp(t_2,"y")!=0 || strcmp(t_3,"z")!=0)
              {
                 printf("%d .satir dosya formati uygun degil..\n",i+1);
                 return 0;
              }
              else
              {
                printf("%d . satir uygun\n",i+1);

              }
             }
             if(dosya->alanlar==2)
             {
                 printf("dosyada ki alanlar xyzrgb kısmı yanlıs verilmis....\n");
                 return 0;
             }



        }

        if(i==3)
        {
            char karakter3[20];
            char karakter4[20];
            int c;
            fscanf(fp,"%s %s",karakter3,karakter4);;
            c=atoi(karakter4);
            if(strcmp(karakter3,"NOKTALAR")!=0 || c<0==1|| c>1000000==1 )
            {
                 printf("%d .satir dosya formati uygun degil..\n",i+1);
                 return 0;
            }
            else
            {
                printf("%d . satir uygun\n",i+1);
            }

        }

        if(i==4)
        {

            char karakter5[20];
            char karakter6[20];
            fscanf(fp,"%s %s",karakter5,karakter6);


            if(strcmp(karakter5,"DATA")!=0 )
            {
                printf("dosya uygun degil....\n");
                return 0;
            }

            if(strcmp(karakter6,"binary")!=0 && strcmp(karakter6,"ascii")!=0 ){

                printf("dosya uygun degil....\n");
                return 0;

            }
            else
            {
                 printf("%d . satir uygun\n",i+1);

            }
          }
          i++;
          if(i==5)
        {
            printf("bu dosya istenilen dosya formatina uygundur..\n");
            return 1;
        }
        }

}
void DosyadanNoktalariAl(FILE *fp,Dosya *dosya,Nokta *noktalar) // dosyadan noktalari alir.
{
    char karakter;
    int j=0,bosluk=0,m=0,satir=0,i=0;
    float buffer;
    int tutucu;
   if( dosya->data==0 && dosya->alanlar==0 )                                                  // ascii
   {
       while(satir<5)
    {  karakter=fgetc(fp);
        while(karakter != '\n')
        {
            karakter=fgetc(fp);
        }
        satir++ ;
    }
    while(!feof(fp))
    {
        if(m==dosya->noktalar)
        {
            break;
        }
        while(karakter != '\n')
        {
            karakter=fgetc(fp);
        }
        karakter=' ';
        fscanf(fp,"%lf %lf %lf",&noktalar[m].x,&noktalar[m].y,&noktalar[m].z);
        noktalar[m].r=-1;
        noktalar[m].g=-1;
        noktalar[m].b=-1;
        m++;
    }
   }
   ////////////////////////////////////////
   if(dosya->data==0 && dosya->alanlar==1)                 //ascii
   {

       while(satir<5)
    {  karakter=fgetc(fp);
        while(karakter != '\n')
        {
            karakter=fgetc(fp);
        }
        satir++ ;
    }
    while(!feof(fp))
    {
        if(m==dosya->noktalar)
        {
            break;
        }
        while(karakter != '\n')
        {
            karakter=fgetc(fp);
        }
        karakter=' ';
        if(rgbsatirkontrol(m,rgbolmayanlar,h)==1)
        {
            fscanf(fp,"%lf %lf %lf %d %d %d",&noktalar[m].x,&noktalar[m].y,&noktalar[m].z,&noktalar[m].r,&noktalar[m].g,&noktalar[m].b);
        }
        if(rgbsatirkontrol(m,rgbolmayanlar,h)==0)
        {
            fscanf(fp,"%lf %lf %lf",&noktalar[m].x,&noktalar[m].y,&noktalar[m].z);
            noktalar[m].r=-1;
            noktalar[m].g=-1;
            noktalar[m].b=-1;
        }
        m++;
    }

   }
   if(dosya->data==0 && dosya->alanlar==2)                              //asciii
   {
       printf("dosya alanlar formati bozuk ....");
   }

   if(dosya->data==1 && dosya->alanlar==0)                             // binary
   {   karakter=fgetc(fp);
       while(i<5)
    {
        while(karakter!='\n')
        {
            karakter=fgetc(fp);

        }

        printf("\n");
        i++;
        if(i==5)
        {
            break;
        }
        karakter=fgetc(fp);

    }
    i=0;
    while(!feof(fp)){
        if(i==dosya->noktalar)
        {
            break;
        }
           fread(&buffer,sizeof(float),1,fp);
              noktalar[i].x=buffer;

           fread(&buffer,sizeof(float),1,fp);
              noktalar[i].y=buffer;

           fread(&buffer,sizeof(float),1,fp);
              noktalar[i].z=buffer;
          i++;
    }
   }
      if(dosya->data==1 && dosya->alanlar==1)                             // binary
   {  karakter=fgetc(fp);
       while(i<5)
    {
        while(karakter!='\n')
        {
            karakter=fgetc(fp);
        }

        printf("\n");
        i++;
        if(i==5)
        {
            break;
        }
        karakter=fgetc(fp);

    }
    i=0;
    while(!feof(fp)){

        if(i==dosya->noktalar)
        {
            break;
        }
           fread(&buffer,sizeof(float),1,fp);
              noktalar[i].x=buffer;

           fread(&buffer,sizeof(float),1,fp);
              noktalar[i].y=buffer;

           fread(&buffer,sizeof(float),1,fp);
              noktalar[i].z=buffer;


           fread(&tutucu,sizeof(int),1,fp);
              noktalar[i].r=tutucu;

           fread(&tutucu,sizeof(int),1,fp);
              noktalar[i].g=tutucu;

           fread(&tutucu,sizeof(int),1,fp);
              noktalar[i].b=tutucu;

          i++;
    }
   }

   if(dosya->data==1 && dosya->alanlar==2)                              //binary
   {
       printf("dosya alanlar formati bozuk ....");
   }

}
void EnYakinEnUzak(Nokta *noktalar,long noktasayisii,FILE *outputdosyasi)
{
    int i=0,k=0;
    int EnYakinDizi[2];
    int EnUzakDizi[2];
    double m,n;
    double EnYakin=sqrt(pow(noktalar[i].x-noktalar[i+1].x,2)+pow(noktalar[i].y-noktalar[i+1].y,2)+pow(noktalar[i].z-noktalar[i+1].z,2));
    double EnUzak=sqrt(pow(noktalar[i].x-noktalar[i+1].x,2)+pow(noktalar[i].y-noktalar[i+1].y,2)+pow(noktalar[i].z-noktalar[i+1].z,2));
    for(i=0;i<noktasayisii;i++)
    {
        for(k=i+1;k<noktasayisii;k++)
        {
           m=sqrt(pow(noktalar[i].x-noktalar[k].x,2)+pow(noktalar[i].y-noktalar[k].y,2)+pow(noktalar[i].z-noktalar[k].z,2));
           if(m<EnYakin)
           {
               EnYakin=m;
               EnYakinDizi[0]=i;
               EnYakinDizi[1]=k;
               printf("%lf\n",m);
           }

        }
    }
    printf("\n");
       for(i=0;i<noktasayisii;i++)
    {
        for(k=i+1;k<noktasayisii;k++)
        {
           n=sqrt(pow(noktalar[i].x-noktalar[k].x,2)+pow(noktalar[i].y-noktalar[k].y,2)+pow(noktalar[i].z-noktalar[k].z,2));
           if(n>EnUzak)
           {
               EnUzak=n;
               EnUzakDizi[0]=i;
               EnUzakDizi[1]=k;
               printf(" %lf\n",n);
           }

        }
    }

    fprintf(outputdosyasi,"%d en ile %d en uzak noktalar..\n",EnUzakDizi[0],EnUzakDizi[1]);
    fprintf(outputdosyasi,"bu noktalar en uzak noktalarin koordinatlari..%lf %lf %lf , %lf %lf %lf\n\n",noktalar[EnUzakDizi[0]].x,noktalar[EnUzakDizi[0]].y,noktalar[EnUzakDizi[0]].z,noktalar[EnUzakDizi[1]].x,noktalar[EnUzakDizi[1]].y,noktalar[EnUzakDizi[1]].z);
    fprintf(outputdosyasi,"%d en ile %d en yakin noktalar..\n",EnYakinDizi[0]+1,EnYakinDizi[1]+1);
    fprintf(outputdosyasi,"bu noktalar en yakin noktalarin koordinatlari..%lf %lf %lf , %lf %lf %lf\n\n",noktalar[EnYakinDizi[0]].x,noktalar[EnYakinDizi[0]].y,noktalar[EnYakinDizi[0]].z,noktalar[EnYakinDizi[1]].x,noktalar[EnYakinDizi[1]].y,noktalar[EnYakinDizi[1]].z);
    fprintf(outputdosyasi,"%lf en uzak mesafe,, %lf en yakin mesafedir..\n",EnUzak,EnYakin);

    printf("\n en uzak mesafe...%.5lf\n",EnUzak);

    printf("en yakin mesafe...%.5lf\n",EnYakin);

    printf("En Uzak noktalar %d %d\n",EnUzakDizi[0]+1,EnUzakDizi[1]+1);

    printf("En Uzak noktalarin koordinatlari %lf %lf %lf , %lf %lf %lf\n",noktalar[EnUzakDizi[0]].x,noktalar[EnUzakDizi[0]].y,noktalar[EnUzakDizi[0]].z,noktalar[EnUzakDizi[1]].x,noktalar[EnUzakDizi[1]].y,noktalar[EnUzakDizi[1]].z);

    printf("En Yakin noktalar %d %d\n",EnYakinDizi[0]+1,EnYakinDizi[1]+1);

    printf("En yakin noktalarin koordinatlari %lf %lf %lf , %lf %lf %lf\n",noktalar[EnYakinDizi[0]].x,noktalar[EnYakinDizi[0]].y,noktalar[EnYakinDizi[0]].z,noktalar[EnYakinDizi[1]].x,noktalar[EnYakinDizi[1]].y,noktalar[EnYakinDizi[1]].z);

}
void KupKenarBilgileri(Nokta *noktalar,long noktasayisii,FILE *outputdosyasi)
{
int i=0;
double maxfark=0;
double x_max = noktalar[0].x;
double x_min = noktalar[0].x;
double y_max = noktalar[0].y;
double y_min = noktalar[0].y;
double z_max = noktalar[0].z;
double Z_min = noktalar[0].z;

 for(i=0;i<noktasayisii;i++)
 {
      if(noktalar[i].x>x_max)
      {
          x_max=noktalar[i].x;
      }
      if(noktalar[i].x<x_min)
      {
          x_min=noktalar[i].x;
      }

      if(noktalar[i].y>y_max)
      {
          y_max=noktalar[i].y;
      }
      if(noktalar[i].y<y_min)
      {
          y_min=noktalar[i].y;
      }

      if(noktalar[i].z>z_max)
      {
          z_max=noktalar[i].z;
      }
      if(noktalar[i].z<Z_min)
      {
          Z_min=noktalar[i].z;
      }

 }

 if(maxfark<(x_max-x_min))
 {
     maxfark=(x_max-x_min);
 }
 if(maxfark<(y_max-y_min))
 {
   maxfark=(y_max-y_min);
 }
 if(maxfark<(z_max-Z_min))
 {
   maxfark=(z_max-Z_min);
 }
 KupKoordinat KupKose[8];
 KupKose[0].x=x_min;
 KupKose[0].y=y_min;
 KupKose[0].z=Z_min;
 KupKose[1].x=x_min+maxfark;
 KupKose[1].y=y_min;
 KupKose[1].z=Z_min;
 KupKose[2].x=x_min;
 KupKose[2].y=y_min+maxfark;
 KupKose[2].z=Z_min;
 KupKose[3].x=x_min;
 KupKose[3].y=y_min;
 KupKose[3].z=Z_min+maxfark;
 KupKose[4].x=x_min+maxfark;
 KupKose[4].y=y_min+maxfark;
 KupKose[4].z=Z_min;
 KupKose[5].x=x_min+maxfark;
 KupKose[5].y=y_min;
 KupKose[5].z=Z_min+maxfark;
 KupKose[6].x=x_min;
 KupKose[6].y=y_min+maxfark;
 KupKose[6].z=Z_min+maxfark;
 KupKose[7].x=x_min+maxfark;
 KupKose[7].y=y_min+maxfark;
 KupKose[7].z=Z_min+maxfark;
  i=0;
while(i<8)
{
  printf("%d. kose bilgileri %lf %lf %lf \n",i+1,KupKose[i].x,KupKose[i].y,KupKose[i].z);

  fprintf(outputdosyasi,"\n%d. kose bilgileri..%lf %lf %lf \n",i+1,KupKose[i].x,KupKose[i].y,KupKose[i].z);
  i++;
}

}
void NoktaUzakliklariOrtalamasi(Nokta *noktalar,long noktasayisii,FILE *outputdosyasi)
{
    int i,k,m;
    long j=0;
    double toplam=0;
    for(i=0;i<noktasayisii;i++)
    {
        for(k=i+1;k<noktasayisii;k++)
        {
           m=sqrt(pow(noktalar[i].x-noktalar[k].x,2)+pow(noktalar[i].y-noktalar[k].y,2)+pow(noktalar[i].z-noktalar[k].z,2));
           toplam=toplam+m;
           j++;
        }
    }
    toplam=toplam/j;
    printf("ortalamasi ...%lf ",toplam);
    fprintf(outputdosyasi,"tüm noktalarin uzakliklari ortalamasi...%lf",toplam);
}
void NoktaKureicindemi(Nokta *noktalar,long noktasayisii,int a,int b,int c,int r,FILE *outputdosyasi)
{
    int i=0;

     while(i<noktasayisii)
     {
       if((pow((noktalar[i].x-a),2)+pow((noktalar[i].y-b),2)+pow((noktalar[i].z-c),2))<pow(r,2))
       {
           printf("%d . nokta, verilen bilgilerle olusturulan kurenin icindedir\n",i+1);
           fprintf(outputdosyasi,"\n%d . nokta, verilen bilgilerle olusturulan kurenin icindedir\n",i+1);
       }
       i++;
     }
}
int main()
{

    Dosya *dosya ;
    int bilgi[4];
    FILE *outputdosyasi;
    Nokta *noktalar;
    char karakter;
    long noktasayisii;
    DIR *klasorum;
    FILE *fp;
    int kal[5];
    char dosyalar[80][80];  // çekilen dosyaların adını tutacak
    struct dirent *yapi;   //ara pointer
    klasorum=opendir("./Klasor/");   //projenin olduğu yerdeki Klasor adındaki klasoru ac
    int k=0,secim;
    char *textdosya;
    outputdosyasi=fopen("output.txt","w");
    if(klasorum)
    {
        while((yapi=readdir(klasorum))!=NULL)    //readdir klasordeki dosya adlarını ceker yapıya atar
       {
            if(strcmp(yapi->d_name,"..") && strcmp(yapi->d_name,"."))   // readdir . ve .. ları alıyor onları elemek icin
            {
                textdosya = yapi->d_name;
                char gecici[4];
                int uzunluk = strlen(textdosya);      // dosya adı uzunlugunu alır.
                int i;
                  for(i=0;i<4;i++)
                     {
                       gecici[i]=textdosya[uzunluk-4+i];
                     }
                  if( gecici[0]=='.' && gecici[1]=='n' && gecici[2]=='k' && gecici[3]=='t' )  //.nkt kontrolu yapar .nkt olmayanları almaz
                     {
                     strcpy(dosyalar[k],textdosya); // .nkt olanları dosyalar[k]ya atar
                     k++;
                     }
            }
        }
       closedir(klasorum);  //klasor kapatır
     }


for(int l=0;l<k;l++)
  {

    char nktadlari[strlen(dosyalar[l])+8];   //
    snprintf(nktadlari, sizeof(nktadlari),"%s%s","Klasor/"  , dosyalar[l]);
    fp=fopen(nktadlari,"r");
    printf("%s dosyasi acildi \n",dosyalar[l]);
    while(secim!=1)
    {
        printf("secim yapiniz.: "); scanf("%d",&secim);
        if(secim != 1)
        {
            printf("ilk olarak dosyadaki bilgileri kontrol etmemiz gerekiyor , lütfen 1 e basiniz..\n");
        }

    }
    if(secim==1)
    {
         fp=fopen(nktadlari,"r");
         // dosya tipi olusturuldu ve dosya formatindaki bilgiler burada olusturdugumuz referansa eklendi...
         dosya=(Dosya*)malloc(sizeof(Dosya));
         DosyaBilgiOku(fp,dosya);
         printf("dosyadaki baslik bilgileri sisteme ekleniyor..\n");
         printf("version ...%d\n",dosya->version);      // version 1 ile 1000 arasında deger alabilir
         printf("noktalar...%d\n",dosya->noktalar);     // dosyada gösterilen nokta sayisini alir
         printf("alanlar ...%d\n",dosya->alanlar);      //dosyada xyz xyzrgb mi ona bakar.
         printf("data    ...%d\n",dosya->data);         //dosyada verilen noktalar ascii mi binary seeklinde mi
         fclose(fp);
         fp=fopen(nktadlari,"r");
         printf("\n nokta sayisi ... %d \n",NoktaSayisi(fp,dosya));  // nokta verilerinin kaç tane olduðunu gösteriyor
         fclose(fp);
         fp=fopen(nktadlari,"r");
         noktasayisii=NoktaSayisi(fp,dosya);
         fclose(fp);
         fp=fopen(nktadlari,"r");
         kal[0]=DosyaBaslikBilgileri(fp,dosya);
         fclose(fp);
         fp=fopen(nktadlari,"r");
         kal[1]=DosyaNoktaSayisiKontrol(fp,dosya,noktasayisii);
         fclose(fp);
         if(dosya->data == 0 && dosya->alanlar==1)
         {
             fp=fopen(nktadlari,"r");
             DosyaNoktaKontrol_1(fp,dosya,noktasayisii);
             fclose(fp);
             if(h>0)
             {   fopen(nktadlari,"r");
                 DosyaNoktaKontrol_2(fp,dosya,noktasayisii);
                 fclose(fp);
             }
         }

      if( kal[0]==1 && kal[1]==1)
      {
         printf("dosyadaki basliklar , istenilen formata uygundur..\n");
         fp=fopen(nktadlari,"r");
         fputs("\nsecilen dosya uyumludur...\n",outputdosyasi);
        // rgb degerleri verilmediyse fakat dosya xyzrgb formatindaysa rgb degerlerine -1 atadim.
         printf("ekran ciktisi...\n");
         EkranCiktisi(fp,dosya,noktasayisii);
         printf("\ndosyadan nokta bilgileri cekildi...");
         noktalar=malloc(sizeof(Nokta)*noktasayisii);
         fclose(fp);
         fp=fopen(nktadlari,"r");
         DosyadanNoktalariAl(fp,dosya,noktalar);
         fclose(fp);
             while(secim != 0)
         {  outputdosyasi=fopen("output.txt","a");
             printf("secim yapiniz....");
             scanf("%d",&secim);
            switch(secim)
           {
         case 2:
             EnYakinEnUzak(noktalar,noktasayisii,outputdosyasi);
             printf("\neger cikmak istiyorsaniz 0 basin..\n");
             break;

         case 3:
             KupKenarBilgileri(noktalar,noktasayisii,outputdosyasi);
             printf("\neger cikmak istiyorsaniz 0 basin..\n");
             break;

         case 4:
             printf("kurenin x y z yaricap bilgilerini giriniz"); scanf("%d%d%d%d",&bilgi[0],&bilgi[1],&bilgi[2],&bilgi[3]);
             NoktaKureicindemi(noktalar,noktasayisii,bilgi[0],bilgi[1],bilgi[2],bilgi[3],outputdosyasi);
             printf("\neger cikmak istiyorsaniz 0 basin..\n");
             break;
         case 5:
             NoktaUzakliklariOrtalamasi(noktalar,noktasayisii,outputdosyasi);
             printf("\neger cikmak istiyorsaniz 0 basin..\n");
             break;
           }
         }

      }
      else
      {   if(dosya->alanlar==1 && dosya->data==0)  // rgb kontrolu..
           {
              if(h>0)
              {fp=fopen(nktadlari,"r");
              DosyaNoktaKontrol_2(fp,dosya,noktasayisii);
              h=0;
              fclose(fp);
              }
           }

          if(dosya->data==1 && dosya->alanlar==1)
          {

           printf("binary verilere sahip dosyalarda rgb kontrolu yapilmadi..\n");
            //
          }
          printf("dosya baslik bilgileri istenilen formatta degildir....\n");
          secim =0;
      }
    }

}

   /*  char karakter;
    long noktasayisii;
    FILE *fp;
    Dosya *dosya ;
    dosya=(Dosya*)malloc(sizeof(Dosya));
    fp=fopen("C://Users//veriler1.nkt","r");
    DosyaBilgiOku(fp,dosya);
    printf("\n");
    printf("version ...%d\n",dosya->version);
    printf("noktalar...%d\n",dosya->noktalar);
    printf("alanlar ...%d\n",dosya->alanlar);
    printf("data    ...%d\n",dosya->data);
    fclose(fp);
    fp=fopen("C://Users//veriler1.nkt","r");
    printf("\n nokta sayisi ... %d \n",NoktaSayisi(fp,dosya));  // nokta verilerinin kaç tane olduðunu gösteriyor
    printf("\n");
    fclose(fp);
    fp=fopen("C://Users//veriler1.nkt","r"); // dosyada , dosya okumayi saglayan gezgini 0 ladik...
    DosyaNoktaSayisiKontrol(fp,dosya);
    fclose(fp);
    printf("\n");
            if(dosya->data==0)
             {
               fp=fopen("C://Users//veriler1.nkt","r");
               DosyaNoktaKontrol_1(fp,dosya);
               fclose(fp);
             }
    fp=fopen("C://Users//veriler1.nkt","r");
    DosyaBaslikBilgileri(fp,dosya);
    fclose(fp);
    fp=fopen("C://Users//veriler1.nkt","r");
    noktasayisii=NoktaSayisi(fp,dosya);
    Nokta *noktalar;
    noktalar=malloc(sizeof(Nokta)*noktasayisii);
    fclose(fp);

    fp=fopen("C://Users//veriler1.nkt","r");
    DosyadanNoktalariAl(fp,dosya,noktalar);

    //printf("\nC*CcC  %d. nokta %lf C*CCcC\n",2,noktalar[1].x);

    //printf("\nC*CcC  %d. nokta %d C*CCcC\n",4,noktalar[5].b);
    //printf("ayik ol ;)\n");
    fclose(fp);
    EnYakinEnUzak(noktalar,noktasayisii);
    printf("\n");
    KupKenarBilgileri(noktalar,noktasayisii);
    printf("\n");
    NoktaUzakliklariOrtalamasi(noktalar,noktasayisii);
    NoktaKureicindemi(noktalar,noktasayisii,3,2,3,15);
    printf("\n");

*/


    return 0;
}



