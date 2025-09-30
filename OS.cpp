#include <iostream>
#include <string>
#include <thread>
#include <cctype>
#include <algorithm>
#include <filesystem>
#include <map>
#include <memory>
#include <sstream>
#include "Boot.hpp"
#include "Core.hpp"
#include "Logs.hpp"

static std::string path = "";
static std::string default_path = "";

std::mutex path_mutex;
std::map<std::string, std::unique_ptr<Command>> command_registry;

std::string path_r = "";

void recognize_cmd(std::string cmd) {
    std::istringstream iss(cmd);
    std::string command;
    iss >> command;
    if (command_registry.count(command)) {
        command_registry[command]->execute(cmd, path_r);
    } else {
        cout << "[!] Invalid command. Try running with elevated privileges." << endl;
    }
}

int main()
{
    SetConsoleTitleA("OS");

   /* HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD index = 0;                                                 -- if you want to properly do some console coloring, system() is
    CONSOLE_SCREEN_BUFFER_INFO console_screen_buffer;                  utterly trash and only supported on Windows.
    GetConsoleScreenBufferInfo(hstdout, &console_screen_buffer);
    SetConsoleTextAttribute(hstdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE);
    */

    system("COLOR 1B");

    std::cout << "OS - 2023\n";
    cout << endl;
    cout << endl;
    
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    LOG log;
    string log_file_name = "";
    log_file_name += asctime(timeinfo);
    log_file_name.erase(std::remove_if(log_file_name.begin(), log_file_name.end(), ::isspace), log_file_name.end());
    log_file_name.erase(std::remove(log_file_name.begin(), log_file_name.end(), ':'), log_file_name.end());
    log.create_log_file(log_file_name + ".log");


    if (boot()) {
        cout << "[~] Booted successfully with no errors." << endl;
        log.create_log(AT_BOOT_LOG, "Booted successfully");
    }
    else {
        cout << "[!] Boot error occured, please look at the lines above for possible fixes." << endl;
        log.create_log(AT_BOOT_ERROR, "Boot not successful. Possible compatibility issues are most likely present.");
        return 0;
    }

    if (!is_elevated()) {
        cout << "[!] OS is not running with elevated privileges." << endl;
        log.create_log(ERROR_LOG, "OS not started with elevated privileges.");
        return 0;
    }

    if (!login())
        return 0;

    path_r = std::filesystem::current_path().string();
    default_path = path_r;

    command_registry["print"] = std::make_unique<SimpleCommand>([](const std::string& cmd, std::string& path_r){ return user_cmd::print(cmd); });
    command_registry["test"] = std::make_unique<SimpleCommand>([](const std::string& cmd, std::string& path_r){ return user_cmd::help_c(cmd); });
    command_registry["ls"] = std::make_unique<SimpleCommand>([](const std::string& cmd, std::string& path_r){ return user_cmd::ls(cmd, path_r); });
    command_registry["cfile"] = std::make_unique<SimpleCommand>([](const std::string& cmd, std::string& path_r){ return user_cmd::cfile(cmd); });
    command_registry["help"] = std::make_unique<SimpleCommand>([](const std::string& cmd, std::string& path_r){ return user_cmd::help(cmd); });
    command_registry["clear"] = std::make_unique<SimpleCommand>([](const std::string& cmd, std::string& path_r){ return user_cmd::clear(cmd); });
    command_registry["sysinfo"] = std::make_unique<SimpleCommand>([](const std::string& cmd, std::string& path_r){ return user_cmd::sysinfo(cmd); });
    command_registry["exit"] = std::make_unique<SimpleCommand>([](const std::string& cmd, std::string& path_r){ return user_cmd::exit_sys(cmd); });
    command_registry["dfile"] = std::make_unique<SimpleCommand>([](const std::string& cmd, std::string& path_r){ return user_cmd::dfile(cmd); });
    command_registry["mkdir"] = std::make_unique<SimpleCommand>([](const std::string& cmd, std::string& path_r){ return user_cmd::mkdir(cmd); });
    command_registry["ddir"] = std::make_unique<SimpleCommand>([](const std::string& cmd, std::string& path_r){ return user_cmd::ddir(cmd); });
    command_registry["exe"] = std::make_unique<SimpleCommand>([](const std::string& cmd, std::string& path_r){ return user_cmd::exe(cmd); });
    command_registry["mp3"] = std::make_unique<SimpleCommand>([](const std::string& cmd, std::string& path_r){ return user_cmd::mp3(cmd); });
    command_registry["nano"] = std::make_unique<SimpleCommand>([](const std::string& cmd, std::string& path_r){ return user_cmd::nano(cmd); });
    command_registry["render"] = std::make_unique<SimpleCommand>([](const std::string& cmd, std::string& path_r){ return user_cmd::render_img(cmd); });
    command_registry["hex"] = std::make_unique<SimpleCommand>([](const std::string& cmd, std::string& path_r){ return user_cmd::hex(cmd); });
    command_registry["concolor"] = std::make_unique<SimpleCommand>([](const std::string& cmd, std::string& path_r){ return user_cmd::con_color(cmd); });
    command_registry["cd"] = std::make_unique<SimpleCommand>([](const std::string& cmd, std::string& path_r){ return user_cmd::cd(cmd, path_r); });

    while (true) {
        thread console_title_stats(display_current_statistics_title);
        string command;
        string path_on_input = "";
        {
            std::lock_guard<std::mutex> lock(path_mutex);
            if (default_path != path_r) {
                if (default_path.size() < path_r.size()) {
                    for (size_t i = default_path.size() + 1; i < path_r.size(); i++) {
                        path_on_input += path_r[i];
                    }
                    cout << "OS1.0.0.0/root/"+path_on_input+ " $ ";
                }
                else {
                    cout << "OS1.0.0.0/root $ ";
                }
            }
            else {
                cout << "OS1.0.0.0/root $ ";
            }
        }
        
       // cout << used_path_alt << endl;
        std::getline(std::cin >> std::ws, command);
        log.create_log(OUTPUT_LOG, "user_cmd -> " + command);
        thread user_cmd_exec(recognize_cmd, command);
        console_title_stats.join();
        user_cmd_exec.join();
        Sleep(1);
    }
    return 0;
}
