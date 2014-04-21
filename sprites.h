#ifndef SPRITES_H
#define SPRITES_H

#include <stdlib.h> /* definição de NULL lel */

/* sprites (desenhos) são vetor de apontadores pra strings das linhas
   o último ponteiro é NULL, assim que draw_sprite sabe onde parar */

#define SPEC_HEIGHT 7
#define SPEC_WIDTH 6

char *spec [] =
  {
    "ENTREI"
    " (}   ",
    "/|\\_/",
    "\\|   ",
    " |\\  ",
    "/ |  ",
    "` `  ",
    NULL
  };

#define ESPECTADOR_HEIGHT 7
#define ESPECTADOR_WIDTH 6

char *espectador [] =
  {
    "OUTRO?"
    " (}   ",
    "/|\\_/",
    "\\|   ",
    " |\\  ",
    "/ |  ",
    "` `  ",
    NULL
  };

#define IMMI_HEIGHT 9
#define IMMI_WIDTH 8

char *immi[] =
  {
    "ENTERED!",
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

#define IMMIC_HEIGHT 9
#define IMMIC_WIDTH 8

char *immic[] =
  {
    "CHECKED!"
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

#define SWEAR_HEIGHT 10
#define SWEAR_WIDTH 15

char *swear[] =
  {
    "       _.-/`)",
    "      // / / )",
    "   .=// / / / )",
    "  //`/ / / / /",
    " // /     ` /",
    "||         /",
    " \\       /",
    "  ))    .'",
    " //    /",
    "      /",
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

#define CADEIRA_HEIGHT 6
#define CADEIRA_WIDTH 9

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

#define BIGMAN_HEIGHT 9
#define BIGMAN_WIDTH 8

char * bigMan [] =
  {
    "  _     ",
    " (_)    ",
    " _;_    ",
    "/ | \\  ",
    "\\ |  \\",
    " `|\\  `",
    "  | \\  ",
    " /  /_  ",
    " `      ",
      NULL
  };

#define AWARD_HEIGHT 10
#define AWARD_WIDTH 9

char * award [] =
  {
    "   ___",
    " .'__ '.",
    "/ /_ |ST\\",
    "|  | |  |",
    "\\ <___> /",
    " ;.___.;",
    " |::|;;|",
    " |::/;;|",
    " |:/`\\;|",
    " |/   \\|",
      NULL
  };


#endif
