#pragma once
#include <intrin.h>
#include <iostream>
#include <Windows.h>
#include <direct.h>
#include <vector>
#include <string>
#include <fstream>
#include <streambuf>
#include <filesystem>
#include<Psapi.h>
#include<conio.h>

using namespace std;

static int threads = 0;
static string cpu_name = "";
static float memory = 0.0f;
static string runtime_data = "";

bool is_elevated() {
	bool fn_return = false;
	HANDLE token = NULL;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token)) {
		TOKEN_ELEVATION elevation;
		DWORD cbSize = sizeof(TOKEN_ELEVATION);
		if (GetTokenInformation(token, TokenElevation, &elevation, sizeof(elevation), &cbSize)) {
			fn_return = elevation.TokenIsElevated;
		}
	}
	if (token) {
		CloseHandle(token);
	}
	return fn_return;
}

void display_current_statistics_title() {
	auto this_process_handle = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS pmc;
	if (GetProcessMemoryInfo(this_process_handle, &pmc, sizeof(pmc))) {
		string console_title = "";
		console_title += "OS - ";
		console_title += runtime_data + " ";
		console_title += "RAM: ";

		int ram_bytes_2_megabytes = pmc.WorkingSetSize / 1024 / 1024;
		console_title += to_string(ram_bytes_2_megabytes);
		console_title += "MB";

		std::wstring conv_str = std::wstring(console_title.begin(), console_title.end());
		LPCSTR console_title_a = console_title.c_str();
		SetConsoleTitleA(console_title_a);
	}
	else {
		SetConsoleTitleA("OS");
	}
}

bool login() {
	string username;
	string password;
	cout << "[?] Input your username: ";
	cin >> username;
	cout << "[?] Input your password: ";
	cin >> password;

	if (std::filesystem::exists("account.acc")) {
		std::ifstream account_data("account.acc");
		string username_r;
		account_data >> username_r;
		string password_r;
		account_data >> password_r;
		if (username == username_r && password == password_r) {
			cout << "[+] Successfully logged in! Welcome, " << username << endl;
			return true;
		}
		else {
			cout << "[!] Incorrect login details. Try again." << endl;
			login();
		}
		
	}
	else {
		cout << "[!] No user accounts were found. Creating a new one..." << endl;
		Sleep(1000);
		string username = "";
		string password = "";
		cout << "[!] Username and password cannot contain whitespaces." << endl;
		cout << "[?] Please input your desired username: ";
		cin >> username;
		cout << "[?] Please input your desired password: ";
		cin >> password;
		ofstream store_account_data("account.acc");
		if (!store_account_data) {
			cout << "[!] Error while checking for your user account." << endl;
			login();
		}
		if (store_account_data.is_open())
		{
			store_account_data << username << endl;
			store_account_data << password << endl;
			store_account_data.close();
		}
		cout << "[+] Successfully created a new user account." << endl;

		return true;
	}
	return false;
}

bool boot() {
	if (!is_elevated()) {
		cout << "[!] OS is not ran with elevated privileges." << endl;
		char ans;
		cout << "[?] If you want to proceed with boot, type in Y (yes) or N (no):";
		cin >> ans;
		if (ans == 'Y')
			return true;
		else
			return false;
	}

	cout << "This program is just a simulation of MS-DOS with certain functionality upgrades. It is by no means meant to be a fully working operating system that supports any low-level computing." << endl << endl;

	
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	runtime_data += asctime(timeinfo);

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
	cpu_name = cpu_string;

	

	SYSTEM_INFO system_info;
	GetSystemInfo(&system_info);
	threads = system_info.dwNumberOfProcessors; // cores

	if (threads < 2) {
		cout << "[!] Unsupported CPU detected on this system." << endl;
		return false;
	}
	
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex); // I misunderstand that
	GlobalMemoryStatusEx(&statex);
	memory = (float)statex.ullTotalPhys / (1024 * 1024 * 1024);

	if (memory < 0.512) {
		cout << "[!] Unsupported RAM amount found on this system." << endl;
		return false;
	}

	return true;
}