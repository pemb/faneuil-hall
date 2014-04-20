#include "display.h"
#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include <pthread.h>

pthread_mutex_t ncurses_lock = PTHREAD_MUTEX_INITIALIZER;

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
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
  /* init_pair(1, COLOR_CYAN, COLOR_BLACK); */
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
