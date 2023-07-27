#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <nfd.h>    

#include "exercise.h"
#include "workout.h"

std::pair<bool, std::string> displayLoadData(const int WIDTH, const int HEIGHT, std::string& savedPath){
    ImGui::Begin("Load Data", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowPos(ImVec2(0, 0));
    ImGui::SetWindowSize(ImVec2(WIDTH / 6, HEIGHT / 3));
    ImGui::SetWindowFontScale(2);
    if(ImGui::Button("Load Data")){
        nfdchar_t* outPath = NULL;
        nfdresult_t result = NFD_OpenDialog("csv;", NULL, &outPath);
        if (result == NFD_OKAY) {
            std::string filePath = outPath;
            savedPath = outPath;
            //std::cout<<filePath<<'\n';
            //std::cout<<savedPath<<'\n';
            ImGui::End();
            return {true, filePath};                
        }
    }
    std::string pathTextBox = "Loaded data from file: \n" + savedPath;
    //ImGui::Text(savedPath.c_str());
    ImGui::TextWrapped(pathTextBox.c_str());
    ImGui::End();
    return {false, ""};    
}

std::vector<Exercise> loadData(std::string filepath){
    std::vector<Exercise> exercises;
    std::ifstream file(filepath);
    std::string linetxt;
    //Read first line to get rid of headings
    std::getline(file, linetxt);
    while(std::getline(file, linetxt)){
        Exercise e(linetxt);
        exercises.push_back(e);
    }

    return exercises;
}

std::vector<std::string> getNames(const std::vector<Exercise>& exercises){
    std::vector<std::string> names;
    for(auto& e : exercises){
        names.push_back(e.data.exercise_title);
    }
    return names;
}

std::vector<Workout> createWorkouts(const std::vector<Exercise>& exercises){
    std::vector<std::vector<Exercise>> exerciseVectors;
    
    for(auto& e : exercises){
        bool inVec = false;
        for(auto& w : exerciseVectors){
            auto lhs = w[0].data.start_time;
            auto rhs = e.data.start_time;
            if(lhs.day == rhs.day 
            && lhs.hour == rhs.hour
            && lhs.min == rhs.min
            && lhs.month == rhs.month
            && lhs.year == rhs.year){
                w.push_back(e);
                inVec = true;
            }
        }
        if(!inVec){
            exerciseVectors.push_back({e});
        }
    }

    std::vector<Workout> workouts;
    for(auto& w : exerciseVectors){
        workouts.emplace_back(Workout(w));
    }
    return workouts;
}