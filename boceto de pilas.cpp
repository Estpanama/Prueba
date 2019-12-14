//Programa de Pilas

#include<stdio.h>
 typedef struct{
     struct elemento* siguiente;
     char* nombre;
 } elemento;
 
 elemento* ultimo;
 
 void agregar(elemento* _elemento){
 	//si la pila está vacía
 	if(ultimo == NULL){
 		ultimo =_elemento 
	 } else {
	 	_elemento ->siguiente = ultimo;
	 	ultimo = _elemento;
	 }
 }
 
 
 elemento* extraer(){
 	if(ultimo == NULL){
 		return NULL;
	 }
	 elemento* elemento_retorno 
 }
 
 int main(){
 	
 	
 	
 	return 0;
 }
