#include <stdio.h>
#include "weather_utils.h"


int his_min_temp (WeatherTable a) {	
	int res = a[0][0][0]._min_temp;	
	for (unsigned int year = 0u; year < YEARS; ++year){
		for (month_t month = january; month <= december; ++month){
			for (unsigned int day = 0u; day < DAYS; ++day){
				if (a[year][month][day]._min_temp <= res){
					res = a[year][month][day]._min_temp;
				}
			}
		}
	}
	return res;

}

void procedimiento(WeatherTable a, int output[YEARS]) {
	
	for (unsigned int year = 0u; year < YEARS; ++year){
		output[year]= a[year][0][0]._max_temp;
		for (month_t month = january; month <= december; ++month){
			for (unsigned int day = 0u; day < DAYS; ++day){
				if (output[year] <= a[year][month][day]._max_temp){
					output[year] = a[year][month][day]._max_temp;
				}
			}
		}
	}

}

void proc(WeatherTable a, month_t output[YEARS]){
	month_t mesMax;
	unsigned int precMax;
	unsigned int precM;
	
	for (unsigned int year = 0u; year < YEARS; ++year){
		mesMax= january;
		precMax=0u;
		for (month_t month = january; month < MONTHS; ++month){
			precM = 0;
			for (unsigned int day = 0u; day < DAYS; ++day){
				precM = precM + a[year][month][day]._rainfall;
			}	
			if (precM >= precMax){
				precMax = precM;
				mesMax = month+1;
			}
			
		}
		output[year] = mesMax;
	}


}
