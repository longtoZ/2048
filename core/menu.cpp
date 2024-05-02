#include "menu.h"
using namespace std;

int userMenu() {
    int key = 0;

    while (true) {
        system("cls");

        printUserMenu();

        key = getch();

        if (key == ONE) {
            return 1;
        } else if (key == TWO) {
            return 2;
        } else if (key == THREE) {
            return 3;
        } else {
            continue;
        }
    }

    return -1;
}

int startMenu(User &user) {
    int key = 0;

    while (true) {
        system("cls");

        printStartMenu(user);

        key = getch();

        if (key == ONE) {
            return 1;
        } else if (key == TWO) {
            return 2;
        } else if (key == THREE) {
            return 3;
        } else if (key == FOUR) {
            return 4;
        } else if (key == FIVE) {
            return 5;
        } else if (key == SIX) {
            return 6;
        } else {
            continue;
        }
    }

    return -1;

}

void startGame(Gameplay &gameplay, User &user) {

    int key = 0;
    int size = 0;

    while (true) {
        system("cls");

        cout << "Choose board size (4x4, 5x5, ..., NxN): ";
        
        cin >> key;

        if (key > 0) {
            size = key;
        } else {
            cout << "Please choose a valid size!" << endl;
            continue;
        }

        if (size > 0)
            break;
    }

    int moved = 0;

    gameplay.size = size;
    gameplay.emptyLeft = gameplay.size*gameplay.size;
    gameplay.board = createEmptyBoard(gameplay.size);
    gameplay.emptyPos = createEmptyPos(gameplay.emptyLeft);
    gameplay.score = 0;
    gameplay.step = 0;

    Stack undoStack;
    Stack redoStack;

    undoStack.init();
    redoStack.init();
    
    createBoard(gameplay);

    // Add first stack
    undoStack.push(gameplay);
    printFull(gameplay, undoStack, redoStack, user);

    // Set start point
    auto start_time = high_resolution_clock::now();

    while (true) {
        key = getch();
        
        if (key==224) {
            key = getch();
            moved = 0;

            if (key == KEYUP) {
                moveUp(gameplay, moved);
            } else if (key == KEYDOWN) {
                moveDown(gameplay, moved);
            } else if (key == KEYLEFT) {
                moveLeft(gameplay, moved);
            } else if (key == KEYRIGHT) {
                moveRight(gameplay, moved);
            }

            if (moved==1) {
                fillRandomNumber(gameplay);
                undoStack.push(gameplay);

                // Empty redoStack when player starts adding new moves
                if (!redoStack.empty()) {
                    cleanStack(redoStack);
                }

                gameplay.step += 1;
            }
            
            printFull(gameplay, undoStack, redoStack, user);

            if (gameOver(gameplay, undoStack, redoStack, start_time, user)) {
                cout << "Game over. Press any key to go to menu..." << endl;
                getch();
                break;
            }

        } else if (key == X) {
            cout << "Game over. Press any key to go to menu..." << endl;
            endGame(gameplay, undoStack, redoStack, start_time, user);
            getch();
            break;
        } else if (key == S) {
            cout << "Game saved. Press any key to go to menu..." << endl;
            saveBoard(gameplay, user);
            endGame(gameplay, undoStack, redoStack, start_time, user);
            getch();
            break;
        } else if (key == U) {
            undo(gameplay, undoStack, redoStack);
            printFull(gameplay, undoStack, redoStack, user);
        } else if (key == R) {
            redo(gameplay, undoStack, redoStack);
            printFull(gameplay, undoStack, redoStack, user);
        }
    }
}

void startPrevGame(Gameplay &gameplay, User &user) {

    int key = 0;
    int moved = 0;
    
    getPrevBoard(gameplay, user);

    // Check for saved game
    if (gameplay.size == 0) {
        cout << YELLOW_TEXT << "\nNo saved game. Press any key to go to menu..." << RESET_FORMAT << endl;
        getch();
        return;
    }

    Stack undoStack;
    Stack redoStack;

    undoStack.init();
    redoStack.init();

    // Add first stack
    undoStack.push(gameplay);
    printFull(gameplay, undoStack, redoStack, user);

    // Set start point
    auto start_time = high_resolution_clock::now();

    while (true) {
        key = getch();
        
        if (key==224) {
            key = getch();
            moved = 0;

            if (key == KEYUP) {
                moveUp(gameplay, moved);
            } else if (key == KEYDOWN) {
                moveDown(gameplay, moved);
            } else if (key == KEYLEFT) {
                moveLeft(gameplay, moved);
            } else if (key == KEYRIGHT) {
                moveRight(gameplay, moved);
            }

            if (moved==1) {
                fillRandomNumber(gameplay);
                undoStack.push(gameplay);

                // Empty redoStack when player starts adding new moves
                if (!redoStack.empty()) {
                    cleanStack(redoStack);
                }

                gameplay.step += 1;
            }
            
            printFull(gameplay, undoStack, redoStack, user);

            if (gameOver(gameplay, undoStack, redoStack, start_time, user)) {
                cout << "Game over. Press any key to go to menu..." << endl;
                getch();
                break;
            }

        } else if (key == X) {
            cout << "Game over. Press any key to go to menu..." << endl;
            getch();
            endGame(gameplay, undoStack, redoStack, start_time, user);
            break;
        } else if (key == S) {
            cout << "Game saved. Press any key to go to menu..." << endl;
            saveBoard(gameplay, user);
            endGame(gameplay, undoStack, redoStack, start_time, user);
            getch();
            break;
        } else if (key == U) {
            undo(gameplay, undoStack, redoStack);
            printFull(gameplay, undoStack, redoStack, user);
        } else if (key == R) {
            redo(gameplay, undoStack, redoStack);
            printFull(gameplay, undoStack, redoStack, user);
        }
    }
}

