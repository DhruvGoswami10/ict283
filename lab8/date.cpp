#include "date.h"
#include <sstream>

Date::Date() : day(1), month(1), year(2000) {}
Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

Date::Date(const std::string & dateStr){
  std::stringstream ss(dateStr);
  char slash;
  ss >> day >> slash >> month >> slash >> year;
}

int Date::GetDay() const { return day; }
int Date::GetMonth() const { return month; }
int Date::GetYear() const { return year; }

void Date::SetDate(int d, int m, int y) {day = d; month = m; year = y;}
