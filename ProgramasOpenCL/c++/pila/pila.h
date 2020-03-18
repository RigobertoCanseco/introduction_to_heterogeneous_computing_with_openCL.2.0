#ifndef PILA_H
#define	PILA_H

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
	typedef void funcionPila;//funci�n como argumento
	/*____________________________________________________________________________
	============================================================================*/
#ifdef	__cplusplus
}
#endif
class Pila
{

private:
	/*============================================================================*/
	//ESTRUCTURA: PILA
	struct estructuraPila {
		DATOS datos;
		struct estructuraPila *siguiente;
	}*Struct;
	/*____________________________________________________________________________
	============================================================================*/
	
	/*============================================================================*/
	//TIPOS DE DATOS
	typedef struct estructuraPila ELEMENTO;//Un elemento de la pila
	typedef ELEMENTO *TOPE;//un puntero de tipo de elemento de la pila
	int numElementos;
public:
	Pila();
	~Pila();
	//PRINCIPALES
	int push(DATOS d, funcionPila funcionPush(DATOS d));//coloca el valor al final de la cola
	int push(DATOS d);
	int pop();//elimina el primer elemento de la cola
	DATOS *valorPop(funcionPila funcionValorPop(DATOS d)); //devuelve el primer elemento de la cola y lo elimina
	DATOS *valorPop();
	DATOS *top(funcionPila funcionTop(DATOS d));//devuelve el primer valor de la cola sin sacarlo
	DATOS *top();
	int mostrar(funcionPila funcionMostrar(DATOS d, int r));//muestra toda la cola
	DATOS** mostrar();
	int vaciar(); //vacia la cola
	int Nelementos() const;//devuelve el numero de elementos
	int vacia() const;//devuelve un 0 si la cola esta vacia
	//SECUNDARIAS
	int pushMultiple(funcionPila funcionPush(DATOS d), int numero, ...);
	int pushMultiple(int numero, ...);
};

#endif	/* PILA_H */
