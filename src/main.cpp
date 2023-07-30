#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <implot.h>
#include <nfd.h>    

#include "exercise.h"
#include "loadData.h"
#include "workout.h"
#include "dataTables.h"

#include "dataChoice.h"

#define U8(_S)    (const char*)u8##_S

int main(){
    int WIDTH = sf::VideoMode::getDesktopMode().width * 0.75;
    int HEIGHT = sf::VideoMode::getDesktopMode().height * 0.75;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "HevyDataViewer");
    ImGui::SFML::Init(window);

    std::string savedPath = "";
    bool dataLoaded = false;

    std::vector<Exercise> exercises;
    std::vector<std::string> exerciseNames;

    std::vector<Workout> workouts;

    std::vector<uint8_t> selected;


    DataTable dataTable(ImVec2(WIDTH/3, 0), ImVec2(2*WIDTH/3, HEIGHT/3));

    //data_choice dataChoice = data_choice::Exercise;
    //data_choice prevChoice = data_choice::Workout;

    sf::Clock deltaClock;
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }else if(event.type == sf::Event::Resized){
                WIDTH = event.size.width;
                HEIGHT = event.size.height;
                window.setView(sf::View(sf::FloatRect(0, 0, WIDTH, HEIGHT)));
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());
        window.clear(sf::Color::Black);

        auto[fileSelected, path]{displayLoadData(WIDTH, HEIGHT, savedPath)};
        dataLoaded = fileSelected;
        if(fileSelected){
            exercises = loadData(path);
            exerciseNames = getNames(exercises);
            workouts = createWorkouts(exercises);

            if(dataTable.dc == data_choice::Exercise){
                for(auto& e : exercises){
                    selected.push_back(false);
                }
                std::cout<<exercises.size()<<'\n';
            }else{
                selected = std::vector<uint8_t>(workouts.size(), false);
            }
        }

        ImGui::Begin("Data Options", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::SetWindowFontScale(2);
        ImGui::SetWindowPos(ImVec2(WIDTH / 6, 0));
        ImGui::SetWindowSize(ImVec2(WIDTH/6, HEIGHT/3));
        ImGui::End();

        dataTable.drawTable(exercises, workouts, selected);

        /*
        TODO
        use dataChoice to decide what to show
            If exercise, get all choices selected in table and draw graph of weight
            If workout create custom display to display all exercises in the workout
        */

        ImGui::Begin("Data Representation", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::SetWindowFontScale(2);
        ImGui::SetWindowPos(ImVec2(0, HEIGHT/3));
        ImGui::SetWindowSize(ImVec2(WIDTH, 2 * HEIGHT/3));
        ImGui::End();

        ImGui::ShowDemoWindow();
    
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
