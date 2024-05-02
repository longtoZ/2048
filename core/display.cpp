#include <display.h>

int convertCellWidth(int n) {
    return 7 + n - 4;
}

string convertNumberToColor(int n) {
    string color = EMPTY_POS_COLOR;

    // Set color for each number
    if (n==2) {
        color = TWO_BACKGROUND_COLOR;
    } else if (n==4) {
        color = FOUR_BACKGROUND_COLOR;
    } else if (n==8) {
        color = EIGTH_BACKGROUND_COLOR;
    } else if (n==16) {
        color = SIXTEEN_BACKGROUND_COLOR;
    } else if (n==32) {
        color = THIRTY_TWO_BACKGROUND_COLOR;
    } else if (n==64) {
        color = SIXTY_FOUR_BACKGROUND_COLOR;
    } else if (n==128) {
        color = ONE_TWENTY_EIGTH_BACKGROUND_COLOR;
    } else if (n==256) {
        color = TWO_FIFTY_SIX_BACKGROUND_COLOR;
    } else if (n==512) {
        color = FIVE_TWELVE_BACKGROUND_COLOR;
    } else if (n==1024) {
        color = TEN_TWENTY_FOUR_COLOR;
    } else if (n==2048) {
        color = TWENTY_FORTY_EIGHT_COLOR;
    } else if (n==4096) {
        color = FORTY_NINETY_SIX_COLOR;
    }

    return color;
}

void centerBoardNumber(int n, int length, string bg, int type = 0) {
    string color = type == 0 ? convertNumberToColor(n) : CELL_BACKGROUND_COLOR;
    int nCopy = n;
    int count =  n == 0 ? 1 : 0;
    while (nCopy > 0) {
        nCopy /= 10;
        count++;
    }

    int leftSpaces = (length-count)/2;
    int rightSpaces = length-leftSpaces-count;
    string s = string(leftSpaces, ' ') + BLACK_TEXT + to_string(n) + string(rightSpaces, ' ');

    const char* str = convertStringToChar(s);
    const char* color_str = convertStringToChar(color);
    const char* bg_str = convertStringToChar(bg);

    printf("%s %s%s%s%s%s ", bg_str, BOLD_TEXT, color_str, str, RESET_FORMAT, bg_str);
}

void emptyLine(int n, int length, string bg) {
    string s = string(length*n+2*n, ' ');

    const char* str = convertStringToChar(s);
    const char* bg_str = convertStringToChar(bg);

    printf("%s%s%s\n", bg_str, str, RESET_FORMAT);
}

void emptyCell(int n, int length, string bg, int type = 0) {
    string color = type == 0 ? convertNumberToColor(n) : CELL_BACKGROUND_COLOR;
    string s = string(length, ' ');

    const char* str = convertStringToChar(s);
    const char* color_str = convertStringToChar(color);
    const char* bg_str = convertStringToChar(bg);

    printf("%s %s%s%s ", bg_str, color_str, str, bg_str);

}

void printBoard(Gameplay &gameplay) {

    int** &board = gameplay.board;
    int n = gameplay.size;
    int cell_width = convertCellWidth(n);

    for (int i=0; i<n; i++) {
        printf("\t");
        emptyLine(n, cell_width, BOARD_BACKGROUND_COLOR);

        for (int k=0; k<n/2; k++) {
            printf("\t");
            for (int j=0; j<n; j++) {
                emptyCell(board[i][j], cell_width, BOARD_BACKGROUND_COLOR);
            }
            printf("%s\n", RESET_FORMAT);

        }

        printf("\t");
        for (int j=0; j<n; j++) {
            if (board[i][j] == 0) {
                emptyCell(board[i][j], cell_width, BOARD_BACKGROUND_COLOR);
            } else {
                centerBoardNumber(board[i][j], cell_width, BOARD_BACKGROUND_COLOR);
            }
        }
        printf("%s\n", RESET_FORMAT);

        for (int k=0; k<(n - n/2 - 1); k++) {
            printf("\t");
            for (int j=0; j<n; j++) {
                emptyCell(board[i][j], cell_width, BOARD_BACKGROUND_COLOR);
            }
            printf("%s\n", RESET_FORMAT);
        } 

    }

    printf("\t");
    emptyLine(n, cell_width, BOARD_BACKGROUND_COLOR);
}

void printGameplayMenu(Gameplay &gameplay, Stack &undoStack, Stack &redoStack, User &user) {
    system("cls");

    int n = gameplay.size;
    int score = gameplay.score;
    int best = score > getBestScore(user).score ? score : getBestScore(user).score;
    int step = gameplay.step;
    int undoStep = undoStack.size-1;
    int redoStep = redoStack.size;
    int cell_length = 12;

    printf("\t");
    emptyLine(5, cell_length, MENU_BACKGROUND_COLOR);

    printf("\t");
    for (int i=0; i<5; i++) {
        emptyCell(n, cell_length, MENU_BACKGROUND_COLOR, 1);
    }
    printf("%s\n", RESET_FORMAT);

    printf("\t");
    printf("%s %s%s%s%s%s ", MENU_BACKGROUND_COLOR, BOLD_TEXT, BLACK_TEXT, CELL_BACKGROUND_COLOR, "    Score   ", MENU_BACKGROUND_COLOR);
    printf("%s %s%s%s%s%s ", MENU_BACKGROUND_COLOR, BOLD_TEXT, BLACK_TEXT, CELL_BACKGROUND_COLOR, "    Best    ", MENU_BACKGROUND_COLOR);
    printf("%s %s%s%s%s%s ", MENU_BACKGROUND_COLOR, BOLD_TEXT, BLACK_TEXT, CELL_BACKGROUND_COLOR, "    Steps   ", MENU_BACKGROUND_COLOR);
    printf("%s %s%s%s%s%s ", MENU_BACKGROUND_COLOR, BOLD_TEXT, BLACK_TEXT, CELL_BACKGROUND_COLOR, " Undo steps ", MENU_BACKGROUND_COLOR);
    printf("%s %s%s%s%s%s ", MENU_BACKGROUND_COLOR, BOLD_TEXT, BLACK_TEXT, CELL_BACKGROUND_COLOR, " Redo steps ", MENU_BACKGROUND_COLOR);
    printf("%s\n", RESET_FORMAT);

    printf("\t");
    centerBoardNumber(score, cell_length, MENU_BACKGROUND_COLOR, 1);
    centerBoardNumber(best, cell_length, MENU_BACKGROUND_COLOR, 1);
    centerBoardNumber(step, cell_length, MENU_BACKGROUND_COLOR, 1);
    centerBoardNumber(undoStep, cell_length, MENU_BACKGROUND_COLOR, 1);
    centerBoardNumber(redoStep, cell_length, MENU_BACKGROUND_COLOR, 1);
    printf("%s\n", RESET_FORMAT);

    printf("\t");
    for (int i=0; i<5; i++) {
        emptyCell(n, cell_length, MENU_BACKGROUND_COLOR, 1);
    }
    printf("%s\n", RESET_FORMAT);

    printf("\t");
    emptyLine(5, cell_length, MENU_BACKGROUND_COLOR);
    printf("\t%s%s - Move up - [ArrowUp]                                                %s\n", MENU_BACKGROUND_COLOR, BLACK_TEXT, RESET_FORMAT);
    printf("\t%s%s - Move down - [ArrowDown]                                            %s\n", MENU_BACKGROUND_COLOR, BLACK_TEXT, RESET_FORMAT);
    printf("\t%s%s - Move left - [ArrowLeft]                                            %s\n", MENU_BACKGROUND_COLOR, BLACK_TEXT, RESET_FORMAT);
    printf("\t%s%s - Move right - [ArrowRight]                                          %s\n", MENU_BACKGROUND_COLOR, BLACK_TEXT, RESET_FORMAT);
    printf("\t%s%s - Undo - [u]                                                         %s\n", MENU_BACKGROUND_COLOR, BLACK_TEXT, RESET_FORMAT);
    printf("\t%s%s - Redo - [r]                                                         %s\n", MENU_BACKGROUND_COLOR, BLACK_TEXT, RESET_FORMAT);
    printf("\t%s%s - Save game - [s]                                                    %s\n", MENU_BACKGROUND_COLOR, BLACK_TEXT, RESET_FORMAT);
    printf("\t%s%s - End game - [x]                                                     %s\n", MENU_BACKGROUND_COLOR, BLACK_TEXT, RESET_FORMAT);

    printf("\t");
    emptyLine(5, cell_length, MENU_BACKGROUND_COLOR);
    printf("\n");

}

void printFull(Gameplay &gameplay, Stack &undoStack, Stack &redoStack, User &user) {
    printGameplayMenu(gameplay, undoStack, redoStack, user);
    printBoard(gameplay);
}

void printStartMenu(User &user) {
    cout << endl << endl;
    cout << 
            "\t __          __  _                          _  \n" 
            "\t \\ \\        / / | |                        | | \n"
            "\t  \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___| | \n"
            "\t   \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | \n"
            "\t    \\  /\\  /  __/ | (_| (_) | | | | | |  __/_| \n"
            "\t     \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___(_) \n"
            "\n";

    cout << "Welcome back, " << BOLD_TEXT << YELLOW_TEXT << user.username << RESET_FORMAT << "!" << endl;

    cout << "\t\nChoose one option:\n"
            "\t\n\t Start new game - [1]\n"
            "\t\n\t Continue previous game - [2]\n"
            "\t\n\t View your achievement - [3]\n"
            "\t\n\t View global leaderboard - [4]\n"
            "\t\n\t Delete account - [5]\n"
            "\t\n\t Logout - [6]" << endl;
    
    // for (int i=1; i<=255; i++) {
    //     cout << "\x1b[38;5;" << i << "m " << i << "\x1b[0m ";
    // }

    // cout << endl;

    // for (int i=1; i<=255; i++) {
    //     cout << "\x1b[48;5;" << i << "m " << i << "\x1b[0m ";
    // }
}

void printUserMenu() {
    cout << endl << endl;
    cout <<
        "\t                                                                   ,---.-,         \n"
        "\t                                                     ,--,          '   ,'  '.      \n"
        "\t       ,----,              ,----..                 ,--.'|         /   /      \\    \n"
        "\t     .'   .' \\            /   /   \\             ,--,  | :        .   ;  ,/.  :   \n"
        "\t   ,----,'    |          /   .     :         ,---.'|  : '        '   |  | :  ;     \n"
        "\t   |    :  .  ;         .   /   ;.  \\        ;   : |  | ;        '   |  ./   :    \n"
        "\t   ;    |.'  /         .   ;   /  ` ;        |   | : _' |        |   :       ,     \n"
        "\t   `----'/  ;          ;   |  ; \\ ; |        :   : |.'  |         \\   \\     /   \n"
        "\t     /  ;  /           |   :  | ; | '        |   ' '  ; :          ;   ,   '\\     \n"
        "\t    ;  /  /-,          .   |  ' ' ' :        \\   \\  .'. |         /   /      \\  \n"
        "\t   /  /  /.`|          '   ;  \\; /  |         `---`:  | '        .   ;  ,/.  :    \n"
        "\t ./__;      :           \\   \\  ',  /               '  ; |        '   |  | :  ;   \n"
        "\t |   :    .'             ;   :    /                |  : ;        '   |  ./   :     \n"
        "\t ;   | .'                 \\   \\ .'                 '  ,/         |   :      /    \n"
        "\t `---'                     `---`                   '--'           \\   \\   .'     \n"
        "\t                                                                   `---`-'         \n";
    cout << endl;
    cout << YELLOW_TEXT << BOLD_TEXT << "\t                                                     - Programmed by LongTo -" << RESET_FORMAT << endl;
    cout << endl << endl;
    cout << "Welcome, player! Use full-screen to enjoy the game\n"
            "\t Login - [1]\n"
            "\t Register - [2]\n"
            "\t Exit - [3]\n";
    cout << endl << endl;
    cout << "Source code: " << BOLD_TEXT << UNDERLINE_TEXT << "https://github.com/longtoZ/2048" << RESET_FORMAT << endl; 
}

void printAchievement(User &user) {
    system("cls");
    int key = 0;

    getAchievement(user);
    cout << endl;
    cout << 
        "Go back to menu - [x]\n"
        "Reset achievement - [r]\n"
    ;

    while (true) {
        key = getch();

        if (key == X) {
            break;
        } else if (key == R) {
            cout << RED_TEXT << "\nAre you sure? This action cannot be undone!" << RESET_FORMAT << endl;
            getch();
            deleteAchievement(user);
            break;
        }
    }
}

void printLeaderboard() {
    system("cls");
    int key = 0;

    getLeaderboard();
    cout << endl;
    cout << 
        "Go back to menu - [x]\n"
    ;

    while (true) {
        key = getch();

        if (key == X) {
            break;
        }
    }
}