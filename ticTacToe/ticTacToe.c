#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#define N 3

void titulo();
void inicializacion(char xtablero[N][N]);
void mostrar(char xtablero[N][N]);
void carga(char xtablero[N][N]);
int espaciosVacios(char xtablero[N][N]);
void movimientoCpu(char xtablero[N][N]);
void movimientoJugador(char xtablero[N][N]);
int chequearFilas(char xtablero[N][N], int n);
int chequearDiagonales(char xtablero[N][N]);
int winLose(char xtablero[N][N]);

int main()
{
    char tablero[N][N];
    char pregunta;
    system("cls");
    do
    {
        titulo();
        inicializacion(tablero);
        carga(tablero);
        printf("Quiere seguir jugando? (S/N) \n");
        fflush(stdin);
        scanf("%c", &pregunta);
        pregunta = toupper(pregunta);
        system("cls");
    } while (pregunta == 'S');

    return 0;
}

void titulo()
{
    printf("//////////////////////");
    printf("\n\n TicTacToe by fmira \n\n");
    printf("////////////////////// \n\n");
    return;
}

void inicializacion(char xtablero[N][N])
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            xtablero[i][j] = ' ';
    return;
}

void mostrar(char xtablero[N][N])
{

    printf(" %2c | %2c | %2c \n", xtablero[0][0], xtablero[0][1], xtablero[0][2]);
    printf("----|----|----\n");
    printf(" %2c | %2c | %2c \n", xtablero[1][0], xtablero[1][1], xtablero[1][2]);
    printf("----|----|----\n");
    printf(" %2c | %2c | %2c \n", xtablero[2][0], xtablero[2][1], xtablero[2][2]);

    return;
}

int espaciosVacios(char xtablero[N][N])
{
    int cont = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (xtablero[i][j] == ' ')
                cont++;
    return (cont);
}

void movimientoJugador(char xtablero[N][N])
{
    int x, y, modificacion = 0;
    do
    {
        printf("\nIngrese numero fila: ");
        fflush(stdin);
        scanf("%d", &x);
        printf("ingrese numero columna: ");
        fflush(stdin);
        scanf("%d", &y);
        if (xtablero[x - 1][y - 1] == ' ')
        {
            xtablero[x - 1][y - 1] = 'X';
            modificacion = 1;
        }
        else
        {
            printf("\nPosicion del tablero ocupada");
            printf("\n");
        }
    } while (modificacion == 0);
    return;
}

void movimientoCpu(char xtablero[N][N])
{
    srand(time(NULL));
    int n, m;
    if (espaciosVacios(xtablero) > 0)
    {
        do
        {
            n = rand() % 3;
            m = rand() % 3;
        } while (xtablero[m][n] != ' ');
        xtablero[m][n] = 'O';
    }
    return;
}

int chequearFilas(char xtablero[N][N], int n)
{
    if (n < N)
    {
        if (xtablero[n][0] == xtablero[n][1] && xtablero[n][0] == xtablero[n][2] && xtablero[n][0] != ' ')
            return n;
        else
            return chequearFilas(xtablero, n + 1);
    }
    return -1;
}

int chequearColumnas(char xtablero[N][N], int n)
{
    if (n < N)
    {
        if (xtablero[0][n] == xtablero[1][n] && xtablero[0][n] == xtablero[2][n] && xtablero[0][n] != ' ')
            return n;
        else
            return chequearColumnas(xtablero, n + 1);
    }
    return -1;
}

int chequearDiagonales(char xtablero[N][N])
{
    if (xtablero[0][0] == xtablero[1][1] && xtablero[0][0] == xtablero[2][2] && xtablero[0][0] != ' ')
        return 1;
    else if (xtablero[2][0] == xtablero[1][1] && xtablero[2][0] == xtablero[0][2] && xtablero[2][0] != ' ')
        return 1;
    else
        return -1;
}

int winLose(char xtablero[N][N])
{
    int f = chequearFilas(xtablero, 0);
    int d = chequearDiagonales(xtablero);
    int c = chequearColumnas(xtablero, 0);
    if (f != -1)
    {
        if (xtablero[f][0] == 'O')
            printf("\nPERDISTE MAN \n\n");
        else
            printf("\nGANASTE FACHEROOO \n\n");
        return 1;
    }
    else if (d != -1)
    {
        if (xtablero[1][1] == 'O')
            printf("\nPERDISTE MAN \n\n");
        else
            printf("\nGANASTE FACHEROOO \n\n");
        return 1;
    }
    else if (c != -1)
    {
        if (xtablero[0][c] == 'O')
            printf("\nPERDISTE MAN \n\n");
        else
            printf("\nGANASTE FACHEROO \n\n");
        return 1;
    }
    else if (espaciosVacios(xtablero) == 0)
    {
        printf("\nES UN EMPATE\n\n");
        return 1;
    }
    else
        return 0;
}

void carga(char xtablero[N][N])
{
    int x, y, resultado = 0;
    mostrar(xtablero);
    do
    {
        movimientoJugador(xtablero);
        system("cls");
        titulo();
        mostrar(xtablero);
        printf("\nEsperando movimiento adversario");
        sleep(1);
        system("cls");
        movimientoCpu(xtablero);
        titulo();
        mostrar(xtablero);
        resultado = winLose(xtablero);
    } while (resultado == 0);
    return;
}
