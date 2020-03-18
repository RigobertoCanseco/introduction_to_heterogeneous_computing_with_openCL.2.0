#ifndef COLA_H
#define	COLA_H

#include <cstdio>
#include <cstdlib>
#include <cstdarg>

#ifdef	__cplusplus
extern "C" {
#endif
	/*============================================================================*/
	//ESTRUCTURA DATOS
	typedef const char *string; //cadena de caracteres
	typedef void *DATOS;//Datos a almacenar
	typedef void funcionCola;
    /*____________________________________________________________________________
	============================================================================*/
#ifdef	__cplusplus
}
#endif
class Cola
{

private:
	/*============================================================================*/
	//ESTRUCTURA: COLA
	struct estructuraCola {
		DATOS datos;
		struct estructuraCola *siguiente;
	}*Struct;
	struct estructuraCola *final;

	/*============================================================================*/
	//TIPOS DE DATOS
	typedef struct estructuraCola ELEMENTO;//Un elemento de la cola
	typedef ELEMENTO *PROXIMO;//un puntero de tipo de elemento de la cola
	int numElementos;

public:
	Cola();
	~Cola();
	//PRINCIPALE
	int push(DATOS d, funcionCola funcionPush(DATOS d));//coloca el valor al final de la cola
	int push(DATOS d);
	int pop();//elimina el primer elemento de la cola
	DATOS *valorPop(funcionCola funcionValorPop(DATOS d)); //devuelve el primer elemento de la cola y lo elimina
	DATOS *valorPop();
	DATOS *top(funcionCola funcionTop(DATOS d) );//devuelve el primer valor de la cola sin sacarlo
	DATOS *top();
	int mostrar(funcionCola funcionMostrar(DATOS d, int r));//muestra toda la cola
	DATOS **mostrar();
	int vaciar(); //vacia la cola
	int Nelementos() const;//devuelve el numero de elementos
	int vacia() const;//devuelve un 0 si la cola esta vacia
	//SECUNDARIAS
	int pushMultiple(funcionCola funcionPush(DATOS d), int numero, ...);
	int pushMultiple(int numero, ...);
};

#endif	/* COLA_H */

