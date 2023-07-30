#include "workout.h"

Workout::Workout(const std::vector<Exercise> exercises){
    this->exercises = exercises;
    //this->num_exercises = exercises.size();
    this->start_time = exercises[0].data.start_time;
    this->end_time = exercises[0].data.end_time;
    this->description = exercises[0].data.description;
    this->title = exercises[0].data.title;
    for(auto& e : exercises){
        this->num_exercises += (!e.data.set_index) ? 1 : 0;
        this->num_sets += 1;
        this->total_volume_kg += (e.data.weight_kg < 0) ? 0.0 : e.data.reps * e.data.weight_kg;
        this->total_dist_km += (e.data.distance_km < 0) ? 0.0 : e.data.reps * e.data.distance_km;
    }
}

void Workout::tableRow(std::vector<uint8_t>& selected, int i){
    //ImGui::TableNextColumn();
    //ImGui::Text(this->title.c_str());
    
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    std::string label = this->title + "##" + std::to_string(i);
    if(ImGui::Selectable(label.c_str(), selected[i] , ImGuiSelectableFlags_SpanAllColumns)){
        selected[i] = !selected[i];
        std::cout<<i<<'\n';
    }
    
    ImGui::TableNextColumn();
    ImGui::Text(this->start_time.string().c_str());
    ImGui::TableNextColumn();
    ImGui::Text(this->end_time.string().c_str());
    ImGui::TableNextColumn();
    ImGui::Text(this->description.c_str());
    ImGui::TableNextColumn();
    ImGui::Text(std::to_string(this->num_exercises).c_str());
    ImGui::TableNextColumn();
    ImGui::Text(std::to_string(this->num_sets).c_str());
    ImGui::TableNextColumn();
    ImGui::Text(std::to_string(this->total_volume_kg).c_str());
    ImGui::TableNextColumn();
    ImGui::Text(std::to_string(this->total_dist_km).c_str());
}
