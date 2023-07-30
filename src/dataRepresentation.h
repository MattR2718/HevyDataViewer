#pragma once
#include <vector>
#include <string>
#include <set>
#include <chrono>
#include <map>

#include <boost/date_time/gregorian/gregorian.hpp>

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <implot.h>

#include "exercise.h"
#include "workout.h"

#include "dataChoice.h"

struct ExerciseData{
    std::vector<float> time;
    std::vector<float> weight;
};

class DataRepresentation{
public:
    ImVec2 pos;
    ImVec2 dim;

    DataRepresentation(ImVec2 _pos, ImVec2 _dim);

    void windowResizeUpdate(ImVec2 _pos, ImVec2 _dim);
    void drawTable(std::vector<Exercise>& exercises,
                    std::vector<Workout>& workouts,
                    std::vector<uint8_t>& selected,
                    const data_choice dc);

private:


};