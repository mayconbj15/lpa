#include <iostream>
#include <string>

using namespace std;

int toInt(char character)
{
    return (int)character - 48;
}

int fibonacci(int n)
{
    int first = 0;
    int second = 1;

    int res = (first + second) % 1000;

    for (int i = 2; i <= n; i++)
    {
        res = (first + second) % 1000;
        first = second;
        second = res;
    }

    return res;
}

int getIndexOfFibonacci(string input)
{
    int index = 0;

    for (int i = 0; i < input.size(); i++)
    {
        index = (index * 10 + toInt(input.at(i))) % 1500;
    }

    return index;
}

int main()
{
    int instances;
    string input;

    cin >> instances;

    for (int i = 0; i < instances; i++)
    {
        cin >> input;

        int K = getIndexOfFibonacci(input);

        printf("%03d\n", K == 0 ? 0 : fibonacci(K));
    }

    return 0;
}