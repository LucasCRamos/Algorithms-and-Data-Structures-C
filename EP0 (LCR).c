/***************************************************************/
/**                                                           **/
/**   Lucas Carvalho Ramos          Número USP: 10693382      **/
/**   Exercício-Programa EP0                                  **/
/**   Professor: Carlos Eduardo Ferreira                      **/
/**   Turma: (01)                                             **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>

int main() {

  int numero,T0=0,T1=0,T2=0,T3=1,T4=1;

  printf("Digite a posicao do numero a ser analisado: ");
  scanf("%d",&numero);

  if (numero==3){

    printf("O numero que ocupa a posicao desejada e: %d",T3);

  }

  else if (numero<3){

    printf("O numero que ocupa a posicao desejada e: %d",T2);

  }

  else {

  while(numero>=4){

    T4=T0+T1+T2+T3;
    T0=T1;
    T1=T2;
    T2=T3;
    T3=T4;

    numero=numero-1;

  }

    printf("O numero que ocupa a posicao desejada e: %d",T4);

  }

    return 0;

}
