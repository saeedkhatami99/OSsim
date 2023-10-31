#pragma once
#include "User_cmd.hpp"

#pragma comment(lib, "Winmm.lib")

using namespace std;

static string current_path = "";

/*void set_cursor(int x = 0, int y = 0)  // experimental -- use other libraries like ncurses/readlines
{
    HANDLE handle;
    COORD coordinates;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(handle, coordinates);
}*/



bool recognize_cmd(std::string cmd) {

    if (user_cmd::print(cmd))
        return true;
    if (user_cmd::help_c(cmd))
        return true;
    if (user_cmd::ls(cmd))
        return true;
    if (user_cmd::cfile(cmd))
        return true;
    if (user_cmd::help(cmd))
        return true;
    if (user_cmd::clear(cmd))
        return true;
    if (user_cmd::sysinfo(cmd))
        return true;
    if (user_cmd::exit_sys(cmd))
        return true;
    if (user_cmd::dfile(cmd))
        return true;
    if (user_cmd::mkdir(cmd))                                   // dont talk about performance, its hurtin.
        return true;
    if (user_cmd::ddir(cmd))
        return true;
    if (user_cmd::exe(cmd))
        return true;
    if (user_cmd::mp3(cmd))
        return true;
    if (user_cmd::nano(cmd))
        return true;


    cout << "[!] Invalid command. Try running with elevated privileges." << endl;
    return false;
}