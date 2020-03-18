
#include "pila.h"
Pila::Pila()
{
	Struct = NULL;
	this->numElementos = 0;
}

Pila::~Pila()
{
	this->vaciar();
}
/*============================================================================*/
//Devuelve el numero de elementos de una pila
//returna: int
//parametro: TOPE pila
int Pila::Nelementos() const
{
	/*
	int elementos = 0;
	if (pila == NULL) {
		return elementos;
	}
	else {
		while (pila != NULL) {
			elementos++;
			pila = pila->siguiente;
		}
	}
	return elementos;
	*/
	return this->numElementos;
}
/*____________________________________________________________________________
============================================================================*/

/*============================================================================*/
//Devuelve TRUE si la pila esta vac�a o FALSE si no lo est�
//retorna: int
//parametro: TOPE pila
int Pila::vacia() const
{
	return (this->Struct == NULL && this->numElementos == 0);
}
/*____________________________________________________________________________
============================================================================*/

/*============================================================================*/
//Elimina el elemento tope de la pila, vevuelve TRUE si se logro eliminar
//retorna: int
//parametro: TOPE *pila
int Pila::pop()
{
	TOPE p = (TOPE)this->Struct;
	if (p!= NULL) {
		this->Struct = p->siguiente;
		free(p);
		this->numElementos--;
		return 1;
	}
	else return 0;
}
/*____________________________________________________________________________
============================================================================*/

/*============================================================================*/
//Inserta un elemento en la pila
//retorna: int 
//parametros: TOPE *pila, Datos d, FuncionPila funcionPush
int Pila::push(DATOS  d, funcionPila funcionPush(DATOS d))
{
	TOPE nuevo;
	nuevo = (TOPE)malloc(sizeof(ELEMENTO));
	if (nuevo != NULL) {
		/* CODIGO AQUI ---> */
		funcionPush(d);
		/* <--------------- */
		nuevo->datos = d;
		nuevo->siguiente =  this->Struct;
		this->Struct = nuevo;
		this->numElementos++;
		return 1;
	}
	else {
		return 0;
	}
}
/*____________________________________________________________________________
============================================================================*/

/*============================================================================*/
//Inserta un elemento en la pila
//retorna: int 
//parametros:
int Pila::push(DATOS  d)
{
	TOPE nuevo;
	nuevo = (TOPE)malloc(sizeof(ELEMENTO));
	if (nuevo != NULL) {
		nuevo->datos = d;
		nuevo->siguiente = this->Struct;
		this->Struct = nuevo;
		return 1;
	}
	else {
		return 0;
	}
}
/*____________________________________________________________________________
============================================================================*/


/*============================================================================*/
//Devuelve el elemento tope de la pila y lo elimina
//returna: DATOS *
//parametros: TOPE *pila, DATOS *d, FuncionPila funcionValorPop
DATOS *Pila::valorPop(funcionPila funcionValorPop(DATOS d))
{
	TOPE p =  this->Struct;
	if ( p != NULL) {
		DATOS *dn = (DATOS*)p->datos;
		/* CODIGO AQUI ---> */
		funcionValorPop(p->datos);
		/* <--------------- */
		this->Struct = p->siguiente;
		free(p);
		this->numElementos--;
		return dn;
	}
	else {
		return NULL;
	}
}
/*____________________________________________________________________________
============================================================================*/

/*============================================================================*/
//Devuelve el elemento tope de la pila y lo elimina
//returna: DATOS *
//parametros: TOPE *pila, DATOS *d, FuncionPila funcionValorPop
DATOS *Pila::valorPop()
{
	TOPE p = this->Struct;
	if (p != NULL) {
		DATOS *dn = (DATOS*)p->datos;
		this->Struct = p->siguiente;
		free(p);
		this->numElementos--;
		return dn;
	}
	else {
		return NULL;
	}
}
/*____________________________________________________________________________
============================================================================*/


/*============================================================================*/
//Devuelve el valor del tope de la pila sin sacarlo
//returna: DATOS *
//parametros: TOPE *pila, DATOS *d, FuncionPila funcionTop
DATOS *Pila::top(funcionPila funcionTop(DATOS d))
{
	TOPE p = this->Struct;
	if (p != NULL) {
		DATOS *dn = (DATOS*)p->datos;
		/* CODIGO AQUI ---> */
		funcionTop(p->datos);
		/* <--------------- */
		return dn;
	}
	else {
		return NULL;
	}
}
/*____________________________________________________________________________
============================================================================*/

/*============================================================================*/
//Devuelve el valor del tope de la pila sin sacarlo
//returna: DATOS *
//parametros: TOPE *pila, DATOS *d, FuncionPila funcionTop
DATOS *Pila::top()
{
	TOPE p = this->Struct;
	if (p != NULL) {
		DATOS *dn = (DATOS*)p->datos;
		return dn;
	}
	else {
		return NULL;
	}
}
/*____________________________________________________________________________
============================================================================*/


/*============================================================================*/
//Vacia la pila, retorna TRUE si se vaci� la pila. 
//returna: int
//parametro: TOPE *pila
int Pila::vaciar()
{
	TOPE p;
	if (this->Struct == NULL) {
		return 0;
	}
	else {
		while (this->Struct != NULL) {
			p = this->Struct;
			this->Struct = this->Struct->siguiente;
			p->siguiente = NULL;
			free(p);
		}
		this->numElementos = 0;
		free(this->Struct);
		return 1;
	}
}
/*____________________________________________________________________________
============================================================================*/

/*============================================================================*/
//Muestra todos los valores de la pila
//retorna: int 
//parametros: TOPE pila, FuncionPila funcionMostrarPila
int Pila::mostrar(funcionPila funcionMostrar(DATOS d, int n))
{
	estructuraPila *p = this->Struct;
	if (this->Struct == NULL) {
		funcionMostrar(NULL, 0);
		return 0;
	}
	else {
		while ( p != NULL) {
			funcionMostrar(p->datos, 1);
			p = p->siguiente;
		}
		printf(" NULL.\n");
		return 1;
	}
}
/*____________________________________________________________________________
============================================================================*/

/*============================================================================*/
//Debuelve en un arreglo de punteros todos los elementos de la pila
//retorna: int 
//parametros:
DATOS** Pila::mostrar()
{
	estructuraPila *p = this->Struct;
	DATOS **arra = NULL;
	int i = 0;

	if (this->Struct == NULL) {
		return NULL;
	}
	else {
		arra = (DATOS**)calloc(this->Nelementos(), sizeof(DATOS));
		while (p != NULL)
		{
			arra[i++] = (DATOS*)(p->datos);
			p = p->siguiente;
		}
		return arra;
		free(arra);
		arra = NULL;
	}
}
/*____________________________________________________________________________
============================================================================*/


/*============================================================================*/
//Insercion multiple
//retorna: int 
//parametros: OPE *pila, FuncionPila funcionPush, int numero,...
int Pila::pushMultiple(funcionPila funcionPush(DATOS d), int numero, ...)
{
	int i = 0;
	int r = 1;
	va_list lista;
	va_start(lista, numero);

	for (i = 0;i<numero;i++) {
		r = r && push( va_arg(lista, DATOS), funcionPush);
	}

	va_end(lista);
	return r;
}
/*____________________________________________________________________________
============================================================================*/

/*============================================================================*/
//Insercion multiple
//retorna: int 
//parametros: OPE *pila, FuncionPila funcionPush, int numero,...
int Pila::pushMultiple( int numero, ...)
{
	int i = 0;
	int r = 1;
	va_list lista;
	va_start(lista, numero);

	for (i = 0;i<numero;i++) {
		r = r && push(va_arg(lista, DATOS));
	}

	va_end(lista);
	return r;
}
/*____________________________________________________________________________
============================================================================*/


