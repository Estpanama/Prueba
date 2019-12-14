#include <stdio.h>
#include<stdlib.h> 
#include <conio.h>
#include <string.h>
#define MAXIMO 30

//-----Declaración de funciones 
void limpiar(char[],int), pasar(char[],char[]), 
     conv_pre(char[],char[]), conv_pos(char[],char[]), 
     rec_exp(char[]), inver(char[],char[]); 
int verif(char[]), tama(char[]), sim(char), 
    prio(char,char); 

//-----Variables globales 
char Simb[4][2]={{'(',')'},{'-','+'},{'/','*'},{'$','\0'}}, 
     expr[50], pila[50], expr_c[50], epre[50], epos[50], 
     elem, simb; 
int i, j, n, tope, val, cont1, cont2, v; 

//-----Inicio del programa 
int main(){ 
  
  limpiar(expr,50); 
  limpiar(pila,50); 
  limpiar(expr_c,50); 
  limpiar(epre,50); 
  limpiar(epos,50); 
  do{ 
    printf("Introduzca la expresión infija: "); 
    for(i=0;(expr[i]=getchar())!='\n';++i); 
    if(expr[i]=='\n'){ 
      expr[i]='\0'; 
    } 
    if(verif(expr)!=3){ 
      printf("\nLa expresión %s no es valida, ",expr); 
      switch(verif(expr)){ 
        case 0: printf("esta mal la función."); 
        case 1: printf("le faltan paréntesis derechos."); 
        case 2: printf("le faltan paréntesis izquierdos."); 
      } 
      getche(); 
       
    } 
  }while(verif(expr)!=3); 
  inver(expr_c,expr); 
  conv_pre(expr_c,epre); 
  printf("\nLa conversión a Prefija es: %s",epre); 
  pasar(expr_c,expr); 
  conv_pos(expr_c,epos); 
  printf("\nLa conversión a Posfija es: %s",epos); 
  getche(); 
} 

//-----Limpia la variable 
void limpiar(char a[], int n){ 
  for(i=0;i<n;i++){ 
    a[i]='\0'; 
  } 
} 

//-----Pasa de una variable a otra 
void pasar(char a[], char b[]){ 
  int n1, n2; 
  n1=tama(a); 
  n2=tama(b); 
  if(n1>n2){ 
    for(i=0;i<n1;i++){ 
      a[i]=b[i]; 
    } 
  } 
  if(n1<n2){ 
    for(i=0;i<n2;i++){ 
      a[i]=b[i]; 
    } 
  } 
} 

//-----Cuenta cuantos caracteres hay en la variable 
int tama(char var[]){ 
  for(n=0;var[n]!='\0';++n); 
  return(n); 
} 

//-----Verifica si no le faltan paréntesis a la función 
int verif(char ex[]){ 
  val=0; 
  n=tama(ex); 
  if(n>0){ 
    tope=0; 
    cont1=cont2=0; 
    for(i=0;i<n;i++){ 
      elem=ex[i]; 
      if(elem=='('){ 
        pila[tope]=elem; 
        tope+=1; 
        pila[tope]='\0'; 
      } 
      else{ 
        if(elem==')'){ 
          if(tope>0){ 
            if(pila[tope-1]=='('){ 
              tope-=1; 
              pila[tope]='\0'; 
            } 
          } 
          else{ 
            pila[tope]=elem; 
            tope+=1; 
            pila[tope]='\0'; 
          } 
        } 
      } 
    } 
    if(tope>0){ 
      for(i=0;i<tope;i++){ 
        if(pila[i]=='('){ 
          cont1+=1; 
        } 
        if(pila[i]==')'){ 
          cont2+=1; 
        } 
      } 
      if(cont1<cont2){ 
        val=2; 
      } 
      if(cont1>cont2){ 
        val=1; 
      } 
    } 
    else{ 
      val=3; 
    } 
  } 
  else{ 
    val=0; 
  } 
  return(val); 
} 

//-----Conversión de la función a prefija 
void conv_pre(char ex[], char epre[]){ 
  char expre[50]; 
  limpiar(expre,50); 
  conv_pos(ex,expre); 
  inver(epre,expre); 
} 

//-----Conversión de la función a postfija 
void conv_pos(char ex[], char epos[]){ 
  tope=-1; 
  n=tama(ex); 
  while(ex[0]!='\0'){ 
    simb=ex[0]; 
    rec_exp(ex); 
    n-=1; 
    if(simb=='('){ 
      tope+=1; 
      pila[tope]=simb; 
    } 
    else{ 
      if(simb==')'){ 
        while(pila[tope]!='('){ 
          int x=tama(epos); 
          epos[x]=pila[tope]; 
          pila[tope]='\0'; 
          tope-=1; 
        } 
        pila[tope]='\0'; 
        tope-=1; 
      } 
      else{ 
        if(sim(simb)==0){ 
          int x=tama(epos); 
          epos[x]=simb; 
        } 
        else{ 
          if(tama(pila)>0){ 
            while(prio(simb,pila[tope])<=0){ 
              int x=tama(epos); 
              epos[x]=pila[tope]; 
              pila[tope]='\0'; 
              tope-=1; 
              if(tope<0){ 
                break; 
              } 
            } 
          } 
          tope+=1; 
          pila[tope]=simb; 
        } 
      } 
    } 
  } 
  while(tope>=0){ 
    int x=tama(epos); 
    epos[x]=pila[tope]; 
    pila[tope]='\0'; 
    tope-=1; 
  } 
} 

//-----Recorre los caracteres un lugar 
void rec_exp(char a[]){ 
  int x=tama(a); 
  for(i=0;i<(x-1);i++){ 
    a[i]=a[i+1]; 
  } 
  a[i]='\0'; 
} 

//-----Verifica si es un operador 
int sim(char s){ 
  v=0; 
  for(i=0;i<4;i++){ 
    for(j=0;j<2;j++){ 
      if(s==Simb[i][j]){ 
        v=1; 
      } 
    } 
  } 
  return(v); 
} 

//-----Verifica la prioridad para colocar en la pila 
int prio(char s1, char s2){ 
  int p1, p2; 
  p1=p2=0; 
  for(i=0;i<4;i++){ 
    for(j=0;j<2;j++){ 
      if(s1==Simb[i][j]){ 
        p1=i; 
      } 
      if(s2==Simb[i][j]){ 
        p2=i; 
      } 
    } 
  } 
  if(p1<p2){ 
    i=-1; 
  } 
  else{ 
    if(p1==p2){ 
      i=0; 
    } 
    else{ 
      i=1; 
    } 
  } 
  return(i); 
} 

//-----Invierte la función completa 
void inver(char a[], char b[]){ 
  int x=tama(b); 
  n=0; 
  for(i=(x-1);i>=0;i--){ 
    simb=b[i]; 
    if(simb==')'){ 
      a[n]='('; 
    } 
    else{ 
      if(simb=='('){ 
        a[n]=')'; 
      } 
      else{ 
        a[n]=simb; 
      } 
    } 
    n++; 
  } 
}
