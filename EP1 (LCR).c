/***************************************************************/
/**                                                           **/
/**   Lucas Carvalho Ramos          Número USP: 10693382      **/
/**   Exercício-Programa EP1                                  **/
/**   Professor: Carlos Eduardo Ferreira                      **/
/**   Turma: (01)                                             **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>

int main()
{

    int P1 = 2, P2 = 3, P3 = 5, P4 = 7, P5 = 11, i, j; /* os cinco primeiros numeros primos*/

    int numero; /* numero a ser digitado para verificacao*/

    int primo = 0; /* variavel que quando vale 1 indica que um novo numero primo foi encontrado e possibilita as passagens dos primos adiante*/

    int resultado = -1; /* quando vale 0 indica que o numero em analise nao e primo*/

    int sair = 0; /* variavel utilizada para sair do for a fim de evitar todas as verificacoes e impressoes desnecessarias*/

    printf("EP1: Soma dos quadrados de primos consecutivos\n");
    printf("Digite um numero (0 < n < 10^8): ");
    scanf("%d", &numero);

    while (numero != 0)
    {

        sair = 0;

        if (numero < 87)
        {

            printf("Nao existem 4 primos consecutivos cujos quadrados somam %d\n",numero);

        }

        else
        {

            for (i = P5 + 1; i <= numero / 2 && sair != 1; i++)
            {

                for (j = 2; j < (i + 2) / 2; j++)
                {

                    if (i % j == 0)
                    {

                        resultado = 0; // i nao e primo

                    }

                    else if (resultado != 0 && j == i / 2 && i % j != 0)
                    {

                        primo = 1;

                    }

                }

                resultado = -1;

                if (primo == 1)
                {

                    P1 = P2;
                    P2 = P3;
                    P3 = P4;
                    P4 = P5;
                    P5 = i;
                    primo = 0;

                }

                if (numero == P1 * P1 + P2 * P2 + P3 * P3 + P4 * P4)
                {

                    printf("%d = %d^2 + %d^2 + %d^2 + %d^2\n",numero,P1,P2,P3,P4);
                    P1 = 2;
                    P2 = 3;
                    P3 = 5;
                    P4 = 7;
                    P5 = 11;
                    sair = 1;

                }

                else if (numero < P1 * P1 + P2 * P2 + P3 * P3 + P4 * P4)
                {

                    printf("Nao existem 4 primos consecutivos cujos quadrados ""somam %d\n",numero);
                    P1 = 2;
                    P2 = 3;
                    P3 = 5;
                    P4 = 7;
                    P5 = 11;
                    sair = 1;
                }
            }
        }

        printf("Digite um numero (0 < n < 10^8): ");
        scanf("%d", &numero);
    }

    if (numero == 0)
    {
        printf("Que a forca esteja com voce!");
    }

    return 0;
}
