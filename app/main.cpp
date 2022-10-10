#include <iostream>
#include <thread>


#include "gui.h"
#include "mainDashboard.h"

int main(){


    std::cout << "ACC Dashboard start" << std::endl;

    std::thread guiThreadId(guiThread);

    while(true){
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}