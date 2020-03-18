#include "cola.h"
Cola::Cola()
{
	Struct = NULL;
	this->numElementos = 0;
}

Cola::~Cola()
{
	vaciar();
}

/*============================================================================*/
//Devuelve el numero de elementos de la cola
//returna: int
//parametro:
int Cola::Nelementos() const
{
	/*
	int elementos = 0;
	estructuraCola *c = this->Struct;
	if (  c  == NULL) {
		return elementos;
	}
	else {
		while ( c != NULL) {
			elementos++;
			c = c->siguiente;
		}
	}
	return elementos;
	*/
	return this->numElementos;
}

/*============================================================================*/
//Devuelve TRUE si la cola esta vac�a o FALSE si no lo est�
//retorna: int
int Cola::vacia() const
{
	return ( this->Struct == NULL && this->numElementos == 0);
}

/*============================================================================*/
//Elimina el primer elemento de la cola
//retorna: int
//parametros:
int Cola::pop()
{
	PROXIMO p = (PROXIMO )this->Struct;
	if (this->Struct != NULL) {
		this->Struct = (p)->siguiente;
		free(p);
		return 1;
		this->numElementos--;
	}
	else return 0;
}
/*____________________________________________________________________________
============================================================================*/

/*============================================================================*/
//Inserta un elemento en la cola, retorna TRUE si se logro insertar
//retorna: int 
//parametros:DATOS d, FuncionCola funcionPush
int Cola::push(DATOS d, funcionCola funcionPush(DATOS d))
{
	PROXIMO nuevo, tmp;
	nuevo = (PROXIMO)malloc(sizeof(ELEMENTO));
	if (nuevo != NULL) {
		/* CODIGO AQUI ---> */
		funcionPush(d);
		/* <--------------- */
		nuevo->datos = d;
		nuevo->siguiente = NULL;
		if (this->Struct == NULL)
			this->Struct = nuevo;
		else
			this->final->siguiente = nuevo;
		this->final = nuevo;
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
//Inserta un elemento en la cola, retorna TRUE si se logro insertar
//retorna: int 
//parametros: DATOS d
int Cola::push(DATOS d)
{
	PROXIMO nuevo, tmp;
	nuevo = (PROXIMO)malloc(sizeof(ELEMENTO));
	if (nuevo != NULL) {
		nuevo->datos = d;
		nuevo->siguiente = NULL;
		if (this->Struct == NULL)
			this->Struct = nuevo;
		else
			this->final->siguiente = nuevo;
		this->final = nuevo;
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
//Devuelve el primer elemento de la cola y lo elimina
//returna: int
//parametros: FuncionCola funcionValorPop
DATOS* Cola::valorPop(funcionCola funcionValorPop(DATOS d))
{
	PROXIMO p = this->Struct;
	if (this->Struct != NULL) {
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
//Devuelve el primer elemento de la cola y lo elimina
//returna: int
//parametros:FuncionCola funcionValorPop
DATOS* Cola::valorPop()
{
	PROXIMO p = this->Struct;
	if (this->Struct != NULL) {
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
//Devuelve el primer valor de la cola sin sacarlo
//returna: int
//parametros:  FuncionCola funcionTop
DATOS* Cola::top(funcionCola funcionTop(DATOS d))
{
	PROXIMO p = this->Struct;
	if (this->Struct != NULL) {
		DATOS *dn = (DATOS *)this->Struct->datos;
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
//Devuelve el primer valor de la cola sin sacarlo
//returna: int
//parametros:
DATOS* Cola::top()
{
	PROXIMO p = this->Struct;
	if (this->Struct != NULL) {
		DATOS *dn = (DATOS *)this->Struct->datos;
		return dn;
	}
	else {
		return NULL;
	}
}
/*____________________________________________________________________________
============================================================================*/


/*============================================================================*/
//Vacia la cola, retorna TRUE si se vaci� 
//returna: int
//parametro: COLA *cola
int Cola::vaciar()
{
	PROXIMO p;
	if (this->Struct == NULL) {
		return 0;
	}
	else {
		while (this->Struct != NULL) {
			p = this->Struct;
			this->Struct = this->Struct->siguiente;
			free(p);
			p = NULL;
		}
		this->numElementos = 0;
		free(this->Struct);
		return 1;
	}
}
/*____________________________________________________________________________
============================================================================*/

/*============================================================================*/
//Muestra todos los valores de la cola
//retorna: int 
//parametros: FuncionCola funcionMostrarCola
int Cola::mostrar(funcionCola funcionMostrar(DATOS d, int r))
{
	estructuraCola *c = this->Struct;
	if (this->Struct == NULL) {
		funcionMostrar(NULL, 0);
		return 0;
	}
	else {
		while ( c != NULL) {
			funcionMostrar(c->datos, 1);
			c = c->siguiente;
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
DATOS** Cola::mostrar()
{
	estructuraCola *c = this->Struct;
	DATOS **arra = NULL;
	int i = 0; 

	if (this->Struct == NULL) {
		return NULL;
	}
	else {
		arra = (DATOS**)calloc(this->Nelementos(), sizeof(DATOS) );
		while (c != NULL) 
		{
			arra[i++] = (DATOS*)(c->datos);
			c = c->siguiente;
		}
		return arra;
		free(arra);
		arra = NULL;
	}
}
/*____________________________________________________________________________
============================================================================*/

/*============================================================================*/
//PUsh Multiple
//retorna: int 
//parametros: FuncionCola funcionPush, int numero,...
int Cola::pushMultiple(funcionCola funcionPush(DATOS d), int numero, ...)
{
	int i = 0;
	int r = 1;
	va_list lista;
	va_start(lista, numero);

	for (i = 0;i<numero;i++) {
		r = r && push(va_arg(lista, DATOS), funcionPush);
	}
	va_end(lista);
	return r;
}
/*____________________________________________________________________________
============================================================================*/

/*============================================================================*/
//PUsh Multiple
//retorna: int 
//parametros:int numero,...
int Cola::pushMultiple( int numero, ...)
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
