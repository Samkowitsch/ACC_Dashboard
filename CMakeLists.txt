cmake_minimum_required(VERSION 3.7 FATAL_ERROR)


set(PROJECT_NAME ACC_Dashboard)


project(${PROJECT_NAME} VERSION "1.0.0" LANGUAGES C CXX)

set(CROSS_BUILD OFF)

set(MAIN ${PROJECT_NAME})


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
Set(CMAKE_CXX_EXTENSIONS OFF)


if(CROSS_BUILD)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    set(PROJECT_TARGET "TARGET")
    add_definitions(-DCOMPILE_TARGET)
else()  
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    set(PROJECT_TARGET "NATIVE")

endif(CROSS_BUILD)




configure_file(
    ${PROJECT_SOURCE_DIR}/includes/Version.h.in
    ${PROJECT_SOURCE_DIR}/includes/Version.h
)

include_directories(
    ${PROJECT_SOURCE_DIR}/lvgl
)


add_subdirectory(${PROJECT_SOURCE_DIR}/lvgl/lvgl)
add_subdirectory(${PROJECT_SOURCE_DIR}/lvgl/lv_drivers)
#add_subdirectory(${PROJECT_SOURCE_DIR}/extern)
#add_subdirectory(${PROJECT_SOURCE_DIR}/Common)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/GUI)
add_subdirectory(${PROJECT_SOURCE_DIR}/app)


message(NOTICE "MSG  Compiler : ${CMAKE_SYSTEM_PROCESSOR}")
#install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
