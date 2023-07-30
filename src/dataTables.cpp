#include "dataTables.h"

DataTable::DataTable(ImVec2 _pos, ImVec2 _dim){
    this->pos = _pos;
    this->dim = _dim;
}

void DataTable::windowResizeUpdate(ImVec2 _pos, ImVec2 _dim){
    this->pos = _pos;
    this->dim = _dim;
}

void DataTable::drawTable(std::vector<Exercise> &exercises,
                        std::vector<Workout> &workouts,
                        std::vector<uint8_t>& selected)
{
    ImGui::Begin("Data", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowFontScale(2);
    ImGui::SetWindowPos(this->pos);
    ImGui::SetWindowSize(this->dim);

    //Create imgui tab bar
    if(ImGui::BeginTabBar("DataTabs")){
        //If exercie chosen
        if(ImGui::BeginTabItem("All Exercises")){
            if (ImGui::BeginTable("ExerciseDataTable", exerciseHeadings.size(), ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders)){
                //Exercise Headings
                this->dc = data_choice::Exercise;

                if(this->dc != this->pc){
                    this->pc = this->dc;
                    selected = std::vector<uint8_t>(exercises.size(), false);
                }

                for(auto& h : this->exerciseHeadings){
                    ImGui::TableSetupColumn(h.c_str());
                }
                ImGui::TableHeadersRow();

                //Loop over exercises and write row
                for(int i = 0; i < exercises.size(); i++){
                    exercises[i].tableRow(selected, i);
                }

                ImGui::EndTable();
            }
            ImGui::EndTabItem();
        }
        if(ImGui::BeginTabItem("All Workouts")){
            if (ImGui::BeginTable("WorkoutDataTable", workoutHeadings.size(), ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders)){
                this->dc = data_choice::Workout;
                
                if(this->dc != this->pc){
                    this->pc = this->dc;
                    selected = std::vector<uint8_t>(workouts.size(), false);
                }
                
                for(auto& h : this->workoutHeadings){
                    ImGui::TableSetupColumn(h.c_str());
                }
                ImGui::TableHeadersRow();

                //Loop over workouts and write row
                for(int i = 0; i < workouts.size(); i++){
                    workouts[i].tableRow(selected, i);
                }

                ImGui::EndTable();
            }
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}
