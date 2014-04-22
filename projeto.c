#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include "display.h"

#define SPECTATOR_MAX_WAIT 2*(SPECTATORS+IMMIGRANTS)
#define JUDGE_SLEEP 3

/* tudo static pra evitar conflitos */

static sem_t no_judge;			/* 1 */
static sem_t exit_sem;			/* 0 */
static sem_t all_gone;			/* 1 */

static pthread_mutex_t mutex;
static pthread_mutex_t rand_lock;
static pthread_cond_t confirmed;
static pthread_cond_t all_signed_in;

static int entered = 0;
static int checked = 0;
static int judge_inside = 0;


void *spectator(void *v)
{
  int i, id;
  while (1)
    {
      id = spec_arrive();

      /* turnstile para entrar no hall */
      sem_wait(&no_judge);
      spec_enter(id);
      sem_post(&no_judge);

      spec_spec(id);

      /* dorme um tempo aleatório antes de sair */

      pthread_mutex_lock(&rand_lock);
      i = (rand() % SPECTATOR_MAX_WAIT) + 1;
      pthread_mutex_unlock(&rand_lock);

      sleep(i);

      spec_leave(id);
    }
  return NULL;
}

void *immigrant(void *v)
{
  int id;
  while (1)
    {

      id = immi_arrive();
      /* turnstile pra entrar no hall */
      sem_wait(&no_judge);
      entered++;
      immi_enter(id);
      sem_post(&no_judge);


      pthread_mutex_lock(&mutex);

      /* o último a fazer checkin avisa o judge */
      if (entered == ++checked && judge_inside)
        pthread_cond_signal(&all_signed_in);

      immi_checkin(id);
      immi_sit(id);

      /* esperam a confirmação e soltam o mutex */
      pthread_cond_wait(&confirmed, &mutex);
      pthread_mutex_unlock(&mutex);

      /* juram e pegam certificado concorrentemente */
      immi_swear(id);
      immi_getcert(id);

      /* turnstile da saída */
      sem_wait(&exit_sem);
      immi_leave(id);

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
  int i;

  /* inicializando as putaria tudo */
  srand(time(0));

  sem_init(&no_judge, 0, 1);
  sem_init(&exit_sem, 0, 0);
  sem_init(&all_gone, 0, 0);

  pthread_mutex_init(&mutex, NULL);
  pthread_mutex_init(&rand_lock, NULL);

  pthread_cond_init(&confirmed, NULL);
  pthread_cond_init(&all_signed_in, NULL);

  /* se init retornar algo é porque zicou a inicialização */

  if (!(i = init()))
    {

      for (i = 0; i < IMMIGRANTS; i++)
	pthread_create(thr_immig + i, NULL, immigrant, NULL);

      for (i = 0; i < SPECTATORS; i++)
	pthread_create(thr_specs + i, NULL, spectator, NULL);

      pthread_create(&thr_judge, NULL, judge, NULL);

      pthread_join(thr_judge, NULL);

      for (i = 0; i < SPECTATORS; i++)
	pthread_join(thr_specs[i], NULL);

      for (i = 0; i < IMMIGRANTS; i++)
	pthread_join(thr_immig[i], NULL);

      i = 0;
    }

  /* clean-up que nunca roda já que o programa é loop inifinito hu3 */

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
