/*
 * YearAvg.h
 *
 *  Created on: Oct 7, 2020
 *      Author: dave
 */

#ifndef YEARAVG_H_
#define YEARAVG_H_
#include <sstream>
using namespace std;
class YearAvg {
public:
	YearAvg();
	YearAvg(double temp, int year, double rain);
	virtual ~YearAvg();
 
	double getRain() const {
		return rain;
	}

	void setRain(double rain) {
		this->rain = rain;
	}

	double getTemp() const {
		return temp;
	}

	void setTemp(double temp) {
		this->temp = temp;
	}

	int getYear() const {
		return year;
	}

	void setYear(int year) {
		this->year = year;
	}
	const std::string toCSV();
	static bool sortByRain(const YearAvg &lhs, const YearAvg &rhs) { return lhs.rain < rhs.rain; }
private:
	double temp;
	int year;
	double rain;

};

#endif /* YEARAVG_H_ */
