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

enum log_type {
	OUTPUT_LOG = 0,
	ERROR_LOG = 1,
	WARNING_LOG = 2,
	AT_BOOT_LOG = 3,
	AT_BOOT_ERROR = 4,
	MEMORY_ERROR = 5,
	MEMORY_WARNING = 6,
	MEMORY_NULL = 7,
	CPU_ERROR = 8,
	SUCCESS_OP = 9
};

class LOG {
private:
	int log_amount = 0;
	int separate_log_amount[11];
	string path = "";
public:
	void create_log(log_type type, string description);
	void create_log_file(string path);
	void view_log_file(string path);
	void view_current_log_info();
};

void LOG::create_log(log_type type, string description) {
	string log = "";
	switch (type) {
	case 0:
		log += "[OUTPUT_LOG] ";
		separate_log_amount[0]++;
		break;
	case 1:
		log += "[ERROR_LOG] ";
		separate_log_amount[1]++;
		break;
	case 2:
		log += "[WARNING_LOG] ";
		separate_log_amount[2]++;
		break;
	case 3:
		log += "[AT_BOOT_LOG] ";
		separate_log_amount[3]++;
		break;
	case 4:
		log += "[AT_BOOT_ERROR] ";
		separate_log_amount[4]++;
		break;
	case 5:
		log += "[MEMORY_ERROR] ";
		separate_log_amount[5]++;
		break;
	case 6:
		log += "[MEMORY_WARNING] ";
		separate_log_amount[6]++;
		break;
	case 7:
		log += "[MEMORY_NULL] ";
		separate_log_amount[7]++;
		break;
	case 8:
		log += "[CPU_ERROR] ";
		separate_log_amount[8]++;
		break;
	case 9:
		log += "[SUCCESS_OP] ";
		separate_log_amount[9]++;
		break;
	default:
		log += "[NO_LOG_TYPE_DEFINED] ";
		separate_log_amount[10]++;
		break;
	}

	log += description;
	std::ofstream log_f;
	log_f.open(path, std::ios_base::app);
	log_f << log + "\n";
	log_f.close();
}

void LOG::create_log_file(string path) {
	if (this->path == "") {
		for (int i = 0; i < 10; i++) {
			this->separate_log_amount[i] = 0;
		}
		ofstream create_log(path);
		create_log.close();
		this->path = path;
	}
}

void LOG::view_log_file(string path) {
	fstream file;
	file.open(path, ios::in);
	if (file.is_open()) {
		string tp;
		while (getline(file, tp)) {
			cout << tp << "\n";
		}
		file.close();
	}
}

void LOG::view_current_log_info() {
	cout << "[~] Current log info: " << endl;
	cout << "		[OUTPUT_LOG] " << separate_log_amount[0] << endl;
	cout << "		[ERROR_LOG] " << separate_log_amount[1] << endl;
	cout << "		[WARNING_LOG] " << separate_log_amount[2] << endl;
	cout << "		[AT_BOOT_LOG] " << separate_log_amount[3] << endl;
	cout << "		[AT_BOOT_ERROR] " << separate_log_amount[4] << endl;
	cout << "		[MEMORY_ERROR] " << separate_log_amount[5] << endl;
	cout << "		[MEMORY_WARNING] " << separate_log_amount[6] << endl;
	cout << "		[MEMORY_NULL] " << separate_log_amount[7] << endl;
	cout << "		[CPU_ERROR] " << separate_log_amount[8] << endl;
	cout << "		[SUCCESS_OP] " << separate_log_amount[9] << endl;
	cout << "		[NO_LOG_TYPE_DEFINED] " << separate_log_amount[10] << endl;

}