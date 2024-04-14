#ifndef _WEATHER_UTILS_H
#define _WEATHER_UTILS_H

#include <stdio.h>
#include "array_helpers.h"
#include "weather.h"

int his_min_temp (WeatherTable a);

void procedimiento(WeatherTable a, int output[YEARS]);

void proc(WeatherTable a, month_t output[YEARS]);

#endif
