cmake_minimum_required(VERSION 3.0.0)

find_package(SFML COMPONENTS graphics system window CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG)
find_package(implot CONFIG REQUIRED)
find_package(unofficial-nativefiledialog CONFIG REQUIRED)
find_package(Boost COMPONENTS date_time REQUIRED)

add_executable(${PROJECT_NAME} main.cpp exercise.cpp date.cpp workout.cpp dataTables.cpp dataRepresentation.cpp)

target_link_libraries(${PROJECT_NAME}
    imgui::imgui
    sfml-graphics sfml-system sfml-window
    ImGui-SFML::ImGui-SFML
    implot::implot
    unofficial::nativefiledialog::nfd
    Boost::date_time
)