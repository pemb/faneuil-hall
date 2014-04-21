#ifndef SPRITES_H
#define SPRITES_H

#include <stdlib.h> /* definição de NULL lel */

/* sprites (desenhos) são vetor de apontadores pra strings das linhas
   o último ponteiro é NULL, assim que draw_sprite sabe onde parar */

#define SPEC_HEIGHT 6
#define SPEC_WIDTH 5


char *spec [] = 
  {
    " (}   ",
    "/|\\_/",
    "\\|   ",
    " |\\  ",
    "/ |  ",
    "` `  ",
    NULL
  };


#define IMMI_HEIGHT 8
#define IMMI_WIDTH 7

char *immi[] = 
  {
    "  /-\\  ",
    "  \\_/  ",
    " /\\Y/\\",
    "|| : ||",
    "(|---|)",
    " | | | ",
    " | | | ",
    " (/ \\) ",
    NULL
  };

#define HAMMER_HEIGHT 4
#define HAMMER_WIDTH 16

char *hammer[] = 
  {
    " __             ",
    "|  | ___________",
    "|  >:===========",
    "|__|            ",
    NULL
  };

/* TODO: defines dos tamanhos do resto */

char * cadeira[] =
  {
    " .-===-. ",
    " | . . | ",
    " | .'. | ",
    "()_____()",
    "||_____||",
    " W     W ",
      NULL
  };

char * bigMan [] = 
  {
    "  _    ",
    " (_)   ",
    " _;_   ",
    "/ | \\  ",
    "\\ |  \\ ",
    " `|\\  `",
    "  | \\  ",
    " /  /_ ",
    " `     ",
      NULL
  };


#endif
