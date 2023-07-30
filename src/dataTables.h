#pragma once
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include "exercise.h"
#include "workout.h"

#include "dataChoice.h"

class DataTable{
public:
    ImVec2 pos;
    ImVec2 dim;
    data_choice dc = data_choice::Exercise;
    data_choice pc = data_choice::Workout;

    DataTable(ImVec2 _pos, ImVec2 _dim);

    void windowResizeUpdate(ImVec2 _pos, ImVec2 _dim);
    void drawTable(std::vector<Exercise>& exercises,
                    std::vector<Workout>& workouts,
                    std::vector<uint8_t>& selected);


private:

    std::vector<std::string> exerciseHeadings = {"title","start_time","end_time","description","exercise_title","superset_id","exercise_notes","set_index","set_type","weight_kg","reps","distance_km","duration_seconds","rpe"};
    std::vector<std::string> workoutHeadings = {"title", "start_time", "end_time", "description", "num_exercises", "num_sets", "total_volume_kg", "total_distance_km"};

};