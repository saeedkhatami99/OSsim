#include "User_cmd.hpp"

using namespace std;

bool user_cmd::help_c(string cmd) {
    if (cmd == "test") {
        cout << "[+] If you see this message, test command was executed successfully." << endl;
        return true;
    }
    return false;
}
bool user_cmd::print(string cmd) {
    if (cmd.find("print") != string::npos) {
        string message = "";
        const char* str_2_chr = cmd.c_str();
        cout << "[io-p] ";
        for (int i = 6; i < strlen(str_2_chr); i++) {
            cout << str_2_chr[i];
        }
        cout << endl;
        return true;
    }
    return false;
}
bool user_cmd::mkdir(string cmd) {
    if (cmd.find("mkdir") != string::npos) {
        const char* str_2_chr = cmd.c_str();
        string dir_name = "";
        cout << "[mkdir] Created a directory ";
        for (int i = 6; i < strlen(str_2_chr); i++) {
            dir_name += str_2_chr[i];
        }
        //dir_name += "/";
        _mkdir(dir_name.c_str());
        cout << dir_name << endl;
        return true;
    }
    return false;
}
bool user_cmd::ddir(string cmd) {
    if (cmd.find("ddir") != string::npos) {
        string delete_directory = "";
        for (int i = 5; i < strlen(cmd.c_str()); i++) {
            delete_directory += cmd[i];
        }
        _rmdir(delete_directory.c_str());
        cout << "[rmdir] Removed a directory " << delete_directory << endl;
        return true;
    }
    return false;
}
bool user_cmd::ls(string cmd) {
    if (cmd.find("ls") != string::npos) {
        if (strlen(cmd.c_str()) < 4) {
            char dir[256];
            _getcwd(dir, 256);
            std::string path = dir;
            for (const auto& entry : std::filesystem::directory_iterator(path)) {
                string current_iteration_path = entry.path().string();
                // cout << "CIP: " << current_iteration_path << endl;
                string end_iteration_path_result = "";
                char str_2_chr[1024];
                bool start_appending = false;
                for (int i = 0; i < strlen(current_iteration_path.c_str()); i++) {
                    if (current_iteration_path[i] == 'O' && current_iteration_path[i + 1] == 'S' && !start_appending) {
                        i += 2;
                        start_appending = true;
                    }
                    if (start_appending) {
                        end_iteration_path_result += current_iteration_path[i];
                    }
                }
                std::cout << "          " << (char)200 << end_iteration_path_result << std::endl;
            }
            return true;
        }
        else {
            char dir[256];
            _getcwd(dir, 256);
            string final_path = "";
            for (int i = 0; i < strlen(dir); i++) {
                final_path += dir[i];
            }
            char str_2_chr_c[1024];
            strcpy(str_2_chr_c, cmd.c_str());
            bool path_check = false;
            if (str_2_chr_c[3] != '\\') {
                path_check = true;
            }
            for (int i = 3; i < strlen(cmd.c_str()); i++) {
                if (path_check) {
                    path_check = false;
                    final_path += '\\';
                    i--;
                }
                else
                    final_path += cmd[i];
            }
            for (const auto& entry : std::filesystem::directory_iterator(final_path)) {
                string current_iteration_path = entry.path().string();
                // cout << "CIP: " << current_iteration_path << endl;
                string end_iteration_path_result = "";
                char str_2_chr[1024];
                bool start_appending = false;
                for (int i = 0; i < strlen(current_iteration_path.c_str()); i++) {
                    if (current_iteration_path[i] == 'O' && current_iteration_path[i + 1] == 'S' && !start_appending) {
                        i += 2;
                        start_appending = true;
                    }
                    if (start_appending) {
                        end_iteration_path_result += current_iteration_path[i];
                    }
                }
                std::cout << "          " << (char)200 << end_iteration_path_result << std::endl;
            }
            return true;
        }

        return true;
    }
    return false;
}
bool user_cmd::sysinfo(string cmd) {
    int cpu_information[4] = { -1 };
    char cpu_string[0x40];
    __cpuid(cpu_information, 0x80000000);
    unsigned int ex_ids = cpu_information[0];
    memset(cpu_string, 0, sizeof(cpu_string));
    for (int i = 0x80000000; i <= ex_ids; ++i)
    {
        __cpuid(cpu_information, i);
        if (i == 0x80000002)
            memcpy(cpu_string, cpu_information, sizeof(cpu_information));
        else if (i == 0x80000003)
            memcpy(cpu_string + 16, cpu_information, sizeof(cpu_information));
        else if (i == 0x80000004)
            memcpy(cpu_string + 32, cpu_information, sizeof(cpu_information));
    }
    cpu_name_alt = cpu_string;
    SYSTEM_INFO system_info;
    GetSystemInfo(&system_info);
    threads_alt = system_info.dwNumberOfProcessors; // cores
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex); // I misunderstand that
    GlobalMemoryStatusEx(&statex);
    memory_alt = (float)statex.ullTotalPhys / (1024 * 1024 * 1024);
    if (cmd.find("sysinfo") != string::npos) {
        cout << "[sysinfo] CPU: " << cpu_name_alt << endl;
        cout << "[sysinfo] RAM: " << (int)memory_alt << "GB" << endl;
        cout << "[sysinfo] CPU threads present: " << threads_alt << endl;
        return true;
    }
    return false;
}
bool user_cmd::exit_sys(string cmd) {
    if (cmd.find("exit") != string::npos) {
        cout << "[-] Turning off the OS..." << endl;
        Sleep(2000);
        SetConsoleTitle(L"OS - alpha - turned off");
        system("cls");
        Sleep(3000);
        exit(EXIT_SUCCESS);
        return true;
    }
    return false;
}
bool user_cmd::help(string cmd) {
    if (cmd.find("help") != string::npos) {
        cout << endl << "[~] List of commands:" << endl << endl << "    - - sysinfo - displays system information" << endl
            << "    - - exit - turns off the OS" << endl
            << "    - - test - runs a test command" << endl
            << "    - - clear - clears the OS window" << endl
            << "    - - print - prints out your message (echo)" << endl
            << "    - - ls - list all files within directory" << endl
            << "    - - mkdir - creates a directory" << endl
            << "    - - ddir - deletes a directory" << endl
            << "    - - cfile - creates a file with any extension" << endl
            << "    - - dfile - deletes a file with any extension" << endl
            << "    - - nano - modify a file or preview it (arg: -e for editing and -v for preview)" << endl
            << "    - - .exe - can run any sort of console-based executable files" << endl
            << "    - - .mp3 - running a command with mp3 file name will play it!" << endl << endl;
        return true;
    }
    return false;
}
bool user_cmd::clear(string cmd) {
    if (cmd.find("clear") != string::npos) {
        system("cls");
        return true;
    }
    return false;
}
bool user_cmd::mp3(string cmd) {
    if (cmd.find(".mp3") != string::npos) {
        char dir[256];
        _getcwd(dir, 256);
        string path_to_file = "";
        for (int i = 0; i < strlen(dir); i++) {
            if (dir[i] == '\\')
                path_to_file += '\\';
            path_to_file += dir[i];
        }
        path_to_file = path_to_file + "\\" + "\\" + cmd;
        string fn_arg = "open " + path_to_file + " type mpegvideo alias song1";
        std::wstring conv_str = std::wstring(fn_arg.begin(), fn_arg.end());
        cout << "[player] Playing song: " << cmd << "(press INSERT to stop playing it)" << endl;
        LPCWSTR lpc_cmd = conv_str.c_str();
        MCIERROR mci_err = mciSendString(lpc_cmd, NULL, 0, 0);
        mci_err = mciSendString(L"play song1", NULL, 0, 0);
        while (true) {
            if (GetAsyncKeyState(VK_INSERT)) {
                mciSendString(L"close song1", NULL, 0, 0);
                break;
            }
            Sleep(1);
        }
        return true;
    }
    return false;
}
bool user_cmd::cfile(string cmd) {
    if (cmd.find("cfile") != string::npos) {
        string file_name_ext = "";
        for (int i = 6; i < strlen(cmd.c_str()); i++) {
            file_name_ext += cmd[i];
        }
        ofstream create_file(file_name_ext);
        create_file.close();
        cout << "[+] Created file " << file_name_ext << endl;
        return true;
    }
    return false;
}
bool user_cmd::dfile(string cmd) {
    if (cmd.find("dfile") != string::npos) {
        string delete_file = "";
        for (int i = 6; i < strlen(cmd.c_str()); i++) {
            delete_file += cmd[i];
        }
        std::filesystem::remove(delete_file);
        cout << "[+] Deleted file " << delete_file << endl;
        return true;
    }
    return false;
}
bool user_cmd::exe(string cmd) {
    if (cmd.find(".exe") != string::npos) {
        std::wstring conv_str = std::wstring(cmd.begin(), cmd.end());
        LPCWSTR executable_path = conv_str.c_str();
        ShellExecute(NULL, L"open", executable_path, NULL, NULL, SW_SHOWDEFAULT); // system is shit, createprocess defeats the purpose
        cout << "[+] Ran an executable file: " << cmd << endl;
        return true;
    }
    return false;
}
bool user_cmd::nano(string cmd) {
    if (cmd.find("nano") != string::npos) {
        string selected_nano_mode = "";
        for (int i = 5; i < 7; i++) {
            selected_nano_mode += cmd[i];
        }
        if (selected_nano_mode == "-v") {
            string nano_file = "";
            for (int i = 8; i < strlen(cmd.c_str()); i++) {
                nano_file += cmd[i];
            }
            cout << endl << "[+] nano -> " << nano_file << endl << endl;
            fstream file;
            file.open(nano_file, ios::in);
            if (file.is_open()) {   
                string tp;
                while (getline(file, tp)) { 
                    cout << tp << "\n"; 
                }
                file.close(); 
            }
            return true;
        }
        else if (selected_nano_mode == "-e") {
            string nano_file = "";
            for (int i = 8; i < strlen(cmd.c_str()); i++) {
                nano_file += cmd[i];
            }
            string input;
            fstream file;
            file.open(nano_file, ios::in);
            if (file.is_open()) {   
                string tp;
                while (getline(file, tp)) { 
                    input = input + tp + '\n'; 
                }
                file.close(); 
            }
            OpenClipboard(GetConsoleWindow());
            EmptyClipboard();
            HGLOBAL h_global = GlobalAlloc(GMEM_MOVEABLE, input.size() + 1);      // since usage of community libraries is forbidden,
            if (!h_global) {                                                      // I used a ghetto method of copying the input into the
                CloseClipboard();                                                 // clipboard and pasting it before asking for input, to sort
                return true;                                                      // of get modifiable text in std::cin without cursor moving.
            }
            memcpy(GlobalLock(h_global), input.c_str(), input.size() + 1);
            GlobalUnlock(h_global);
            SetClipboardData(CF_TEXT, h_global);
            CloseClipboard();
            GlobalFree(h_global);

            INPUT inp;
            inp.type = INPUT_KEYBOARD;
            inp.ki.wScan = 0;
            inp.ki.time = 0;
            inp.ki.dwExtraInfo = 0;

            inp.ki.wVk = VK_CONTROL;
            inp.ki.dwFlags = 0;
            SendInput(1, &inp, sizeof(INPUT));

            inp.ki.wVk = 'V';
            inp.ki.dwFlags = 0;
            SendInput(1, &inp, sizeof(INPUT));

            inp.ki.wVk = 'V';
            inp.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &inp, sizeof(INPUT));

            inp.ki.wVk = VK_CONTROL;
            inp.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &inp, sizeof(INPUT));
            Sleep(1000);

            getline(std::cin >> std::ws, input);
            filesystem::remove(nano_file);
            ofstream create_file(nano_file);
            create_file << input;
            create_file.close();
            cout << "[+] Nano -> success (" << nano_file << ")" << endl;
            return true;
        }
        else {
            cout << "[!] Invalid nano arguments. Use -v or -e." << endl;
            return true;
        }

        return false;
    }
}