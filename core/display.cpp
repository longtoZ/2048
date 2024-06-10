#include <display.h>

int convertCellWidth(int n)
{
    if (n < 5)
        return 7 + n - 4;
    else
        // Set max width 9 for cell
        return 9;
}

int convertCellHeight(int n)
{
    if (n < 5)
        return n;
    else
        // Set max height 5 for cell
        return 5;
}

string convertNumberToColor(int n)
{
    string color = EMPTY_POS_COLOR;

    // Set color for each cell number
    if (n == 2)
    {
        color = TWO_BACKGROUND_COLOR;
    }
    else if (n == 4)
    {
        color = FOUR_BACKGROUND_COLOR;
    }
    else if (n == 8)
    {
        color = EIGTH_BACKGROUND_COLOR;
    }
    else if (n == 16)
    {
        color = SIXTEEN_BACKGROUND_COLOR;
    }
    else if (n == 32)
    {
        color = THIRTY_TWO_BACKGROUND_COLOR;
    }
    else if (n == 64)
    {
        color = SIXTY_FOUR_BACKGROUND_COLOR;
    }
    else if (n == 128)
    {
        color = ONE_TWENTY_EIGTH_BACKGROUND_COLOR;
    }
    else if (n == 256)
    {
        color = TWO_FIFTY_SIX_BACKGROUND_COLOR;
    }
    else if (n == 512)
    {
        color = FIVE_TWELVE_BACKGROUND_COLOR;
    }
    else if (n == 1024)
    {
        color = TEN_TWENTY_FOUR_COLOR;
    }
    else if (n == 2048)
    {
        color = TWENTY_FORTY_EIGHT_COLOR;
    }
    else if (n == 4096)
    {
        color = FORTY_NINETY_SIX_COLOR;
    }

    return color;
}

string centerBoardNumber(int n, int length, string txt, string bg, int type = 0)
{
    string color = type == 0 ? convertNumberToColor(n) : CELL_BACKGROUND_COLOR;
    int nCopy = n;
    int count = n == 0 ? 1 : 0;
    while (nCopy > 0)
    {
        nCopy /= 10;
        count++;
    }

    int leftSpaces = (length - count) / 2;
    int rightSpaces = length - leftSpaces - count;
    string s = string(leftSpaces, ' ') + txt + to_string(n) + string(rightSpaces, ' ');

    string line = bg + " " + BOLD_TEXT + color + s + RESET_FORMAT + bg + " ";
    return line;

}

string emptyLine(int n, int length, string bg)
{
    string s = string(length * n + 2 * n, ' ');

    string line = bg + s + RESET_FORMAT + "\n";
    return line;

}

string emptyCell(int n, int length, string bg, int type = 0)
{
    string color = type == 0 ? convertNumberToColor(n) : CELL_BACKGROUND_COLOR;
    string s = string(length, ' ');

    string line = bg + " " + color + s + bg + " ";
    return line;

}

void printBoard(Gameplay &gameplay)
{

    int **&board = gameplay.board;
    int n = gameplay.size;
    int cell_width = convertCellWidth(n);
    int cell_height = convertCellHeight(n);
    int lineLength = cell_width * n + 2 * n;
    string finalBoard = "";

    for (int i = 0; i < n; i++)
    {
        // Top border of the board
        finalBoard += emptyLine(n, cell_width, BOARD_BACKGROUND_COLOR);

        // Height above the number
        for (int k = 0; k < cell_height / 2; k++)
        {
            for (int j = 0; j < n; j++)
            {
                finalBoard += emptyCell(board[i][j], cell_width, BOARD_BACKGROUND_COLOR);
            }
            finalBoard += RESET_FORMAT "\n";
        }

        // Number
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == 0)
            {
                finalBoard += emptyCell(board[i][j], cell_width, BOARD_BACKGROUND_COLOR);
            }
            else
            {
                finalBoard += centerBoardNumber(board[i][j], cell_width, BLACK_TEXT, BOARD_BACKGROUND_COLOR);
            }
        }
        finalBoard += RESET_FORMAT "\n";

        // Height below the number
        for (int k = 0; k < (cell_height - cell_height / 2 - 1); k++)
        {
            for (int j = 0; j < n; j++)
            {
                finalBoard += emptyCell(board[i][j], cell_width, BOARD_BACKGROUND_COLOR);
            }
            finalBoard += RESET_FORMAT "\n";
        }
    }

    // Bottom border of the board
    finalBoard += emptyLine(n, cell_width, BOARD_BACKGROUND_COLOR);

    // Center the board
    stringstream ss(finalBoard);
    string line;

    while (getline(ss, line, '\n'))
    {
        cout << setCenterAlignSize(lineLength) << line << endl;
    }
}

void printGameplayMenu(Gameplay &gameplay, Stack &undoStack, Stack &redoStack, User &user)
{
    int n = gameplay.size;
    int score = gameplay.score;
    int best = score > getBestScore(user).score ? score : getBestScore(user).score;
    int step = gameplay.step;
    int undoStep = undoStack.size - 1;
    int redoStep = redoStack.size;
    int cell_length = 12;
    int lineLength = cell_length * 5 + 2 * 5;
    string finalMenu = "";

    // Top border of the menu
    finalMenu += emptyLine(5, cell_length, MENU_BACKGROUND_COLOR);

    // Height above the title
    for (int i = 0; i < 5; i++)
    {
        finalMenu += emptyCell(n, cell_length, MENU_BACKGROUND_COLOR, 1);
    }
    finalMenu += RESET_FORMAT "\n";

    // Titles
    finalMenu += string(MENU_BACKGROUND_COLOR) + " " + BOLD_TEXT + BLACK_TEXT + CELL_BACKGROUND_COLOR + "    Score   " + MENU_BACKGROUND_COLOR + " ";
    finalMenu += string(MENU_BACKGROUND_COLOR) + " " + BOLD_TEXT + BLACK_TEXT + CELL_BACKGROUND_COLOR + "    Best    " + MENU_BACKGROUND_COLOR + " ";
    finalMenu += string(MENU_BACKGROUND_COLOR) + " " + BOLD_TEXT + BLACK_TEXT + CELL_BACKGROUND_COLOR + "    Steps   " + MENU_BACKGROUND_COLOR + " ";
    finalMenu += string(MENU_BACKGROUND_COLOR) + " " + BOLD_TEXT + (gameplay.canUndoRedo ? BLACK_TEXT : RED_TEXT) + CELL_BACKGROUND_COLOR + " Undo steps " + MENU_BACKGROUND_COLOR + " ";
    finalMenu += string(MENU_BACKGROUND_COLOR) + " " + BOLD_TEXT + (gameplay.canUndoRedo ? BLACK_TEXT : RED_TEXT) + CELL_BACKGROUND_COLOR + " Redo steps " + MENU_BACKGROUND_COLOR + " ";
    finalMenu += RESET_FORMAT "\n";

    // Value of each title
    finalMenu += centerBoardNumber(score, cell_length, BLACK_TEXT, MENU_BACKGROUND_COLOR, 1);
    finalMenu += centerBoardNumber(best, cell_length, BLACK_TEXT, MENU_BACKGROUND_COLOR, 1);
    finalMenu += centerBoardNumber(step, cell_length, BLACK_TEXT, MENU_BACKGROUND_COLOR, 1);
    finalMenu += centerBoardNumber(undoStep, cell_length, (gameplay.canUndoRedo ? BLACK_TEXT : RED_TEXT), MENU_BACKGROUND_COLOR, 1);
    finalMenu += centerBoardNumber(redoStep, cell_length, (gameplay.canUndoRedo ? BLACK_TEXT : RED_TEXT), MENU_BACKGROUND_COLOR, 1);
    finalMenu += RESET_FORMAT "\n";

    // Height below the title
    for (int i = 0; i < 5; i++)
    {
        finalMenu += emptyCell(n, cell_length, MENU_BACKGROUND_COLOR, 1);
    }
    finalMenu += RESET_FORMAT "\n";

    finalMenu += emptyLine(5, cell_length, MENU_BACKGROUND_COLOR);

    // Gameplay instructions
    finalMenu += string(MENU_BACKGROUND_COLOR) + BLACK_TEXT + " - Use arrow to move                                                  " + RESET_FORMAT + "\n";

    if (gameplay.canUndoRedo)
    {
        finalMenu += string(MENU_BACKGROUND_COLOR) + BLACK_TEXT + " - Undo - [u]                                                         " + RESET_FORMAT + "\n";
        finalMenu += string(MENU_BACKGROUND_COLOR) + BLACK_TEXT + " - Redo - [r]                                                         " + RESET_FORMAT + "\n";
    }
    finalMenu += string(MENU_BACKGROUND_COLOR) + BLACK_TEXT + " - Save game - [s]                                                    " + RESET_FORMAT + "\n";
    finalMenu += string(MENU_BACKGROUND_COLOR) + BLACK_TEXT + " - End game - [x]                                                     " + RESET_FORMAT + "\n";

    // Bottom border of the menu
    finalMenu += emptyLine(5, cell_length, MENU_BACKGROUND_COLOR) + "\n";

    // Center the menu
    stringstream ss(finalMenu);
    string line;

    while (getline(ss, line, '\n'))
    {
        cout << setCenterAlignSize(lineLength) << line << endl;
    }
}

void printFull(Gameplay &gameplay, Stack &undoStack, Stack &redoStack, User &user)
{
    system("cls");
    cout << endl << endl;
    printGameplayMenu(gameplay, undoStack, redoStack, user);
    printBoard(gameplay);
}

int printStartMenu(User &user)
{
    string pre =
        "\n\n" 
        TAB_WIDTH_1 " __          __  _                          _  \n" 
        TAB_WIDTH_1 " \\ \\        / / | |                        | | \n" 
        TAB_WIDTH_1 "  \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___| | \n" 
        TAB_WIDTH_1 "   \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | \n" 
        TAB_WIDTH_1 "    \\  /\\  /  __/ | (_| (_) | | | | | |  __/_| \n" 
        TAB_WIDTH_1 "     \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___(_) \n" 
        TAB_WIDTH_1 "\n"
        "Welcome back, " BOLD_TEXT YELLOW_TEXT +
        string(user.username) + RESET_FORMAT "!\n"
        "Choose one option:\n\n";

    string post = "";
    string options[] = {
        "Start new game",
        "Continue previous game",
        "View your achievement",
        "View global leaderboard",
        "Delete account",
        "Logout",
    };

    int chosen = generateSelections(options, 6, pre, post);

    return chosen;
}

int printUserMenu()
{
    string pre =
        "\n\n" 
        TAB_WIDTH_2 "                                                                   ,---.-,         \n" 
        TAB_WIDTH_2 "                                                     ,--,          '   ,'  '.      \n" 
        TAB_WIDTH_2 "       ,----,              ,----..                 ,--.'|         /   /      \\    \n" 
        TAB_WIDTH_2 "     .'   .' \\            /   /   \\             ,--,  | :        .   ;  ,/.  :   \n" 
        TAB_WIDTH_2 "   ,----,'    |          /   .     :         ,---.'|  : '        '   |  | :  ;     \n" 
        TAB_WIDTH_2 "   |    :  .  ;         .   /   ;.  \\        ;   : |  | ;        '   |  ./   :    \n" 
        TAB_WIDTH_2 "   ;    |.'  /         .   ;   /  ` ;        |   | : _' |        |   :       ,     \n" 
        TAB_WIDTH_2 "   `----'/  ;          ;   |  ; \\ ; |        :   : |.'  |         \\   \\     /   \n" 
        TAB_WIDTH_2 "     /  ;  /           |   :  | ; | '        |   ' '  ; :          ;   ,   '\\     \n" 
        TAB_WIDTH_2 "    ;  /  /-,          .   |  ' ' ' :        \\   \\  .'. |         /   /      \\  \n" 
        TAB_WIDTH_2 "   /  /  /.`|          '   ;  \\; /  |         `---`:  | '        .   ;  ,/.  :    \n" 
        TAB_WIDTH_2 " ./__;      :           \\   \\  ',  /               '  ; |        '   |  | :  ;   \n" 
        TAB_WIDTH_2 " |   :    .'             ;   :    /                |  : ;        '   |  ./   :     \n" 
        TAB_WIDTH_2 " ;   | .'                 \\   \\ .'                 '  ,/         |   :      /    \n" 
        TAB_WIDTH_2 " `---'                     `---`                   '--'           \\   \\   .'     \n" 
        TAB_WIDTH_2 "                                                                   `---`-'         \n\n" 
        YELLOW_TEXT BOLD_TEXT TAB_WIDTH_2  "                                                     - Programmed by LongTo -" RESET_FORMAT
        "\n\n"
        "Welcome, player! Use full-screen to enjoy the game\n\n";

    string post =
        "\n"
        "Source code: " BOLD_TEXT UNDERLINE_TEXT "https://github.com/longtoZ/2048" RESET_FORMAT;
        
    string options[] = {
        "Login",
        "Register",
        "View global leaderboard",
        "Exit",
    };

    int chosen = generateSelections(options, 4, pre, post);

    return chosen;
}

void printAchievement(User &user)
{
    system("cls");
    int key = 0;

    string pre1 = getAchievement(user);
    string post1 = "";
    string options1[] = {
        "Go back to menu",
        "Reset achievement",
    };

    int chosen1 = generateSelections(options1, 2, pre1, post1, "center");
    if (chosen1 == 1)
    {
        return;
    }
    else if (chosen1 == 2)
    {
        string pre2 = TAB_WIDTH_1 RED_TEXT "Are you sure? This action cannot be undone!" RESET_FORMAT;
        string post2 = "";
        string options2[] = {
            "Yes",
            "No",
        };

        int chosen2 = generateSelections(options2, 2, pre2, post2);
        if (chosen2 == 1)
        {
            deleteAchievement(user);
        }
        else
        {
            printAchievement(user);
        }
    }
}

void printLeaderboard(User &user, bool highlightUser)
{
    system("cls");
    int key = 0;
    int rankOfUser = -1;
    int scoreToHighlight = -1;

    if (user.username != nullptr) {
        Data bestScore = getBestScore(user);

        if (highlightUser)
        {
            scoreToHighlight = bestScore.score;
        }
    }

    string pre = getLeaderboard(user, rankOfUser, scoreToHighlight);
    string post = "";
    string options[] = {
        "Go back to menu",
    };

    int chosen = generateSelections(options, 1, pre, post, "center");
    if (chosen == 1)
    {
        return;
    }
}