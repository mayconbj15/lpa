#include <iostream>

using namespace std;

int numberOfPiles(int x, int y)
{
    int aux = 0;

    int dimension = (2 * x) + (2 * y);

    while (y != 0)
    {
        aux = y;
        y = x % y;
        x = aux;
    }
    return dimension / x;
}

int main()
{
    unsigned long long x, y;

    while (scanf("%llu%llu", &x, &y) != EOF)
    {
        cout << numberOfPiles(x, y) << endl;
    }
}
