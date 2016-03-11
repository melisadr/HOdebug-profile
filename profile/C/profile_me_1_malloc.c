#include <stdlib.h>
#include <math.h>

#define SIZE 5000

void first_assign(int i1, int i2, double * a, double * b, double * c )
{  
  a[i2*SIZE+i1] = a[i2*SIZE+i1] + b[i2*SIZE+i1] + c[i2*SIZE+i1];
}

void second_assign(int i1, int i2, double * a, double * b, double * c )
{  
  a[i1*SIZE+i2] = a[i1*SIZE+i2] + b[i1*SIZE+i2] + c[i1*SIZE+i2];
}

int main( int argc, char * argv[] ){
	double *a, *b, *c;
	int n = 5000;
  int i, j; 
	a = (double *) malloc(sizeof(double) * n * n);
  b = (double *) malloc(sizeof(double) * n * n);
	c = (double *) malloc(sizeof(double) * n * n);
 
  for( i = 0; i < n; i++ ){
    for( j = 0; j < n; j++ ){

      a[i*n + j] = 1.0;
      b[i*n + j] = 2.0;
      c[i*n + j] = 3.0;
    }
  }

   for( i = 0; i < n; i++ ){
    for( j = 0; j < n; j++ ){
      first_assign(i, j, a, b, c);
    }
  }

  for( i = 0; i < n; i++ ){
    for( j = 0; j < n; j++ ){
      second_assign(i, j, a, b, c);
    }
  }
	free(a);
  free(b);
  free(c);
  return 0;
}
