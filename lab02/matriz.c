#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Tamanho das matrizes
#define P 4
#define S 2
#define T 5

//Valores das matrizes
int mat1 [P][S] = {{7,1},{9,5},{2,6},{3,6}};
int mat2 [S][T] = {{3,7,2,5,1},{9,1,4,9,7}};
int mat3 [P][T]; //Matriz resultante

//Armazena a linha e coluna da matriz que vai ser multiplicada
struct v {
   int i;
   int j;
};

void *runner(void *param) {
   struct v *aux=param;
   int n, soma=0;
   //Executa o calculo da linha da matriz 1 pela coluna da matriz 2
   for(n = 0; n < S; n++){
      soma+=mat1[aux->i][n] * mat2[n][aux->j];
   }
   //Guarda o resultado
   mat3[aux->i][aux->j] = soma;
   pthread_exit(0);
}

int main(int argc, char *argv[]) {

   int i,j, cont = 0;
   //Laço para fazer o calculo da matriz resultante
   for(i = 0; i < P; i++) {
      for(j = 0; j < T; j++) {
         struct v *aux = (struct v *) malloc(sizeof(struct v));
         aux->i = i;
         aux->j = j;
         pthread_t tid;       
         pthread_attr_t atri;
         pthread_attr_init(&atri);
         pthread_create(&tid,&atri,runner,aux);
         pthread_join(tid, NULL);
         cont++;
      }
   }
   //Escreve o resultado da matriz
   for(i = 0; i < P; i++) {
      for(j = 0; j < T; j++) {
         printf("%d ", mat3[i][j]);
      }
      printf("\n");
   }
}
