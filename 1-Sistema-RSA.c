#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int mdc_euclides(int a, int b)
{
    printf("\nAlgoritmo de Euclides\n");
    int resto;
    while (b != 0)
    {
        resto = a % b;
        printf("%d mod %d = %d\n", a, b, resto);
        a = b;
        b = resto; // b = resto
    }
    return a;
}

int fatorarPollardRho(int n)
{
    int x = 2, y = 2, d = 1;
    printf("Fatoracao de %d\n", n);

    while (d == 1)
    {
        x = (x * x + 1) % n;
        y = ((y * y + 1) % n);
        y = ((y * y + 1) % n);
        d = mdc_euclides(abs(x - y), n);
        printf("x = %d, y = %d, mdc = %d\n", x, y, d);
    }

    if (d == n)
    {
        printf("Fator nao encontrado\n");
        return -1;
    }
    else
    {
        printf("Fator encontrado: %d\n\n", d);
        return d;
    }
}

int inversoModular(int a, int m) // para determinar o inverso modular de E em relação a z
{
    // vamos usar cópias locais para não sobrescrever os parâmetros de entrada
    int orig_a = a;
    int orig_m = m;

    mdc_euclides(a, m);

    int x0 = 0, x1 = 1;
    int q, t;

    // algoritmo estendido (iterativo)
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

    // agora 'a' contem o mdc(orig_a, orig_m)
    if (a != 1)
    {
        printf("\nInverso modular nao existe");
        return -1; // inverso nao existe
    }

    // x1 contem o coeficiente de Bezout;
    if (x1 < 0)
        x1 += orig_m;

    printf("\nSubstituindo, temos que o inverso de %d em %d e %d\n\n", orig_a, orig_m, x1);
    return x1;
}

int precodificar(char mensagem) // converte caractere em codigo numerico
{
    if (islower((unsigned char)mensagem))
        mensagem = toupper((unsigned char)mensagem);

    // espaço -> 00
    if (mensagem == ' ')
        return 0; // codigo 00

    if (mensagem >= 'A' && mensagem <= 'Z')
        return mensagem - 'A' + 11; // 'A' -> 11

    return -1; // nao suportado
}

char numletra(int codigo) // converte codigo numerico em caractere
{
    if (codigo == 0)
        return ' ';
    if (codigo >= 11 && codigo <= 36)
        return (char)('A' + (codigo - 11));
    return '?';
}

int primo(int num)
{ // saber se é primo
    if (num < 2)
        return 0;
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

// mdc silencioso (sem prints)
int mdc_simples(int a, int b)
{
    if (a < 0)
        a = -a;
    if (b < 0)
        b = -b;
    while (b != 0)
    {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

long long powmod(long long base, long long exp, long long mod);
int phi_naive(int n);

// calcula base^exp mod n escolhendo a redução de expoente automaticamente
// e imprime qual teorema foi aplicado e a decomposição do expoente
long long verificacao(long long base, long long exp, int n)
{
    // caso n primo -> Fermat: reduce modulo (n-1)
    if (primo(n))
    {
        long long mod = n - 1;
        long long q = exp / mod;
        long long r = exp % mod;

        printf("Aplicado Pequeno Teorema de Fermat: e = %lld*(%lld) + %lld\n", q, mod, r);

        printf("Calculando M^%lld mod %d\n", r, n);
        return powmod(base, r, n);
    }

    // se mdc(base,n) == 1 -> Euler: reduce modulo phi(n)
    int g = mdc_simples((int)base, n);
    if (g == 1)
    {
        int phi = phi_naive(n);
        long long q = exp / phi;
        long long r = exp % phi;
        printf("Aplicado Teorema de Euler: e = %lld*(%d) + %lld (phi=%d)\n", q, phi, r, phi);
        printf("Calculando M^%lld mod %d \n", r, n);
        return powmod(base, r, n);
    }

    // caso geral: aplicar Divisão Euclidiana (mostramos decomposição), mas não há redução segura
    int phi = phi_naive(n);
    long long q = exp / phi;
    long long r = exp % phi;
    printf("Aplicado Teorema da Divisao Euclidiana: e = %lld*(%d) + %lld\n", q, phi, r);
    printf("mdc(M,n) = %d != 1, portanto nao se pode reduzir via Euler, calculando M^e mod n diretamente\n", g);
    return powmod(base, exp, n);
}

int fermat(int a, int p) // se n é primo, então a^(p-1) mod p = 1
{
    int r = 1;
    for (int i = 0; i < p - 1; i++)
    {
        r = (r * a) % p;
    }
    printf("Fermat: %d^(%d) mod %d = %d\n", a, p - 1, p, r);
    return r;
}

// exponenciacao modular (base^exp mod mod) usando exponentiation by squaring
long long powmod(long long base, long long exp, long long mod)
{
    long long res = 1 % mod;
    base %= mod;
    while (exp > 0)
    {
        if (exp & 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

// calcula phi(n) pela fatoracao por tentativa (suficiente para n pequenos)
int phi_naive(int n)
{
    int result = n;
    int temp = n;
    for (int p = 2; p * p <= temp; p++)
    {
        if (temp % p == 0)
        {
            while (temp % p == 0)
                temp /= p;
            result -= result / p;
        }
    }
    if (temp > 1)
        result -= result / temp;
    return result;
}

// aplica o teorema de Euler: se mdc(a,n) = 1 entao a^{phi(n)} ≡ 1 (mod n)
// esta funcao calcula a^{phi(n)} mod n e imprime o resultado; retorna o valor calculado
int euler(int a, int n)
{
    int g = mdc_euclides(a, n);
    if (g != 1)
    {
        printf("Teorema de Euler nao se aplica: mdc(%d,%d) = %d\n", a, n, g);
        return -1;
    }

    int phi = phi_naive(n);
    long long r = powmod(a, phi, n);
    printf("Euler: %d^(%d) mod %d = %lld\n", a, phi, n, r);
    return (int)r;
}

int main()
{
    printf("Lucas Fujimoto Tokunaga\n 241025283\n");
    int N1, N2;
    printf("Digite dois numeros compostos distintos N1 e N2 de 3 ou 4 digitos, sendo produto de primos distintos para que o metodo p de Pollard seja eficiente: \n");
    scanf("%d %d", &N1, &N2);
    if ((N1 < 100 || N1 > 9999) || (N2 < 100 || N2 > 9999) || (N1 == N2))
    {
        printf("Numeros invalidos\n");
        return 0;
    }
    printf("%d %d\n", N1, N2);
    printf("---------------------------------------------------\n");
    printf("Etapa 1:\n");
    printf("---------------------------------------------------\n");
    int p = fatorarPollardRho(N1);
    int q = fatorarPollardRho(N2);

    printf("\np: %d, q: %d\n", p, q);

    int n = p * q;
    printf("n (p*q) = %d\n", n);

    int zn = (p - 1) * (q - 1);
    printf("z(n) = (p-1)*(q-1) = %d\n", zn);

    printf("---------------------------------------------------\n");
    printf("Etapa 2:\n");
    printf("---------------------------------------------------\n");

    int e; // encontrar e
    for (e = 2; e < zn; e++)
    {
        if (mdc_euclides(e, zn) == 1)
        {
            break;
        }
    }

    int d; // encontrar d
    d = inversoModular(e, zn);

    printf("\nChave publica: (n = %d, e = %d)\n", n, e);
    printf("Chave privada: (n = %d, d = %d)\n", n, d);

    printf("---------------------------------------------------\n");
    printf("Etapa 3:\n");
    printf("---------------------------------------------------\n");

    printf("\nDigite uma mensagem para cifrar: \n");
    char mensagem[101];
    int codificado[101];
    scanf(" %[^\n]", mensagem);

    for (int i = 0; mensagem[i] != '\0'; i++)
    {
        int code = precodificar(mensagem[i]);
        if (code < 0)
        {
            printf("Caractere '%c' nao suportado, ignorando\n", mensagem[i]);
            continue;
        }

        long long r;

        // (escolhe Fermat/Euler/Divisão Euclidiana quando aplicável)
        r = verificacao(code, e, n);
        codificado[i] = (int)r;
        printf("Cifrado: M=%d -> C=%lld\n", code, r);
    }
    printf("\nMensagem cifrada:\n");

    for (int i = 0; mensagem[i] != '\0'; i++)
    {
        int C = codificado[i];
        int last2 = C % 100; // últimos dois dígitos

        printf("Codificado[%d]: %d\n", i, C);
    }

    // Decodificação: para cada bloco cifrado C, calcular M = C^d mod n
    printf("\nDecodificando com D = %d...\n", d);
    int decodificado[101];
    char recuperada[101];
    int idx = 0;

    for (int i = 0; mensagem[i] != '\0'; i++)
    {
        long long M = verificacao((long long)codificado[i], (long long)d, n);
        decodificado[i] = (int)M;
        char ch = numletra(decodificado[i]);
        recuperada[i] = ch;
        idx++;
    }
    recuperada[idx] = '\0';

    printf("\nMensagem recuperada: %s\n", recuperada);

    return 0;
}