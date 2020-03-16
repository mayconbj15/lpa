#include <iostream>

using namespace std;

int kesimoMaior(int *vet1, int *vet2, int kesimo);
int *criarVetor(int n);

int *criarVetor(int n)
{
    int *vetor = new int[n];

    for (int i = 0; i < n; i++)
    {
        cin >> vetor[i];
    }

    return vetor;
}

int kesimoMaior(int *vet1, int *vet2, int kesimo)
{
    int maior = 0;
    int cont1 = 0;
    int cont2 = 0;

    while (kesimo > 0)
    {
        if (vet1[cont1] > vet2[cont2])
        {
            maior = vet1[cont1];
            cont1++;
        }
        else
        {
            maior = vet2[cont2];
            cont2++;
        }
        kesimo--;
    }
}

int main()
{
    int n;
    int kesimo;

    cin >> n;

    int *vet1 = criarVetor(n);
    int *vet2 = criarVetor(n);

    cin >> kesimo;

    int maior = kesimoMaior(vet1, vet2, kesimo);

    cout << maior;
}