#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <semaphore.h>

sem_t noJudge; //1
sem_t mutex; //1
sem_t confimed; //0
sem_t exit; //0
sem_t allGone; //0
sem_t allSignedIn;//nao fala
volatile int entered = 0;
volatile int checked = 0;
volatile int judge = 0;

void* spectator (void *v) {
  while (true) {
    sem_wait(&noJudge);
    spec_enter();
    sem_post(&noJudge);

    spectate();

    spec_leave();
  }
}

void* immigrant (void *v) {
  while (true) {
    sem_wait(&noJudge);
    immi_enter();
    entered++;
    sem_post(&noJudge);
  
    sem_wait(&mutex);
    checkIn();
    checked++;
  
    if (judge == 1 && entered == checked) {
      sem_post(&allSignedIn);
    } else {
      sem_post(&mutex);
    }

    sitDown();
    sem_wait(&confirmed);

    swear();
    getCertificate();

    sem_wait(&exit);
    immi_leave();
    checked--;
    if (checked == 0)
      sem_post(&allGone);
    else
      sem_post(&exit);
  }
}

void *judge (void *v) {
  while (true) {
    sem_wait(&noJudge);
    sem_wait(&mutex);

    enter();
    judge = 1;

    if (entered > checked) {
      sem_post(&mutex);
      sem_wait(&allSignedIn);
    }

    confirm();

    //teste
    for (; checked > 0; checked--)
      sem_post(&confirmed);
    entered = 0;
  
    leave();
    judge = 0;
  
    sem_post(&exit);
    sem_wait(&allGone);
    sem_post(&mutex);
    sem_post(&noJudge);
  }
}


int main() {
  sem_init(&noJudge, 0, 1);
  sem_init(&mutex, 0, 1);
  sem_init(&confimed, 0, 0);
  sem_init(&exit, 0, 0);
  sem_init(&allGone, 0, 0);
  sem_init(&allSignedIn, 0, 0); //confirmar

  
  

  return 0;
}
