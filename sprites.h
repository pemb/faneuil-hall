#ifndef SPRITES_H
#define SPRITES_H

#include <stdlib.h> /* definição de NULL lel */

/* sprites (desenhos) são vetor de apontadores pra strings das linhas
   o último ponteiro é NULL, assim que draw_sprite sabe onde parar */

#define SPEC_HEIGHT 6
#define SPEC_WIDTH 6

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

#define SPECE_HEIGHT 7
#define SPECE_WIDTH 6

char *spece [] =
  {
    "ENTREI",
    " (}   ",
    "/|\\_/",
    "\\|   ",
    " |\\  ",
    "/ |  ",
    "` `  ",
    NULL
  };

#define SPECO_HEIGHT 7
#define SPECO_WIDTH 6

char *speco [] =
  {
    "OUTRO?",
    " (}   ",
    "/|\\_/",
    "\\|   ",
    " |\\  ",
    "/ |  ",
    "` `  ",
    NULL
  };
#define IMMI_HEIGHT 8
#define IMMI_WIDTH 16

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


#define IMMIE_HEIGHT 9
#define IMMIE_WIDTH 16

char *immie[] =
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

#define IMMIS_HEIGHT 9
#define IMMIS_WIDTH 16

char *immis[] =
  {
    "IM SO TIRED!",
    "    /-\\  ",
    "    \\_/  ",
    "   /\\Y/\\",
    "  || : ||",
    "  (|---|)",
    "   | | | ",
    "   | | | ",
    "   (/ \\) ",
    NULL
  };


#define IMMIC_HEIGHT 9
#define IMMIC_WIDTH 16

char *immic[] =
  {
    "CHECK-IN!",
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
#define SWEAR_WIDTH 16

char *swear[] =
  {
    "       _.-/`)  ",
    "      // / / ) ",
    "   .=// / / / )",
    "  //`/ / / / / ",
    " // /     ` /  ",
    "||         /   ",
    " \\\\       /    ",
    "  ))    .'     ",
    " //    /       ",
    "      /        ",
    NULL
  };

char conf[] = {"CONFIRMED!"};

#define HAMMER_HEIGHT 5
#define HAMMER_WIDTH 28

char *hammer[] =
  {
    "SILENCE! THE JUDGE IS HERE!",
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
#define AWARD_WIDTH 16

char * award [] =
  {
    "   ___   ",
    " .'__ '. ",
    "/ /_ |ST\\",
    "|  | |  |",
    "\\ <___> /",
    " ;.___.; ",
    " |::|;;| ",
    " |::/;;| ",
    " |:/`\\;| ",
    " |/   \\| ",
      NULL
  };


#endif
