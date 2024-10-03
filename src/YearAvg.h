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
using std::string;
using std::stringstream;

class YearAvg {
public:
	YearAvg();
	YearAvg(double temp, int year, double rain);
	virtual ~YearAvg();
 
	double getRain() const {
		return rain_;
	}

	void setRain(double rain) {
		this->rain_ = rain;
	}

	double getTemp() const {
		return temp_;
	}

	void setTemp(double temp) {
		this->temp_ = temp;
	}

	int getYear() const {
		return year_;
	}

	void setYear(int year) {
		this->year_ = year;
	}
	
	bool operator < (const YearAvg &yearObj) const
	{
		return year_ < yearObj.year_;
	}

	const std::string toCSV()const;
	
/*	static bool sortByRain(const YearAvg &lhs, const YearAvg &rhs) { return lhs.rain < rhs.rain; }*/
	static bool sortByRain(const YearAvg &lhs, const YearAvg &rhs) { return lhs.rain_ < rhs.rain_; }
	
private:
	double temp_;
	int year_;
	double rain_;

};

#endif /* YEARAVG_H_ */
