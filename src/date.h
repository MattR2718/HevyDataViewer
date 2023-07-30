#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

class Date{
public:
    int day;
    std::string month;
    int year;
    int hour;
    int min;

    Date();
    Date(std::string s);

    std::string string();
    int monthNum();

private:
    std::map<std::string, int> monthNums{
        {"Jan", 1},
        {"Feb", 2},
        {"Mar", 3},
        {"Apr", 4},
        {"May", 5},
        {"Jun", 6},
        {"Jul", 7},
        {"Aug", 8},
        {"Sep", 9},
        {"Oct", 10},
        {"Nov", 11},
        {"Dec", 12}
    };


};