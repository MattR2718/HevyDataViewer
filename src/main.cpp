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

#define U8(_S)    (const char*)u8##_S

enum class data_choice{
    Exercise = 0,
    Workout
};

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

    std::vector<std::string> exerciseHeadings = {"title","start_time","end_time","description","exercise_title","superset_id","exercise_notes","set_index","set_type","weight_kg","reps","distance_km","duration_seconds","rpe"};
    std::vector<std::string> workoutHeadings = {"title", "start_time", "end_time", "description", "num_exercises", "num_sets", "total_volume_kg", "total_distance_km"};

    std::vector<bool> selected;

    data_choice dataChoice = data_choice::Exercise;
    data_choice prevChoice = data_choice::Workout;

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

        if(prevChoice != dataChoice){
            prevChoice = dataChoice;
            selected.clear();
            if(dataChoice == data_choice::Exercise){
                selected = std::vector<bool>(exercises.size(), false);
            }else{
                selected = std::vector<bool>(workouts.size(), false);
            }
        }

        auto[fileSelected, path]{displayLoadData(WIDTH, HEIGHT, savedPath)};
        dataLoaded = fileSelected;
        if(fileSelected){
            exercises = loadData(path);
            exerciseNames = getNames(exercises);
            workouts = createWorkouts(exercises);

            if(dataChoice == data_choice::Exercise){
                for(auto& e : exercises){
                    selected.push_back(false);
                }
                std::cout<<exercises.size()<<'\n';
            }else{
                selected = std::vector<bool>(workouts.size(), false);
            }
        }

        ImGui::Begin("Data Options", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::SetWindowFontScale(2);
        ImGui::SetWindowPos(ImVec2(WIDTH / 6, 0));
        ImGui::SetWindowSize(ImVec2(WIDTH/6, HEIGHT/3));
        ImGui::End();

        int i = 0;

        ImGui::Begin("Data", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::SetWindowFontScale(2);
        ImGui::SetWindowPos(ImVec2(WIDTH/3, 0));
        ImGui::SetWindowSize(ImVec2(2*WIDTH/3, HEIGHT/3));

        if(ImGui::BeginTabBar("DataTabs")){
            if(ImGui::BeginTabItem("All Exercises")){
                if (ImGui::BeginTable("ExerciseDataTable", exerciseHeadings.size(), ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders)){
                    dataChoice = data_choice::Exercise;
                    for(auto& h : exerciseHeadings){
                        ImGui::TableSetupColumn(h.c_str());
                    }
                    ImGui::TableHeadersRow();
                    int i = 0;
                    if(selected.size() > 3){ selected[2] = true; }
                    for (auto& e : exercises){
                        ImGui::TableNextColumn();
                        //ImGui::Text(this->data.title.c_str());
                        if(ImGui::Selectable(e.data.title.c_str(), &selected[i], ImGuiSelectableFlags_SpanAllColumns)){
                            selected[i] = !selected[i];
                            std::cout<<i<<'\n';
                        }

                        e.tableRow(selected, i);
                        i++;
                    }
                    ImGui::EndTable();
                }
                ImGui::EndTabItem();
            }

            if(ImGui::BeginTabItem("All Workouts")){
                if (ImGui::BeginTable("WorkoutDataTable", workoutHeadings.size(), ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders)){
                    dataChoice = data_choice::Workout;
                    for(auto& h : workoutHeadings){
                        ImGui::TableSetupColumn(h.c_str());
                    }
                    ImGui::TableHeadersRow();
                    for(auto& w : workouts){
                        w.tableRow();
                    }

                    ImGui::EndTable();
                }
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }

        ImGui::End();

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
