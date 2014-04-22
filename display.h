#ifndef DISPLAY_H
#define DISPLAY_H

#define NOT_PRESENT 0
#define OUTSIDE 1
#define INSIDE 2

int init(int, int);

void finish(void);

int spec_arrive(void);

void spec_enter(int);

void spec_spec(int);

void spec_leave(int);

int immi_arrive(void);

void immi_getcert(int);

void immi_leave(int);

void immi_enter(int);

void immi_checkin(int);

void immi_sit(int);

void immi_swear(int);

void judge_enter(void);

void judge_confirm(void);

void judge_leave(void);

#endif
