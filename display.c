#include "display.h"
#include <stdio.h>

void spec_enter(void)
{
  puts("Spectator enters.");
}

void spec_spec(void)
{
  puts("Spectator spectates.");
}

void spec_leave(void)
{
  puts("Spectator leaves.");
}

void immi_getcert(void)
{
  puts("Immigrant gets certificate.");
}

void immi_leave(void)
{
  puts("Immigrant leaves.");
}

void immi_enter(void)
{
  puts("Immigrant enters.");
}

void immi_checkin(void)
{
  puts("Immigrant checks in.");
}

void immi_sit(void)
{
  puts("Immigrant sits down.");
}

void immi_swear(void)
{
  puts("Immigrant swears.");
}

void judge_enter(void)
{
  puts("Judge enters.");
}

void judge_confirm(void)
{
  puts("Judge confirms.");
}

void judge_leave(void)
{
  puts("Judge leaves.");
}
