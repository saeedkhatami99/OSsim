#include "User_cmd.hpp"
#include <mutex>

using namespace std;

bool user_cmd::help_c(string cmd) {
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    if (cmd == "test") {
        cout << "[+] If you see this message, test command was executed successfully." << endl;
        return true;
    }
    return false;
}
bool user_cmd::print(string cmd) {
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    if (cmd.find("print") != string::npos) {
        string message = cmd.substr(6);
        cout << "[io-p] " << message << endl;
        return true;
    }
    return false;
}
bool user_cmd::mkdir(string cmd) {
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    if (cmd.find("mkdir") != string::npos) {
        string dir_name = cmd.substr(6);
        if (_mkdir(dir_name.c_str()) != 0) {
            cout << "[!] Error creating directory " << dir_name << endl;
        } else {
            cout << "[mkdir] Created a directory " << dir_name << endl;
        }
        return true;
    }
    return false;
}
bool user_cmd::ddir(string cmd) {
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    if (cmd.find("ddir") != string::npos) {
        string delete_directory = cmd.substr(5);
        if (_rmdir(delete_directory.c_str()) != 0) {
            cout << "[!] Error removing directory " << delete_directory << endl;
        } else {
            cout << "[rmdir] Removed a directory " << delete_directory << endl;
        }
        return true;
    }
    return false;
}
bool user_cmd::ls(string cmd, const string& default_path) {
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    if (cmd.find("ls") != string::npos) {
        if (cmd.size() < 4) {
            std::string path = default_path;
            cout << path << endl;
            try {
                for (const auto& entry : std::filesystem::directory_iterator(path)) {
                    string current_iteration_path = entry.path().string();
                    string end_iteration_path_result = "";
                    bool start_appending = false;
                    for (size_t i = 0; i < current_iteration_path.size(); i++) {
                        if (current_iteration_path.substr(i, 2) == "OS" && !start_appending) {
                            i += 2;
                            start_appending = true;
                        }
                        if (start_appending) {
                            end_iteration_path_result += current_iteration_path[i];
                        }
                    }
                    std::cout << "          " << (char)200 << end_iteration_path_result << std::endl;
                }
            } catch (const std::filesystem::filesystem_error& e) {
                cout << "[!] Error listing directory: " << e.what() << endl;
            }
            return true;
        }
        else {
            std::string final_path = default_path;
            final_path += (cmd[3] == '\\' ? "" : "\\") + cmd.substr(3);
            try {
                for (const auto& entry : std::filesystem::directory_iterator(final_path)) {
                    string current_iteration_path = entry.path().string();
                    string end_iteration_path_result = "";
                    bool start_appending = false;
                    for (size_t i = 0; i < current_iteration_path.size(); i++) {
                        if (current_iteration_path.substr(i, 2) == "OS" && !start_appending) {
                            i += 2;
                            start_appending = true;
                        }
                        if (start_appending) {
                            end_iteration_path_result += current_iteration_path[i];
                        }
                    }
                    std::cout << "          " << (char)200 << end_iteration_path_result << std::endl;
                }
            } catch (const std::filesystem::filesystem_error& e) {
                cout << "[!] Error listing directory: " << e.what() << endl;
            }
            return true;
        }
    }
    return false;
}
bool user_cmd::sysinfo(string cmd) {
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    int cpu_information[4] = { -1 };
    std::string cpu_string(0x40, '\0');
    __cpuid(cpu_information, 0x80000000);
    unsigned int ex_ids = cpu_information[0];
    for (int i = 0x80000000; i <= ex_ids; ++i)
    {
        __cpuid(cpu_information, i);
        if (i == 0x80000002)
            memcpy(cpu_string.data(), cpu_information, sizeof(cpu_information));
        else if (i == 0x80000003)
            memcpy(cpu_string.data() + 16, cpu_information, sizeof(cpu_information));
        else if (i == 0x80000004)
            memcpy(cpu_string.data() + 32, cpu_information, sizeof(cpu_information));
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
bool user_cmd::hex(string cmd) {
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    if (cmd.find("hex") != string::npos) {                                      // hex -r test
        string val_to_hex = cmd.substr(4);
        bool reverse_hex = false;
        size_t space_pos = val_to_hex.find(' ');
        if (space_pos != string::npos && val_to_hex.substr(0, space_pos) == "-r") {
            reverse_hex = true;
            val_to_hex = val_to_hex.substr(space_pos + 1);
        }
        if (reverse_hex) {
            cout << "[+] Hex (reverse) from " << val_to_hex << " is " << strtoul(val_to_hex.c_str(), NULL, 16) << endl;
            return true;
        }
        else {
            ostringstream ret;
            for (char c : val_to_hex)
                ret << std::hex << std::setfill('0') << std::setw(2) << (int)(unsigned char)c;
            cout << "[+] Hex from " << val_to_hex << " is " << ret.str() << endl;
            return true;
        }

    }

    return false;
}
bool user_cmd::render_img(string cmd) {
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    if (cmd.find("render") != string::npos) {
        string img_file = cmd.substr(7);
        std::wstring conv_str = std::wstring(img_file.begin(), img_file.end());
        LPCWSTR file = conv_str.c_str();
        RECT rect;
        GetWindowRect(GetConsoleWindow(), &rect);
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;
        unsigned char buf[8];
        std::ifstream in(img_file);
        if (!in) {
            cout << "[!] Error opening image file " << img_file << endl;
            return true;
        }
        HDC hdc = CreateCompatibleDC(NULL);
        if (!hdc) {
            cout << "[!] Error creating device context" << endl;
            return true;
        }
        HDC console_dc = GetDC(GetConsoleWindow());
        HBITMAP bmp = (HBITMAP)LoadImageW(NULL, file, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        if (!bmp) {
            cout << "[!] Error loading image " << img_file << endl;
            DeleteDC(hdc);
            return true;
        }
        BITMAP bm = { 0 };
        GetObject(bmp, sizeof(bm), &bm);
        LONG cx = bm.bmWidth;
        LONG cy = bm.bmHeight;
        HBITMAP hold = (HBITMAP)SelectObject(hdc, bmp);
        int image_px_loc_x = 0;
        int image_px_loc_y = 0;
        for (int i = (width - 50 - cx); i < width - 50 + cx; i++) {
            for (int j = 0 + (cy / 3); j < (cy/3) + cy; j++) {
                DWORD color = GetPixel(hdc, image_px_loc_x, image_px_loc_y);
                SetPixel(console_dc, i, j, RGB((short)GetRValue(color), (short)GetGValue(color), (short)GetBValue(color)));

                image_px_loc_y++;
            }
            image_px_loc_x++;
            image_px_loc_y = 0;
        }
        cout << "[+] Rendered image " << img_file << endl;
        SelectObject(hdc, hold);
        DeleteObject(bmp);
        DeleteDC(hdc);
        return true;
    }
    return false;
}
bool user_cmd::exit_sys(string cmd) {
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    if (cmd.find("exit") != string::npos) {
        cout << "[-] Turning off the OS..." << endl;
        Sleep(2000);
        SetConsoleTitleA("OS - turned off");
        system("cls");
        Sleep(3000);
        exit(EXIT_SUCCESS);
        return true;
    }
    return false;
}
bool user_cmd::help(string cmd) {
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    if (cmd.find("help") != string::npos) {
        cout << endl << "[~] List of commands:" << endl << endl << "    - - sysinfo - displays system information" << endl
            << "    - - exit - turns off the OS" << endl
            << "    - - test - runs a test command" << endl
            << "    - - clear - clears the OS window" << endl
            << "    - - concolor - first parameter: yellow blue red green white" << endl
            << "                 - second parameter: yellow blue red green pink" << endl
            << "                 changes terminal colors (first parameter - background, second parameter - text)" << endl
            << "    - - print - prints out your message (echo)" << endl
            << "    - - render - renders out a .bmp file in console" << endl
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
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    if (cmd.find("clear") != string::npos) {
        system("cls");
        return true;
    }
    return false;
}
bool user_cmd::cd(string cmd, string& path_r) {
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    std::string path = std::filesystem::current_path().string();
    if (cmd.find("cd") != string::npos) {
        string desired_path = cmd.substr(3);
        if (desired_path == "#") {
            std::lock_guard<std::mutex> lock(path_mutex);
            path_r = path;
            cout << "[+] Working directory is now root." << endl;
            return true;
        }
        try {
            if (filesystem::is_directory(path + "\\" + desired_path)) {
                std::lock_guard<std::mutex> lock(path_mutex);
                path_r = path + "\\" + desired_path;
                cout << "[+] Changed working directory to \\" + desired_path + "\\" << endl;
                return true;
            }
            else {
                cout << "[!] Directory not found or there was an error while reading the path." << endl;
                return true;
            }
        } catch (const std::filesystem::filesystem_error& e) {
            cout << "[!] Error accessing directory: " << e.what() << endl;
            return true;
        }
    }
    return false;
}
bool user_cmd::mp3(string cmd) {
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    if (cmd.find(".mp3") != string::npos) {
        std::string path_to_file = std::filesystem::current_path().string() + "\\" + cmd;
        string fn_arg = "open " + path_to_file + " type mpegvideo alias song1";
        cout << "[player] Playing song: " << cmd << "(press INSERT to stop playing it)" << endl;
        LPCSTR lpc_cmd = fn_arg.c_str();
        MCIERROR mci_err = mciSendStringA(lpc_cmd, NULL, 0, 0);
        mci_err = mciSendStringA("play song1", NULL, 0, 0);
        while (true) {
            if (GetAsyncKeyState(VK_INSERT)) {
                mciSendStringA("close song1", NULL, 0, 0);
                break;
            }
            Sleep(1);
        }
        return true;
    }
    return false;
}
bool user_cmd::cfile(string cmd) {
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    if (cmd.find("cfile") != string::npos) {
        string file_name_ext = cmd.substr(6);
        ofstream create_file(file_name_ext);
        if (!create_file) {
            cout << "[!] Error creating file " << file_name_ext << endl;
        } else {
            create_file.close();
            cout << "[+] Created file " << file_name_ext << endl;
        }
        return true;
    }
    return false;
}
bool user_cmd::dfile(string cmd) {
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    if (cmd.find("dfile") != string::npos) {
        string delete_file = cmd.substr(6);
        if (!std::filesystem::remove(delete_file)) {
            cout << "[!] Error deleting file " << delete_file << endl;
        } else {
            cout << "[+] Deleted file " << delete_file << endl;
        }
        return true;
    }
    return false;
}
bool user_cmd::exe(string cmd) {
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    if (cmd.find(".exe") != string::npos) {
        ShellExecuteA(NULL, "open", cmd.c_str(), NULL, NULL, SW_SHOWDEFAULT); // system is shit, createprocess defeats the purpose
        cout << "[+] Ran an executable file: " << cmd << endl;
        return true;
    }
    return false;
}
bool user_cmd::con_color(string cmd) {
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    if (cmd.find("concolor") != string::npos) {
        string arg1 = "";
        string arg2 = "";
        string color1 = "";
        string color2 = "";
        int start_idx = 9;
        int start_idx2 = 0;
        for (size_t i = start_idx; i < cmd.size(); i++) {
            if (cmd[i] == ' ') {
                start_idx2 = i+1;
                break;
            }
            else {
                color1 += cmd[i];
            }
        }
        for (size_t j = start_idx2; j < cmd.size(); j++) {
            color2 += cmd[j];
        }
        cout << color1 << " " << color2 << endl;
        if (color1 == "yellow") {
            arg1 = '6';
        }
        if (color1 == "blue") {
            arg1 = '3';
        }
        if (color1 == "red") {
            arg1 = '4';
        }
        if (color1 == "green") {
            arg1 = '2';
        }
        if (color1 == "white") {
            arg1 = '7';
        }
        if (color2 == "yellow") {
            arg2 = 'E';
        }
        if (color2 == "blue") {
            arg2 = 'B';
        }
        if (color2 == "red") {
            arg2 = 'C';
        }
        if (color2 == "green") {
            arg2 = 'A';
        }
        if (color2 == "pink") {
            arg2 = 'D';
        }
        string send_cmd = "COLOR " + arg1 + arg2;
        system(send_cmd.c_str());
        return true;
    }
    return false;
}
bool user_cmd::nano(string cmd) {
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    if (cmd.find("nano") != string::npos) {
        string selected_nano_mode = cmd.substr(5, 2);
        if (selected_nano_mode == "-v") {
            string nano_file = cmd.substr(8);
            cout << endl << "[+] nano -> " << nano_file << endl << endl;
            fstream file;
            file.open(nano_file, ios::in);
            if (!file.is_open()) {
                cout << "[!] Error opening file " << nano_file << endl;
            } else {
                string tp;
                while (getline(file, tp)) {
                    cout << tp << "\n";
                }
                file.close();
            }
            return true;
        }
        else if (selected_nano_mode == "-e") {
            string nano_file = cmd.substr(8);
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
            try {
                filesystem::remove(nano_file);
            } catch (const std::filesystem::filesystem_error& e) {
                cout << "[!] Error removing old file: " << e.what() << endl;
            }
            ofstream create_file(nano_file);
            if (!create_file) {
                cout << "[!] Error creating file " << nano_file << endl;
            } else {
                create_file << input;
                create_file.close();
                cout << "[+] Nano -> success (" << nano_file << ")" << endl;
            }
            return true;
        }
        else {
            cout << "[!] Invalid nano arguments. Use -v or -e." << endl;
            return true;
        }

        return false;
    }
    return false;
}
