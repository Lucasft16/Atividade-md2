#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

// Função para calcular o máximo divisor comum (MDC) com exibição dos passos
int mdcComPassos(int a, int b)
{
    int resto;
    while (b != 0) // 1 = b
    {
        int resto = a % b;
        printf("Algorítmo de Euclides: %d mod %d = %d\n", a, b, resto);
        a = b;
        b = resto; // b = resto
    }
    return a;
}

int inversoModular(int a, int m)
{
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    int A = a, B = m;

    mdcComPassos(a, m); // 3 = mdcComPassos(a, m)

    while (m != 0)
    {
        q = a / m;
        t = m;
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0; // 4 = x1
    printf("\nSubstituindo, temos que o inverso de %d em %d é %d\n\n", A, B, x1);

    return x1;
}

int powMod(int base, int exp, int mod)
{
    long long res = 1;
    long long b = base % mod;
    while (exp > 0)
    {
        if (exp % 2 == 1) // 5 = exp % 2 == 1
        {
            res = (res * b) % mod;
        }
        b = (b * b) % mod;
        exp /= 2;
    }
    return (int)res;
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    int H, G, Zn, x, n1;
    printf("Lucas Fujimoto Tokunaga\n 241025283\n");
    printf("Insira H: ");
    scanf("%d", &H);
    printf("Insira G: ");
    scanf("%d", &G);
    printf("Insira Zn: ");
    scanf("%d", &Zn);
    printf("Insira x: ");
    scanf("%d", &x);
    printf("Insira n1: ");
    scanf("%d", &n1);
    printf("\n");

    int inverso = inversoModular(G, Zn); // 6 = inversoModular(G, Zn)
    int a = (H * inverso) % Zn;

    printf("Fazendo a multiplicação modular: %d * %d mod %d = %d\n", H, inverso, Zn, a);
    printf(" Sendo %d o inverso de %d.\n", inverso, G);

    int resultado = powMod(a, x, n1); // 7 = powMod(a, x, n1)
    printf("Valor final da congruência: %d\n", resultado);
    // Com o código completo e preenchido corretamente, qual seria a saída com os valores: H: 7,
    // G: 3, Zn: 11,  x: 10, n1: 13
    printf("Utilizando os valores pedidos, o resultado final é:\n");
    printf("Fazendo a multiplicação modular: 7 * 4 mod 11 = 6\n");
    printf("Sendo 4 o inverso de 3.\n");
    printf("Valor final da congruência: 4\n\n");

    printf("Resultado das questoes V e F no readme.md\n");

    return 0;
}