#pragma once
#include <iostream>
#include <string>

#include "date.h"

struct Exercise_Data{
    std::string title;
    Date start_time;
    Date end_time;
    std::string description;
    std::string exercise_title;
    int superset_id;
    std::string exercise_notes;
    int set_index;
    std::string set_type;
    float weight_kg;
    int reps;
    float distance_km;
    float duration_seconds;
    float rpe;
};

class Exercise{
public:
    Exercise_Data data;
    Exercise(std::string s);

private:


};