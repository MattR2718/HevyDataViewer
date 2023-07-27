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

#define U8(_S)    (const char*)u8##_S

int main(){
    int WIDTH = sf::VideoMode::getDesktopMode().width;
    int HEIGHT = sf::VideoMode::getDesktopMode().height;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "HevyDataViewer");
    ImGui::SFML::Init(window);

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

        sf::CircleShape c(100);
        c.setFillColor(sf::Color::Green);
        c.setPosition(sf::Vector2f(50, 50));
        window.draw(c);

        std::string s = "Afternoon workout 💪";


        ImGui::ShowDemoWindow();

        ImGui::Begin("TOP RIGHT");
        ImGui::SetWindowPos(ImVec2(WIDTH/2, 0));
        ImGui::SetWindowSize(ImVec2(WIDTH/2, HEIGHT/2));
        ImGui::SetWindowFontScale(2);
        ImGui::Text(U8("%s"), s.c_str());
        ImGui::End();
        

        auto[fileSelected, path]{displayLoadData()};
        if(fileSelected){
            std::vector<Exercise> exercises = loadData(path);
        }
    
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
