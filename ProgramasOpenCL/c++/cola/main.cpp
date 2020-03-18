#include <stdio.h>
#include <stdlib.h>
#include "cola.h"

funcionCola colaPush(DATOS datosNuevos);
funcionCola colaValorPop(DATOS datosEliminados);
funcionCola colaTop(DATOS datosTope);
funcionCola colaMostrar(DATOS d, int r);

typedef struct
{
	char uchar;
	int uint;
	long ulong;
	short ushort;
}myStruct;

int main(int argc, char** argv)
{
	Cola c;
	myStruct e, e1, e2, e3, e4, e5, *pstruct, **Ptr;
	char x;

	e.uchar = 65;e.uint = 1283;e.ulong = 1323232;e.ushort = 132;
	e1.uchar = 66;e1.uint = 1284;e1.ulong = 1323233;e1.ushort = 133;
	e2.uchar = 67;e2.uint = 1285;e2.ulong = 1323234;e2.ushort = 134;
	e3.uchar = 68;e3.uint = 1286;e3.ulong = 1323235;e3.ushort = 135;
	e4.uchar = 69;e4.uint = 1287;e4.ulong = 1323236;e4.ushort = 136;
	e5.uchar = 70;e5.uint = 1288;e5.ulong = 1323237;e5.ushort = 137;


	c.mostrar(colaMostrar);
	c.pushMultiple(colaPush, 6, &e, &e1, &e2, &e3, &e4, &e5);
	c.mostrar(colaMostrar);
	
	pstruct = (myStruct*)c.valorPop(colaValorPop);
	printf("\nDato elimminado %c\n", pstruct->uchar);
	c.mostrar(colaMostrar);
	c.pop();
	c.mostrar(colaMostrar);

	pstruct = (myStruct*)c.top(colaTop);
	printf("\nDato tope %c\n", pstruct->uchar);
	c.mostrar(colaMostrar);

	Ptr = (myStruct**)c.mostrar();
	printf("\n %c, %c, %c, %c:",Ptr[0]->uchar, Ptr[1]->uchar, Ptr[2]->uchar, Ptr[3]->uchar);

	c.vaciar() ? printf("1") : printf("0");
	c.mostrar(colaMostrar);

	scanf("%c", &x);
	
	return (EXIT_SUCCESS);
}
funcionCola colaPush(DATOS d)
{
	myStruct *s = (myStruct*)d;
	printf("Datos insertados; Uchar : %c ushort: %d.\n", s->uchar, s->ushort);
}
funcionCola colaValorPop(DATOS datosEliminados)
{
	myStruct *s = (myStruct*)datosEliminados;
	printf("Datos eliminados;Uchar : %c \t ushort: %d.\n", s->uchar, s->ushort);
}
funcionCola colaTop(DATOS datoTope)
{
	myStruct *s = (myStruct*)datoTope;
	printf("Datos tope; Uchar : %c \t ushort: %d.\n", s->uchar, s->ushort);
}
funcionCola colaMostrar(DATOS d, int resultado)
{
	if (resultado) {
		myStruct *s = (myStruct*)d;
		printf("(%c,%d,%f,%d) --> ", s->uchar, s->uint, s->ulong, s->ushort);
	}
	else printf("\nCola vacia.\n");
}
