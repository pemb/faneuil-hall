#ifndef DISPLAY_H
#define DISPLAY_H

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

void draw_sprite(WINDOW *, char **, int y, int x);

void erase_hammer(int y, int x);

void erase_spec(int y, int x);

void erase_immi(int y, int x);

void erase_drawing(int y, int x, int eltos_y, int eltos_x);

void draw_immi(int y, int x);

void draw_spec(int y, int x);

int init(void);

void finish(void);

void spec_enter(void);

void spec_spec(void);

void spec_leave(void);

void immi_getcert(void);

void immi_leave(void);

void immi_enter(void);

void immi_checkin(void);

void immi_sit(void);

void immi_swear(void);

void judge_enter(void);

void judge_confirm(void);

void judge_leave(void);

#endif
