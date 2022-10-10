
#Get all source files
file(GLOB GUISOURCES "${PROJECT_SOURCE_DIR}/GUI/*.cpp")
file(GLOB GUISCREENS "${PROJECT_SOURCE_DIR}/GUI/Screens/*.cpp")

file(GLOB GUISTYLES "${PROJECT_SOURCE_DIR}/GUI/Styles/*.cpp")
file(GLOB GUIFONTS "${PROJECT_SOURCE_DIR}/GUI/Fonts/*.c")
file(GLOB GUIASSETS "${PROJECT_SOURCE_DIR}/GUI/Assets/*.c")


#link_libraries(stdc++fs)

add_library(gui_lib
            STATIC
            ${GUISOURCES}
            ${GUIASSETS}
            ${GUIFONTS}
            ${GUISCREENS}
            ${GUISTYLES}
            )   



if(CROSS_BUILD)
    target_link_libraries(
        gui_lib 
        src_lib
        lv_drivers
        lvgl
        )
else()
    find_package(SDL2 REQUIRED SDL2)
    target_link_libraries(
        gui_lib 
        src_lib
        lv_drivers
        lvgl
        SDL2
        )
endif()
            


target_include_directories(
    gui_lib 
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/includes
    ${PROJECT_SOURCE_DIR}/lvgl 
    ${PROJECT_SOURCE_DIR}/GUI 
    ${PROJECT_SOURCE_DIR}/GUI/Assets
    ${PROJECT_SOURCE_DIR}/GUI/Fonts
    ${PROJECT_SOURCE_DIR}/GUI/Styles
    ${PROJECT_SOURCE_DIR}/GUI/Screens
    )