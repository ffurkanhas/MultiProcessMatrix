#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int size = 0;
int **matrix, **matrix2, **matrix3;
int max_satir = 0;

struct matr {
   int i;
   int j;
};

int **create_matrix();
void *matrix_filler(void *param);
void *mult(void *args);
void *sum(void *args);

int main(int argc, char *argv[]) {
	srand ((unsigned)time(NULL));

	printf("Bir N sayisi giriniz: ");
	scanf("%d",&size);

	matrix  = create_matrix( size );
  	matrix2 = create_matrix( size );
	matrix3 = create_matrix( size );

	int i,j;
	for(i = 0; i < size; i++) {
    	for(j = 0; j < size; j++) {
	        struct matr *data = (struct matr *) malloc(sizeof(struct matr));
	        data->i = i;
	        data->j = j;
	        pthread_t tid;
	        pthread_create(&tid,NULL,matrix_filler,data);
	        pthread_join(tid, NULL);
    	}
    }

	for(i = 0; i < size; i++) {
    	for(j = 0; j < size; j++) {
	        struct matr *data = (struct matr *) malloc(sizeof(struct matr));
	        data->i = i;
	        data->j = j;
	        pthread_t tid;
	        pthread_create(&tid,NULL,mult,data);
	        pthread_join(tid, NULL);
        }
    }

	for(i = 0; i < size; i++) {
    	struct matr *data = (struct matr *) malloc(sizeof(struct matr));
    	data->i = i;
    	pthread_t tid;
    	pthread_create(&tid,NULL,sum,data);
    	pthread_join(tid, NULL);
    }

    for(i = 0; i < size; i++) {
    	for(j = 0; j < size; j++) {
        	printf("%d ", matrix[i][j]);
        }
    	printf("\n");
    }
    printf("-----------\n");
    for(i = 0; i < size; i++) {
    	for(j = 0; j < size; j++) {
        	printf("%d ", matrix2[i][j]);
    	}
    	printf("\n");
    }
    printf("-----------\n");
    for(i = 0; i < size; i++) {
    	for(j = 0; j < size; j++) {
        	printf("%d ", matrix3[i][j]);
    	}
    	printf("\n");
    }
    printf("-----------\n");
    printf("%d\n",max_satir);
}

int **create_matrix(){

    int **temp_matrix = (int **) malloc(sizeof(int *)*size);
    int i = 0;
    for(i = 0; i < size; i++)
        temp_matrix[i] = (int *) malloc(sizeof(int)*size); 
     return temp_matrix;
}

void *matrix_filler(void *param) {
   struct matr *data = param;

   matrix[data->i][data->j] = rand();
   matrix2[data->i][data->j] = rand();

}

void *mult(void *args) {
   struct matr *data = args;
   int n, sum = 0;

   for(n = 0; n < size; n++){
      sum += matrix[data->i][n] * matrix2[n][data->j];
   }

   matrix3[data->i][data->j] = sum;

}

void *sum(void *args) {
	struct matr *data = args;
	int n, sum = 0;

	for(n = 0; n < size; n++){
		sum += matrix3[data->i][n];
	}

	if(sum > max_satir)
		max_satir = sum;

}