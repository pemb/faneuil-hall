#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

//#define a 2;
//#define N_SPECTATORS 2;

sem_t noJudge; //1
sem_t mutex; //1
sem_t confirmed; //0
sem_t saida; //0
sem_t allGone; //0
sem_t allSignedIn;//nao fala
volatile int entered = 0;
volatile int checked = 0;
volatile int judgeInside = 0;

void* spectator (void *v) {
  int r;
  while (1) {
    sleep(2);
    sem_wait(&noJudge);
    printf ("Spectator entrando\n");

    sem_post(&noJudge);

    // spectate();
    printf("Spectator spectando.\n");
    

    /* spec_leave(); */
    printf ("Spectator saindo\n");
  }
}

void* immigrant (void *v) {
  int r;
  while (1) {
    sem_wait(&noJudge);
    // immi_enter();
    sleep(1);
    printf("Immigrant entrando.\n");
    //    entered++;
    __sync_fetch_and_add(&entered, 1);
    sem_post(&noJudge);
  
    sem_wait(&mutex);
    //checkIn();
    printf("Immigrant checking in.\n");
    checked++;
   
    if (judgeInside == 1 && entered == checked) {
      sem_post(&allSignedIn);
    } else {
      sem_post(&mutex);
    }

    //    sitDown();
    printf("Immigrant sentando.\n");
    sem_wait(&confirmed);

    //    swear();
    printf("Immigrant jurando.\n");
    //getCertificate();
    printf("Immigrant pegando certificado.\n");

    sem_wait(&saida);
    //    immi_leave();
    printf("Immigrant saindo.\n");
    //    checked--;
    r = __sync_sub_and_fetch(&checked, 1);
    if (r == 0) 
      sem_post(&allGone);
    
    else 
      sem_post(&saida);
  }
}

void *judge (void *v) {
  int temp;
  while (1) {
    sleep(5);
    sem_wait(&noJudge);
    sem_wait(&mutex);

    //enter();
    printf("Juiz entrando.\n");
    judgeInside = 1;

    if (entered > checked) {
      sem_post(&mutex);
      sem_wait(&allSignedIn);
    }

    //confirm();
    printf("Juiz confirmando.\n");

    //teste
    for (temp = checked; temp > 0; temp--)
      sem_post(&confirmed);
    entered = 0;
    sleep(3);
    // leave(); 
    printf("Juiz saindo.\n");
    judgeInside = 0;
  
    sem_post(&saida);
    sem_wait(&allGone);
    sem_post(&mutex);
    sem_post(&noJudge);
  }
}


int main() {
  pthread_t thr_judge;
  pthread_t thr_immig[2];
  pthread_t thr_specs[2];
  int i=0;
  sem_init(&noJudge, 0, 1);
  sem_init(&mutex, 0, 1);
  sem_init(&confirmed, 0, 0);
  sem_init(&saida, 0, 0);
  sem_init(&allGone, 0, 0);
  sem_init(&allSignedIn, 0, 0); //confirmar

  pthread_create(&thr_judge, NULL, judge, NULL);

  for (i = 0; i < 2; i++)
    pthread_create(thr_immig+i, NULL, immigrant, (void*) &i);

  for (i = 0; i < 2; i++)
    pthread_create(thr_specs+i, NULL, spectator, (void*) &i);
  
  pthread_join(thr_judge, NULL);
  
  for (i = 0; i <  2; i++)
    pthread_join(thr_immig[i], NULL);

  for (i=0; i < 2; i++)
    pthread_join(thr_specs[i], NULL);

  return 0;
}
