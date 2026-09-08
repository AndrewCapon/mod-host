#include <sys/time.h>
#include <stddef.h>
#include <stdio.h>

#include "tap_tempo.h"

static inline unsigned long TapTempoGetCurrentMS(void)
{
	unsigned long result;

	// verified to be faster vs `clock_gettime`
	struct timeval tv;
	gettimeofday(&tv, NULL);
	result = (tv.tv_sec*1000) + (tv.tv_usec / 1000);

	return result;
}

void TapTempoInit(tap_tempo_t *tap_tempo)
{
	ma_init(&(tap_tempo->ma), tap_tempo->intervals, TT_MAXTAPS, true);
	tap_tempo->last_time = 0;
}

float TapTempoUpdate(tap_tempo_t *tap_tempo)
{
	float         result = 20.0f;
	unsigned long current_ms    = TapTempoGetCurrentMS();
	float         interval_time = current_ms - tap_tempo->last_time;

	if(tap_tempo->last_time && (interval_time > TT_MAXTIME))
		TapTempoInit(tap_tempo);
 
	if(tap_tempo->last_time == 0)
	{
		tap_tempo->last_time = current_ms;
	}
	else
	{
		ma_add(&(tap_tempo->ma), interval_time);
		result = 60000.0f / ma_average(&(tap_tempo->ma));
	}

	tap_tempo->last_time = current_ms;

	if(result < TT_MIN_TEMPO)
		result = TT_MIN_TEMPO;
	else if(result > TT_MAX_TEMPO)
		result = TT_MAX_TEMPO;
		
	return result;
}