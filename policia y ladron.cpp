#include <iostream>
#include <string>
#include <cstdlib>
#include<cmath>
#include <ctime>

using namespace std;

//Constantes de valor máximo de la matriz (filas y columnas respectivamente)
const int MAXF = 100, MAXC = 100;

//Estructuras
struct sMovimiento
{
    string direccion; //Arriba, abajo, izquierda o derecha
    int movimiento; //Entre el 1 y el 6
};

struct sArma
{
    string nombre;
    float contundencia;
    float impacto;
};

//Funciones
void inicializarTablero(string tablero[][MAXC], int filas, int columnas);
void imprimirTablero(string tablero[][MAXC], int filas, int columnas);

//Función principal
int main()
{
    string tablero[MAXF][MAXF];
    int filas, columnas;
    cout << "Ingrese el numero de filas del tablero: ";
    cin >> filas;
    cout << "Ingrese el numero de columnas del tablero: ";
    cin >> columnas;
    
    inicializarTablero(tablero, filas, columnas);
    imprimirTablero(tablero, filas, columnas);

}

//Inicia el tablero
void inicializarTablero(string tablero [][MAXC], int filas, int columnas)
{

    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            tablero[i][j] = "x";
        }
    }
    tablero[0][0] = "L";
    tablero[filas-1][columnas-1] = "P";
}

//Imprime el tablero
void imprimirTablero(string tablero[][MAXC], int filas, int columnas)
{
    for (int i = 0; i < filas; i++)
    {        
        cout << endl;
        cout << "\t";
        for (int j = 0; j < columnas; j++)
        {
            cout << tablero[i][j] << "\t";
        }
    }
    cout << endl;
}

sMovimiento dados()
{
    sMovimiento dado;

}