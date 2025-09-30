#pragma once
#include <intrin.h>
#include <iostream>
#include <Windows.h>
#include <direct.h>
#include <vector>
#include <string>
#include <fstream>
#include <streambuf>
#include <istream>
#include <filesystem>
#include <sstream>
#include <wingdi.h>
#include <winsock.h>
#include <Psapi.h>
#include <algorithm>
#include <functional>
#include <mutex>

extern std::mutex path_mutex;

using namespace std;

/*void clipboard(HWND hwnd, const string& s) {
    OpenClipboard(hwnd);
    EmptyClipboard();
    HGLOBAL h_global = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
    if (!h_global) {                                                            function used for storing text file into clipboard
        CloseClipboard();
        return;
    }
    memcpy(GlobalLock(h_global), s.c_str(), s.size() + 1);
    GlobalUnlock(h_global);
    SetClipboardData(CF_TEXT, h_global);
    CloseClipboard();
    GlobalFree(h_global);
}

void paste() {
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;

    input.ki.wVk = VK_CONTROL;
    input.ki.dwFlags = 0;
    SendInput(1, &input, sizeof(INPUT));

    input.ki.wVk = 'V';
    input.ki.dwFlags = 0;                                        really fucked up function for pasting the clipboard stuff, simulate CTRL + V basically.
    SendInput(1, &input, sizeof(INPUT));

    input.ki.wVk = 'V';
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));

    input.ki.wVk = VK_CONTROL;
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
    Sleep(1000);
}*/
//extern string used_path_alt = "";
static int threads_alt = 0;
static string cpu_name_alt = "";
static float memory_alt = 0.0f;
static string runtime_data_alt = "";

namespace user_cmd {
    bool con_color(string cmd);
    bool cd(string cmd, string& path_r);
    bool render_img(string cmd);
    bool hex(string cmd);
    bool help_c(string cmd);
    bool print(string cmd);
    bool mkdir(string cmd);
    bool ddir(string cmd);
    bool ls(string cmd, const string& current_path);
    bool sysinfo(string cmd);
    bool exit_sys(string cmd);
    bool help(string cmd);
    bool clear(string cmd);
    bool mp3(string cmd);
    bool cfile(string cmd);
    bool dfile(string cmd);
    bool exe(string cmd);
    bool nano(string cmd);
}

class Command {
public:
    virtual ~Command() = default;
    virtual bool execute(const std::string& cmd, std::string& path_r) = 0;
};

class SimpleCommand : public Command {
    std::function<bool(const std::string&, std::string&)> func;
public:
    SimpleCommand(std::function<bool(const std::string&, std::string&)> f) : func(f) {}
    bool execute(const std::string& cmd, std::string& path_r) override { return func(cmd, path_r); }
};
