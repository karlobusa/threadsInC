#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define REDOVI 6
#define STUPCI 6

int suma = 0;
int disp[REDOVI][STUPCI];

void *PrintHello(void *threadid)
{
   long tid;
   long i;
   int red = 0;
   tid = (long)threadid;
   for (i = 0; i < REDOVI; i++)
   {
      red = red + disp[tid][i];
      suma += disp[tid][i];
   }
   printf("Suma %ld. reda je %d\n", tid + 1, red);
   pthread_exit(NULL);
}

int main()
{

   /*Counter variables for the loop*/
   int i, j;
   int counter = 0;
   for (i = 0; i < REDOVI; i++)
   {
      for (j = 0; j < STUPCI; j++)
      {
         disp[i][j] = counter;
         counter++;
      }
   }
   //Displaying array elements
   printf("prva matrica:\n");
   for (i = 0; i < REDOVI; i++)
   {
      for (j = 0; j < STUPCI; j++)
      {
         printf("%d ", disp[i][j]);
      }
      printf("\n");
   }

   pthread_t threads[REDOVI];
   int rc;
   long t;

   for (t = 0; t < REDOVI; t++)
   {
      printf("In main: creatingthread%ld\n", t);
      rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
      if (rc)
      {
         printf("rc, povratna vrijednost pthread_create nije nula, neka greska...\n");
         exit(-1);
      }
   }

   for (t = 0; t < REDOVI; t++)
   {
      pthread_join(threads[t], NULL);
      printf("Join thread %ld\n", t);
   }

   printf("Suma je %d\n", suma);
   pthread_exit(NULL);

   return 0;
}
