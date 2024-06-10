#include "init.h"

void run()
{
    preventPlaying();
    programStartPopup(10);
    
    while (true)
    {
        bool continueToMenu = false;
        User user;

        while (true)
        {
            system("cls");

            int userOption = userMenu();

            if (userOption == 1)
            {
                while (true)
                {
                    system("cls");

                    int loginState = userLogin(user);

                    if (loginState == 1)
                    {
                        continueToMenu = true;
                        break;
                    }
                    else if (loginState == 2)
                    {
                        continue;
                    }
                    else if (loginState == -1)
                    {
                        break;
                    }
                }
            }
            else if (userOption == 2)
            {
                while (true)
                {
                    system("cls");

                    int registerState = userRegister(user);

                    if (registerState == 1)
                    {
                        break;
                    }
                    else if (registerState == 0)
                    {
                        continue;
                    }
                    else if (registerState == -1)
                    {
                        break;
                    }
                }
            }
            else if (userOption == 3)
            {
                printLeaderboard(user);
            }
            else if (userOption == 4)
            {
                programExitPopup(10);
                exit(0);
            }

            if (continueToMenu)
            {
                break;
            }
        }

        loginPopup(10);
        while (true)
        {
            system("cls");

            int menuOption = startMenu(user);
            Gameplay gameplay;

            if (menuOption == 1)
            {
                startGame(gameplay, user);
            }
            else if (menuOption == 2)
            {
                startPrevGame(gameplay, user);
            }
            else if (menuOption == 3)
            {
                printAchievement(user);
            }
            else if (menuOption == 4)
            {
                printLeaderboard(user, true);
            }
            else if (menuOption == 5)
            {
                int res = userDelete(user);
                if (res == 1)
                    break;
            }
            else if (menuOption == 6)
            {
                cleanUser(user);
                logoutPopup(10);
                break;
            }
        }
    }
}

// g++ -I ./core/headers/ ./core/*.cpp main.cpp -o 2048 -g