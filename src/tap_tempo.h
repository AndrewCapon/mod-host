#ifndef TAP_TEMPO_H
#define TAP_TEMPO_H

#include <stdint.h>

#include "moving_average.h"

#define TT_MAXTAPS (8)
#define TT_MAXTIME (4000)
#define TT_MIN_TEMPO (20)
#define TT_MAX_TEMPO (280)

typedef struct _tap_tempo_t
{
  moving_average_data_t	ma;
	float									intervals[TT_MAXTAPS];
	unsigned long 				last_time;
} tap_tempo_t;


void  TapTempoInit(tap_tempo_t *tt_data);
float TapTempoUpdate(tap_tempo_t *tt_data);

#endif