#include <stdio.h>

int main()
{
    printf("Lucas Fujimoto Tokunaga\n 241025283\n");
    int n;
    printf("Digite um numero inteiro positivo N(1 <= N <= 105): ");
    if (scanf("%d", &n) != 1)
        return 0;
    int original = n;
    int primos[20];
    int expoentes[20];
    int m = 0; // contador de fatores distintos

    if (n <= 1) // Tentativa e erro, para encontrar a fatoração prima correta
    {
        // testando para n <= 1 nada a fatorar
        printf("Fatores primos de %d:\n", original);
        printf("(nenhum)\n");
        printf("Tau (numero de divisores) = 1\n");
        printf("Sigma (soma dos divisores) = 1\n");
        printf("Razao (sigma/tau) = 1.00\n");
        return 0;
    }

    // testando para fator 2
    if (n % 2 == 0)
    {
        int cnt = 0;
        while (n % 2 == 0)
        {
            n /= 2;
            cnt++;
        }
        primos[m] = 2;
        expoentes[m] = cnt;
        m++;
    }

    // divisores ímpares; usar i*i <= n para evitar chamadas a sqrt e problemas com n mutável
    for (int i = 3; i * i <= n; i += 2)
    {
        if (n % i == 0)
        {
            int cnt = 0;
            while (n % i == 0)
            {
                n /= i;
                cnt++;
            }
            primos[m] = i;
            expoentes[m] = cnt;
            m++;
        }
    }

    // se restou um primo > 1
    if (n > 1)
    {
        primos[m] = n;
        expoentes[m] = 1;
        m++;
    }

    // imprimir fatores armazenados com expoentes
    printf("Fatores primos de %d:\n", original);
    for (int j = 0; j < m; ++j)
    {
        printf("%d^%d", primos[j], expoentes[j]);
        if (j + 1 < m)
            printf(" * ");
    }
    printf("\n");

    // calcula tau e sigma a partir de primos[] e expoentes[], com m fatores distintos
    int tau = 1;
    int sigma = 1;

    for (int i = 0; i < m; ++i)
    {
        int p = primos[i];
        int e = expoentes[i];

        // tau acumula (e+1)
        tau *= (e + 1);

        // calcula p^(e+1)
        int p_pow = 1;
        for (int k = 0; k < e + 1; ++k)
            p_pow *= p;

        // termo = (p^(e+1) - 1) / (p - 1)
        int term = (p_pow - 1) / (p - 1);

        sigma *= term;
    }

    // imprimir resultados
    printf("Tau (numero de divisores) = %d\n", tau);
    printf("Sigma (soma dos divisores) = %d\n", sigma);

    double razao = (double)sigma / (double)tau;
    printf("Razao (sigma/tau) = %.2f\n", razao);

    return 0;
}
