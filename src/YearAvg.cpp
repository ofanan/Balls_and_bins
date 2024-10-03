/*
 * YearAvg.cpp
 *
 *  Created on: Oct 7, 2020
 *      Author: dave
 */

#include "YearAvg.h"

YearAvg::YearAvg() {
	this->temp_ = 0;
	this->year_ = 0;
	this->rain_ = 0;

}
YearAvg::YearAvg(double temp, int year, double rain) {
	this->temp_ = temp;
	this->year_ = year;
	this->rain_ = rain;

}

YearAvg::~YearAvg() {
	// TODO Auto-generated destructor stub
}

// Return "this" fields formatted as a single .csv string, where the delimiter is ","
const std::string YearAvg::toCSV()const {
	return std::to_string (this->getTemp()) + "," +
		   std::to_string (this->getYear()) + "," + 
		   std::to_string (this->getRain());
}


