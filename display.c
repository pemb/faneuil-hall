#include "display.h"
#include "sprites.h"
#include <unistd.h>
#include <curses.h>
#include <pthread.h>
#include <string.h>
#include <malloc.h>

/* tudo static pra não conflitar com coisas externas */

static pthread_mutex_t ncurses_lock = PTHREAD_MUTEX_INITIALIZER;

static WINDOW * hall, * outside;

typedef struct _sprite {
  WINDOW * window;
  char **charmap;
  int y, x;
} sprite;

static sprite *specsSprites[SPECTATORS];
static sprite *immigsSprites[IMMIGRANTS];
static sprite *swearOrAward[IMMIGRANTS];
static sprite *judge;

/* contabiliza onde cada thread está */

static int specs[SPECTATORS];
static int immigs[IMMIGRANTS];

#define OUTSIDE_SIZE IMMI_WIDTH + SPEC_WIDTH + 2

char juiz_entrou[] = "The judge is in.";
/* Função que imprime um sprite na janela win, com início nas coordenadas x,y */
sprite* draw_sprite( WINDOW * win, char** charmap, int y, int x)
{
  int p;
  sprite *temp = (sprite *) malloc(sizeof(sprite));
  temp->window = win;
  temp->charmap = charmap;
  temp->y = y;
  temp->x= x;

  /* escreve as strings */
  for(p=0; charmap[p] != NULL; p++)
    mvwaddstr(win, y + p, x, charmap[p]);
  return temp;
}
/* Função que apaga um sprite na janela win, nas coordenadas x,y */
void erase_sprite(sprite *temp)
{
  int p;
  /* escreve linhas em branco do tamanho das strings */
  for (p = 0; temp->charmap[p] != NULL; p++)
    mvwhline(temp->window, temp->y + p, temp->x, ' ', strlen(temp->charmap[p]));
  free(temp);
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
  specsSprites[id] = draw_sprite(outside, spec, (SPEC_HEIGHT+1)*id, 0);
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
  erase_sprite(specsSprites[id]);
  specsSprites[id] = draw_sprite(hall, spece, 0, (SPECE_WIDTH+1)*id);
  wrefresh(outside);
  wrefresh(hall);
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

/* Função que troca o estado do espectador para "spectating" */
void spec_spec(int id)
{
  pthread_mutex_lock(&ncurses_lock);
  erase_sprite(specsSprites[id]);
  specsSprites[id] = draw_sprite(hall, speco, 0, (SPECO_WIDTH+1)*id);
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
  erase_sprite(specsSprites[id]);
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
  immigsSprites[id] = draw_sprite(outside, immi, (IMMI_HEIGHT+1)*id, x-IMMI_WIDTH);
  wrefresh(outside);
  pthread_mutex_unlock(&ncurses_lock);
  return id;
}


/* Função que leva o imigrante para o lado direito */
void immi_enter(int id)
{
  pthread_mutex_lock(&ncurses_lock);
  immigs[id] = INSIDE;
  /* apaga de fora e desenha enfileirados horizontamente embaixo dos spectators */
  erase_sprite(immigsSprites[id]);
  immigsSprites[id] = draw_sprite(hall, immie, IMMIE_HEIGHT+1, (SWEAR_WIDTH+1)*id);
  wrefresh(outside);
  wrefresh(hall);
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

/* Função que troca o estado do imigrante para "checking in" */
void immi_checkin(int id)
{
  pthread_mutex_lock(&ncurses_lock);
  erase_sprite(immigsSprites[id]);
  immigsSprites[id] = draw_sprite(hall, immic, IMMIC_HEIGHT+1, (SWEAR_WIDTH+1)*id);
  wrefresh(hall);
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}


/* Função que troca o estado do espectador para sentando */
void immi_sit(int id)
{
  pthread_mutex_lock(&ncurses_lock);
  erase_sprite(immigsSprites[id]);
  immigsSprites[id] = draw_sprite(hall, immis, IMMIS_HEIGHT+1, (SWEAR_WIDTH+1)*id);
  wrefresh(hall);
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);

}

/* Função que troca o estado do espectador para jurando */
void immi_swear(int id)
{
  pthread_mutex_lock(&ncurses_lock);
  swearOrAward[id] = draw_sprite(hall, swear, SPEC_HEIGHT+IMMIC_HEIGHT+5, (SWEAR_WIDTH+1)*id);
  wrefresh(hall);
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

/* Função que troca o estado do imigrante para pegando o certificado */
void immi_getcert(int id)
{
  pthread_mutex_lock(&ncurses_lock);
  erase_sprite(swearOrAward[id]);
  swearOrAward[id] = draw_sprite(hall, award, SPEC_HEIGHT+IMMIC_HEIGHT+5, (SWEAR_WIDTH+1)*id);
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
  erase_sprite(immigsSprites[id]);
  erase_sprite(swearOrAward[id]);
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
  judge = draw_sprite(hall, hammer, y - HAMMER_HEIGHT, (x - HAMMER_WIDTH)/2);
  wrefresh(hall);
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

/* Função que troca o estado do juíz para confirmando */
void judge_confirm(void)
{
  int i;
  pthread_mutex_lock(&ncurses_lock);
  for (i=0;i<3;i++) {
    mvwaddstr(hall, SPECO_HEIGHT + IMMIC_HEIGHT + 5, (IMMIC_WIDTH+1)*i, conf); /* ajeitar o lugar */
    wrefresh(hall);
    sleep(1);
  }
  
  for (i = 0; i < 3; i++)
    mvwhline(hall, SPECO_HEIGHT + IMMIC_HEIGHT + 5, (IMMIC_WIDTH+1)*i, ' ', strlen(conf));
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

/* Função que faz o juíz ir embora apagando-o da tela */
void judge_leave(void)
{
  pthread_mutex_lock(&ncurses_lock);
  /* apaga */
  erase_sprite(judge);
  wrefresh(hall);
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}
