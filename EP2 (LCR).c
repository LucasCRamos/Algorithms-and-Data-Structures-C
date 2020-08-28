/***************************************************************/
/**                                                           **/
/** Lucas Carvalho Ramos                 Numero USP: 10693382 **/
/** Exercicio-Programa 02                                     **/
/** Professor: Carlos Eduardo Ferreira                        **/
/** Turma: 01                                                 **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BISSEC_TOL (1e-6)
/*#define RANDOM_SEED 1234*/

void ativa_sorteador()
{
#ifdef RANDOM_SEED
    srand(RANDOM_SEED);
#else
    srand(time(NULL));
#endif
}

double sorteia_real() /* devolve um real sorteado uniformemente no intervalo [0,1] */
{
    return (double) rand() / RAND_MAX;
}

int sorteia_voto_com_falha(double f)
{
    double sorteado = sorteia_real();

    if (sorteado<=f) /*se isso acontecer, o voto terá falha*/

    {

        return 1;

    }

    else /*se isso acontecer, o voto não terá falha*/
    {

        return 0;
    }

}
double prob_erro (int N, double a, double f, int T)
{

    int i,j,k; /*variaveis de incremento*/
    int recebe; /*variavel que recebe 0 ou 1*/
    int falhaA=0,falhaB=0; /*quantidade de falhas de A e B em cada simulação*/
    int quantidadeA=a*N; /*quantidade de pessoas que votou em A*/
    int quantidadeB=N-quantidadeA; /*quantidade de pessoas que votou em B*/
    int SalveA; /*salva quantidadeA+falhaB-falhaA*/
    int SalveB; /*salva quantidadeB+falhaA-falhaB*/
    int erro=0; /*numero total de erros*/
    double Prob; /*recebe o valor da probabilidade em double*/

    for(i = 0; i<T; i++) /*simulacao dos votos de A*/
    {

        for(j = 0; j<quantidadeA; j++)
        {

            recebe=sorteia_voto_com_falha(f);


            if (recebe==1)
            {

                falhaA=falhaA+1;

            }

        }


        for(k = 0; k<quantidadeB; k++) /*simulacao dos votos de B*/
        {

            recebe=sorteia_voto_com_falha(f);


            if (recebe==1)
            {
                falhaB=falhaB+1;

            }

        }

        SalveA=quantidadeA+falhaB-falhaA;
        SalveB=quantidadeB+falhaA-falhaB;


        if (SalveB>=SalveA) /*o empate também eh considerado como erro*/
        {
            erro=erro+1;
        }

        /*importante zerá-las para que as falhas não se acumulem de simulação para simulação*/

        falhaA=0;
        falhaB=0;

    }

    Prob=(erro*(1.0)/T*(1.0));

    return Prob;
}

double bissecta (int N, double a, int T, double tol)
{

    double fa=0;  /*se f=fa=0, a sempre vence*/
    double fb=1;  /*se f=fb=1, b sempre vence*/
    double f=(fa+fb)/2;  /*valor da falha que é utilizado como comparativo*/

    while ((fa-fb)>=BISSEC_TOL || (fa-fb)<=-BISSEC_TOL)  /*condicao para que a funcao pare de atualizar f*/
    {

        if(1-(prob_erro(N,a,f,T))>=1-tol)  /*probabilidade de A vencer >=1-tolerancia, atualiza fa*/
        {
            fa=(fa+fb)/2;
        }

        else
        {

            fb=(fa+fb)/2; /*probabilidade de B vencer >=1-tolerancia, atualiza fb*/
        }

        f=(fa+fb)/2;

    }

    printf("Maior falha das urnas toleravel: %.7f",f);

    return f;

}

int main()
{

    int N,T;

    double a,tol;

    ativa_sorteador();

    printf("Digite o numero de votantes (0 < N <= 2X10^9): ");
    scanf("%d",&N);

    printf("Digite a porcentagem de votos do candidato A (0.5 < a <= 1): ");
    scanf("%lf",&a);

    printf("Digite o numero de simulacoes (0 < T <= 2x10^9): ");
    scanf("%d",&T);

    printf("Digite a probabilidade toleravel de erros (0 <= tol <= 1): ");
    scanf("%lf",&tol);

    bissecta(N,a,T,tol); /*chama a funcao bissecta e passa para ela os parâmetros de referência*/

    return 0;

}
