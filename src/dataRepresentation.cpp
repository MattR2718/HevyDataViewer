#include "dataRepresentation.h"

DataRepresentation::DataRepresentation(ImVec2 _pos, ImVec2 _dim){
    this->pos = _pos;
    this->dim = _dim;
}

void DataRepresentation::windowResizeUpdate(ImVec2 _pos, ImVec2 _dim){
    this->pos = _pos;
    this->dim = _dim;
}

void DataRepresentation::drawTable(std::vector<Exercise> &exercises, 
                                    std::vector<Workout> &workouts, 
                                    std::vector<uint8_t> &selected, 
                                    const data_choice dc)
{
    ImGui::Begin("Data Representation", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowFontScale(2);
    ImGui::SetWindowPos(this->pos);
    ImGui::SetWindowSize(this->dim);

    if(dc == data_choice::Exercise){
        std::set<std::string> chosenExerciseNames;
        for(int i = 0; i < exercises.size(); i++){
            if(selected[i]){ chosenExerciseNames.insert(exercises[i].data.exercise_title); }
        }

        /* for(auto& n : chosenExerciseNames){
            ImGui::Text(n.c_str());
        } */

        //sysdays converts to suration?
        //std::mctime in ctime

        const std::chrono::time_point now{std::chrono::system_clock::now()};
        const std::chrono::year_month_day ymd{std::chrono::floor<std::chrono::days>(now)};
        //std::cout<<ymd<<'\n';

        std::string nowstr = std::to_string(static_cast<int>(ymd.year())) + "-" + std::to_string(static_cast<unsigned>(ymd.month())) + "-" + std::to_string(static_cast<unsigned>(ymd.day()));
        boost::gregorian::date nowDate(boost::gregorian::from_string(nowstr));
        //std::cout<<nowDate<<'\n';

        std::map<std::string, ExerciseData> exercisesData;
        float minw = 10000.0;
        float maxw = -10000.0;
        float mint = 1000000.0;
        float maxt = -1000000.0;
        for(int i = exercises.size() - 1; i > -1; i--){
            if(chosenExerciseNames.contains(exercises[i].data.exercise_title)){
                std::string exstr = std::to_string(static_cast<int>(exercises[i].data.start_time.year)) + "-" + 
                                    std::to_string(static_cast<unsigned>(exercises[i].data.start_time.monthNum())) + "-" + 
                                    std::to_string(static_cast<unsigned>(exercises[i].data.start_time.day));
                boost::gregorian::date exDate(boost::gregorian::from_string(exstr));

                long diff = -(nowDate - exDate).days();
                //std::cout<<diff<<'\n';
                
                if((float)diff > maxt){ maxt = (float)diff; }
                if((float)diff < mint){ mint = (float)diff; }
                if((float)exercises[i].data.weight_kg > maxw){ maxw = (float)exercises[i].data.weight_kg; }
                if((float)exercises[i].data.weight_kg < minw){ minw = (float)exercises[i].data.weight_kg; }
                
                /* if(exercisesData[exercises[i].data.exercise_title].time.size() > 0 && exercisesData[exercises[i].data.exercise_title].weight.size() > 0 && exercisesData[exercises[i].data.exercise_title].time[exercisesData[exercises[i].data.exercise_title].time.size() - 1] == diff && exercisesData[exercises[i].data.exercise_title].weight[exercisesData[exercises[i].data.exercise_title].weight.size() - 1] < exercises[i].data.weight_kg){
                    exercisesData[exercises[i].data.exercise_title].weight[exercisesData[exercises[i].data.exercise_title].weight.size() - 1] = exercises[i].data.weight_kg;
                }else{
                    exercisesData[exercises[i].data.exercise_title].time.push_back(diff);
                    exercisesData[exercises[i].data.exercise_title].weight.push_back(exercises[i].data.weight_kg);
                } */

                exercisesData[exercises[i].data.exercise_title].time.push_back(diff);
                exercisesData[exercises[i].data.exercise_title].weight.push_back(exercises[i].data.weight_kg);

            }
        }
        
        /* ImGui::Text(std::to_string(mint).c_str());
        ImGui::Text(std::to_string(maxt).c_str());
        ImGui::Text(std::to_string(minw).c_str());
        ImGui::Text(std::to_string(maxw).c_str()); */

        mint -= 0.1 * mint;
        maxt += 0.1 * maxt;
        minw -= 0.1 * minw;
        maxw += 0.1 * maxw;

        if(ImPlot::BeginPlot("Progress", ImVec2(this->dim.x * 0.99, this->dim.y * 0.99))){
            ImPlot::SetupAxes("Days Since", "Weight kg");
            ImPlot::SetupAxisLimits(ImAxis_X1, mint, maxt, ImGuiCond_Always);
            ImPlot::SetupAxisLimits(ImAxis_Y1,minw,maxw, ImGuiCond_Always);
            for(auto& ele : exercisesData){
                std::string lineName = ele.first;
                std::vector<float> tim = ele.second.time;
                std::vector<float> wei = ele.second.weight;
                
                //ImPlot::PlotLine(ele.first.c_str(), ele.second.time, ele.second.weight, ele.second.time.size());
                ImPlot::SetNextMarkerStyle(ImPlotMarker_Cross, 6);
                ImPlot::PlotLine(lineName.c_str(), tim.data(), wei.data(), tim.size());
            }
            ImPlot::EndPlot();
        }

    }


    ImGui::End();

    //ImPlot::ShowDemoWindow();
}
