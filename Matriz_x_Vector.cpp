#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{

    int **Matriz, *Vector, *resultado;

    int n;

    cout << "Ingrese tamnio de Matriz y Vector (Mismo tamanio para ambos): ";
    cin >> n;

    Matriz = new int *[n];
    Vector = new int[n];

    Matriz[0] = new int[n * n];

    for (int i = 1; i < n; i++)
    {
        Matriz[i] = Matriz[i - 1] + n;
    }

    srand(time(0));
    cout << "La matriz y el vector generados son " << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == 0)
                cout << "[";
            Matriz[i][j] = rand() % 100;
            cout << Matriz[i][j];
            if (j == n - 1)
                cout << "]";
            else
                cout << "  ";
        }
        
        Vector[i] = rand() % 100;
        cout << "\t  [" << Vector[i] << "]" << endl;
    }
    cout << "\n";

    resultado = new int[n];

    for (int i = 0; i < n; i++)
    {
        resultado[i] = 0;
        for (int j = 0; j < n; j++)
        {
            resultado[i] += Matriz[i][j] * Vector[j];
        }
    }

    cout << "El resultado total es: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << resultado[i] << endl;
    }

    return 0;
}