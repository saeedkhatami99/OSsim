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
