/*    
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

  AO PREENCHER ESSE CABEÇALHO COM O MEU NOME E O MEU NÚMERO USP, 
  DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESSE PROGRAMA. 
  TODAS AS PARTES ORIGINAIS DESSE EXERCÍCIO-PROGRAMA (EP) FORAM 
  DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUÇÕES DESSE EP
  E QUE PORTANTO NÃO CONSTITUEM PLÁGIO. DECLARO TAMBÉM QUE SOU RESPONSÁVEL
  POR TODAS AS CÓPIAS DESSE PROGRAMA E QUE EU NÃO DISTRIBUI OU FACILITEI A
  SUA DISTRIBUIÇÃO. ESTOU CIENTE QUE OS CASOS DE PLÁGIO SÃO PUNIDOS COM 
  REPROVAÇÃO DIRETA NA DISCIPLINA.

  EP1
  Nome: Lucas Carvalho Ramos
  NUSP: 10693382
  Prof: Cristina Gomes Fernandes


  main.c

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 200

void fractal0(int ordem, double ref, FILE *fp)
{

    if (ordem == 0)
    {

        fprintf(fp, "%lf 0 rlineto\n", ref);
        fprintf(fp, "120 rotate\n");
        fprintf(fp, "%lf 0 rlineto\n", ref);
        fprintf(fp, "120 rotate\n");
        fprintf(fp, "%lf 0 rlineto\n", ref);
    }

    if (ordem == 1)
    {

        fprintf(fp, "%lf 0 rlineto\n", ref);
        fprintf(fp, "300 rotate\n");
        fprintf(fp, "%lf 0 rlineto\n", ref);
        fprintf(fp, "120 rotate\n");
        fprintf(fp, "%lf 0 rlineto\n ", ref);
        fprintf(fp, "300 rotate\n");
        fprintf(fp, "%lf 0 rlineto\n", ref);
    }

    if (ordem >= 2)
    {

        fractal0(ordem - 1, ref, fp);
        fprintf(fp, "300 rotate\n");
        fractal0(ordem - 1, ref, fp);
        fprintf(fp, "120 rotate\n");
        fractal0(ordem - 1, ref, fp);
        fprintf(fp, "300 rotate\n");
        fractal0(ordem - 1, ref, fp);
    }
}

void fractal1(int ordem, double ref, double x, double y, FILE *fp)
{

    if (ordem == -1)
        return;

    double x0 = x - ref / 2;
    double x1 = x + ref / 2;
    double y0 = y - ref / 2;
    double y1 = y + ref / 2;

    fprintf(fp, "%lf %lf moveto\n", x0, y);
    fprintf(fp, "%lf %lf lineto\n", x1, y);

    fprintf(fp, "%lf %lf moveto\n", x0, y0);
    fprintf(fp, "%lf %lf lineto\n", x0, y1);

    fprintf(fp, "%lf %lf moveto\n", x1, y0);
    fprintf(fp, "%lf %lf lineto\n", x1, y1);

    fractal1(ordem - 1, ref / 2, x0, y0, fp);
    fractal1(ordem - 1, ref / 2, x0, y1, fp);
    fractal1(ordem - 1, ref / 2, x1, y0, fp);
    fractal1(ordem - 1, ref / 2, x1, y1, fp);
}

int main()
{
    int desenho, ordem;

    FILE *fp;

    char nomearq[MAX];

    printf("Digite 0 para visualizar a estrela de Koch\n");
    printf("Digite 1 para visualizar a árvore H\n");
    printf("Digite 2 para visualizar o fractal do autor do EP\n");

    scanf("%d", &desenho);

    printf("Qual a ordem da figura a ser gerada?\n");

    scanf("%d", &ordem);

    printf("Digite o nome do arquivo a ser salvo: ");

    scanf("%s*[^\n]", nomearq);

    fp = fopen(nomearq, "w");

    fprintf(fp, "<< /PageSize [595 842] >> setpagedevice\n");

    if (desenho == 0)
    {

        int valor = 1;

        for (int i = 0; i < ordem; i++)
        {

            valor = valor * 3;
        }

        double ref = 550.0 / valor;

        fprintf(fp, "25 200 moveto\n");
        fractal0(ordem, ref, fp);
        fprintf(fp, "120 rotate\n");
        fractal0(ordem, ref, fp);
        fprintf(fp, "120 rotate\n");
        fractal0(ordem, ref, fp);
    }

    if (desenho == 1)
    {

        double ref = 215.0;
        double x = 595.0 / 2;
        double y = 842.0 / 2;

        fractal1(ordem, ref, x, y, fp);
    }

    if (desenho == 2)
    {

        double x = 595.0 / 2;
        double y = 842.0 / 8;
        double ref1 = 500;
        double ref2 = 1000;

        while (ordem != -1)
        {

            double x0 = x - (ref1) / 2;
            double x1 = x + (ref1) / 2;
            double y1 = y + (ref2) / 2;

            fprintf(fp, "%lf %lf moveto\n", x0, y);
            fprintf(fp, "%lf %lf lineto\n", x1, y);

            fprintf(fp, "%lf %lf moveto\n", x, y1);
            fprintf(fp, "%lf %lf lineto\n", x0, y);

            fprintf(fp, "%lf %lf moveto\n", x, y1);
            fprintf(fp, "%lf %lf lineto\n", x1, y);

            ordem = ordem - 1;
            ref1 = ref1 / 2;
            ref2 = ref2 / 2;
        }
    }

    fprintf(fp, "stroke");

    fclose(fp);

    return 0;
}