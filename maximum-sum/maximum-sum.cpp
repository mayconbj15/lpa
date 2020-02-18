#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Matriz
{
public:
    int n;
    int **matriz;

    ~Matriz();                       //destrutor
    Matriz(int linhas, int colunas); //construtor

    void lerEntradas();
    void mostrarMatriz();
    void processa();

    int encontraSubRetangulos(int **matriz, int n, int i, int j, int soma);
    int buscaRetangulo(int **matriz, int n, int x, int y, int i, int j);
};

/**
 * Construtor da classe Matriz.
 */
Matriz::Matriz(int linhas, int colunas)
{
    if (linhas <= 100 && colunas <= 100)
    {
        this->n = linhas;
        this->n = colunas;
        this->matriz = new int *[colunas];

        for (int y = 0; y < colunas; y++)
        {
            this->matriz[y] = new int[linhas];
        }
    }
}

void Matriz::lerEntradas()
{
    for (int x = 0; x < this->n; x++)
    {
        for (int y = 0; y < this->n; y++)
        {
            cin >> this->matriz[x][y];
        }
    }
} //end lerEntradas()

int Matriz::buscaRetangulo(int **matriz, int n, int x, int y, int i, int j)
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

int Matriz::encontraSubRetangulos(int **matriz, int n, int i, int j, int soma)
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

void Matriz::processa()
{
    int soma = this->matriz[0][0];
    int novaSoma = this->matriz[0][0];

    for (int i = 0; i < this->n; i++)
    {
        for (int j = 0; j < this->n; j++)
        {
            novaSoma = encontraSubRetangulos(matriz, this->n, i, j, novaSoma);
        }
    }

    cout << novaSoma << endl;
}

int main()
{
    int n;
    int numero;

    cin >> n;

    Matriz *matriz = new Matriz(n, n);

    matriz->lerEntradas();

    // printarMatriz(matriz, n);

    matriz->processa();

    return 0;
}
