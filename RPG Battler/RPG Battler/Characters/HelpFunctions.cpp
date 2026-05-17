#include "HelpFunctions.h"

bool ask()
{
    char answer = ' ';
    while (answer != 'y' && answer != 'n')
    {
        std::cin >> answer;
        if (answer != 'y' && answer != 'n') std::cout << "Invalid answer" << std::endl;
    }
    return answer == 'y';
}
