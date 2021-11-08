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
    float probabilidad;
};

struct sJugador
{
    int posF;
    int posC;
    sArma armas[2];
    int energia = 30;
};

//Funciones
void inicializarTablero(string tablero[][MAXC], int filas, int columnas);
void imprimirTablero(string tablero[][MAXC], int filas, int columnas);
sMovimiento dados();
sArma inicializarArmas(sArma arma);
sJugador inicializarPolicia(int filas, int columnas);
sJugador inicializarLadron();

//Función principal
int main()
{
    //Inicialización de valores
    string tablero[MAXF][MAXF];
    sMovimiento dado;
    int filas, columnas;
    cout << "Ingrese el numero de filas del tablero: ";
    cin >> filas;
    cout << "Ingrese el numero de columnas del tablero: ";
    cin >> columnas;
    sJugador policia = inicializarPolicia(filas,columnas);
    sJugador ladron = inicializarLadron();
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
    tablero[filas - 1][columnas - 1] = "P";
    
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

//Entrega los dados con una direccion y un numero de posiciones
sMovimiento dados()
{
    sMovimiento dado;
    int direccion;
    srand(time(NULL));
    dado.movimiento = 1 + rand() % (6);
    srand(time(NULL));
    direccion = 1 + rand() % (4);
    switch (direccion)
    {
        case 1:
            dado.direccion = "arriba";
            break;
        case 2:
            dado.direccion = "abajo";
            break;
        case 3:
            dado.direccion = "izquierda";
            break;
        case 4:
            dado.direccion = "derecha";
            break;
    }
    return dado;
}

//Le da valores al arma dependiendo del arma recibida
sArma inicializarArmas(sArma arma)
{
    if (arma.nombre == "celular") {
        arma.contundencia = 0.4;
        arma.probabilidad = 0.7;
    }
    else if (arma.nombre == "libro") {
        arma.contundencia = 0.8;
        arma.probabilidad = 0.4;
    }
    else if (arma.nombre == "gas") {
        arma.contundencia = 0.5;
        arma.probabilidad = 0.6;
    }
    else if (arma.nombre == "bolillo") {
        arma.contundencia = 0.7;
        arma.probabilidad = 0.4;
    }
    return arma;
}

//Ingresa los valores inciales del policia
sJugador inicializarPolicia(int filas, int columnas)
{
    sJugador policia;
    policia.armas[0].nombre = "gas";
    policia.armas[1].nombre = "bolillo";
    policia.armas[0] = inicializarArmas(policia.armas[0]);
    policia.armas[1] = inicializarArmas(policia.armas[1]);
    policia.posF = filas - 1;
    policia.posC = columnas - 1;
    return policia;
}

//Ingresa los valores iniciales del ladrón
sJugador inicializarLadron()
{
    sJugador ladron;
    ladron.armas[0].nombre = "celular";
    ladron.armas[1].nombre = "libro";
    ladron.armas[0] = inicializarArmas(ladron.armas[0]);
    ladron.armas[1] = inicializarArmas(ladron.armas[1]);
    ladron.posF = 0;
    ladron.posC = 0;
    return ladron;
}