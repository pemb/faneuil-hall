#ifndef DISPLAY_H
#define DISPLAY_H

typedef struct _win_border_struct {
  char ls, rs, ts, bs, tl, tr, bl, br;
} WIN_BORDER;

typedef struct _WIN_struct {

  int startx, starty;
  int height, width;
  WIN_BORDER border;
  char barra;
} WIN;

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
