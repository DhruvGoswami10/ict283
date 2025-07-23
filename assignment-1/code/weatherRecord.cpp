#include "WeatherRecord.h"

WeatherRecord::WeatherRecord() : windSpeed(0.0f), temperature(0.0f), solarRadiation(0.0f){}

WeatherRecord::WeatherRecord(const Date & d, const Time & t, float windSpeed, float temp, float solarRadiation) 
    : date(d), time(t), windSpeed(windSpeed), temperature(temp), solarRadiation(solarRadiation) {}

Date WeatherRecord::getDate() const{
    return date;
}

Time WeatherRecord::getTime() const{
    return time;
}

float WeatherRecord::getWindSpeed() const{
    return windSpeed;
}

float WeatherRecord::getTemperature() const{
    return temperature;
}

float WeatherRecord::getSolarRadiation() const{
    return solarRadiation;
}

void WeatherRecord::setDate(const Date & d){
    date = d;
}

void WeatherRecord::setTime(const Time & t){
    time = t;
}

void WeatherRecord::SetWindSpeed(float speed){
    windSpeed = speed;
}

void WeatherRecord::setTemperature(float temp){
    temperature = temp;
}

void WeatherRecord::setSolarRadiation(float radiation){
    solarRadiation = radiation;
}