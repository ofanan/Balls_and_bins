/*
 * YearAvg.cpp
 *
 *  Created on: Oct 7, 2020
 *      Author: dave
 */

#include "YearAvg.h"

YearAvg::YearAvg() {
	this->temp = 0;
	this->year = 0;
	this->rain = 0;

}
YearAvg::YearAvg(double temp, int year, double rain) {
	this->temp = temp;
	this->year = year;
	this->rain = rain;

}

YearAvg::~YearAvg() {
	// TODO Auto-generated destructor stub
}

// Return "this" fields formatted as a single .csv string, where the delimiter is ","
const std::string YearAvg::toCSV() {
	return std::to_string (this->temp) + "," +
		   std::to_string (this->year) + "," + 
		   std::to_string (this->rain);
}
