#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include "display.h"

#define SPECTATORS 10
#define SPECTATOR_MAX_WAIT 2*(SPECTATORS+IMMIGRANTS)
#define IMMIGRANTS 4
#define JUDGE_SLEEP 1

typedef struct _coords {
  int x, y;
} coords;

sem_t no_judge;			/* 1 */
sem_t exit_sem;			/* 0 */
sem_t all_gone;			/* 1 */

pthread_mutex_t mutex;
pthread_mutex_t rand_lock;
pthread_cond_t confirmed;
pthread_cond_t all_signed_in;

volatile int entered = 0;
volatile int spectators = 0;
volatile int checked = 0;
volatile int judge_inside = 0;

coords specs[SPECTATORS];
coords immigs[IMMIGRANTS];

void *spectator(void *v)
{
  int id = *(int*) v;
  while (1)
    {

      if (specs[id].x == 0 && specs[id].y == 0) {
	//Desenha na esquerda e atualiza novos valores
      }

      int i;
      /* turnstile para entrar no hall */
      sem_wait(&no_judge);
      spec_enter();
      sem_post(&no_judge);

      spec_spec();

      /* dorme um tempo aleatório */

      pthread_mutex_lock(&rand_lock);
      i = (rand() % SPECTATOR_MAX_WAIT) + 1;
      pthread_mutex_unlock(&rand_lock);

      sleep(i);

      spec_leave();
    }
  return NULL;
}

void *immigrant(void *v)
{
  int id = *(int*) v;
  while (1)
    {
      
      if (immigs[id].x == 0 && immigs[id].y == 0) {
	//Desenha na esquerda e atualiza novos valores
      }

      /* turnstile pra entrar no hall */
      sem_wait(&no_judge);
      entered++;
      immi_enter();
      sem_post(&no_judge);


      pthread_mutex_lock(&mutex);

      /* o último a fazer checkin avisa o judge */
      if (entered == ++checked && judge_inside)
	pthread_cond_signal(&all_signed_in);

      immi_checkin();
      immi_sit();

      /* esperam a confirmação e soltam o mutex */
      pthread_cond_wait(&confirmed, &mutex);
      pthread_mutex_unlock(&mutex);

      /* juram e pegam certificado concorrentemente */
      immi_swear();
      immi_getcert();

      /* turnstile da saída */
      sem_wait(&exit_sem);
      immi_leave();

      /* último a sair */
      if (!--checked)
	sem_post(&all_gone);
      else
	sem_post(&exit_sem);

    }
  return NULL;
}

void *judge(void *v)
{
  while (1)
    {
      /* dá tempo de immigrants entrarem */
#ifdef JUDGE_SLEEP
      sleep(JUDGE_SLEEP);
#endif
      /* trava a turnstile de entrada */
      sem_wait(&no_judge);

      /* pega o mutex */
      pthread_mutex_lock(&mutex);

      judge_inside = 1;
      judge_enter();

      /* só espera se ainda tem immigrants sem checkin */
      while (entered > checked)
	pthread_cond_wait(&all_signed_in, &mutex);

      judge_confirm();

      /* confirma */
      pthread_cond_broadcast(&confirmed);
      pthread_mutex_unlock(&mutex);

      entered = judge_inside = 0;

      judge_leave();
      if (checked)
	{
	  sem_post(&exit_sem);
	  sem_wait(&all_gone);
	}
      sem_post(&no_judge);
    }
  return NULL;
}


int main()
{
  pthread_t thr_judge;
  pthread_t thr_immig[IMMIGRANTS];
  pthread_t thr_specs[SPECTATORS];
  int i, *p_id;

  srand(time(0));

  sem_init(&no_judge, 0, 1);
  sem_init(&exit_sem, 0, 0);
  sem_init(&all_gone, 0, 0);

  pthread_mutex_init(&mutex, NULL);
  pthread_mutex_init(&rand_lock, NULL);

  pthread_cond_init(&confirmed, NULL);
  pthread_cond_init(&all_signed_in, NULL);

  if (!(i = init()))
    {

      for (i = 0; i < IMMIGRANTS; i++) {
	p_id = (int*) malloc(sizeof(int));
	*p_id = i;
	pthread_create(thr_immig + i, NULL, immigrant, (void *) &i);
      }
      for (i = 0; i < SPECTATORS; i++){
	p_id = (int*) malloc(sizeof(int));
	*p_id = i;
	pthread_create(thr_specs + i, NULL, spectator, (void *) &i);
      }
      pthread_create(&thr_judge, NULL, judge, NULL);

      pthread_join(thr_judge, NULL);

      for (i = 0; i < SPECTATORS; i++)
	pthread_join(thr_specs[i], NULL);

      for (i = 0; i < IMMIGRANTS; i++)
	pthread_join(thr_immig[i], NULL);

      i = 0;
    }

  finish();

  sem_destroy(&no_judge);
  sem_destroy(&exit_sem);
  sem_destroy(&all_gone);

  pthread_mutex_destroy(&mutex);
  pthread_mutex_destroy(&rand_lock);
  pthread_cond_destroy(&confirmed);
  pthread_cond_destroy(&all_signed_in);

  return i;
}
