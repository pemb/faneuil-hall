#include <ncurses.h>

typedef struct _win_border_struct {
  chtype ls, rs, ts, bs, tl, tr, bl, br;
} WIN_BORDER;

typedef struct _WIN_struct {

  int startx, starty;
  int height, width;
  WIN_BORDER border;
  chtype barra;
} WIN;

void chair_spec(WIN * p_win, bool flag, int i);
void desk_judge(WIN * p_win, bool flag);
void init_win_params(WIN * p_win);
void print_win_params(WIN * p_win);
void create_box(WIN * win, bool flag);

#define qtd_cadeiras 15
#define spectadores  13

int main(int argc, char *argv[])
{
  WIN win;
  int ch;

  initscr();			/* Start curses mode            */
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
  while ((ch = getch()) != 'G')
    {
    }
  endwin();			/* End curses mode                */
  return 0;
}

void init_win_params(WIN * p_win)
{
  getmaxyx(stdscr, p_win->height, p_win->width);
  p_win->width = p_win->width - 10;
  p_win->height = p_win->height - 10;
  p_win->starty = (LINES - p_win->height) / 2;
  p_win->startx = (COLS - p_win->width) / 2;

  p_win->border.ls = ACS_VLINE;
  p_win->border.rs = ACS_VLINE;
  p_win->border.ts = ACS_HLINE;
  p_win->border.bs = ACS_HLINE;
  p_win->border.tl = ACS_ULCORNER;
  p_win->border.tr = ACS_URCORNER;
  p_win->border.bl = ACS_LLCORNER;
  p_win->border.br = ACS_LRCORNER;


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

      mvvline(y + 1, x + 40, 'X', h - 1);	/* barra vertical */

      desk_judge(p_win, true);

      for (i = 0; i < spectadores; i++)
	chair_spec(p_win, false, i);
      for (; i < qtd_cadeiras; i++)
	chair_spec(p_win, true, i);


  } else
    for (j = y; j <= y + h; ++j)
      for (i = x; i <= x + w; ++i)
	mvaddch(j, i, ' ');

  refresh();

}

void desk_judge(WIN * p_win, bool flag)
{
  int x, y, w, h;

  x = p_win->startx;
  y = p_win->starty;
  w = p_win->width;
  h = p_win->height;

  if (flag == FALSE)
    {
      mvvline(0.8 * (y + h), 0.8 * (x + w), '|', 10);
      mvvline(0.8 * (y + h), 0.6 * (x + w), '|', 10);
      mvhline(0.8 * (y + h), 0.6 * (x + w), '-',
	      0.8 * (x + w) - 0.6 * (x + w));
  } else
    {
      mvvline(0.8 * (y + h), 0.8 * (x + w), '|', 10);
      mvvline(0.8 * (y + h), 0.6 * (x + w), '|', 10);
      mvhline(0.8 * (y + h), 0.6 * (x + w), '-',
	      0.8 * (x + w) - 0.6 * (x + w));
      mvhline(0.9 * (y + h), 0.6 * (x + w), '-',
	      0.8 * (x + w) - 0.6 * (x + w));

    }
}

char cadeira[][10] =
  {
    " .-===-. ",
    " | . . | ",
    " | .'. | ",
    "()_____()",
    "||_____||",
    " W     W ",
  };

void chair_spec(WIN * p_win, bool flag, int i)
{
  int x, y, w, h, x1, y1, j;

  x1 = p_win->startx;
  y1 = p_win->starty;
  w = p_win->width;
  h = p_win->height;

  y = (y1 + h) * 0.2;
  x = (x1 + w) * 0.3 + i * 10;

  if (flag == FALSE)
      for (j = 0; j < 6; j++)
	mvaddstr(y + j, x, cadeira[j]);
  else
    {


    }
}
