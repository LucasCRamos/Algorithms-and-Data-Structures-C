/***************************************************************/
/**                                                           **/
/** Lucas Carvalho Ramos                 Numero USP: 10693382 **/
/** Exercicio-Programa 03                                     **/
/** Professor: Carlos Eduardo Ferreira                        **/
/** Turma: 01                                                 **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX        400
#define MAX2    160000
#define FNMAX      200

int FuncaoAuxiliar (FILE *fp) /*Funcao que auxilia a intLeDesenho*/
{
    int num, aux, c;

    while (1)
    {
        aux = fscanf (fp, "%d", &num);

        if (aux == 1)
        {
            return num;
        }

        c = fgetc (fp);

        if (c < 0)
        {
            return c;
        }

        if (c != '\n')
        {
            return -1;
        }

    }

    return 0;
}

int LeDesenho( char nomearq[FNMAX], int M[MAX][MAX], int *pm, int *pn, int *pmax )
{

    FILE *fp ;
    char help[128] ;
    int  aux, i, j ;

    if (!(fp = fopen(nomearq, "r")))
    {
        printf("Erro na abertura do arquivo %s\n\n", nomearq);
        printf(" ERRO: Operacao abortada devido a erro na leitura\n\n\n");
        return 1;
    }

    aux = fscanf(fp, "%s", help) ;

    if(aux != 1)
    {
        printf("Erro na leitura do arquivo %s\n", nomearq) ;
        fclose(fp) ;
        return 1 ;
    }

    if(strcmp(help,"P2") != 0)
    {
        printf("Formato desconhecido\n\n");
        printf(" ERRO: Operacao abortada devido a erro na leitura\n\n\n");
        fclose(fp) ;
        return 1 ;
    }

    *pn = FuncaoAuxiliar(fp);
    *pm = FuncaoAuxiliar(fp);
    *pmax = FuncaoAuxiliar(fp);

    if(*pm == -1 || *pn == -1 || *pmax == -1)
    {
        printf ("%d %d %d\n", *pn, *pm, *pmax);
        printf("Formato incorreto\n\n");
        printf(" ERRO: Operacao abortada devido a erro na leitura\n\n\n");
        fclose(fp) ;
        return 1 ;
    }

    if(*pm>MAX || *pn>MAX)
    {
        printf("Dimensao da matriz e' maior que o permitido\n\n") ;
        printf(" ERRO: Operacao abortada devido a erro na leitura\n\n\n");
        fclose(fp);
        return 1 ;
    }

    for(i=0; i<*pm; i++)
    {
        for(j=0; j<*pn; j++)
        {
            M[i][j]=FuncaoAuxiliar(fp);
            aux=M[i][j];

            if(aux == -1)
            {
                printf("Formato ou dado incorreto\n") ;
                fclose(fp) ;
                return 1 ;
            }
        }
    }

    fclose(fp) ;

    return 0 ;

}

int LeTexto(char nomearq[FNMAX], char T[MAX2], int *pk)
{
    FILE *fp;
    int i;

    fp = fopen(nomearq, "r");

    i = 0;

    while (fscanf(fp, "%c", &T[i]) > 0)
    {

        i++;

        if (T[i] < 0)
        {
            printf ("Caractere %c desconhecido. Codigo do caractere: %d\n\n", T[i], T[i]);
            printf(" ERRO: Operacao abortada devido a erro na leitura\n\n\n");
            return 1 ;

        }

    }

    *pk=i;

    T[i] = '\0';

    fclose(fp);

    return 0;
}

int ProximosBBits( char T[MAX2], int b, int *pik, int *pib )
{

    int B,proximo;

    B=pow(2,b);

    if(*pib>=8)
    {

        *pib=0;
        *pik=*pik+1;
    }

    *pib=b+*pib;

    proximo = T[*pik]%B;

    T[*pik]=T[*pik]/B;

    return proximo;

}

void Codifica( int D[MAX][MAX], int m, int n, char T[MAX2], int k, int D1[MAX][MAX], int b, int d, int modo )
{

    int ik,ib,i,j,B,soma;

    B = pow(2,b);

    ik=0;

    ib=0;

    soma=0;

    if(b==1 || b==2 || b==4 || b==8)
    {

        for(i=0; (i+d-1)<m; i=i+d)
        {

            for(j=0; (j+d-1)<n; j=j+d)
            {


                if(j==0 && i==0)
                {

                    D1[d-1][d-1]=((D[d-1][d-1])/B)*B + ((D[d-1][d-1]+b)%B);

                }

                else

                {

                    soma=ProximosBBits(T,b,&ik,&ib);

                    D1[i+d-1][j+d-1] = (D[i+d-1][j+d-1]/B)*B + (D[i+d-1][j+d-1]+soma)%B;


                }

                if(modo==1 && !(j==0 && i==0))
                {

                    printf("(%d,%d) bits %d original %02x codificado %02x\n",(i+d-1),(j+d-1),soma,D[i+d-1][j+d-1],D1[i+d-1][j+d-1]);


                }

            }

        }

    }
}

int Maximo( int D1[MAX][MAX], int m, int n )
{

    int max,i,j;

    max=0;

    for (i=0; i<m; i++)
    {

        for (j=0; j<n; j++)
        {

            if (D1[i][j]>max)
            {

                max=D1[i][j];

            }

        }

    }

    return max;

}

int BeDe( int k, int m, int n, int *pb, int *pd )
{

    int min;

    if(m >= n)
    {

        min=n;

    }

    else
    {
        min=m;

    }

    if(k==0)
    {
        *pb=0;
        *pd=min;

        return 0;
    }

    else
    {
        *pb=1;
        *pd=min;
    }

    while(*pb<=8 && *pd>=1)
    {

        if   (((m/(*pd))*(n/(*pd))*(*pb)) >= (8*k + *pb) )
        {

            return 0;

        }

        else

        {

            *pd=*pd-1;

        }

        if(*pd==0 && *pb!=8)
        {

            *pb=*pb*2;
            *pd=min;
        }

        else if(*pd==0 && *pb==8)
        {

            printf(" k=%d\n\n",k);
            printf(" ERRO: Nao e possivel ocultar os %d caracteres da mensagem\n\n",k);
            printf(" ERRO: Operacao abortada pois mensagem nao pode ser ocultada\n\n\n");
            return 1;

        }


    }

    return 0;

}

void DeBeDe( int D[MAX][MAX], int D1[MAX][MAX], int m, int n, int *pb, int *pd )
{

    int i,j,sai;

    sai=0;

    for (i=0; i<m && sai==0; i++)
    {
        for(j=0; j<n && sai==0; j++)
        {

            if((D1[i][j] - D[i][j]) !=0 && sai==0)
            {

                *pd=i+1;


                if(((D1[i][j] - D[i][j] + 256) % 2)==1)
                {
                    *pb=1;
                }
                if(((D1[i][j] - D[i][j] + 256) % 4)==2)
                {
                    *pb=2;
                }
                if(((D1[i][j] - D[i][j] + 256) % 16)==4)
                {
                    *pb=4;
                }
                if(((D1[i][j] - D[i][j] + 256) % 256)==8)
                {
                    *pb=8;

                }

                sai=1;

            }

        }

    }

}

int DeCodifica( int D[MAX][MAX], int D1[MAX][MAX], int m, int n, int b, int d, char T[MAX2], int modo )
{

    int potencia,B,i,j,cont,incremento,acumulado;

    potencia=0;

    B = pow(2,b);

    cont=0;

    incremento=0;

    acumulado=0;

    for(i=0; (i+d-1)<m; i=i+d)
    {

        for(j=0; (j+d-1)<n; j=j+d)
        {

            if(j==0 && i==0) j=d;


            potencia=pow(pow(2,b),cont);


            acumulado=acumulado+((potencia)*((D1[i+d-1][j+d-1]-D[i+d-1][j+d-1]+256)%B));


            cont=cont+1;

            if (cont==(8/b))
            {

                T[incremento]=acumulado;

                acumulado=0;

                cont=0;

                incremento++;


            }

            if(modo==1)

            {

                printf("(%d,%d) bits %d original %02x codificado %02x\n",(i+d-1),(j+d-1),((D1[i+d-1][j+d-1]-D[i+d-1][j+d-1]+256)%B),D[i+d-1][j+d-1],D1[i+d-1][j+d-1]);


            }

        }

    }

    return 0;

}

int LeTextoDecod(char T[MAX2], int *pk)
{

    int i;

    i = 0;

    while (T[i]!='\0')
    {

        i++;

    }

    *pk=i;


    return 0;
}

int EscreveTexto(char nomearq[FNMAX], char T[MAX2], int k)
{

    FILE *fp;
    int  i;
    char c;

    if (!(fp = fopen(nomearq, "w")))
    {
        printf("Erro na abertura do arquivo %s\n\n", nomearq);
        printf(" ERRO: Operacao abortada devido a erro na leitura\n\n\n");
        return 1;
    }

    i = 0 ;

    while(i<k)
    {

        c = T[i];

        if (c < 0)
        {
            printf ("Caractere %c desconhecido. Codigo do caractere: %d\n", c, c);
            fclose(fp) ;
            return 1 ;
        }

        fprintf(fp, "%c", c) ;

        i++ ;
    }

    fclose(fp) ;

    return 0 ;
}

int EscreveDesenho( char nomearq[FNMAX], int D1[MAX][MAX], int m, int n, int max)
{

    FILE *fp ;

    int  i,j;

    char nomearq2[FNMAX];

    scanf("%s*[^\n]", nomearq2);

    fp = fopen(nomearq2, "w");

    fprintf(fp, "P2\n") ;
    fprintf(fp, "%d %d\n", n, m) ;
    fprintf(fp, "%d\n", max) ;

    for(i=0; i<m; i++)
    {
        for(j=0; j<n; j++)
        {
            fprintf(fp, "%03d ", D1[i][j]) ;
        }
        fprintf(fp, "\n") ;
    }

    fclose(fp) ;
    return 0 ;

}

int main()
{
    FILE *fp;

    int k;

    int b,d;

    int i,j;

    int erro;

    int modo;

    int m,n,valmax; /*numero de linhas,colunas e valor maximo*/

    int max;

    int m2,n2;

    int opcao; /*qualquer um diferente de 0*/

    int D[MAX][MAX];

    int D1[MAX][MAX];

    char nomearq[FNMAX]; /*string que recebe os nomes dos arquivos*/

    char T[MAX2];

    k=0;

    erro=0;

    modo=0;

    opcao=5;

    while(opcao!=0)
    {

        if(modo==0)
        {

            printf("Digite a operacao desejada:\n");
            printf("   1. Codificar\n");
            printf("   2. Decodificar\n");
            printf("   3. Mostrar mensagem\n");
            printf("   4. Ativar modo verborragico\n");
            printf("   0. Finalizar\n\n");

            printf("OPCAO: ");
            scanf ("%d",&opcao);

        }

        else
        {

            printf("Digite a operacao desejada:\n");
            printf("   1. Codificar\n");
            printf("   2. Decodificar\n");
            printf("   3. Mostrar mensagem\n");
            printf("   4. Desativar modo verborragico\n");
            printf("   0. Finalizar\n\n");

            printf("OPCAO: ");
            scanf ("%d",&opcao);


        }

        while(opcao==4)
        {

            if (modo==0)
            {

                modo=1;

                printf(" Modo verborragico ativado\n\n");
                printf("Digite a operacao desejada:\n");
                printf("   1. Codificar\n");
                printf("   2. Decodificar\n");
                printf("   3. Mostrar mensagem\n");
                printf("   4. Desativar modo verborragico\n");
                printf("   0. Finalizar\n\n");

                printf("OPCAO: ");
                scanf ("%d",&opcao);

            }

            else if (modo==1)
            {

                modo=0;
                printf(" Modo verborragico desativado\n\n");
                printf("Digite a operacao desejada:\n");
                printf("   1. Codificar\n");
                printf("   2. Decodificar\n");
                printf("   3. Mostrar mensagem\n");
                printf("   4. Ativar modo verborragico\n");
                printf("   0. Finalizar\n\n");

                printf("OPCAO: ");
                scanf ("%d",&opcao);

            }

        }

        if (opcao==1)
        {

            printf("Arquivo que contem o desenho original: ");

            scanf("%s*[^\n]", nomearq);

            erro=LeDesenho(nomearq,D,&m,&n,&valmax);

            if(erro==0)
            {

                printf("m = %d ",m);
                printf("n = %d\n",n);

                for(i=0; i<m; i++)
                {

                    for(j=0; j<n; j++)
                    {

                        D1[i][j]=D[i][j];

                    }

                }

                printf("Arquivo que contem a mensagem a ser ocultada: ");

                scanf("%s*[^\n]", nomearq);

                if (!(fp = fopen(nomearq, "r")))
                {
                    printf("Erro na abertura do arquivo %s\n\n", nomearq);
                    printf(" ERRO: Operacao abortada devido a erro na leitura\n\n\n");
                    erro=1;
                }

                if(erro==0)
                {

                    i = 0;

                    while (fscanf(fp, "%c", &T[i]) > 0)
                    {

                        i++;

                    }

                    T[i] = '\0';

                    erro=LeTexto(nomearq,T,&k);

                    if (erro==0 )
                    {

                        erro=BeDe(k,m,n,&b,&d); /*colocar mensagem de erro la dentro mesmo*/

                        if(erro==0)
                        {

                            if(b==0 && k==0 && d!=0)
                            {

                                printf("Mensagem muito longa\n\n");
                                printf(" ERRO: Operacao abortada devido a erro na leitura\n\n\n");
                                erro=1;
                            }

                            if(erro==0)
                            {

                                printf(" k = %d\n",k);
                                printf(" b = %d ",b);
                                printf(" d = %d\n",d);

                                Codifica(D,m,n,T,k,D1,b,d,modo);

                                printf("Gravar desenho esteganografado em: ");


                                max = Maximo(D1,m,n);

                                if(valmax>max) max=valmax;

                                EscreveDesenho(nomearq,D1,m,n,max);

                                printf("\n\n");

                                fclose(fp);
                            }
                        }
                    }
                }
            }
        }

        if (opcao==2)

        {

            printf("Arquivo que contem o desenho original: ");

            scanf("%s*[^\n]", nomearq);

            erro=LeDesenho(nomearq,D,&m,&n,&valmax);

            if (erro==0)
            {

                printf(" m = %d ",m);
                printf("n = %d\n",n);

                printf("Arquivo que contem o desenho esteganografado: ");

                scanf("%s*[^\n]", nomearq);

                erro=LeDesenho(nomearq,D1,&m2,&n2,&valmax);


                if (erro==0)
                {

                    if(m2!=m || n2!=n)
                    {

                        printf(" m = %d ",m2);
                        printf("n = %d\n\n",n2);
                        printf(" ERRO: Operacao abortada. Desenhos devem ser do mesmo tamanho\n\n\n");
                        erro=1;

                    }


                    else
                    {

                        printf(" m = %d ",m);
                        printf(" n = %d\n",n);

                        DeBeDe(D,D1,m,n,&b,&d);

                        printf(" b = %d ",b);
                        printf(" d = %d\n",d);

                        DeBeDe(D,D1,m,n,&b,&d);

                        DeCodifica(D,D1,m,n,b,d,T,modo);

                        LeTextoDecod(T,&k);

                        printf(" k = %d\n",k);

                        printf("Gravar mensagem codificada em: ");

                        scanf("%s*[^\n]", nomearq);

                        printf("\n\n");

                        fp=fopen(nomearq,"w");

                        erro=EscreveTexto(nomearq,T,k);

                        fclose(fp);

                    }

                }

            }

        }

        if (opcao==3)
        {


            printf(" Arquivo que contem a mensagem: ");

            scanf("%s*[^\n]", nomearq);

            if (!(fp = fopen(nomearq, "r")))
            {
                printf("Erro na abertura do arquivo %s\n\n", nomearq);
                printf(" ERRO: Operacao abortada devido a erro na leitura\n\n\n");
            }

            else
            {

                i = 0;


                while (fscanf(fp, "%c", &T[i]) > 0)
                {

                    i++;

                }

                T[i] = '\0';

                erro=LeTexto(nomearq,T,&k);

                if (erro==0)
                {

                    if(k>MAX2)
                    {
                        erro=1;
                        printf("Mensagem muito longa\n\n");
                        printf(" ERRO: Operacao abortada devido a erro na leitura\n\n\n");
                    }

                    if(erro==0)
                    {

                        printf("k = %d\n\n\n",k);
                        printf(" MENSAGEM contida no arquivo %s (tudo entre ---> e <---)\n",nomearq);
                        printf("--->");
                        printf("%s",T);
                        printf("<---\n\n\n");

                    }

                }

            }

            fclose(fp);

        }

    }

    return 0;
}
