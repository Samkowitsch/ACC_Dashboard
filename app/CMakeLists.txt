


add_executable(
    ${MAIN} 
    main.cpp
    )


target_link_libraries(
    ${MAIN} 
    src_lib
    gui_lib
    )


target_include_directories(
    ${MAIN} 
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/includes 
    ${PROJECT_SOURCE_DIR}/GUI 
    ${PROJECT_SOURCE_DIR}
    ${SDL2_INCLUDE_DIRS}
)



