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
const std::string YearAvg::toCSV() {
	/*
	std::ostringstream strs; // init an empty output buffer string
	strs << temp; // write the temperature into the buffer
	std::string tempStr = strs.str(); // copy the buffer's content into tempStr 
	strs.str(""); // empty the buffer
	strs << year;
	std::string yearStr = strs.str();
	strs.str("");
	strs << rain;
	std::string rainStr = strs.str();
	return tempStr + "," + yearStr + "," + rainStr;
	*/
	return std::to_string (this->temp) + "," +
		   std::to_string (this->year) + "," + 
		   std::to_string (this->rain);

}
