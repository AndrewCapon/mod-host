#ifndef MOVING_AVERAGE_H
#define MOVING_AVERAGE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct _moving_average_data_t
{
  float    average;
  float    *data;
  uint16_t idx;
  uint16_t count;
  uint16_t size;
  bool     alwaysAccurate;
} moving_average_data_t;

void 	ma_reset(moving_average_data_t *ma);
void 	ma_init(moving_average_data_t *ma, float *data, uint16_t size, bool alwaysAccurate);
void 	ma_add(moving_average_data_t *ma, float fValue);
void 	ma_add_all(moving_average_data_t *ma, float fValue);
float ma_average(moving_average_data_t *ma);

#endif