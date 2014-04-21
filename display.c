#include "display.h"
#include "sprites.h"
#include <unistd.h>
#include <curses.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t ncurses_lock = PTHREAD_MUTEX_INITIALIZER;

WINDOW * hall, * outside;

/* contabiliza onde cada thread está */
int specs[SPECTATORS];
int immigs[IMMIGRANTS];

#define OUTSIDE_SIZE IMMI_WIDTH + SPEC_WIDTH + 2

char juiz_entrou[] = "The judge is in.";
/* Função que imprime um sprite na janela win, com início nas coordenadas x,y */
void draw_sprite( WINDOW * win, char** sprite, int y, int x)
{
  int p;
  /* escreve as strings */
  for(p=0; sprite[p] != NULL; p++)
    mvwaddstr(win, y + p, x, sprite[p]);
}
/* Função que apaga um sprite na janela win, nas coordenadas x,y */
void erase_sprite( WINDOW * win, char ** sprite, int y, int x)
{
  int p;
  /* escreve linhas em branco do tamanho das strings */
  for (p = 0; sprite[p] != NULL; p++)
    mvwhline(win, y + p, x, ' ', strlen(sprite[p]));
}
/* Função que desenha o salão, como dois retângulos */
void draw_borders(void)
{
  /* desenha perímetro do hall */
  box(stdscr, 0, 0);

  /* desenha divisão da esquerda */
  mvaddch(0, OUTSIDE_SIZE, ACS_TTEE);
  mvvline(1, OUTSIDE_SIZE, ACS_VLINE, LINES-2);
  mvaddch(LINES-1, OUTSIDE_SIZE, ACS_BTEE);
}

/* Função que inicializa a interface, e cria as janelas */
int init(void)
{

  /* inicializa uma porrada de coisa */
  initscr();
  if (has_colors() == FALSE)
    {
      fprintf (stderr, "Your terminal does not support color.\n");
      return 1;
    }
  start_color();
  cbreak();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);

  /* desenha as linhas */

  draw_borders();

  /* cria janelas do lado de fora e do hall, DESENHEM AQUI PFVR */

  outside = newwin(LINES-2, OUTSIDE_SIZE-1, 1, 1);
  hall = newwin(LINES-2, COLS-(OUTSIDE_SIZE+2), 1, OUTSIDE_SIZE+1);

  refresh();

  return 0;
}

void finish(void)
{
  endwin();
}

/* Função que desenha um espectador na esquerda */
int spec_arrive(void)
{
  int id;
  pthread_mutex_lock(&ncurses_lock);
  for (id = 0; specs[id] != NOT_PRESENT; id++);
  specs[id] = OUTSIDE;
  /* desenha enfileirados verticalmente na esquerda */
  draw_sprite(outside, spec, (SPEC_HEIGHT+1)*id, 0);
  wrefresh(outside);
  pthread_mutex_unlock(&ncurses_lock);
  return id;
}

/* Função que leva o espectador para o lado direito */
void spec_enter(int id)
{
  pthread_mutex_lock(&ncurses_lock);
  specs[id] = INSIDE;
  /* apaga de fora e desenha enfileirados horizontamente no topo */
  erase_sprite(outside, spec, (SPEC_HEIGHT+1)*id, 0);
  draw_sprite(hall, spec, 0, (SPEC_WIDTH+1)*id);
  wrefresh(outside);
  wrefresh(hall);
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

/* Função que troca o estado do espectador para "spectating" */
void spec_spec(int id)
{
  pthread_mutex_lock(&ncurses_lock);
  erase_sprite(hall, spec, 0, (SPEC_WIDTH+1)*id);
  draw_sprite(hall, espectador, 0, (ESPECTADOR_WIDTH+1)*id);
  wrefresh(hall);
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);

}

/* Função que faz o espectador ir embora do hall */
void spec_leave(int id)
{
  pthread_mutex_lock(&ncurses_lock);
  specs[id] = NOT_PRESENT;
  /* só apaga */
  erase_sprite(hall, spec, 0, (SPEC_WIDTH+1)*id);
  wrefresh(hall);
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

/* Função que desenha um imigrante na esquerda */
int immi_arrive(void)
{
  int id, y, x;
  pthread_mutex_lock(&ncurses_lock);
  for (id = 0; immigs[id] != NOT_PRESENT; id++);
  immigs[id] = OUTSIDE;
  getmaxyx(outside, y, x);
  /* desenha enfileirados verticalmente na direita */
  draw_sprite(outside, immi, (IMMI_HEIGHT+1)*id, x-IMMI_WIDTH);
  wrefresh(outside);
  pthread_mutex_unlock(&ncurses_lock);
  return id;
}


/* Função que leva o imigrante para o lado direito */
void immi_enter(int id)
{
  int y, x;
  pthread_mutex_lock(&ncurses_lock);
  immigs[id] = INSIDE;
  getmaxyx(outside, y, x);
  /* apaga de fora e desenha enfileirados horizontamente embaixo dos spectators */
  erase_sprite(outside, immi, (IMMI_HEIGHT+1)*id, x-IMMI_WIDTH);
  draw_sprite(hall, immie, IMMIE_HEIGHT+1, (IMMIE_WIDTH+1)*id);
  wrefresh(outside);
  wrefresh(hall);
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

/* Função que troca o estado do imigrante para "checking in" */
void immi_checkin(int id)
{
  pthread_mutex_lock(&ncurses_lock);
  erase_sprite(hall, immie, IMMIE_HEIGHT+1, (IMMIE_WIDTH+1)*id);
  draw_sprite(hall, immic, IMMIC_HEIGHT+1, (IMMIC_WIDTH+1)*id);
  wrefresh(hall);
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}


/* Função que troca o estado do espectador para sentando */
void immi_sit(int id)
{
  pthread_mutex_lock(&ncurses_lock);
  /* TODO */
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);

}

/* Função que troca o estado do espectador para jurando */
void immi_swear(int id)
{
  pthread_mutex_lock(&ncurses_lock);
  draw_sprite(hall, swear, SPEC_HEIGHT+IMMIC_HEIGHT+5, (SWEAR_WIDTH+1)*id);
  wrefresh(hall);
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

/* Função que troca o estado do imigrante para pegando o certificado */
void immi_getcert(int id)
{
  pthread_mutex_lock(&ncurses_lock);
  erase_sprite(hall, swear, SPEC_HEIGHT+IMMIC_HEIGHT+5, (SWEAR_WIDTH+1)*id);
  draw_sprite(hall, award, SPEC_HEIGHT+IMMIC_HEIGHT+5, (AWARD_WIDTH+1)*id);
  wrefresh(hall);
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

/*Função que faz o imigrante ir embora do hall */
void immi_leave(int id)
{
  pthread_mutex_lock(&ncurses_lock);
  immigs[id] = NOT_PRESENT;
  /* só apaga */
  erase_sprite(hall, immic, IMMIC_HEIGHT+1, (IMMIC_WIDTH+1)*id);
  erase_sprite(hall, award, SPEC_HEIGHT+IMMIC_HEIGHT+5, (AWARD_WIDTH+1)*id);
  wrefresh(hall);
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

/* Função que mostra que o juíz entrou ao desenhar um martelo no local do juíz */
void judge_enter(void)
{
  int y, x;
  pthread_mutex_lock(&ncurses_lock);
  getmaxyx(hall, y, x);
  /* desenha centralizado em baixo */
  draw_sprite(hall, hammer, y - HAMMER_HEIGHT, (x - HAMMER_WIDTH)/2);
  wrefresh(hall);
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

/* Função que troca o estado do juíz para confirmando */
void judge_confirm(void)
{
  int i, y, x;
  pthread_mutex_lock(&ncurses_lock);
  getmaxyx(hall, y, x);
  for (i=0;i<3;i++) {
    erase_sprite(hall, hammer, y - HAMMER_HEIGHT, (x - HAMMER_WIDTH)/2);
    mvwaddstr(hall, y/2, x/2, "CONFIRMED!"); /* ajeitar o lugar */
    wrefresh(hall);
    sleep(0.2);
    draw_sprite(hall, hammer, y - HAMMER_HEIGHT, (x - HAMMER_WIDTH)/2);
    mvwhline(hall, y/2, x/2, ' ', 10);  /*ajeitar o lugar */
    wrefresh(hall);
    sleep(0.2);
  }
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

/* Função que faz o juíz ir embora apagando-o da tela */
void judge_leave(void)
{
  int y, x;
  pthread_mutex_lock(&ncurses_lock);
  getmaxyx(hall, y, x);
  /* apaga */
  erase_sprite(hall, hammer, y - HAMMER_HEIGHT, (x - HAMMER_WIDTH)/2);
  wrefresh(hall);
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}
