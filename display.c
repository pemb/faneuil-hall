#include "display.h"
#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include <pthread.h>

pthread_mutex_t ncurses_lock = PTHREAD_MUTEX_INITIALIZER;

void init(void)
{
  initscr();
  /* start_color(); */
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  /* init_pair(1, COLOR_CYAN, COLOR_BLACK); */

}

void finish(void)
{
  endwin();
}

void spec_enter(void)
{
  pthread_mutex_lock(&ncurses_lock);
  printw("Spectator enters.");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void spec_spec(void)
{
  pthread_mutex_lock(&ncurses_lock);
  printw("Spectator spectates.");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
  
}

void spec_leave(void)
{
  pthread_mutex_lock(&ncurses_lock);
  printw("Spectator leaves.");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void immi_getcert(void)
{
  pthread_mutex_lock(&ncurses_lock);
  printw("Immigrant gets certificate.");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void immi_leave(void)
{
  pthread_mutex_lock(&ncurses_lock);
  printw("Immigrant leaves.");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void immi_enter(void)
{
  pthread_mutex_lock(&ncurses_lock);
  printw("Immigrant enters.");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void immi_checkin(void)
{
  pthread_mutex_lock(&ncurses_lock);
  printw("Immigrant checks in.");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void immi_sit(void)
{
  pthread_mutex_lock(&ncurses_lock);
  printw("Immigrant sits down.");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);

}

void immi_swear(void)
{
  pthread_mutex_lock(&ncurses_lock);
  printw("Immigrant swears.");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void judge_enter(void)
{
  pthread_mutex_lock(&ncurses_lock);
  printw("Judge enters.");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void judge_confirm(void)
{
  pthread_mutex_lock(&ncurses_lock);
  printw("Judge confirms.");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}

void judge_leave(void)
{
  pthread_mutex_lock(&ncurses_lock);
  printw("Judge leaves.");
  refresh();
  pthread_mutex_unlock(&ncurses_lock);
  sleep(1);
}
