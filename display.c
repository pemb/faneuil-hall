#include "display.h"
#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t ncurses_lock = PTHREAD_MUTEX_INITIALIZER;

/* static WINDOW * hall, outside; */

#define BORDER 5

char juiz_entrou[] = "O Juiz esta na sala.";
char *smallMan [] = 
  {
    " (}  ",
    "/|\\_/",
    "\\|   ",
    " |\\  ",
    "/ |  ",
    "` `  ",
    "",
  };

char *immi[] = /* ou 10 */
  {
    "  /-\\  ",
    "  \\_/  ",
    "/\\Y/\\ ",
    "|| : ||",
    "(|---|)",
    " | | | ",
    " | | | ",
    " (/ \\) ",
    ""
  };

char *hammer[] = 
  {
    " __             ",
    "|  | ___________",
    "|  >:===========",
    "|__|            ",
    ""
  };

void draw_sprite( WINDOW * win, char** sprite, int y, int x) {
  int p;
  pthread_mutex_lock(&ncurses_lock);
  for(p=0; sprite[p][0] != '\0'; p++)
    mvwaddstr( win, y + p, x, sprite[p]);
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);

}

void erase_hammer(int y, int x) {
  erase_drawing(y, x, 4, 17);

}

/* Desenha um spectator na posicao y,x desejada */
void draw_spec(int y, int x) {
  int p;
  pthread_mutex_lock(&ncurses_lock);
  for(p=0; p<6; p++)
    mvaddstr(y + p, x, smallMan[p]);
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}
/* Desenha imigrante na coord y,x */
void draw_immi(int y, int x) {
  int p;
  pthread_mutex_lock(&ncurses_lock);
  for(p=0; p<8; p++)
    mvaddstr(y + p, x, immi[p]);
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void erase_spec(int y, int x) {
  erase_drawing(y, x, 6, 6);

}

void erase_immi(int y, int x) {
  erase_drawing(y, x, 8, 8);

}

void erase_block(WINDOW * win, int y, int x, int eltos_y, int eltos_x) {
  int i;
  pthread_mutex_lock(&ncurses_lock);
  for (i = 0; i < eltos_y; i++)
    mvwhline(win, y + i, x, ' ', eltos_x);
  refresh();
  pthread_mutex_unlock(&ncurses_lock);  
}


void draw_hall(void)
{
  /* desenha perímetro do hall */
  box(stdscr, 0, 0);

  /* desenha divisão da esquerda */
  mvaddch(0, COLS/4, ACS_TTEE);
  mvvline(1, COLS/4, ACS_VLINE, LINES-2);
  mvaddch(LINES-1, COLS/4, ACS_BTEE);
  refresh();
}

int init(void)
{
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

  draw_hall();
  /*sleep(10);*/
  
  return 0;
}

void finish(void)
{
  endwin();
}

void spec_enter(void)
{
  pthread_mutex_lock(&ncurses_lock);
  /* mvaddstr(1,1,"Spectator enters.\n");*/
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void spec_spec(void)
{
  pthread_mutex_lock(&ncurses_lock);
  /*addstr("Spectator spectates.\n");*/
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
  
}

void spec_leave(void)
{
  pthread_mutex_lock(&ncurses_lock);
  /* addstr("Spectator leaves.\n");*/
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void immi_getcert(void)
{
  pthread_mutex_lock(&ncurses_lock);
  /* addstr("Immigrant gets certificate.\n");*/
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void immi_leave(void)
{
  pthread_mutex_lock(&ncurses_lock);
  /* addstr("Immigrant leaves.\n");*/
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void immi_enter(void)
{
  pthread_mutex_lock(&ncurses_lock);
  /*addstr("Immigrant enters.\n");*/
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void immi_checkin(void)
{
  pthread_mutex_lock(&ncurses_lock);
  /* addstr("Immigrant checks in.\n"); */
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void immi_sit(void)
{
  pthread_mutex_lock(&ncurses_lock);
  /* addstr("Immigrant sits down.\n"); */
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);

}

void immi_swear(void)
{
  pthread_mutex_lock(&ncurses_lock);
  /* addstr("Immigrant swears.\n"); */
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void judge_enter(void)
{
  pthread_mutex_lock(&ncurses_lock);
  /*  addstr("Judge enters.\n"); */
  draw_hammer(LINES * 0.9, COLS * 0.8);
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void judge_confirm(void)
{
  pthread_mutex_lock(&ncurses_lock);
  /* addstr("Judge confirms.\n");*/
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void judge_leave(void)
{
  pthread_mutex_lock(&ncurses_lock);
  /*addstr("Judge leaves.\n"); */
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

