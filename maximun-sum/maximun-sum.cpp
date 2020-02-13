#include <iostream>
#include <stdlib.h>

using namespace std;

int **inicializarMatriz(int **matriz, int n);
void printarMatriz(int **matriz, int n);
int expandeVertical(int **matriz, int i, int j, int expansao, int soma);
int expandeDiagonal(int **matriz, int i, int j, int expansao, int soma);
int expandeHorizontal(int **matriz, int i, int j, int expansao, int soma, int n);
int expande(int **matriz, int n, int i, int j);
bool podeExpandir(int i, int j, int n, int expansao);
void processa(int **matriz, int n);

int **inicializarMatriz(int **matriz, int n)
{
    matriz = (int **)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        matriz[i] = (int *)malloc(n * sizeof(int));

        for (int j = 0; j < n; j++)
        {
            matriz[i][j] = 0;
        }
    }

    return matriz;
}

void printarMatriz(int **matriz, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << matriz[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\n";
}

int expandeHorizontal(int **matriz, int i, int j, int expansao, int soma, int n)
{
    int novaSoma = 0;
    cout << "somaP" << soma;
    for (int count = 1; j + expansao <= n; count++, j++)
    {

        novaSoma = soma + soma + matriz[i][j];
        cout << "e:" << matriz[i][j] << " ";

        if (novaSoma > soma)
            soma = novaSoma;
    }
    cout << "soma" << novaSoma;
    cout << "\n";

    return soma;
}

int expandeVertical(int **matriz, int i, int j, int expansao, int soma)
{
}
int expandeDiagonal(int **matriz, int i, int j, int expansao, int soma)
{
}

int expande(int **matriz, int i, int j, int n)
{
    int expansao = 1;

    while (podeExpandir(i, j, n, expansao))
    {
        int soma = matriz[i][j];

        if ((i + expansao) <= n)
            soma = expandeHorizontal(matriz, i, j + 1, expansao, soma, n);

        //cout << "soma" << i << j << ":" << soma;

        if ((j + expansao) <= n)
        {
            soma = expandeVertical(matriz, i, j, expansao, soma);
            soma = expandeDiagonal(matriz, i, j, expansao, soma);
        }
        expansao++;
    }
}

bool podeExpandir(int i, int j, int n, int expansao)
{
    return (i + expansao) <= n || (j + expansao) <= n;
}

void processa(int **matriz, int n)
{
    int i, j = 0;
    int soma = 0;
    int expansao = 1;

    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < n; j++)
        {
            expande(matriz, i, j, n);
            soma = matriz[0][0];
        }

        expansao++;
    }
}

int main()
{
    int n;
    int numero;

    int **matriz;

    cin >> n;

    matriz = inicializarMatriz(matriz, n);

    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < n; j++)
        {
            cin >> numero;
            matriz[i][j] = numero;
        }
    }

    printarMatriz(matriz, n);

    processa(matriz, n);
}
