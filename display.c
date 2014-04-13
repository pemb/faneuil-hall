#include "display.h"
#include <stdio.h>
#include <unistd.h>

void spec_enter(void)
{
  puts("Spectator enters.");
  sleep(1);
}

void spec_spec(void)
{
  puts("Spectator spectates.");
  sleep(1);
}

void spec_leave(void)
{
  puts("Spectator leaves.");
  sleep(1);
}

void immi_getcert(void)
{
  puts("Immigrant gets certificate.");
  sleep(1);
}

void immi_leave(void)
{
  puts("Immigrant leaves.");
  sleep(1);
}

void immi_enter(void)
{
  puts("Immigrant enters.");
  sleep(1);
}

void immi_checkin(void)
{
  puts("Immigrant checks in.");
  sleep(1);
}

void immi_sit(void)
{
  puts("Immigrant sits down.");
  sleep(1);
}

void immi_swear(void)
{
  puts("Immigrant swears.");
  sleep(1);
}

void judge_enter(void)
{
  puts("Judge enters.");
  sleep(1);
}

void judge_confirm(void)
{
  puts("Judge confirms.");
  sleep(1);
}

void judge_leave(void)
{
  puts("Judge leaves.");
  sleep(1);
}
