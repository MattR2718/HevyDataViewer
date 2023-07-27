#include "exercise.h"

Exercise::Exercise(std::string s){
    bool inQuote = false;
    std::string word = "";
    std::vector<std::string> words;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == '\"'){
            inQuote = !inQuote;
        }
        if(s[i] == ',' && !inQuote){
            words.push_back(word);
            word = "";
            continue;
        }
        word += s[i];

    }
    words.push_back(word);

    //std::cout << s << '\n';

    for(auto& w : words){
        //std::cout<<"- " << w<<'\n';
        if(w.length() == 0){ w = "-1"; }
    }

    this->data.title = words[0].substr(1, words[0].length() - 2);
    this->data.start_time = Date(words[1].substr(1, words[1].length() - 2));
    this->data.end_time = Date(words[2].substr(1, words[2].length() - 2));
    this->data.description = words[3].substr(1, words[3].length() - 2);
    this->data.exercise_title = words[4].substr(1, words[4].length() - 2);
    this->data.superset_id = std::stoi(words[5]);
    this->data.exercise_notes = words[6].substr(1, words[6].length() - 2);
    this->data.set_index = std::stoi(words[7]);
    this->data.set_type = words[8].substr(1, words[8].length() - 2);
    //std::cout<<"STOF:-"<<words[9]<<"-"<<'\n';
    this->data.weight_kg = std::stof(words[9]);
    this->data.reps = std::stoi(words[10]);
    this->data.distance_km = std::stof(words[11]);
    this->data.duration_seconds = std::stof(words[12]);
    this->data.rpe = std::stof(words[13]);

}

void Exercise::tableRow(){
    ImGui::TableNextColumn();
    ImGui::Text(this->data.title.c_str());
    ImGui::TableNextColumn();
    ImGui::Text(this->data.start_time.string().c_str());
    ImGui::TableNextColumn();
    ImGui::Text(this->data.start_time.string().c_str());
    ImGui::TableNextColumn();
    ImGui::Text(this->data.description.c_str());
    ImGui::TableNextColumn();
    ImGui::Text(this->data.exercise_title.c_str());
    ImGui::TableNextColumn();
    ImGui::Text(std::to_string(this->data.superset_id).c_str());
    ImGui::TableNextColumn();
    ImGui::Text(this->data.exercise_notes.c_str());
    ImGui::TableNextColumn();
    ImGui::Text(std::to_string(this->data.set_index).c_str());
    ImGui::TableNextColumn();
    ImGui::Text(this->data.set_type.c_str());
    ImGui::TableNextColumn();
    ImGui::Text(std::to_string(this->data.weight_kg).c_str());
    ImGui::TableNextColumn();
    ImGui::Text(std::to_string(this->data.reps).c_str());
    ImGui::TableNextColumn();
    ImGui::Text(std::to_string(this->data.distance_km).c_str());
    ImGui::TableNextColumn();
    ImGui::Text(std::to_string(this->data.duration_seconds).c_str());
    ImGui::TableNextColumn();
    ImGui::Text(std::to_string(this->data.rpe).c_str());
    
}
