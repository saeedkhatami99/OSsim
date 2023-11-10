#include <iostream>
#include <string>
#include <thread>
#include <cctype>
#include "Boot.hpp"
#include "Core.hpp"
#include "Logs.hpp"

int main()
{
    SetConsoleTitle(L"OS");

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
    log_file_name.erase(std::remove(log_file_name.begin(), log_file_name.end(), 58), log_file_name.end());
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

    while (true) {
        thread console_title_stats(display_current_statistics_title);
        string command;
        string path_on_input = "";
        if (default_path != path) {
            if (strlen(default_path.c_str()) < strlen(path.c_str())) {
                int idx = strlen(default_path.c_str()) - strlen(path.c_str());
                for (int i = strlen(default_path.c_str()) + 1; i < strlen(path.c_str()); i++) {
                    path_on_input += path[i];
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
