#include "time.h"
#include <sstream>
#include <iomanip> // what is this for?
// This is for manipulating the output format, such as setting the width and fill characters.

Time::Time() : hour(0), min(0), sec(0) {}

Time::Time(const std::string & timeStr){
    std::stringstream ss(timeStr);
    char sep;
    ss >> hour >> sep >> min >> sep >> sec;
}

int Time::getHour() const { return hour; }
int Time::getMin() const { return min; }
int Time::getSec() const { return sec; }

void Time::setTime(int h, int m, int s) {
    hour = h;
    min = m;
    sec = s;
}

std::string Time::toString() const {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hour << ":"
        << std::setw(2) << std::setfill('0') << min << ":"
        << std::setw(2) << std::setfill('0') << sec;
    return oss.str();
}