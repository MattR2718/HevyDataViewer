#pragma once
#include <iostream>
#include <string>

#include "exercise.h"
#include "date.h"

class Workout{
public:
    std::vector<Exercise> exercises;
    std::string title;
    Date start_time;
    Date end_time;
    std::string description;
    int num_exercises = 0;
    int num_sets = 0;
    float total_volume_kg = 0;
    float total_dist_km = 0;

    Workout(const std::vector<Exercise> exercises);
    void tableRow();

private:


};