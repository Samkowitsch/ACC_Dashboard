
#Get all source files
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

link_libraries(stdc++fs)

add_library(src_lib
            STATIC
            ${SOURCES}
            )   


target_link_libraries(
    src_lib 
    )

target_include_directories(
    src_lib 
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/includes 
    ${PROJECT_SOURCE_DIR}/GUI/Assets
    ${PROJECT_SOURCE_DIR}/GUI/Styles
    ${PROJECT_SOURCE_DIR}/GUI/Screens
    )