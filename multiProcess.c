#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <time.h>

int size = 10,x = 0, y = 0;
int **matrix, **matrix2, **matrix3;

int **create_matrix(){

    int **temp_matrix = (int **) malloc(sizeof(int *)*size);
    int i = 0, j = 0;
    for(i = 0; i < size; i++)
        temp_matrix[i] = (int *) malloc(sizeof(int)*size); 
     return temp_matrix;
}

void print_matrix( int **matrix, int size ){
  int i, j;
  for (i = 0; i < size; ++i) {
    for (j = 0; j < size-1; ++j) {
      printf( "%d, ", matrix[ i ][ j ] );
    }
    printf( "%d", matrix[ i ][ j ] );
    putchar( '\n' );
  }
}

void * matrix_filler( void *args ){
	int index;
    index = (int) args;

	srand(time(NULL));
	int r = rand()%150000;
	printf("%d\n",index); 
	matrix[index%size][index%size] = r;
	int k = rand()%150000;
	matrix2[index%size][index%size] = k;
}


int main(){
	pthread_t * threads;
	threads = (pthread_t *) malloc( size * size * sizeof(pthread_t) );
	int i;

	matrix  = create_matrix( size );
  	matrix2 = create_matrix( size );
	matrix3 = create_matrix( size );

	for ( i = 0; i < size * size; ++i ) {
    	int *tid;
    	tid = (int *) malloc( sizeof(int) );
    	*tid = i;
    	pthread_create( &threads[i], NULL, matrix_filler, (void *)tid );
	}

	for ( i = 0; i < size * size; ++i ) {
    	pthread_join( threads[i], NULL );
	}

    printf( "Matrix 1:\n" );
    print_matrix( matrix, size );
    printf( "Matrix 2:\n" );
    print_matrix( matrix2, size );

    return 0;
}