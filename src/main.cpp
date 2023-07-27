#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <nfd.h>    

#include "exercise.h"
#include "loadData.h"
#include "workout.h"

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

    std::vector<std::string> exerciseHeadings = {"title","start_time","end_time","description","exercise_title","superset_id","exercise_notes","set_index","set_type","weight_kg","reps","distance_km","duration_seconds","rpe"};
    std::vector<std::string> workoutHeadings = {"title", "start_time", "end_time", "description", "num_exercises", "num_sets", "total_volume_kg", "total_distance_km"};

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
        }

        ImGui::Begin("Data Options", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::SetWindowFontScale(2);
        ImGui::SetWindowPos(ImVec2(WIDTH / 6, 0));
        ImGui::SetWindowSize(ImVec2(WIDTH/6, HEIGHT/3));
        ImGui::End();

        ImGui::Begin("Data", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::SetWindowFontScale(2);
        ImGui::SetWindowPos(ImVec2(WIDTH/3, 0));
        ImGui::SetWindowSize(ImVec2(2*WIDTH/3, HEIGHT/3));

        if(ImGui::BeginTabBar("DataTabs")){
            if(ImGui::BeginTabItem("All Exercises")){
                if (ImGui::BeginTable("ExerciseDataTable", exerciseHeadings.size(), ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders)){
                    for(auto& h : exerciseHeadings){
                        ImGui::TableSetupColumn(h.c_str());
                    }
                    ImGui::TableHeadersRow();
                    for (auto& e : exercises){
                        e.tableRow();
                    }
                    ImGui::EndTable();
                }
                ImGui::EndTabItem();
            }

            if(ImGui::BeginTabItem("All Workouts")){
                if (ImGui::BeginTable("WorkoutDataTable", workoutHeadings.size(), ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders)){
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

        ImGui::Begin("Progression Graph", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
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
