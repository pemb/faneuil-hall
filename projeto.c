#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include "display.h"

#define SPECTATORS 10
#define IMMIGRANTS 10

sem_t no_judge;			/* 1 */
sem_t saida;			/* 0 */
sem_t all_gone;			/* 1 */

pthread_mutex_t mutex;
pthread_cond_t confirmed;
pthread_cond_t all_signed_in;

volatile int entered = 0;
volatile int checked = 0;
volatile int judgeInside = 0;


void *spectator(void *v)
{
  while (1)
    {
      /* turnstile para entrar no hall */
      sem_wait(&no_judge);
      sem_post(&no_judge);

      spec_enter();
      spec_spec();

      /* TODO: espera aleatória */

      sleep(10);

      spec_leave();
    }
  return NULL;
}

void *immigrant(void *v)
{
  while (1)
    {

      /* turnstile pra entrar no hall */
      sem_wait(&no_judge);
      entered++;
      immi_enter();
      sem_post(&no_judge);


      /* faz checkin */
      pthread_mutex_lock(&mutex);
      checked++;
      immi_checkin();


      /* o último a fazer checkin avisa o judge */
      if (judgeInside && entered == checked)
	pthread_cond_signal(&all_signed_in);

      immi_sit();

      /* esperam a confirmação e soltam o mutex */
      pthread_cond_wait(&confirmed, &mutex);
      pthread_mutex_unlock(&mutex);

      /* juram e pegam certificado paralelamente */
      immi_swear();
      immi_getcert();

      /* turnstile da saída */
      sem_wait(&saida);
      immi_leave();

      /* último a sair */
      if (!--checked)
	sem_post(&all_gone);
      else
	sem_post(&saida);

    }
  return NULL;
}

void *judge(void *v)
{
  while (1)
    {

      /* dá tempo de immigrants entrarem */
      sleep(5);

      /* trava a turnstile de entrada */
      sem_wait(&no_judge);

      /* pega o mutex */
      pthread_mutex_lock(&mutex);

      judgeInside = 1;
      judge_enter();

      /* só espera se ainda tem immigrants sem checkin */
      if (entered > checked)
	pthread_cond_wait(&all_signed_in, &mutex);
      pthread_mutex_unlock(&mutex);

      /* confirma */
      judge_confirm();
      pthread_cond_broadcast(&confirmed);

      entered = 0;
      judgeInside = 0;
      judge_leave();

      sem_post(&saida);
      sem_wait(&all_gone);
      sem_post(&no_judge);
    }
  return NULL;
}


int main()
{
  pthread_t thr_judge;
  pthread_t thr_immig[IMMIGRANTS];
  pthread_t thr_specs[SPECTATORS];
  int i;
  sem_init(&no_judge, 0, 1);
  sem_init(&saida, 0, 0);
  sem_init(&all_gone, 0, 0);
  /* sem_init(&all_signed_in, 0, 0); //confirmar */

  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&confirmed, NULL);
  pthread_cond_init(&all_signed_in, NULL);


  pthread_create(&thr_judge, NULL, judge, NULL);

  for (i = 0; i < IMMIGRANTS; i++)
    pthread_create(thr_immig + i, NULL, immigrant, (void *) &i);

  for (i = 0; i < SPECTATORS; i++)
    pthread_create(thr_specs + i, NULL, spectator, (void *) &i);

  pthread_join(thr_judge, NULL);

  for (i = 0; i < IMMIGRANTS; i++)
    pthread_join(thr_immig[i], NULL);

  for (i = 0; i < SPECTATORS; i++)
    pthread_join(thr_specs[i], NULL);

  sem_destroy(&no_judge);
  sem_destroy(&saida);
  sem_destroy(&all_gone);

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&confirmed);
  pthread_cond_destroy(&all_signed_in);

  return 0;
}
