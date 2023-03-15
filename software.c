// Author of the program - Justas Mileika 2021 Vilnius University, Software Engineering, Bachelor's degree, first year, group 2. E-mail: justasmileika@gmail.com
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "module.h"
#include "User_Interface.h"
#include "BackEnd_Functions.h"

int main()
{
    printProgramIntroduction();
    while(1)
    {
        int choice = showMenu(MAIN_MENU, menuOptions, 5, ASKING_CHOICE);
        switch (choice)
        {
        case 1:
            createNewPlaylist(MAX_LINE_LENGTH);
            break;
        case 2:
            modifyExistingPlaylist(MAX_LINE_LENGTH, MAX_LIST_INDEX);
            break;
        case 3:
            checkDatabase(MAX_LINE_LENGTH);
            break;
        case 4:
            printHelp();
            break;
        case 5:
            exitProgram();
            break;
        }
    }
    return 0;
}
