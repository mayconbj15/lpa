#include <iostream>
#include <string>

using namespace std;

string tirarEspaco(string palavra);
string tirarEspacosInicio(string palavra);

void mostrarPalavras(string palavras[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << palavras[i] << endl;
    }
}

string *tirarEspacos(string palavras[], int n)
{
    for (int i = 0; i < n; i++)
    {
        palavras[i] = tirarEspacosInicio(palavras[i]);
        palavras[i] = tirarEspaco(palavras[i]);
    }

    return palavras;
}

string tirarEspacosInicio(string palavra)
{
    string stringAux = "";
    int i = 0;
    if (palavra[0] == ' ')
    {
        while (palavra[i] == ' ')
        {
            i++;
        }

        stringAux = palavra.substr(i, palavra.length());
    }
    else
    {
        return palavra;
    }
    return stringAux;
}

string tirarEspaco(string palavra)
{
    int i = 0;

    string stringAux = "";

    while (i < palavra.length())
    {
        if (palavra[i] != ' ')
            stringAux += palavra[i];
        else if (i + 1 < palavra.length() && palavra[i] == ' ' && palavra[i + 1] != ' ')
            stringAux += palavra[i];

        i++;
    }

    return stringAux;
}

int tamanhoMaiorPalavra(string palavras[], int n)
{
    int maiorTamanho = 0;

    for (int i = 0; i < n; i++)
    {
        if (palavras[i].length() > maiorTamanho)
            maiorTamanho = palavras[i].length();
    }

    return maiorTamanho;
}

void mostraCentralizadoDireita(string palavras[], int n, int maiorTamanho)
{
    for (int i = 0; i < n; i++)
    {
        int x = maiorTamanho - palavras[i].length();

        for (int j = 0; j < palavras[i].length(); x--)
        {
            if (x > 0)
                cout << ' ';
            else
            {
                cout << palavras[i][j];
                j++;
            }
        }
        cout << endl;
    }
}

bool stringVazia(string palavra)
{
    bool vazia = true;

    for (int i = 0; i < palavra.length(); i++)
    {
        if (palavra.at(i) != ' ')
            vazia = false;
    }

    return vazia;
}

int main()
{
    int n;

    cin >> n;

    do
    {
        fflush(stdin); //limpa buffer de entrada

        string palavras[n];

        for (int i = 0; i < n; i++)
        {
            getline(cin, palavras[i]);

            if (stringVazia(palavras[i]))
                i--;
        }

        // mostrarPalavras(palavras, n);

        tirarEspacos(palavras, n);

        //mostrarPalavras(palavras, n);

        int maiorTamaho = tamanhoMaiorPalavra(palavras, n);

        mostraCentralizadoDireita(palavras, n, maiorTamaho);

        cin >> n;
    } while (n != 0);
}