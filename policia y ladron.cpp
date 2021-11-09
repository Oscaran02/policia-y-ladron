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
    string nombre; //Nombre del arma usada
    double contundencia; //Letalidad del arma usada
    double probabilidad; //Probabilidad de impacto del arma
};

struct sJugador
{
    int posF; //Posición en y
    int posC; //Posición en x
    sArma armas[2]; //Dos armas del jugador
    double energia = 30; //Energia del jugador
};

//Funciones
void inicializarTablero(string tablero[][MAXC], int filas, int columnas);
void imprimirTablero(string tablero[][MAXC], int filas, int columnas, sJugador policia, sJugador ladron);
sMovimiento dados();
sArma inicializarArmas(sArma arma);
sJugador inicializarPolicia(int filas, int columnas);
sJugador inicializarLadron();
void movimiento(string tablero[][MAXC], int filas, int columnas, sJugador& policia, sJugador& ladron, bool& turno, sMovimiento& dado);

//Función principal
int main()
{
    //Inicialización de valores
    string tablero[MAXF][MAXF];
    sMovimiento dado;
    bool turno = false; //False para ladrón, true para policia
    int filas, columnas, salida = 0;
    cout << "Ingrese el numero de filas del tablero: ";
    cin >> filas;
    cout << "Ingrese el numero de columnas del tablero: ";
    cin >> columnas;
    system("cls");
    sJugador policia = inicializarPolicia(filas,columnas);
    sJugador ladron = inicializarLadron();
    inicializarTablero(tablero, filas, columnas);
    imprimirTablero(tablero, filas, columnas, policia, ladron);
    

    //Ejecución del juego
    while (salida != 1)
    {
        movimiento(tablero, filas, columnas, policia, ladron, turno, dado);

        //Si se queda alguien sin energia
        if (policia.energia<0)
        {
            salida = 1;
        }
        else if (ladron.energia < 0)
        {
            salida = 1;
        }

        //Si entra en modo duelo
        if (true)
        {

        }
        imprimirTablero(tablero, filas, columnas, policia, ladron);
    }

    //Pantalla de ganador
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
void imprimirTablero(string tablero[][MAXC], int filas, int columnas, sJugador policia, sJugador ladron)
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
    cout << endl << endl;
    cout << "Energia del ladron: " << ladron.energia <<endl;
    cout << "Energia del policia: " << policia.energia <<endl;
    system("pause");
    system("cls");
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

//Se encarga de mover a un jugador
void movimiento(string tablero[][MAXC], int filas, int columnas, sJugador &policia, sJugador &ladron, bool &turno, sMovimiento &dado)
{
    int posAntigua;
    int movimientosRestantes;
    dado = dados();
    if (turno) //Policia
    {
        turno = false; //Le da el turno al ladrón
        if (dado.direccion == "arriba")
        {
            posAntigua = policia.posF;
            movimientosRestantes = dado.movimiento * -1;

            while (movimientosRestantes != 0)
            {
                //Rebote cuando llega al limite de la tabla
                if (policia.posF == 0)
                {
                    movimientosRestantes *= -1;
                }
                //Movimiento hacia arriba
                if (movimientosRestantes < 0)
                {
                    policia.posF--;
                    movimientosRestantes++;
                }
                //Movimiento hacia abajo
                else if (movimientosRestantes > 0)
                {
                    policia.posF++;
                    movimientosRestantes--;
                }

                //Si pasa por encima del otro
                if (policia.posC == ladron.posC && policia.posF == ladron.posF)
                {
                    ladron.energia -= 2;
                    //looking if something happens
                }
            }
            //Actualización del tablero
            tablero[posAntigua][policia.posC] = "x";
            tablero[policia.posF][policia.posC] = "P"; //remplazo de letra por el policia
        }
        else if (dado.direccion == "abajo")
        {
            posAntigua = policia.posF;
            movimientosRestantes = dado.movimiento;

            while (movimientosRestantes != 0)
            {
                //Rebote cuando llega al limite de la tabla
                if (policia.posF == filas-1)
                {
                    movimientosRestantes *= -1;
                }
                //Movimiento hacia arriba
                if (movimientosRestantes < 0)
                {
                    policia.posF--;
                    movimientosRestantes++;
                }
                //Movimiento hacia abajo
                else if (movimientosRestantes > 0)
                {
                    policia.posF++;
                    movimientosRestantes--;
                }

                //Si pasa por encima del otro
                if (policia.posC == ladron.posC && policia.posF == ladron.posF)
                {
                    ladron.energia -= 2;
                    //looking if something happens
                }
            }
            //Actualización del tablero
            tablero[posAntigua][policia.posC] = "x";
            tablero[policia.posF][policia.posC] = "P"; //remplazo de letra por el policia
        }
        else if (dado.direccion == "izquierda")
        {
            posAntigua = policia.posC;
            movimientosRestantes = dado.movimiento * -1;

            while (movimientosRestantes != 0)
            {
                //Rebote cuando llega al limite de la tabla
                if (policia.posC == 0)
                {
                    movimientosRestantes *= -1;
                }
                //Movimiento hacia arriba
                if (movimientosRestantes < 0)
                {
                    policia.posC--;
                    movimientosRestantes++;
                }
                //Movimiento hacia abajo
                else if (movimientosRestantes > 0)
                {
                    policia.posC++;
                    movimientosRestantes--;
                }

                //Si pasa por encima del otro
                if (policia.posC == ladron.posC && policia.posF == ladron.posF)
                {
                    ladron.energia -= 2;
                    //looking if something happens
                }
            }
            //Actualización del tablero
            tablero[policia.posF][posAntigua] = "x";
            tablero[policia.posF][policia.posC] = "P"; //remplazo de letra por el policia
        }
        else //Derecha
        {
            posAntigua = policia.posC;
            movimientosRestantes = dado.movimiento;

            while (movimientosRestantes != 0)
            {
                //Rebote cuando llega al limite de la tabla
                if (policia.posC == filas - 1)
                {
                    movimientosRestantes *= -1;
                }
                //Movimiento hacia arriba
                if (movimientosRestantes < 0)
                {
                    policia.posC--;
                    movimientosRestantes++;
                }
                //Movimiento hacia abajo
                else if (movimientosRestantes > 0)
                {
                    policia.posC++;
                    movimientosRestantes--;
                }

                //Si pasa por encima del otro
                if (policia.posC == ladron.posC && policia.posF == ladron.posF)
                {
                    ladron.energia -= 2;
                    //looking if something happens
                }
            }
            //Actualización del tablero
            tablero[policia.posF][posAntigua] = "x";
            tablero[policia.posF][policia.posC] = "P"; //remplazo de letra por el policia
        }
    }
    else //Ladrón
    {
        turno = true; //Le da el turno al policia
        if (dado.direccion == "arriba")
        {
            posAntigua = ladron.posF;
            movimientosRestantes = dado.movimiento * -1;

            while (movimientosRestantes != 0)
            {
                //Rebote cuando llega al limite de la tabla
                if (ladron.posF == 0)
                {
                    movimientosRestantes *= -1;
                }
                //Movimiento hacia arriba
                if (movimientosRestantes < 0)
                {
                    ladron.posF--;
                    movimientosRestantes++;
                }
                //Movimiento hacia abajo
                else if (movimientosRestantes > 0)
                {
                    ladron.posF++;
                    movimientosRestantes--;
                }

                //Si pasa por encima del otro
                if (policia.posC == ladron.posC && policia.posF == ladron.posF)
                {
                    policia.energia -= 2;
                    //looking if something happens
                }
            }
            //Actualización del tablero
            tablero[posAntigua][ladron.posC] = "x";
            tablero[ladron.posF][ladron.posC] = "L"; //remplazo de letra por el ladron
        }
        else if (dado.direccion == "abajo")
        {
            posAntigua = ladron.posF;
            movimientosRestantes = dado.movimiento;

            while (movimientosRestantes != 0)
            {
                //Rebote cuando llega al limite de la tabla
                if (ladron.posF == filas - 1)
                {
                    movimientosRestantes *= -1;
                }
                //Movimiento hacia arriba
                if (movimientosRestantes < 0)
                {
                    ladron.posF--;
                    movimientosRestantes++;
                }
                //Movimiento hacia abajo
                else if (movimientosRestantes > 0)
                {
                    ladron.posF++;
                    movimientosRestantes--;
                }

                //Si pasa por encima del otro
                if (policia.posC == ladron.posC && policia.posF == ladron.posF)
                {
                    policia.energia -= 2;
                    //looking if something happens
                }
            }
            //Actualización del tablero
            tablero[posAntigua][ladron.posC] = "x";
            tablero[ladron.posF][ladron.posC] = "L"; //remplazo de letra por el ladron
        }
        else if (dado.direccion == "izquierda")
        {
            posAntigua = ladron.posC;
            movimientosRestantes = dado.movimiento * -1;

            while (movimientosRestantes != 0)
            {
                //Rebote cuando llega al limite de la tabla
                if (ladron.posC == 0)
                {
                    movimientosRestantes *= -1;
                }
                //Movimiento hacia arriba
                if (movimientosRestantes < 0)
                {
                    ladron.posC--;
                    movimientosRestantes++;
                }
                //Movimiento hacia abajo
                else if (movimientosRestantes > 0)
                {
                    ladron.posC++;
                    movimientosRestantes--;
                }

                //Si pasa por encima del otro
                if (policia.posC == ladron.posC && policia.posF == ladron.posF)
                {
                    policia.energia -= 2;
                    //looking if something happens
                }
            }
            //Actualización del tablero
            tablero[ladron.posF][posAntigua] = "x";
            tablero[ladron.posF][ladron.posC] = "L"; //remplazo de letra por el ladron
        }
        else //Derecha
        {
            posAntigua = ladron.posC;
            movimientosRestantes = dado.movimiento;

            while (movimientosRestantes != 0)
            {
                //Rebote cuando llega al limite de la tabla
                if (ladron.posC == filas - 1)
                {
                    movimientosRestantes *= -1;
                }
                //Movimiento hacia arriba
                if (movimientosRestantes < 0)
                {
                    ladron.posC--;
                    movimientosRestantes++;
                }
                //Movimiento hacia abajo
                else if (movimientosRestantes > 0)
                {
                    ladron.posC++;
                    movimientosRestantes--;
                }

                //Si pasa por encima del otro
                if (policia.posC == ladron.posC && policia.posF == ladron.posF)
                {
                    policia.energia -= 2;
                    //looking if something happens
                }
            }
            //Actualización del tablero
            tablero[ladron.posF][posAntigua] = "x";
            tablero[ladron.posF][ladron.posC] = "L"; //remplazo de letra por el ladron
        }
    }

    //En caso de que queden en la misma posición
    if (policia.posC == ladron.posC && policia.posF == ladron.posF)
    {
        tablero[policia.posF][policia.posC] = "P-L";
    }
}