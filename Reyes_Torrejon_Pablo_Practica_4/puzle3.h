#define N 6
#define N_PIEZAS 3
//Implementaremos de momento los operadores d¡necesarios para llegar a la solucion
#define ARRIBA_A 1
#define ABAJO_A 2
#define IZQUIERDA_A 3
#define DERECHA_A 4
#define ARRIBA_B 5
#define ABAJO_B 6
#define IZQUIERDA_B 7
#define DERECHA_B 8
#define ARRIBA_C 9
#define ABAJO_C 10
#define IZQUIERDA_C 11
#define DERECHA_C 12
//índices de los vectores filas y cols
#define A 1
#define B 2
#define C 3
//tEstado
#ifndef T_ESTADO
#define T_ESTADO
typedef struct{
    int celdas [N][N];
    int filas[N_PIEZAS];
    int cols[N_PIEZAS];
}tEstado;
#endif

static int puzle_inicial[N][N] = {
{-1, 0, 0, 3, 0, 0},
{-1, 0, 0, 3, 0, 0},
{0, 1, 0, 3, 0, 0},
{1, 1, 1, -1, 2, 0},
{0, 1, 0, 2, 2, 2},
{0, 0, 0, 0, 0, 0}
};

static int puzle_final[N][N] = {
    {-1, 0, 0, 0, 0, 0},
    {-1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 1, 0, -1, 0, 3},
    {1, 1, 1, 2, 0, 3},
    {0, 1, 2, 2, 2, 3}
};

static int filas_inicial[N_PIEZAS] = {3, 4, 1};

static int filas_final[N_PIEZAS] = {4, 5, 4};

static int cols_inicial[N_PIEZAS] = {1, 4, 3};

static int cols_final[N_PIEZAS] = {1, 3, 5};

/* A partir de una configuraci�n de fichas construye un estado v�lido para el problema
  de acuerdo al tipo de datos tEstado. */
tEstado *crearEstado(int puzle[N][N], int fil[N_PIEZAS], int col[N_PIEZAS]);

/* Genera el estado inicial a partir de crearEstado y puzle_inicial. */
tEstado *estadoInicial();

/* Devuelve el coste de aplicar el operador. */
int coste(unsigned op, tEstado *estado);

/* Muestra el contenido del puzle. */
void dispEstado(tEstado *estado);

/* Muestra el nombre de cada operador: Arriba, Abajo, Izquierda, Derecha. */
void dispOperador(unsigned op);

/* Genera el estado final a partir de crearEstado y puzle_final. */
tEstado *estadoObjetivo();


/* Comprueba si es posible aplicar un operador a una configuraci�n determinada para el puzle.
  Devuelve 1 si el movimiento es v�lido y 0 en otro caso. */
int esValido(unsigned op, tEstado* estado);

/* Aplica un operador a una configuraci�n concreta del puzle.
  Devuelve la nueva configuraci�n del tablero tras el movimiento. */
tEstado *aplicaOperador(unsigned op, tEstado *estado);

/* Devuelve 1 si dos estados son iguales y 0 en caso contrario. */
int iguales(tEstado *s, tEstado *t);

/* Devuelve 1 si un estado es igual al estado objetivo. */
int testObjetivo(tEstado *estado);
