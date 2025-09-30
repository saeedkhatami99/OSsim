#pragma once
#include "User_cmd.hpp"
#include <mutex>
#include <map>
#include <memory>
#include <sstream>

#pragma comment(lib, "Winmm.lib")

using namespace std;

static string current_path = "";

extern std::map<std::string, std::unique_ptr<Command>> command_registry;

void recognize_cmd(std::string cmd);