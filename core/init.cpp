#include "init.h"

void run() {

    while (true) {
        bool continueToMenu = false;
        User user;

        while (true) {
            system("cls");

            int userOption = userMenu();

            if (userOption == 1) {
                while (true) {
                    system("cls");

                    int loginState = userLogin(user);

                    if (loginState == 1) {
                        // Login successfully
                        string fullPath = "database\\user\\" + user.username;
                        createDirectory(fullPath);
                        cout << GREEN_TEXT << "\nLogin succesfully! Press any key to continue." << RESET_FORMAT << endl;
                        getch();
                        continueToMenu = true;
                        break;
                    } else if (loginState == 2) {
                        cout << RED_TEXT << "\nUser or password is incorrect! Press any key to try again." << RESET_FORMAT << endl;
                        getch();
                    } else if (loginState == -1) {
                        break;
                    }
                }
            } else if (userOption == 2) {
                system("cls");
                userRegister();
            } else if (userOption == 3) {
                exit(0);
            }

            if (continueToMenu) {
                break;
            }
        } 

        while (true) {
            system("cls");
        
            int menuOption = startMenu(user);

            if (menuOption == 1) {
                Gameplay gameplay;
                startGame(gameplay, user);
            } else if (menuOption == 2) {
                Gameplay gameplay;
                startPrevGame(gameplay, user);
            } else if (menuOption == 3) {
                printAchievement(user);
            } else if (menuOption == 4) {
                printLeaderboard();
            } else if (menuOption == 5) {
                int res = userDelete(user);
                
                if (res == 1) {
                    break;
                }
            } else if (menuOption == 6) {
                break;
            }

        }
    }
}

// g++ -I ./core/headers/ ./core/*.cpp main.cpp -o 2048