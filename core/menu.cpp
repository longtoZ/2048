#include "menu.h"
using namespace std;

int userMenu() {
    return printUserMenu();
}

int startMenu(User &user) {
    return printStartMenu(user);
}

void startGame(Gameplay &gameplay, User &user) {

    int key = 0;

    // Set up game
    string boardSizeOptions[] = {
        "4x4",
        "5x5",
        "6x6",
        "7x7",
        "8x8",
        "9x9",
        "10x10",
    };

    string undoRedoSelections[] = {
        "Enable",
        "Disable"
    };

    int size = generateSelections(boardSizeOptions, 7, "Choose board size (4x4, 5x5, ..., NxN): ", "") + 3;
    gameplay.canUndoRedo = generateSelections(undoRedoSelections, 2, "Use undo/redo feature?", "") == 1 ? true : false;

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

    // Set eternal playing mode
    bool eternal = false;

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

            if (gameOver(gameplay) && !eternal) {
                char choice = 'y';

                cout << "\n\tGame over. Do you want to continue playing? [Y/N]" << endl;
                
                cin >> choice;

                choice = tolower(choice);

                if (choice == 'y') {
                    eternal = true;
                    continue;
                } else {
                    cout << "\tGame ended!" << endl;
                    endGame(gameplay, undoStack, redoStack, start_time, user);
                    break;
                }
            } else if (gameWon(gameplay) && !eternal) {
                char choice = 'y';

                cout << "\n\tYou won at 2048. Do you want to continue playing? [Y/N]" << endl;
                
                cin >> choice;

                choice = tolower(choice);

                if (choice == 'y') {
                    eternal = true;
                    continue;
                } else {
                    cout << "\tGame ended!" << endl;
                    endGame(gameplay, undoStack, redoStack, start_time, user);
                    break;
                }
            }

        } else if (key == X) {
            cout << "\tGame ended!" << endl;
            endGame(gameplay, undoStack, redoStack, start_time, user);
            break;
        } else if (key == S) {
            cout << GREEN_TEXT << "\tGame saved!" << RESET_FORMAT << endl;
            saveBoard(gameplay, user);
            endGame(gameplay, undoStack, redoStack, start_time, user);
            break;
        } else if (key == U) {
            if (gameplay.canUndoRedo) {
                int state = undo(gameplay, undoStack, redoStack);
                printFull(gameplay, undoStack, redoStack, user);
                if (state == 0) {
                    cout << YELLOW_TEXT << "\tNo step to undo" << RESET_FORMAT << endl;
                }
            } else {
                printFull(gameplay, undoStack, redoStack, user);
                cout << YELLOW_TEXT << "\n\tUndo feature is disabled. Please start a new game and enable it!" << RESET_FORMAT << endl;            
            }
        } else if (key == R) {
            if (gameplay.canUndoRedo) {
                int state = redo(gameplay, undoStack, redoStack);
                printFull(gameplay, undoStack, redoStack, user);
                if (state == 0) {
                    cout << YELLOW_TEXT << "\tNo step to redo" << RESET_FORMAT << endl;
                }
            } else {
                printFull(gameplay, undoStack, redoStack, user);
                cout << YELLOW_TEXT << "\n\tRedo feature is disabled. Please start a new game and enable it!" << RESET_FORMAT << endl;            
            }
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

    // Set up game 
    string undoRedoSelections[] = {
        "Enable",
        "Disable"
    };

    gameplay.canUndoRedo = generateSelections(undoRedoSelections, 2, "Use undo/redo feature?", "") == 1 ? true : false;

    Stack undoStack;
    Stack redoStack;

    undoStack.init();
    redoStack.init();

    // Add first stack
    undoStack.push(gameplay);
    printFull(gameplay, undoStack, redoStack, user);

    // Set start point
    auto start_time = high_resolution_clock::now();

    // Set eternal playing mode
    bool eternal = false;

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

            if (gameOver(gameplay) && !eternal) {
                char choice = 'y';

                cout << "\n\tGame over. Do you want to continue playing? [Y/N]" << endl;
                
                cin >> choice;

                choice = tolower(choice);

                if (choice == 'y') {
                    eternal = true;
                    continue;
                } else {
                    cout << "\tGame ended!" << endl;
                    endGame(gameplay, undoStack, redoStack, start_time, user);
                    break;
                }
            } else if (gameWon(gameplay) && !eternal) {
                char choice = 'y';

                cout << "\n\tYou won at 2048. Do you want to continue playing? [Y/N]" << endl;
                
                cin >> choice;

                choice = tolower(choice);

                if (choice == 'y') {
                    eternal = true;
                    continue;
                } else {
                    cout << "\tGame ended!" << endl;
                    endGame(gameplay, undoStack, redoStack, start_time, user);
                    break;
                }
            }
            
        } else if (key == X) {
            cout << "\tGame ended!" << endl;
            endGame(gameplay, undoStack, redoStack, start_time, user);
            break;
        } else if (key == S) {
            cout << GREEN_TEXT << "\tGame saved!" << RESET_FORMAT << endl;
            saveBoard(gameplay, user);
            endGame(gameplay, undoStack, redoStack, start_time, user);
            break;
        } else if (key == U) {
            if (gameplay.canUndoRedo) {
                int state = undo(gameplay, undoStack, redoStack);
                printFull(gameplay, undoStack, redoStack, user);
                if (state == 0) {
                    cout << YELLOW_TEXT << "\tNo step to undo" << RESET_FORMAT << endl;
                }
            } else {
                printFull(gameplay, undoStack, redoStack, user);
                cout << YELLOW_TEXT << "\n\tUndo feature is disabled. Please start a new game and enable it!" << RESET_FORMAT << endl;            
            }
        } else if (key == R) {
            if (gameplay.canUndoRedo) {
                int state = redo(gameplay, undoStack, redoStack);
                printFull(gameplay, undoStack, redoStack, user);
                if (state == 0) {
                    cout << YELLOW_TEXT << "\tNo step to redo" << RESET_FORMAT << endl;
                }
            } else {
                printFull(gameplay, undoStack, redoStack, user);
                cout << YELLOW_TEXT << "\n\tRedo feature is disabled. Please start a new game and enable it!" << RESET_FORMAT << endl;            
            }
        }
    }
}
