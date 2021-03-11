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

  ep3.c

  funcao char *infixaParaPosfixa inspirada no material da professora da aula 9 - dia 21 de setembro

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "polinomios.h"

#define MAX 100

char *infixaParaPosfixa(char *inf);
void *mallocSafe(unsigned int n);

char *infixaParaPosfixa(char *inf)
{
    char *posf;
    int n = strlen(inf);
    int i;    /*percorre infixa*/
    int j;    /*percorre posfixa*/
    char *s;  /*pilha*/
    int topo; /*topo da pilha*/
    char x;   /*item do topo da pilha*/

    posf = (char *)mallocSafe((n + 1) * sizeof(char));

    s = mallocSafe(n * sizeof(char));
    topo = 0;

    for (i = j = 0; i < n; i++)
    {

        switch (inf[i])
        {

        case '~':
        case '(':
            s[topo++] = inf[i];
            break;
        case ')':
            while ((x = s[--topo]) != '(')
                posf[j++] = x;
            break;

        case '+':
        case '-':
            while (topo != 0 && (x = s[topo - 1]) != '(')
                posf[j++] = s[--topo];
            s[topo++] = inf[i];
            break;

        case '*':
        case '/':
        case '%':
            while (topo != 0 && (x = s[topo - 1]) != '(' && (x) != '+' && (x) != '-')
                posf[j++] = s[--topo];
            s[topo++] = inf[i];
            break;

        default:
            if (inf[i] != ' ')
                posf[j++] = inf[i];
        }
    }
    while (topo != 0)
        posf[j++] = s[--topo];

    posf[j] = '\0';

    free(s);

    return posf;
}

void descarta_resto_da_linha()
{
    char c;

    do
    {
        scanf("%c", &c);
    } while (c != '\n' && c != EOF);
}

polinomio calculaExpressao(char posfixa[], polinomio var[])
{

    int tam;

    polinomio p, q, res;

    p = NULL;

    q = NULL;

    int topo = 0;

    int aux;

    tam = strlen(posfixa);

    polinomio *pilha;

    pilha = (polinomio *)mallocSafe((tam) * sizeof(polinomio));

    for (int i = 0; i < tam; i++)
    {

        switch (posfixa[i])
        {

        case '+':

            q = pilha[--topo];
            p = pilha[--topo];

            pilha[topo++] = soma(p, q);

            break;

        case '-':

            q = pilha[--topo];
            p = pilha[--topo];

            pilha[topo++] = subt(p, q);

            break;

        case '*':

            q = pilha[--topo];
            p = pilha[--topo];

            pilha[topo++] = mult(p, q);

            break;

        case '/':

            q = pilha[--topo];
            p = pilha[--topo];

            pilha[topo++] = quoc(p, q);

            break;

        case '%':

            q = pilha[--topo];
            p = pilha[--topo];

            pilha[topo++] = rest(p, q);

        case '~':

            p = pilha[--topo];
            pilha[topo++] = nega(p);

            break;

        default: /* só os polinomios */

        {

            aux = posfixa[i] - 'a';

            pilha[topo++] = var[aux];
        }
                }
    }

    res = pilha[topo - 1];

    free(pilha);

    return res;
}

int main()
{

    polinomio var[26];

    polinomio resultante;

    char expressao[MAX];

    char *posfixa;

    char poli, comando;

    int aux;

    int quit = 0;

    printf("*************************\n");
    printf("Calculadora de polinomios\n");
    printf("*************************\n");

    for (int i = 0; i < 26; i++)
    {
        var[i] = cria();
    }

    do
    {
        printf("\nDigite uma expressão ou quit para sair do programa: ");
        scanf("%c", &poli);
        scanf("%c", &comando);

        aux = poli - 'a'; /*guarda a posição do primeiro polinomio digitado*/

        if (comando != '?' && comando != ':')
        {

            if (comando == '=')
            {

                scanf("%s", expressao);

                posfixa = infixaParaPosfixa(expressao);

                resultante = calculaExpressao(posfixa, var);

                var[aux] = resultante;

                impr(poli, resultante);
            }

            else
            {

                scanf("%s", expressao);
                if (poli == 'q' && comando == 'u' && expressao[0] == 'i' && expressao[1] == 't')
                {

                    quit = 1;
                }
            }
        }

        else if (comando == '?')
        {

            impr(poli, var[aux]);
        }

        else if (comando == ':')
        {

            var[aux] = leia(var[aux]);
            impr(poli, var[aux]);
        }

        descarta_resto_da_linha();

    } while (quit != 1);

    return 0;
}