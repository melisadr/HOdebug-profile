
##Compila libreria

```
cd fpe_x87_sse/
gcc -c fpe_x87_sse.c
``` 

## Genera objeto con -DTRAPFPE

```
gcc -DTRAPFPE -c test_fpe1.c -o test_fpe1_o.o
gcc test_fpe1.o  ./fpe_x87_sse/fpe_x87_sse.o -lm
```

## sin flag
```
gcc -c test_fpe2.c -o test_fpe2_o.o
gcc test_fpe2_o.o -o test_fpe2.e
```
#FPE
##FPE1 
sin esa flag, me corría normalmente y el resultado de una division por cero daba infinito
con la flag, y compilado como se ve abajo  aparece **Excepción de coma flotante (`core' generado)**


##FPE2
sin esa flag, me corría normalmente y el resultado de una division por cero 1 ya que interpretaba que era mayor que 1 y listo.
con la flag, y compilado como se ve abajo  aparece **Excepción de coma flotante (`core' generado)**

##FPE3
Tuve que agregar en el .c `#include <math.h>`
Para linkeo, `gcc test_fpe3_o.o -lm -o test_fpe3.e` y con **-DTRAPFPE** `gcc test_fpe3_trap.o  ./fpe_x87_sse/fpe_x87_sse.o -lm -o test_fpe3_trap.e`

#sigsegv


Cuando se compila con `gcc source.c -o small.x -D__SMALL -O0 -g` no tiene problemas en correr. 
Cuando no corre con la flag -D__SMALL, da un error de segmentacion ya que no le alcanza el stack para correr. 
Cuando se coloca ulimit -s unlimited, si bien tarda el código, termina exitosamente y esto es porque definimos el stack size omo el maximo posible. 

```
ulimit -a > ulimit1.log
ulimit -s unlimited 
ulimit -a > ulimit1unlimited.log
diff ulimit1.log ulimit1unlimited.log 
12c12
stack size              (kbytes, -s) 8192
---
stack size              (kbytes, -s) unlimited
``` 

La solución anterior es realmente una solucion momentanea ya que hay que establecer como unlimited cada vez que se quiera ejecutar, habría que buscar alguna
solución para que corra más eficientemente.

#valgrind

El ciclo inicialmente era un ciclo infinito, con lo cual, el programa nunca terminaba y la memoria aumentaba constantemente.
Luego de correrlo con valgrind, se vio que la funcion estaba alocando arrays y no los estaba liberando. 
Se arreglo este problema y el programa funciono correcatamente.

#funny
Cuando ejecute funny sin flag, por pantalla solo me decía que había una violación de segmento, pero no me decía donde.
Al ejecutarlo con esa flag, el programa tenía unas lineas de código que enviaban un mensaje de error como si fuese un debugger manual, por decirlo de alguna forma. 
El problema estaba en el malloc que tenía una dimensión muy grande en comparación con el tamaño del stack. 



