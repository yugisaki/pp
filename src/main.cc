#include <iostream>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <string>

const char* command[] = {"run"};
const int command_len = 1;

void run() {
    std::filesystem::path cwd = std::filesystem::current_path();
    std::string compiletor;
    #if defined(_WIN32) || defined(_WIN64)
        std::cout << "os: windows" << "\n";
        compiletor = "clang++ " + cwd.string() + "\\src\\main.cc -o " + cwd.string() + "\\build\\pp";
    #else
        std::cout << "os: posix" << "\n";
        compiletor = "clang++ " + cwd.string() + "/src/main.cc -o " + cwd.string() + "/build/pp";
    #endif
    int compiled = system(compiletor.c_str());
    if (compiled != 0) {
        std::cerr << "Compilation failed with code: " << compiled << "\n";
        return;
    }
    std::string run;
    #if defined(_WIN32) || defined(_WIN64)
       run = cwd.string() + "\\build\\pp";
    #else
        run = cwd.string() + "/build/pp";
    #endif
    int execResult = system(run.c_str());
}

int main(int argc, char** argv) {
    if (argc > 1) {
        for (int i = 0; i < command_len; i++) {

            if (std::strcmp(argv[1], command[i]) == 0) {
                run();
                return 0;
            }
        }
        std::cerr << "Unknown command: " << argv[1] << "\n";
    } else {
        std::cout << "No command was given.\n";
    }
    return 0;
}
