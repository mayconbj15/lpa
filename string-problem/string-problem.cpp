#include<iostream>
#include<string>

using namespace std;

string tirarEspaco(string palavra);

void mostrarPalavras(string palavras[], int n){
    for(int i=0; i < n; i++){
        cout << palavras[i] << endl;
    }
}

void tirarEspacos(string palavras[], int n){
    for(int i=0; i < n; i++){
        tirarEspaco(palavras[i]);
    }
}

string tirarEspaco(string palavra){
    int i = 0;
    
    string stringAux("");

    while(i < palavra.length()){
        if(palavra[i] != ' '){
            stringAux[i] += palavra[i];
        }
            

        i++;
    }

    cout << palavra << endl;
    cout << stringAux << endl;
}

int main(){
    int n;
    
    cin >> n;

    fflush(stdin); //limpa buffer de entrada
    
    string palavras[n];

    for(int i=0; i < n; i++){
        getline(cin, palavras[i]);
    }

    mostrarPalavras(palavras, n);

    tirarEspacos(palavras, n);
    
}