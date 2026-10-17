#include <stdint.h>
#include <stdbool.h>

#include "moving_average.h"

void ma_reset(moving_average_data_t *ma)
{
  ma->average = 0.0;
  ma->last = 0.0;
  ma->idx = 0;
  ma->count = 0;
  uint16_t u; for(u=0; u < ma->size ; u++)
    ma->data[u] = 0.0;
}

void ma_init(moving_average_data_t *ma, double *data, uint16_t size, bool alwaysAccurate)
{
  ma->size = size;
  ma->data = data;
  ma->alwaysAccurate = alwaysAccurate;
	ma_reset(ma);
}


void ma_add(moving_average_data_t *ma, double fValue)
{
  double fRemoved = ma->data[ma->idx];
  ma->data[ma->idx] = fValue;
  ma->last = fValue;
  ma->count ++;

  if(ma->alwaysAccurate && ma->count <= ma->size )
  {
    ma->average = 0;
    uint32_t u; for (u=0; u < ma->count; u++)
      ma->average += ma->data[u]/ma->count ;
  }
  else
  {
    ma->average = ma->average - (fRemoved / ma->size ) + (fValue / ma->size );
  }
  ma->idx = (ma->idx+1) % ma->size ;
}

void ma_add_all(moving_average_data_t *ma, double fValue)
{
  ma->average = fValue;
  ma->count = ma->size ;
  ma->idx = 0;
  uint32_t u; for (u=0; u < ma->count; u++)
    ma->data[u] = fValue;
}

double ma_average(moving_average_data_t *ma)
{
  return ma->average;
}

