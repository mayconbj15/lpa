#include <iostream>
#include <stdlib.h>

using namespace std;

int **inicializarMatriz(int **matriz, int n);
void printarMatriz(int **matriz, int n);
int buscaRetangulo(int **matriz, int n, int x, int y, int i, int j);
int encontraSubRetangulos(int **matriz, int n, int i, int j, int soma);
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
        cout << endl;
    }

    cout << endl;
}

int buscaRetangulo(int **matriz, int n, int x, int y, int i, int j)
{
    int soma = 0;
    int countX = 0;
    int countY = 0;

    for (countX = 0; countX <= i; x++, countX++)
    {
        for (countY = 0; countY <= j; y++, countY++)
        {
            if (x < n && y < n)
            {
                soma += matriz[x][y];
                // cout << "x: " << x << " y " << y << " \n";
                //cout << matriz[x][y] << " ";
            }
        }
        y -= countY;
    }

    return soma;
}

int encontraSubRetangulos(int **matriz, int n, int i, int j, int soma)
{
    int novaSoma = 0;

    for (int a = 0; a < n; a++)
    {
        for (int b = 0; b < n; b++)
        {
            novaSoma = buscaRetangulo(matriz, n, a, b, i, j);
            //cout << "novaSoma " << novaSoma;
            if (novaSoma > soma)
                soma = novaSoma;
        }
    }

    return soma;
}

void processa(int **matriz, int n)
{
    int soma = matriz[0][0];
    int novaSoma = matriz[0][0];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            novaSoma = encontraSubRetangulos(matriz, n, i, j, novaSoma);
        }
    }

    cout << novaSoma << endl;
}

int main()
{
    int n;
    int numero;

    int **matriz;

    cin >> n;
    if (n <= 100)
    {
        matriz = inicializarMatriz(matriz, n);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> numero;
                matriz[i][j] = numero;
            }
        }

        // printarMatriz(matriz, n);

        processa(matriz, n);
    }

    return 0;
}
