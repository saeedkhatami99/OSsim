#include <iostream>
#include <string>
#include "Boot.hpp"
#include "Core.hpp"

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

    std::cout << "OS\n";
    cout << endl;
    cout << endl;
    if (boot())
        cout << "[~] Booted successfully with no errors." << endl;
    else {
        cout << "[!] Boot error occured, please look at the lines above for possible fixes." << endl;
        return 0;
    }

    if (!is_elevated()) {
        cout << "[!] OS is not running with elevated privileges." << endl;
        return 0;
    }

    if (!login())
        return 0;

    while (true) {
        display_current_statistics_title();

        string command;
        cout << "OS/root: $ ";
        std::getline(std::cin >> std::ws, command);

        if (!recognize_cmd(command)) {
            cout << "[!] Command not recognized or you need higher privileges. Try gaining root access." << endl;
        }
    }
    return 0;
}
