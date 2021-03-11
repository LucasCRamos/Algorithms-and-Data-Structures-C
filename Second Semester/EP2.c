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

  polinomios.c

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
#include "polinomios.h"

typedef struct celula
{

  double coeficiente;
  int expoente;
  struct celula *prox;
} Celula;

/*Escolhi fazer uso de listas sem cabeça*/
/*Os termos dos polinomios estarao em ordem decrescente*/

/* Funcoes auxiliares */

void *mallocSafe(unsigned nbytes)
{
  void *p;
  p = malloc(nbytes);
  if (p == NULL)
  {
    printf("Deu ruim! malloc devolveu NULL!\n");
    exit(EXIT_FAILURE);
  }
  return p;
}

Celula *insereOrdena(double x, int y, Celula *ini) /*funcao usada para inserir uma celula no polinomio e ordena-la decrescentemente*/
{
  Celula *p;
  Celula *q;
  Celula *nova;
  nova = mallocSafe(sizeof(Celula));
  nova->coeficiente = x;
  nova->expoente = y;

  int referencia;

  referencia = y;

  if (x != 0)
  {

    if (ini != NULL && ini->expoente == referencia)
    {

      ini->coeficiente = ini->coeficiente + nova->coeficiente;
      free(nova); /*eh preciso dar free, pois caso o expoente seja igual a algum ja existente, os coeficientes irao se agrupar, nao necessitando da nova celula*/
    }

    else if (ini == NULL || ini->expoente < referencia) // se trocar < por >, fica crescente
    {
      nova->prox = ini;
      ini = nova;
    }

    else
    {

      p = ini;
      q = p->prox;
      while (q != NULL && q->expoente > referencia) // se trocar > por <, fica crescente
      {

        p = q;
        q = p->prox;
      }

      if (q != NULL && q->expoente == referencia)
      {

        q->coeficiente = q->coeficiente + nova->coeficiente;
        free(nova); /*eh preciso dar free, pois caso o expoente seja igual a algum ja existente, os coeficientes irao se agrupar, nao necessitando da nova celula*/
      }

      else
      {

        p->prox = nova;
        nova->prox = q;
      }
    }
  }

  return ini;
}

int buscaRemove(Celula **ini) /*funcao que auxilia a remover possiveis 0's como coeficientes, uma vez que nossa celula não deve guardar monomios nulos*/
{
  Celula *p, *q;
  if (*ini == NULL)
    return 0;
  if ((*ini)->coeficiente == 0)
  {
    q = *ini;
    *ini = q->prox;
    free(q);
  }
  else
  {
    p = *ini;
    q = p->prox;
    while (q != NULL && q->coeficiente != 0)
    {
      p = q;
      q = p->prox;
    }
    if (q != NULL)
    {
      p->prox = q->prox;
      free(q);
      return 1;
    }
  }

  return 0;
}

/* Funcoes dadas */

void impr(char c, polinomio p)
{

  printf("\n");

  if (p == NULL)
  { /* se entra neste caso, eh pq tem-se como resultante um polinomio nulo */
    printf("%c(x) = 0", c);
  }

  else
  {

    Celula *q;

    int contador = 0;

    printf("%c(x) = ", c);

    for (q = p; q != NULL; q = q->prox)
    {

      if (contador == 0)
      {
        if (q->expoente == 0)
        {

          printf("%.2lf ", q->coeficiente);
        }

        else
        {

          printf("%.2lf x^%d ", q->coeficiente, q->expoente);
        }

        contador++;
      }

      else
      {

        if (q->expoente == 0)
        {

          printf("+ %.2lf ", q->coeficiente);
        }

        else
        {
          printf("+ %.2lf x^%d ", q->coeficiente, q->expoente);
        }
      }
    }
  }

  printf("\n");
}

polinomio cria()
{

  Celula *p;
  p=NULL;

  return (void *)p;
}

polinomio leia()
{
  double coef;
  int exp;

  Celula *ini;

  ini = NULL;

  do
  {

    scanf("%lf", &coef);

    if (coef != 0)
    {

      scanf("%d", &exp);
      ini = insereOrdena(coef, exp, ini);
    }

  } while (coef != 0);

  return ini;
}

polinomio copia(polinomio p)
{

  Celula *q;
  Celula *auxp;

  auxp = p;

  q = mallocSafe(sizeof(Celula));

  while (auxp != NULL)
  {

    q = insereOrdena(auxp->coeficiente, auxp->expoente, q);

    auxp = auxp->prox;
  }

  buscaRemove(&q);

  return q;
}

polinomio soma(polinomio p, polinomio q)
{

  double coef;
  int exp;

  Celula *sum;
  sum = NULL;
  Celula *paux;
  Celula *qaux;

  paux = p;
  qaux = q;

  while (paux != NULL || qaux != NULL)
  {

    if (qaux != NULL && paux != NULL)
    {

      if (paux->expoente < qaux->expoente)
      {

        coef = paux->coeficiente;
        exp = paux->expoente;
        sum = insereOrdena(coef, exp, sum);
        paux = paux->prox;
      }

      else if (qaux->expoente < paux->expoente)
      {

        coef = qaux->coeficiente;
        exp = qaux->expoente;

        sum = insereOrdena(coef, exp, sum);
        qaux = qaux->prox;
      }

      else
      {

        coef = qaux->coeficiente + paux->coeficiente;
        exp = paux->expoente;

        if (coef != 0)
        {

          sum = insereOrdena(coef, exp, sum);
        }

        paux = paux->prox;
        qaux = qaux->prox;
      }
    }

    else if (paux != NULL && qaux == NULL)
    {

      coef = paux->coeficiente;
      exp = paux->expoente;

      sum = insereOrdena(coef, exp, sum);
      paux = paux->prox;
    }

    else
    {

      coef = qaux->coeficiente;
      exp = qaux->expoente;

      sum = insereOrdena(coef, exp, sum);
      qaux = qaux->prox;
    }
  }

  return sum;
}

polinomio subt(polinomio p, polinomio q)
{

  double coef;
  int exp;

  int remove_zero;

  Celula *subtracao;
  subtracao = NULL;
  Celula *paux;
  Celula *qaux;

  paux = p;
  qaux = q;

  while (paux != NULL || qaux != NULL)
  {

    if (qaux != NULL && paux != NULL)
    {

      if (paux->expoente < qaux->expoente)
      {

        coef = paux->coeficiente;
        exp = paux->expoente;

        subtracao = insereOrdena(coef, exp, subtracao);
        paux = paux->prox;
      }

      else if (qaux->expoente < paux->expoente)
      {

        coef = -qaux->coeficiente;
        exp = qaux->expoente;

        subtracao = insereOrdena(coef, exp, subtracao);
        qaux = qaux->prox;
      }

      else
      {

        coef = paux->coeficiente - qaux->coeficiente;
        exp = paux->expoente;

        if (coef != 0)
        {

          subtracao = insereOrdena(coef, exp, subtracao);
        }

        else
        {

          subtracao = insereOrdena(0, 0, subtracao);
        }

        paux = paux->prox;
        qaux = qaux->prox;
      }
    }

    else if (paux != NULL && qaux == NULL)
    {

      coef = paux->coeficiente;
      exp = paux->expoente;

      subtracao = insereOrdena(coef, exp, subtracao);
      paux = paux->prox;
    }

    else
    {

      coef = -qaux->coeficiente;
      exp = qaux->expoente;

      subtracao = insereOrdena(coef, exp, subtracao);
      qaux = qaux->prox;
    }
  }
  /* nesta funcao, eh possivel que ao subtrairmos, acabemos com um monomio nulo, que nao desejamos guardar */
  /* por este motivo, aciono o buscaRemove para remover eventuais termos nulos */

  do
  {

    remove_zero = buscaRemove(&subtracao);

  } while (remove_zero == 1);

  return subtracao;
}

polinomio nega(polinomio p)
{

  double x;
  int y;

  Celula *aux;
  Celula *aux2;

  aux2 = NULL;

  for (aux = p; aux != NULL; aux = aux->prox)
  {

    x = aux->coeficiente;
    y = aux->expoente;
    aux2 = insereOrdena(-x, y, aux2);
  }

  return aux2;
}

polinomio mult(polinomio p, polinomio q)
{

  Celula *mult;
  Celula *paux;
  Celula *qaux;

  double coef;
  int exp;

  mult = NULL;

  for (paux = p; paux != NULL; paux = paux->prox)
  {

    for (qaux = q; qaux != NULL; qaux = qaux->prox)
    {

      coef = paux->coeficiente * qaux->coeficiente;
      exp = paux->expoente + qaux->expoente;
      mult = insereOrdena(coef, exp, mult);
    }
  }

  return mult;
}

polinomio quoc(polinomio p, polinomio q)
{

  int exp;
  double coef;

  Celula *quociente;
  Celula *temp;
  Celula *auxp;
  Celula *auxq;

  quociente = NULL;
  temp = NULL;
  auxp = p;
  auxq = q;

  if (auxp->expoente < auxq->expoente) /*se o primeiro expoente tiver grau menor que o segundo, o retorno é ele mesmo*/
  {
    return auxp;
  }

  exp = auxp->expoente - auxq->expoente;
  coef = auxp->coeficiente / auxq->coeficiente;

  quociente = insereOrdena(coef, exp, quociente);
  temp = subt(auxp, mult(quociente, auxq));

  if (temp == NULL)
    return quociente;

  while (temp->expoente > auxq->expoente)
  {

    exp = temp->expoente - auxq->expoente;

    coef = temp->coeficiente / auxq->coeficiente;

    quociente = insereOrdena(coef, exp, quociente);

    temp = subt(auxp, mult(quociente, auxq));

    if (temp == NULL)
      return quociente;
  }

  if (temp->expoente == auxq->expoente)
  {

    exp = temp->expoente - auxq->expoente;

    coef = temp->coeficiente / auxq->coeficiente;

    quociente = insereOrdena(coef, exp, quociente);

    temp = subt(auxp, mult(quociente, auxq));

    if (temp == NULL)
      return quociente;
  }

  return quociente;
}

polinomio rest(polinomio p, polinomio q)
{
  return subt(p, (mult(quoc(p, q), q)));
}

void libera(polinomio p)
{

  Celula *aux;
  aux = p;

  while (aux != NULL)
  {

    Celula *lixo = aux->prox;

    free(aux);

    aux = lixo;
  }
}