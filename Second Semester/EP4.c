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

  Nome: Lucas Carvalho Ramos
  NUSP: 10693382

  ep4.c

  Referências: Com exceção das rotinas fornecidas no esqueleto e em sala
  de aula, caso você tenha utilizado alguma referência, liste-as abaixo
  para que o seu programa não seja considerada plágio.
  Exemplo:

  - função mallocSafe copiada de: 

       http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 200
#define false 0
#define true 1

void *mallocSafe (size_t nbytes) {
   void *ptr;
   ptr = malloc (nbytes);
   if (ptr == NULL) {
      printf ("Socorro! malloc devolveu NULL!\n");
      exit (EXIT_FAILURE);
   }
   return ptr;
}

FILE *fp;

int checa(int **lab, int **visitado, int x, int y, int M, int N) /*checa posicoes*/
{
    if (lab[x][y] == 1 || visitado[x][y] == 0)
        return false;

    return true;
}

int ehValido(int x, int y, int M, int N) /*Verifica se faz sentido analisar as posicoes da matriz*/
{
    if (x < M && y < N && x >= 0 && y >= 0)
        return true;

    return false;
}

void menorCaminho(int **matrizAuxiliar, int **lab, int **visitado, int i, int j, int x, int y, int *minimo, int dist, int M, int N) /*Calcula a menor distância do coelho até a cenoura*/
{

    if (i == x && j == y)
    {
        if (dist <= *minimo)
        {
            *minimo = dist;

            for (int i = 0; i < M; i++)
            {

                for (int j = 0; j < N; j++)
                {
                    matrizAuxiliar[i][j] = visitado[i][j];
                }
            }
        }

        return;
    }

    visitado[i][j] = 0;

    if (ehValido(i + 1, j, M, N) && checa(lab, visitado, i + 1, j, M, N))
        menorCaminho(matrizAuxiliar, lab, visitado, i + 1, j, x, y, minimo, dist + 1, M, N);

    if (ehValido(i, j + 1, M, N) && checa(lab, visitado, i, j + 1, M, N))
        menorCaminho(matrizAuxiliar, lab, visitado, i, j + 1, x, y, minimo, dist + 1, M, N);

    if (ehValido(i - 1, j, M, N) && checa(lab, visitado, i - 1, j, M, N))
        menorCaminho(matrizAuxiliar, lab, visitado, i - 1, j, x, y, minimo, dist + 1, M, N);

    if (ehValido(i, j - 1, M, N) && checa(lab, visitado, i, j - 1, M, N))
        menorCaminho(matrizAuxiliar, lab, visitado, i, j - 1, x, y, minimo, dist + 1, M, N);

    visitado[i][j] = 1;
}

int menu()
{

    int opcao;

    printf("0: carregar um novo labirinto e posição inicial do Herbert\n");
    printf("1: dar nova posicao inicial do Herbert no mesmo labirinto\n");
    printf("2: sair do programa\n\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &opcao);
    printf("\n");

    return opcao;
}

int funcaoAuxiliar(FILE *fp) /*Funcao que auxilia a leitura do arquivo*/
{
    int num, aux, c;

    while (1)
    {
        aux = fscanf(fp, "%d", &num);

        if (aux == 1)
        {
            return num;
        }

        c = fgetc(fp);

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

void imprimeLabirintoInicial(FILE *fp) /*Imprime o labirinto inicial contido no arquivo texto*/
{

    int M, N;

    M = funcaoAuxiliar(fp);
    N = funcaoAuxiliar(fp);

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (j <= N - 2)
            {
                printf("%d ", funcaoAuxiliar(fp));
            }

            else
            {
                printf("%d\n", funcaoAuxiliar(fp));
            }
        }
    }

    printf("\n");
}

void imprimeLabirintoFinal(int **matrizAuxiliar, int **lab, int M, int N, int p1, int p2) /*Imprime o labirinto com o percurso, e posições do coelho e da cenoura*/
{

    for (int i = 0; i < M; i++)
    {

        for (int j = 0; j < N; j++)
        {

            if (matrizAuxiliar[i][j] == 0 && !(i == p1 - 1 && j == p2 - 1))
                lab[i][j] = 4;

            if (j <= N - 2)

                if (lab[i][j] == 2)
                    printf("H ");
                else if (lab[i][j] == 3)
                    printf("C ");
                else if (lab[i][j] == 4)
                    printf("* ");
                else
                    printf("%d ", lab[i][j]);

            else if (lab[i][j] == 2)
                printf("H\n");
            else if (lab[i][j] == 3)
                printf("C\n");
            else if (lab[i][j] == 4)
                printf("*\n");
            else
                printf("%d\n", lab[i][j]);
        }
    }

    printf("\n");
}

void libera(int **matrizAuxiliar, int **lab, int **visitado, int M) /*Funcao que desaloca as memórias alocadas*/
{

    for (int i = 0; i < M; i++)
    {
        free(matrizAuxiliar[i]);
        free(lab[i]);
        free(visitado[i]);
    }

    free(matrizAuxiliar);
    free(lab);
    free(visitado);
}

int main()
{

    char nomearq[MAX]; /*string que guarda nome do arquivo que contem o labirinto*/

    int M, N; /* numero de linhas e colunas, respectivamente*/

    int p1, p2; /*variaveis que guardam a posicao inicial do coelho*/

    int cenouras; /*variavel que guarda numero de cenouras*/

    int c1, c2; /*variaveis que guardam as coordenadas da cenoura*/

    int minimo; /*guarda o valor da distancia minima*/

    int men;

    printf("*************************\n");
    printf("Carrotsvile search engine\n");
    printf("*************************\n\n");

    men = menu();

    while (men != 2)

    {
        if (men == 0)
        {

            printf("Digite o nome do arquivo com o labirinto: ");
            scanf("%s", nomearq);
            printf("\nLabirinto:\n");
            fp = fopen(nomearq, "r");

            if (fp == NULL)
            {
                printf("\nProblema na abertura do arquivo!\n");
                exit(EXIT_FAILURE);
            }

            imprimeLabirintoInicial(fp);

            fclose(fp);
        }

        if (men == 0 || men == 1)
        {

            fp = fopen(nomearq, "r");

            if (fp == NULL)
            {
                printf("\nProblema na abertura do arquivo!\n");
                exit(EXIT_FAILURE);
            }

            M = funcaoAuxiliar(fp);
            N = funcaoAuxiliar(fp);

            int **lab = (int **)mallocSafe(M * sizeof(sizeof(int *)));

            for (int i = 0; i < M; i++)
            {

                lab[i] = (int *)mallocSafe(N * sizeof(int));
            }

            int **matrizAuxiliar = (int **)mallocSafe(M * sizeof(sizeof(int *)));

            for (int i = 0; i < M; i++)
            {

                matrizAuxiliar[i] = (int *)mallocSafe(N * sizeof(int));
            }

            int **visitado = (int **)mallocSafe(M * sizeof(sizeof(int *)));

            for (int i = 0; i < M; i++)
            {

                visitado[i] = (int *)mallocSafe(N * sizeof(int));
            }

            for (int i = 0; i < M; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    lab[i][j] = funcaoAuxiliar(fp);
                }
            }

            printf("Digite a posicao inicial do Herbert: ");
            scanf("%d %d", &p1, &p2);
            printf("\n");

            cenouras = funcaoAuxiliar(fp);

            minimo = M * N;

            for (int i = 0; i < M; i++)
            {

                for (int j = 0; j < N; j++)
                {

                    matrizAuxiliar[i][j] = 1;
                }
            }

            while (cenouras > 0)
            {

                for (int i = 0; i < M; i++)
                {

                    for (int j = 0; j < N; j++)
                    {

                        visitado[i][j] = 1;
                    }
                }

                c1 = funcaoAuxiliar(fp);
                c2 = funcaoAuxiliar(fp);

                menorCaminho(matrizAuxiliar, lab, visitado, p1 - 1, p2 - 1, c1 - 1, c2 - 1, &minimo, 0, M, N);

                lab[p1 - 1][p2 - 1] = 2;
                lab[c1 - 1][c2 - 1] = 3;

                cenouras--;
            }

            if (minimo != M * N)
            {

                if (minimo==0)
                printf("O Herbert já estava em cima da cenoura e a comeu rapidamente :)\n\n");
                else
                printf("O Herbert achou uma cenoura em %d passos!\n\n", minimo);
            }

            else
            {
                printf("O Herbert não achou nenhuma cenoura!!! :(\n\n");
            }

            imprimeLabirintoFinal(matrizAuxiliar, lab, M, N, p1, p2);

            libera(matrizAuxiliar, lab, visitado, M);

            fclose(fp);
        }

        men = menu();
    }

    printf("Tchau, Herbert!");

    return 0;
}