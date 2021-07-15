#include <graphics.h>
#include <stdio.h>
#include<stdlib.h>
#include <conio.h>
#include<math.h>

int main()
{
    initwindow(1000,1000,"prolab.exe");

    for(int i=0; i<500; i++)
    {
        setcolor(DARKGRAY);
        line(1000-(20*i),1,1000-(20*i),1000);
        line(1,1000-(20*i),1000,1000-(20*i));
    }

    for(int i=0; i<500; i++)
    {
        setcolor(WHITE);
        line(1000-(20*i),497,1000-(20*i),503);
        line(497,1000-(20*i),503,1000-(20*i));

    }

    line(1,500,1000,500);
    line(500,1,500,1000);
    char sayilar[25];
    settextstyle(SMALL_FONT, HORIZ_DIR, 4);

    for(int j=1; j<25; j++)
    {
        sprintf(sayilar,"%d",j);
        outtextxy(506,480-(20*(j-1)),sayilar);
        outtextxy(520+(20*(j-1)),506,sayilar);
    }

    for(int j=1; j<25; j++)
    {
        sprintf(sayilar,"-%d",j);
        outtextxy(506,520+(20*(j-1)),sayilar);
        outtextxy(480-(21*(j-1)),506,sayilar);
    }

    FILE *filep = fopen("inputs.txt","r");
    int sayac;
    sayac = 0;
    int a[1000], i=0, j=0, s=0;

    while(!feof(filep))
        fscanf(filep, "%d", &a[i++]);

    while (j < i)
    {
        j++;
        sayac++;
    }
    // printf("%d\n",sayac);

    int outputs[sayac/2][2];

    for(int i=0; i<sayac/2; i++)
    {
        for(int j=0; j<2; j++)
        {
            outputs[i][j]=a[s];
            s++;
        }
    }

    if(filep != NULL)
    {
        for(int i = 0; i < sayac/2; i++)
        {
            printf("%d.Nokta: ",i+1);
            for(int j = 0; j < 2; j++)
            {
                printf("%d ",outputs[i][j]);
            }
            printf("\n");
        }
    }

    else if (filep == NULL)
    {
        printf("dosya yok\n");
    }

    float nokta1[1][2],nokta2[1][2];
    float gecici;

    float x1,y1,x2,y2;
    float uzaklik=0.0;

    for(int i = 0; i < (sayac/2) - 1; i++)
    {
        for(int j = i; j < (sayac/2) - 1; j++)
        {
            x1 = outputs[i][0];
            x2 = outputs[j+1][0];
            y1 = outputs[i][1];
            y2 = outputs[j+1][1];

            gecici = sqrt(pow((x1-x2),2)+pow((y1-y2),2));

            if(gecici > uzaklik)
            {
                uzaklik = gecici;
                nokta1[0][0] = x1;
                nokta1[0][1] = y1;
                nokta2[0][0] = x2;
                nokta2[0][1] = y2;
            }
        }
    }

   float merkezx, merkezy, yaricap=0;

    merkezx = (nokta1[0][0]+nokta2[0][0])/2.0;
    merkezy = (nokta1[0][1]+nokta2[0][1])/2.0;

    for (int i=0; i<sayac/2; i++)
    {
        circle(500 + (20*outputs[i][0]), 500 - (20*outputs[i][1]), 5);
        floodfill(500 + (20*outputs[i][0]), 500 - (20*outputs[i][1]), WHITE);
    }

    float nokta[1][2];
    int flag = 0;

    for(int i = 0; i < (sayac/2); i++)
    {
            x1 = outputs[i][0];
            y1 = outputs[i][1];

            gecici = sqrt(pow((x1-merkezx),2)+pow((y1-merkezy),2));
            if(gecici > (uzaklik/2.0))
            {
                flag = 1;
               yaricap = gecici;
                nokta[0][0] = x1;
                nokta[0][1] = y1;
            }
            else
                yaricap = uzaklik/2.0;

    }

    if(flag == 1)
    {
       yaricap = 0.0;

        x1 = nokta[0][0];
        y1 = nokta[0][1];

        gecici = sqrt(pow((x1-merkezx),2)+pow((y1-merkezy),2));

        printf("\n%f\n", gecici);

        if(gecici > yaricap)
        {
            yaricap = gecici;
            nokta[0][0] = x1;
            nokta[0][1] = y1;
        }

        x1 = nokta1[0][0];
        y1 = nokta1[0][1];

        gecici = sqrt(pow((x1-merkezx),2)+pow((y1-merkezy),2));

        printf("\n%f\n", gecici);

        if(gecici > yaricap)
        {
            yaricap = gecici;
            nokta[0][0] = x1;
            nokta[0][1] = y1;
        }

        x1 = nokta2[0][0];
        y1 = nokta2[0][1];

        gecici = sqrt(pow((x1-merkezx),2)+pow((y1-merkezy),2));

        printf("\n%f\n", gecici);

        if(gecici > yaricap)
        {
            yaricap = gecici;
            nokta[0][0] = x1;
            nokta[0][1] = y1;
        }
    }

    printf("\n\nYaricap: %f\n\n",yaricap);
    printf("Merkez Koordinatlari: %f %f\n\n",merkezx,merkezy);

    circle(500 + (20 * merkezx), 500 - (20 * merkezy), 3);
    floodfill(500 + (20 * merkezx), 500 - (20 * merkezy),WHITE);
    circle((20 * merkezx) + 500, 500 - (20 * merkezy), 20 * yaricap);

    fclose(filep);

    getch();
    closegraph();
}
