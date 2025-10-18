#include <stdio.h>

int mdc_euclides(int a, int b) // calcula o mdc de a e b
{
    while (b != 0)
    {
        int temp = b;
        b = a % b; // O resto da divisão
        a = temp;
    }
    return a;
}

int main()
{
    printf("Lucas Fujimoto Tokunaga\n 241025283\n");
    int n;
    printf("Digite o numero de chaves (1 <= N <= 10): ");
    if (scanf("%d", &n) != 1)
        return 0;
    if (n < 1 || n > 10)
        return 0;
    int c[10];
    printf("Digite os ciclos de ativacao das chaves:\n");
    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &c[i]) != 1)
            return 0;
        if (c[i] < 2 || c[i] > 20)
            return 0; // conforme limites do enunciado
    }

    int mmc = c[0];
    for (int i = 1; i < n; ++i)
    {
        int prev = mmc; // guardar mmc anterior para exibição
        int g = mdc_euclides(prev, c[i]);
        mmc = (prev * c[i]) / g; // calcula o mmc usando o mdc
        printf("Passo %d: MMC(%d, %d) = %d\n", i, prev, c[i], mmc);
        if (mmc > 50)
            break; // já ultrapassou limite, podemos parar
    }

    if (mmc >= 1 && mmc <= 50)
    {
        printf("O primeiro ano encontrado ate 50 anos = %d\n", mmc);
    }
    else
    {
        printf("Nao e possivel encontrar entre 50 anos\n");
    }

    return 0;
}