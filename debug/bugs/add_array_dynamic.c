#include <stdio.h>
#include <stdlib.h>

int add_array(int *a, int *b, int n){
  int sum = 0;
  int i = 0;
  for (i = 0; i <= n + 1; i++) {
    sum += abs(a[i]);
    sum += abs(b[i]);
  };
  return sum;
}

int main(int argc, char **argv) {
  int *a, *b;
  int n = 3;
  a = malloc(sizeof(int) * 3);
  b = malloc(sizeof(int) * 3);
  int i, sum;
  for (i = 0; i < n; i++) {
    a[i] = i;
    b[i] = i;
  }
  sum = add_array(a, b, 3);
  printf("The addition is %d\n", sum);
  return 0;
}

/* tiene un bug pero con malloc no salta porque te da
segmentos de memoria y lo que no se ocupa, se pone en 
cero
si se pone n, en lugar de n+1, hay que poner n*/
