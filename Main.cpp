#include <conio.h>
#include <Windows.h>
#include <stdio.h>

//Caracteristicas pantalla
#define ANCHO 20
#define PRIMERA_LINEA  10
#define PRIMERA_COLUMNA 20
#define FPS 20

//Elementos Juego
#define PERSONAJE '*'
#define FONDO_PANTALLA '-'
#define BALA 'o'

//Definicion de variables globales

int posicionJugador; //posicion del jugador en pantalla
int posicionBala; //posicion actual de la bala en pantalla
int estadoBala; // 1-> bala izquierda, 2 -> bala derecha
char caracterActual; //ultimo caracter recibido


//Declaracion de funciones

void dibujar(); //Funcion de dibujado
void actualizarEstados(); //Funcion de actualizacion de estados
void colocarLinea(); //Colocacion de pantalla
void init(); //Funcion de inicilizacion


int main()
{
	init(); //Llamada a inicializacion

	//Bucle de juego
	while (1)
	{
		system("cls"); //Limpiar consola
		colocarLinea(); //Colocar pantalla en la linea deseada
		actualizarEstados(); //Actualizamos posiciones de los elementos del juego
		dibujar();

		//Calcula de espera para cumplir FPS
		Sleep(1000 / FPS);
	}
	return 0;
}

//Definicion de funciones
void dibujar()
{
	//Colocamos el inicio de la pantalla en la columna deseada
	for (int i = 0; i < PRIMERA_COLUMNA; i++)
	{
		printf(" ");
	}

	//Imprimimos por pantalla las posiciones de los elementos
	for (int i = 1; i < ANCHO+1; i++)
	{
		if (i == posicionJugador)
			printf("%c", PERSONAJE);

		else if (i == posicionBala)
			printf("%c", BALA);

		else
			printf("%c", FONDO_PANTALLA);
	}
}

void actualizarEstados()
{
	//Comprobacion de entrada 
	if (_kbhit())
	{
		//Obtencion del caracter pulsado
		caracterActual = _getch();
		
		//Movimiento del jugador
		if (posicionJugador < ANCHO & caracterActual == 'p')
			posicionJugador++;
		else if (posicionJugador > 1 & caracterActual == 'o')
			posicionJugador--;

		//Comprobacion de disparo
		else if (!estadoBala & caracterActual == 'q')
		{ 
			estadoBala = 1;
			posicionBala = posicionJugador;
		}
			
		else if (!estadoBala & caracterActual == 'w')
		{
			estadoBala = 2;
			posicionBala = posicionJugador;
		}
			
	}

	//Actualizacion si hay bala en pantalla
	if (posicionBala > ANCHO | posicionBala < 1)
		estadoBala = 0;

	else if (estadoBala == 1)
	{
		posicionBala--;
	}

	else if (estadoBala == 2)
	{
		posicionBala++;
	}
}

void colocarLinea()
{
	for (int i = 0; i < PRIMERA_LINEA; i++)
	{
		printf("\n");
	}
}

void init()
{
	posicionJugador = 1;
	estadoBala = 0;
}