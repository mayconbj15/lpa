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

    int maiorSubRetangulo();
    int kadane(int *vet, int n);
    int *inicializarComZeros(int *vet, int n);
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

int *Matriz::inicializarComZeros(int *vet, int n)
{
    for (int i = 0; i < n; i++)
    {
        vet[i] = 0;
    }
    return vet;
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

int Matriz::maiorSubRetangulo()
{
    int direita, esquerda;

    int maiorSoma, soma = 0;

    int *temp = (int *)malloc(n * sizeof(int));

    for (esquerda = 0; esquerda < this->n; esquerda++)
    {
        //inicializa o temporário com 0's
        temp = this->inicializarComZeros(temp, n);

        for (direita = esquerda; direita < this->n; direita++)
        {
            for (int i = 0; i < this->n; i++)
            {
                temp[i] += this->matriz[i][direita];
            }

            soma = kadane(temp, n);

            if (soma > maiorSoma)
                maiorSoma = soma;
        }
    }

    return maiorSoma;
}

int Matriz::kadane(int *vet, int n)
{
    int maximoLocal = 0;
    int maximoGlobal = -1;

    for (int i = 0; i < n; i++)
    {

        maximoLocal = max(vet[i], vet[i] + maximoLocal);

        if (maximoLocal > maximoGlobal)
            maximoGlobal = maximoLocal;
    }

    return maximoGlobal;
}

int main()
{
    int n;
    int numero;

    cin >> n;

    Matriz *matriz = new Matriz(n, n);

    matriz->lerEntradas();

    //matriz->mostrarMatriz(matriz, n);

    int maiorSoma = matriz->maiorSubRetangulo();

    cout << maiorSoma << endl;

    return 0;
}
