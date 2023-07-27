#pragma once
#include <iostream>
#include <sstream>
#include <vector>

class Date{
public:
    int day;
    std::string month;
    int year;
    int hour;
    int min;

    Date();
    Date(std::string s);

private:


};