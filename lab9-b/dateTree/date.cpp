#include "date.h"
#include <sstream>

Date::Date() : day(1), month(1), year(2000) {}

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

Date::Date(const std::string & dateStr){
  std::stringstream ss(dateStr);
  char slash;
  // Initialize with default values first
  day = 1; month = 1; year = 2000;

  // Try to parse, but if it fails, defaults will remain
  ss >> day >> slash >> month >> slash >> year;
}

int Date::GetDay() const { return day; }
int Date::GetMonth() const { return month; }
int Date::GetYear() const { return year; }

void Date::SetDate(int d, int m, int y) {day = d; month = m; year = y;}

int Date::toComparableInt() const{
  return year * 10000 + month * 100 + day;
}

bool Date::operator<(const Date& other) const{
  return this -> toComparableInt() < other.toComparableInt();
}

bool Date::operator>(const Date& other) const{
  return this -> toComparableInt() > other.toComparableInt();
}

bool Date::operator==(const Date& other) const{
  return this -> toComparableInt() == other.toComparableInt();
}

bool Date::operator<=(const Date& other) const{
  return this -> toComparableInt() <= other.toComparableInt();
}

bool Date::operator>=(const Date& other) const{
  return this -> toComparableInt() >= other.toComparableInt();
}

bool Date::operator!=(const Date& other) const{
  return this -> toComparableInt() != other.toComparableInt();
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
  os << date.GetDay() << "/" << date.GetMonth() << "/" << date.GetYear();
  return os;
}
