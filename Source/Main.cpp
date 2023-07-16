#include "Core/Application.h"

#include <string>
#include <filesystem>

int main(int argc, char *argv[]) {

    /*  
        Verify that we always have the path to the resources needed
        works only if Resources and Shaders folder end up in the same folder
        as the executable
    */
    std::string path = argv[0];
    std::filesystem::current_path(path.substr(0, path.find_last_of("/")));

	Application* app = new Application(960, 540, "Test App");

	app->SetMonitorFromCurrent();
	
	return app->Run();
}