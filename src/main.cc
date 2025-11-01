#include <iostream>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <string>
#include <fstream>

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

void build(){
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
}

void newProject(std::string name) {
    std::filesystem::path cwd = std::filesystem::current_path();
    std::string mkdir;
    std::string mkdir_src;
    std::string mkdir_build;

    #if defined(_WIN32) || defined(_WIN64)
    mkdir = "mkdir " + cwd.string() + "\\" + name;
    mkdir_src = "mkdir " + cwd.string() + "\\" + name + "\\src";
    mkdir_build = "mkdir " + cwd.string() + "\\" + name + "\\build";
    #else
    mkdir = "mkdir " + cwd.string() + "/" + name;
    mkdir_src = "mkdir " + cwd.string() + "/" + name + "/src";
    mkdir_build = "mkdir " + cwd.string() + "/" + name + "/build";
    #endif
    system(mkdir.c_str());
    system(mkdir_src.c_str());
    system(mkdir_build.c_str());
    std::string main_cc_text = "#include <iostream>\n\nint main(){\n\tstd::cout << \"Hello, world!\" << std::endl;\n} ";
    std::string file_name;
    std::string gitignore;
    std::string clangd;
    #if defined(_WIN32) || defined(_WIN64)
    file_name = name + "\\src\\main.cc";
    gitignore = name + "\\.gitignore";
    clangd = name + "\\.clangd";
    #else
    file_name = name + "/src/main.cc";
    gitignore = name + "/.gitignore";
    clangd = name + "/.clangd";
    #endif
    std::ofstream main_cc(file_name);
    main_cc << main_cc_text;
    main_cc.close();

    std::ofstream gitignore_file(gitignore);
    gitignore_file << "/build\n.clangd";
    gitignore_file.close();

    std::ofstream clangd_file(clangd);
    clangd_file << "CompileFlags:\n\tAdd: [-I/pp/include]";
    clangd_file.close();
}

int main(int argc, char** argv) {
    if (argc > 1) {
        if (std::strcmp(argv[1],"run") == 0){
            run();
        }else if(std::strcmp(argv[1], "build") == 0){
            build();
        }else if(std::strcmp(argv[1],"new") == 0){
            if (argc > 2){
                newProject(argv[2]); //name new cannot be used
            }else{
                std::cerr << "name of the project not found\n" << argv << "\n";
            }
        }else{
            std::cerr << "Unknown command: " << argv[1] << "\n";
        }
    } else {
        std::cout << "No command was given.\n";
    }
    return 0;
}
