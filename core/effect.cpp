#include "effect.h"

void gameOverPopup(int duration)
{

    ScreenSize screenSize = getScreenSize();
    int consoleWidth = screenSize.width;
    int consoleHeight = screenSize.height;

    for (int i = 0; i < consoleHeight; i++)
    {
        gotoxy(0, i);
        cout << FORTY_NINETY_SIX_COLOR << string(consoleWidth, ' ') << RESET_FORMAT;
        sleepIgnoreInput(duration);
    }

    string text =
        "       _________    __  _________   ____ _    ____________    \n"
        "      / ____/   |  /  |/  / ____/  / __ \\ |  / / ____/ __ \\   \n"
        "     / / __/ /| | / /|_/ / __/    / / / / | / / __/ / /_/ /   \n"
        "    / /_/ / ___ |/ /  / / /___   / /_/ /| |/ / /___/ _, _/    \n"
        "    \\____/_/  |_/_/  /_/_____/   \\____/ |___/_____/_/ |_|     \n";

    stringstream ss(text);
    string line;
    int y = (consoleHeight - 6) / 2;

    while (getline(ss, line, '\n'))
    {
        int x = (consoleWidth - line.length()) / 2;
        gotoxy(x, y);
        cout << FORTY_NINETY_SIX_COLOR << YELLOW_TEXT << line << RESET_FORMAT;
        y++;
        sleepIgnoreInput(duration * 10);
    }

    sleepIgnoreInput(duration * 100);

    for (int i = 0; i < consoleHeight; i++)
    {
        gotoxy(0, i);
        cout << string(consoleWidth, ' ') << RESET_FORMAT;
        sleepIgnoreInput(duration);
    }

    gotoxy(0, 0);
}

void gameWonPopup(int duration)
{
    ScreenSize screenSize = getScreenSize();
    int consoleWidth = screenSize.width;
    int consoleHeight = screenSize.height;

    for (int i = 0; i < consoleHeight; i++)
    {
        gotoxy(0, i);
        cout << FOUR_BACKGROUND_COLOR << string(consoleWidth, ' ') << RESET_FORMAT;
        sleepIgnoreInput(duration);
    }

    string text =
        "    __  ______  __  __   _       ______  _   __   __  \n"
        "    \\ \\/ / __ \\/ / / /  | |     / / __ \\/ | / /  / /  \n"
        "    \\  / / / / / / /   | | /| / / / / /  |/ /  / /   \n"
        "    / / /_/ / /_/ /    | |/ |/ / /_/ / /|  /  /_/    \n"
        "    /_/\\____/\\____/     |__/|__/\\____/_/ |_/  (_)     \n";

    stringstream ss(text);
    string line;
    int y = (consoleHeight - 6) / 2;

    while (getline(ss, line, '\n'))
    {
        int x = (consoleWidth - line.length()) / 2;
        gotoxy(x, y);
        cout << FOUR_BACKGROUND_COLOR << RED_TEXT << line << RESET_FORMAT;
        y++;
        sleepIgnoreInput(duration * 10);
    }

    sleepIgnoreInput(duration * 100);

    for (int i = 0; i < consoleHeight; i++)
    {
        gotoxy(0, i);
        cout << string(consoleWidth, ' ') << RESET_FORMAT;
        sleepIgnoreInput(duration);
    }

    gotoxy(0, 0);
}

void gameStartPopup(int duration)
{
    ScreenSize screensize;
    screensize = getScreenSize();
    int consoleWidth = screensize.width;
    int consoleHeight = screensize.height;

    for (int i = 0; i < consoleHeight; i++)
    {
        gotoxy(0, i);
        cout << FOUR_BACKGROUND_COLOR << string(consoleWidth, ' ') << RESET_FORMAT;
        sleepIgnoreInput(duration);
    }

    string three =
        "      ________  ______  ____________  \n"
        "     /_  __/ / / / __ \\/ ____/ ____/  \n"
        "      / / / /_/ / /_/ / __/ / __/     \n"
        "     / / / __  / _, _/ /___/ /___     \n"
        "    /_/ /_/ /_/_/ |_/_____/_____/     \n";

    stringstream ss(three);
    string line;
    int y = (consoleHeight - 5) / 2;

    while (getline(ss, line, '\n'))
    {
        int x = (consoleWidth - line.length()) / 2;
        gotoxy(x, y);
        cout << FOUR_BACKGROUND_COLOR << RED_TEXT << line << RESET_FORMAT;
        y++;
        sleepIgnoreInput(duration);
    }

    sleepIgnoreInput(duration * 100);
    y = (consoleHeight - 5) / 2;

    for (int i = 0; i < 5; i++)
    {
        gotoxy(0, y);
        cout << FOUR_BACKGROUND_COLOR << string(consoleWidth, ' ') << RESET_FORMAT;
        y++;
        sleepIgnoreInput(duration);
    }

    string two =
        "      _______       ______  \n"
        "     /_  __/ |     / / __ \\ \n"
        "      / /  | | /| / / / / / \n"
        "     / /   | |/ |/ / /_/ /  \n"
        "    /_/    |__/|__/\\____/   \n";

    stringstream ss2(two);
    y = (consoleHeight - 5) / 2;

    while (getline(ss2, line, '\n'))
    {
        int x = (consoleWidth - line.length()) / 2;
        gotoxy(x, y);
        cout << FOUR_BACKGROUND_COLOR << RED_TEXT << line << RESET_FORMAT;
        y++;
        sleepIgnoreInput(duration);
    }

    sleepIgnoreInput(duration * 100);
    y = (consoleHeight - 5) / 2;

    for (int i = 0; i < 5; i++)
    {
        gotoxy(0, y);
        cout << FOUR_BACKGROUND_COLOR << string(consoleWidth, ' ') << RESET_FORMAT;
        y++;
        sleepIgnoreInput(duration);
    }

    string one =
        "       ____  _   ________ \n"
        "      / __ \\/ | / / ____/ \n"
        "     / / / /  |/ / __/    \n"
        "    / /_/ / /|  / /___    \n"
        "    \\____/_/ |_/_____/    \n";

    stringstream ss3(one);
    y = (consoleHeight - 5) / 2;

    while (getline(ss3, line, '\n'))
    {
        int x = (consoleWidth - line.length()) / 2;
        gotoxy(x, y);
        cout << FOUR_BACKGROUND_COLOR << RED_TEXT << line << RESET_FORMAT;
        y++;
        sleepIgnoreInput(duration);
    }

    sleepIgnoreInput(duration * 100);
    y = (consoleHeight - 5) / 2;

    for (int i = 0; i < 5; i++)
    {
        gotoxy(0, y);
        cout << FOUR_BACKGROUND_COLOR << string(consoleWidth, ' ') << RESET_FORMAT;
        y++;
        sleepIgnoreInput(duration);
    }

    string go =
        "    __________  ____  ____  __  \n"
        "   / ____/ __ \\/ __ \\/ __ \\/ /  \n"
        "  / / __/ / / / / / / / / / /   \n"
        " / /_/ / /_/ / /_/ / /_/ /_/    \n"
        " \\____/\\____/\\____/\\____(_)     \n";

    stringstream ss4(go);
    y = (consoleHeight - 5) / 2;

    while (getline(ss4, line, '\n'))
    {
        int x = (consoleWidth - line.length()) / 2;
        gotoxy(x, y);
        cout << FOUR_BACKGROUND_COLOR << RED_TEXT << line << RESET_FORMAT;
        y++;
        sleepIgnoreInput(duration);
    }

    sleepIgnoreInput(duration * 100);
    y = (consoleHeight - 5) / 2;

    for (int i = 0; i < 5; i++)
    {
        gotoxy(0, y);
        cout << FOUR_BACKGROUND_COLOR << string(consoleWidth, ' ') << RESET_FORMAT;
        y++;
        sleepIgnoreInput(duration);
    }

    for (int i = 0; i < consoleHeight; i++)
    {
        gotoxy(0, i);
        cout << string(consoleWidth, ' ') << RESET_FORMAT;
        sleepIgnoreInput(duration);
    }

    gotoxy(0, 0);
}

void loginPopup(int duration)
{
    ScreenSize screenSize = getScreenSize();
    int consoleWidth = screenSize.width;
    int consoleHeight = screenSize.height;

    for (int i = 0; i < consoleHeight; i++)
    {
        gotoxy(0, i);
        cout << FOUR_BACKGROUND_COLOR << string(consoleWidth, ' ') << RESET_FORMAT;
        sleepIgnoreInput(duration);
    }

    string text =
        "  _       __________    __________  __  _________ \n"
        " | |     / / ____/ /   / ____/ __ \\/  |/  / ____/ \n"
        " | | /| / / __/ / /   / /   / / / / /|_/ / __/    \n"
        " | |/ |/ / /___/ /___/ /___/ /_/ / /  / / /___    \n"
        " |__/|__/_____/_____/\\____/\\____/_/__/_/_____/    \n"
        "        ____  __    _____  ____________           \n"
        "       / __ \\/ /   /   \\ \\/ / ____/ __ \\          \n"
        "      / /_/ / /   / /| |\\  / __/ / /_/ /          \n"
        "     / ____/ /___/ ___ |/ / /___/ _, _/           \n"
        "    /_/   /_____/_/  |_/_/_____/_/ |_|            \n";

    stringstream ss(text);
    string line;

    int y = (consoleHeight - 10) / 2;

    while (getline(ss, line, '\n'))
    {
        int x = (consoleWidth - line.length()) / 2;
        gotoxy(x, y);
        cout << FOUR_BACKGROUND_COLOR << RED_TEXT << line << RESET_FORMAT;
        y++;
        sleepIgnoreInput(duration * 10);
    }

    sleepIgnoreInput(duration * 100);
    y = (consoleHeight - 10) / 2;

    for (int i = 0; i < 10; i++)
    {
        gotoxy(0, y);
        cout << FOUR_BACKGROUND_COLOR << string(consoleWidth, ' ') << RESET_FORMAT;
        y++;
        sleepIgnoreInput(duration);
    }

    for (int i = 0; i < consoleHeight; i++)
    {
        gotoxy(0, i);
        cout << string(consoleWidth, ' ') << RESET_FORMAT;
        sleepIgnoreInput(duration);
    }

    gotoxy(0, 0);
}

void logoutPopup(int duration)
{
    ScreenSize screenSize = getScreenSize();
    int consoleWidth = screenSize.width;
    int consoleHeight = screenSize.height;

    for (int i = 0; i < consoleHeight; i++)
    {
        gotoxy(0, i);
        cout << FOUR_BACKGROUND_COLOR << string(consoleWidth, ' ') << RESET_FORMAT;
        sleepIgnoreInput(duration);
    }

    string text =
        "    __________  _____   ________ \n"
        "   / ____/ __ \\/  _/ | / / ____/ \n"
        "  / / __/ / / // //  |/ / / __   \n"
        " / /_/ / /_/ // // /|  / /_/ /   \n"
        " \\____/\\____/___/_/_|_/\\____/    \n"
        "        ____  __  ________       \n"
        "       / __ \\/ / / /_  __/       \n"
        "      / / / / / / / / /          \n"
        "     / /_/ / /_/ / / /           \n"
        "     \\____/\\____/ /_/            \n";

    stringstream ss(text);
    string line;

    int y = (consoleHeight - 10) / 2;

    while (getline(ss, line, '\n'))
    {
        int x = (consoleWidth - line.length()) / 2;
        gotoxy(x, y);
        cout << FOUR_BACKGROUND_COLOR << RED_TEXT << line << RESET_FORMAT;
        y++;
        sleepIgnoreInput(duration * 10);
    }

    sleepIgnoreInput(duration * 100);
    y = (consoleHeight - 10) / 2;

    for (int i = 0; i < consoleHeight; i++)
    {
        gotoxy(0, i);
        cout << string(consoleWidth, ' ') << RESET_FORMAT;
        sleepIgnoreInput(duration);
    }

    gotoxy(0, 0);
}

void programStartPopup(int duration)
{
    ScreenSize screenSize = getScreenSize();
    int consoleWidth = screenSize.width;
    int consoleHeight = screenSize.height;

    for (int i = 0; i < consoleHeight; i++)
    {
        gotoxy(0, i);
        cout << FOUR_BACKGROUND_COLOR << string(consoleWidth, ' ') << RESET_FORMAT;
        sleepIgnoreInput(duration);
    }

    string text =

        "____/\\\\\\\\\\\\\\\\\\_________/\\\\\\\\\\\\\\_______________/\\\\\\________/\\\\\\\\\\\\\\\\\\____         \n"
        " __/\\\\\\///////\\\\\\_____/\\\\\\/////\\\\\\___________/\\\\\\\\\\______/\\\\\\///////\\\\\\__        \n"
        "  _\\///______\\//\\\\\\___/\\\\\\____\\//\\\\\\________/\\\\\\/\\\\\\_____\\/\\\\\\_____\\/\\\\\\__       \n"
        "   ___________/\\\\\\/___\\/\\\\\\_____\\/\\\\\\______/\\\\\\/\\/\\\\\\_____\\///\\\\\\\\\\\\\\\\\\/___      \n"
        "    ________/\\\\\\//_____\\/\\\\\\_____\\/\\\\\\____/\\\\\\/__\\/\\\\\\______/\\\\\\///////\\\\\\__     \n"
        "     _____/\\\\\\//________\\/\\\\\\_____\\/\\\\\\__/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\__/\\\\\\______\\//\\\\\\_    \n"
        "      ___/\\\\\\/___________\\//\\\\\\____/\\\\\\__\\///////////\\\\\\//__\\//\\\\\\______/\\\\\\__   \n"
        "       __/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\__\\///\\\\\\\\\\\\\\/_____________\\/\\\\\\_____\\///\\\\\\\\\\\\\\\\\\/___  \n"
        "        _\\///////////////_____\\///////_______________\\///________\\/////////_____ \n";

    stringstream ss(text);
    string line;
    int y = (consoleHeight - 9) / 2;

    while (getline(ss, line, '\n'))
    {
        int x = (consoleWidth - line.length()) / 2;
        gotoxy(x, y);
        cout << FOUR_BACKGROUND_COLOR << RED_TEXT;

        for (int i = 0; i < line.length(); i++)
        {
            cout << line[i];
            sleepIgnoreInput(1);
        }

        cout << RESET_FORMAT;

        y++;
    }

    sleepIgnoreInput(duration * 100);

    for (int i = 0; i < consoleHeight; i++)
    {
        gotoxy(0, i);
        cout << string(consoleWidth, ' ') << RESET_FORMAT;
        sleepIgnoreInput(duration);
    }

    gotoxy(0, 0);
}

void programExitPopup(int duration)
{
    ScreenSize screenSize = getScreenSize();
    int consoleWidth = screenSize.width;
    int consoleHeight = screenSize.height;

    for (int i = 0; i < consoleHeight; i++)
    {
        gotoxy(0, i);
        cout << FOUR_BACKGROUND_COLOR << string(consoleWidth, ' ') << RESET_FORMAT;
        sleepIgnoreInput(duration);
    }

    string text =
        "__/\\\\\\\\\\\\\\\\\\\\\\\\\\____/\\\\\\________/\\\\\\__/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\_____/\\\\\\____         \n"
        " _\\/\\\\\\/////////\\\\\\_\\///\\\\\\____/\\\\\\/__\\/\\\\\\///////////____/\\\\\\\\\\\\\\__        \n"
        "  _\\/\\\\\\_______\\/\\\\\\___\\///\\\\\\/\\\\\\/____\\/\\\\\\______________/\\\\\\\\\\\\\\\\\\_       \n"
        "   _\\/\\\\\\\\\\\\\\\\\\\\\\\\\\\\______\\///\\\\\\/______\\/\\\\\\\\\\\\\\\\\\\\\\_____\\//\\\\\\\\\\\\\\__      \n"
        "    _\\/\\\\\\/////////\\\\\\_______\\/\\\\\\_______\\/\\\\\\///////_______\\//\\\\\\\\\\___     \n"
        "     _\\/\\\\\\_______\\/\\\\\\_______\\/\\\\\\_______\\/\\\\\\_______________\\//\\\\\\____    \n"
        "      _\\/\\\\\\_______\\/\\\\\\_______\\/\\\\\\_______\\/\\\\\\________________\\///_____   \n"
        "       _\\/\\\\\\\\\\\\\\\\\\\\\\\\\\/________\\/\\\\\\_______\\/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\_____/\\\\\\____  \n"
        "        _\\/////////////__________\\///________\\///////////////_____\\///_____ \n";

    stringstream ss(text);
    string line;
    int y = (consoleHeight - 9) / 2;

    while (getline(ss, line, '\n'))
    {
        int x = (consoleWidth - line.length()) / 2;
        gotoxy(x, y);
        cout << FOUR_BACKGROUND_COLOR << RED_TEXT;

        for (int i = 0; i < line.length(); i++)
        {
            cout << line[i];
            sleepIgnoreInput(1);
        }

        cout << RESET_FORMAT;
        y++;
    }

    sleepIgnoreInput(duration * 100);

    for (int i = 0; i < consoleHeight; i++)
    {
        gotoxy(0, i);
        cout << string(consoleWidth, ' ') << RESET_FORMAT;
        sleepIgnoreInput(duration);
    }

    gotoxy(0, 0);
}

void preventPlaying()
{
    ScreenSize screenSize = getScreenSize();
    int consoleWidth = screenSize.width;
    int consoleHeight = screenSize.height;

    while (consoleWidth < 150 || consoleHeight < 40)
    {
        system("cls");
        string notif1 = YELLOW_TEXT "Your console window is too small to play the game, which is " UNDERLINE_TEXT + to_string(consoleWidth) + " x " + to_string(consoleHeight) + RESET_FORMAT;
        string notif2 = YELLOW_TEXT "Please resize the console window to at least 150 x 40 then press any key to check again!" RESET_FORMAT;

        int x = (consoleWidth - notif1.length()) / 2;
        int y = (consoleHeight - 2) / 2;

        gotoxy(x, y);
        cout << notif1;
        gotoxy(x, y + 1);
        cout << notif2;

        getch();

        screenSize = getScreenSize();
        consoleWidth = screenSize.width;
        consoleHeight = screenSize.height;
    }
}