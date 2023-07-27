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

std::pair<bool, std::string> displayLoadData(){
    ImGui::Begin("Load Data");
        if(ImGui::Button("Load Data")){
            nfdchar_t* outPath = NULL;
            nfdresult_t result = NFD_OpenDialog("csv;", NULL, &outPath);
            if (result == NFD_OKAY) {
                std::string filePath = outPath;
                //std::cout<<filePath<<'\n';
                ImGui::End();
                return {true, filePath};                
            }
        }
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
        //std::cout<<linetxt<<'\n';
        //std::cout<<exercises.size()<<'\n';
    }

    //std::cout<<exercises.size()<<'\n';

    return exercises;
}