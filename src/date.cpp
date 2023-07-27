#include "date.h"

Date::Date(){
    
}

Date::Date(std::string s){
    std::stringstream ss(s);
    std::string word;
    std::vector<std::string> words;
    while(ss >> word){
        words.push_back(word);
    }

    /* for(auto& w : words){
        std::cout<<"-"<<w<<"-"<<'\n';
    } */
    this->day = std::stoi(words[0]);
    this->month = words[1];
    this->year = std::stoi(words[2].substr(0, words[2].length() - 1));
    this->hour = std::stoi(words[3].substr(0, 2));
    this->min = std::stoi(words[3].substr(3, 2));
}

std::string Date::string(){
    return std::to_string(this->day) + " " + this->month + " " + std::to_string(this->year) + " " + std::to_string(this->hour) + ":" + std::to_string(this->min);
}

/* bool Date::operator==(const Date & lhs, const Date & rhs){
    return lhs.day == rhs.day 
            && lhs.hour == rhs.hour
            && lhs.min == rhs.min
            && lhs.month == rhs.month
            && lhs.year == rhs.year;
} */
