#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdalign.h>
#include <stdbool.h>
#include <tgmath.h>

// include AnnexK (offers athread safe and re-entrant version of strtok() function of tokenisation called strok_r())
#define __STDC_WANT_LIB_EXT1__ 1

#ifndef __STDC_WANT_LIB_EXT1__
#error "we need strtok_r() from AnnexK"
#endif