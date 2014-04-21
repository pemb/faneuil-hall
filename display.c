#include "display.h"
#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include <pthread.h>
#include <string.h>
pthread_mutex_t ncurses_lock = PTHREAD_MUTEX_INITIALIZER;

void chair_spec(WIN * p_win, bool flag, int i);
void desk_judge(WIN * p_win, bool flag);
void init_win_params(WIN * p_win);
void print_win_params(WIN * p_win);
void create_box(WIN * win, bool flag);

#define qtd_cadeiras 8
#define spectadores  8

char juiz_entrou[] = {"O Juiz esta na sala."};

void init_win_params(WIN * p_win)
{
  getmaxyx(stdscr, p_win->height, p_win->width);
  p_win->width = p_win->width - 10;
  p_win->height = p_win->height - 10;
  p_win->starty = (LINES - p_win->height) / 2;
  p_win->startx = (COLS - p_win->width) / 2;

  p_win->border.ls = '|';
  p_win->border.rs = '|';
  p_win->border.ts = '=';
  p_win->border.bs = '=';
  p_win->border.tl = '+';
  p_win->border.tr = '+';
  p_win->border.bl = '+';
  p_win->border.br = '+';


}

void print_win_params(WIN * p_win)
{
#ifdef _DEBUG
  mvprintw(25, 0, "%d %d %d %d", p_win->startx, p_win->starty,
	   p_win->width, p_win->height);
  refresh();
#endif
}

void create_box(WIN * p_win, bool flag)
{
  int i, j;
  int x, y, w, h;

  x = p_win->startx;
  y = p_win->starty;
  w = p_win->width;
  h = p_win->height;

  if (flag == TRUE)
    {
      mvaddch(y, x, p_win->border.tl);
      mvaddch(y, x + w, p_win->border.tr);
      mvaddch(y + h, x, p_win->border.bl);
      mvaddch(y + h, x + w, p_win->border.br);
      mvhline(y, x + 1, p_win->border.ts, w - 1);
      mvhline(y + h, x + 1, p_win->border.bs, w - 1);
      mvvline(y + 1, x, p_win->border.ls, h - 1);
      mvvline(y + 1, x + w, p_win->border.rs, h - 1);

      mvvline(y + 1, x + 42, 'X', h - 1);	/* barra vertical */

      /*    desk_judge(p_win, true);

      for (i = 0; i < spectadores; i++)
	chair_spec(p_win, false, i);
      for (; i < qtd_cadeiras; i++)
	chair_spec(p_win, true, i);
      // drawEveryOne(p_win, y+1, x+1); 
      //hammer(p_win);
      */
  } else
    for (j = y; j <= y + h; ++j)
      for (i = x; i <= x + w; ++i)
	mvaddch(j, i, ' ');

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
  WIN win;
  int ch;
  start_color();		/* Start the color functionality */
  cbreak();			/* Line buffering disabled, Pass on
				 * everty thing to me           */
  keypad(stdscr, TRUE);		/* I need that nifty F1         */
  noecho();
  init_pair(1, COLOR_CYAN, COLOR_BLACK);

  /* Initialize the window parameters */
  init_win_params(&win);
  print_win_params(&win);
  curs_set(0);
  attron(COLOR_PAIR(1));
  refresh();
  attroff(COLOR_PAIR(1));

  create_box(&win, TRUE);
  return 0;
}

void finish(void)
{
  endwin();
}

void spec_enter(void)
{
  pthread_mutex_lock(&ncurses_lock);
  addstr("Spectator enters.\n");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void spec_spec(void)
{
  pthread_mutex_lock(&ncurses_lock);
  addstr("Spectator spectates.\n");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
  
}

void spec_leave(void)
{
  pthread_mutex_lock(&ncurses_lock);
  addstr("Spectator leaves.\n");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void immi_getcert(void)
{
  pthread_mutex_lock(&ncurses_lock);
  addstr("Immigrant gets certificate.\n");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void immi_leave(void)
{
  pthread_mutex_lock(&ncurses_lock);
  addstr("Immigrant leaves.\n");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void immi_enter(void)
{
  pthread_mutex_lock(&ncurses_lock);
  addstr("Immigrant enters.\n");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void immi_checkin(void)
{
  pthread_mutex_lock(&ncurses_lock);
  addstr("Immigrant checks in.\n");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void immi_sit(void)
{
  pthread_mutex_lock(&ncurses_lock);
  addstr("Immigrant sits down.\n");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);

}

void immi_swear(void)
{
  pthread_mutex_lock(&ncurses_lock);
  addstr("Immigrant swears.\n");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void judge_enter(void)
{
  pthread_mutex_lock(&ncurses_lock);
  addstr("Judge enters.\n");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void judge_confirm(void)
{
  pthread_mutex_lock(&ncurses_lock);
  addstr("Judge confirms.\n");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void judge_leave(void)
{
  pthread_mutex_lock(&ncurses_lock);
  addstr("Judge leaves.\n");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}
