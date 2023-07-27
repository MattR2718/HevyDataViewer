#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <nfd.h>    

#include "exercise.h"

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