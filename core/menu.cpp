#include "menu.h"
using namespace std;

int userMenu()
{
    return printUserMenu();
}

int startMenu(User &user)
{
    return printStartMenu(user);
}

void startGame(Gameplay &gameplay, User &user)
{

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
        "Disable"};

    int size = generateSelections(boardSizeOptions, 7, "Choose board size (4x4, 5x5, ..., NxN): ", "") + 3;
    gameplay.canUndoRedo = generateSelections(undoRedoSelections, 2, "Use undo/redo feature?", "") == 1 ? true : false;

    gameStartPopup(10);

    int moved = 0;

    gameplay.size = size;
    gameplay.emptyLeft = gameplay.size * gameplay.size;
    gameplay.board = createEmptyBoard(gameplay.size);
    gameplay.emptyPos = createEmptyPos(gameplay.emptyLeft);
    gameplay.score = 0;
    gameplay.step = 0;
    gameplay.startTime = convertTimeToLong(high_resolution_clock::now());

    // Set up undo and redo stacks
    Stack undoStack;
    Stack redoStack;
    undoStack.init();
    redoStack.init();

    // Create board
    createBoard(gameplay);

    // Add first stack
    undoStack.push(gameplay);
    system("cls");
    printFull(gameplay, undoStack, redoStack, user);

    // Set eternal playing mode
    bool eternal = false;

    while (true)
    {
        key = getch();

        if (key == 224)
        {
            key = getch();
            moved = 0;

            if (key == KEYUP)
            {
                moveUp(gameplay, moved);
            }
            else if (key == KEYDOWN)
            {
                moveDown(gameplay, moved);
            }
            else if (key == KEYLEFT)
            {
                moveLeft(gameplay, moved);
            }
            else if (key == KEYRIGHT)
            {
                moveRight(gameplay, moved);
            }

            // Only fill random number if player moved
            if (moved == 1)
            {
                fillRandomNumber(gameplay);
                undoStack.push(gameplay);

                // Empty redoStack when player starts adding new moves
                if (!redoStack.empty())
                {
                    getch();
                    cleanStack(redoStack);
                }

                gameplay.step += 1;
            }

            printFull(gameplay, undoStack, redoStack, user);

            if (gameOver(gameplay) && !eternal)
            {
                // Game over popup
                gameOverPopup(10);
                printFull(gameplay, undoStack, redoStack, user);

                char choice = 'y';

                cout << endl;
                cout << setLeftAlignSize() << "Game over. Do you want to continue playing? [Y/N] ";

                cin >> choice;

                choice = tolower(choice);
                if (choice == 'y')
                {
                    eternal = true;
                    cout << setLeftAlignSize() << GREEN_TEXT << "Use undo to continue playing!" << RESET_FORMAT << endl;
                }
                else
                {
                    cout << setLeftAlignSize() << "Game ended!" << endl;
                    endGame(gameplay, undoStack, redoStack, user);
                    break;
                }
            }
            else if (gameWon(gameplay) && !eternal)
            {
                // Game won popup
                gameWonPopup(10);
                printFull(gameplay, undoStack, redoStack, user);

                storeAchievement(gameplay.size, gameplay.score, gameplay.step, calculateElapsedTimeString(convertLongToTime(gameplay.startTime)), user);

                char choice = 'y';
                int rankOfUser = -1;

                // Print leaderboard
                string leaderboard = getLeaderboard(user, rankOfUser, gameplay.score);
                stringstream ss(leaderboard);
                string line;

                while (getline(ss, line, '\n'))
                {
                    int lineLength = replaceAllRegex(line).length();
                    cout << setCenterAlignSize(lineLength) << line << endl;
                }

                if (rankOfUser != -1)
                {
                    cout << endl;
                    cout << setLeftAlignSize() << "You won at 2048. You rank is " << rankOfUser << "\n"
                         << setLeftAlignSize() << "Do you want to continue playing? [Y/N] ";
                }
                else
                {
                    cout << endl;
                    cout << setLeftAlignSize() << "You won at 2048. But you are not in top 20. Do you want to continue playing? [Y/N] ";
                }

                cin >> choice;

                choice = tolower(choice);

                if (choice == 'y')
                {
                    eternal = true;
                    cout << setLeftAlignSize() << GREEN_TEXT << "Press arrow keys to continue playing!" << RESET_FORMAT << endl;
                }
                else
                {
                    cout << setLeftAlignSize() << "Game ended!" << endl;
                    endGame(gameplay, undoStack, redoStack, user);
                    break;
                }
            }
        }
        // Exit game
        else if (key == X_key)
        {
            cout << setLeftAlignSize() << "Game ended!" << endl;
            endGame(gameplay, undoStack, redoStack, user);
            break;
        }
        // Save game
        else if (key == S)
        {
            cout << setLeftAlignSize() << GREEN_TEXT << "Game saved!" << RESET_FORMAT << endl;
            saveBoard(gameplay, user);
            endGame(gameplay, undoStack, redoStack, user);
            break;
        }
        // Undo
        else if (key == U)
        {
            if (gameplay.canUndoRedo)
            {
                int state = undo(gameplay, undoStack, redoStack);
                printFull(gameplay, undoStack, redoStack, user);
                if (state == 0)
                {
                    cout << setLeftAlignSize() << YELLOW_TEXT << "No step to undo" << RESET_FORMAT << endl;
                }
            }
            else
            {
                printFull(gameplay, undoStack, redoStack, user);
                cout << endl
                     << setLeftAlignSize() << YELLOW_TEXT << "Undo feature is disabled. Please start a new game and enable it!" << RESET_FORMAT << endl;
            }
        }
        // Redo
        else if (key == R)
        {
            if (gameplay.canUndoRedo)
            {
                int state = redo(gameplay, undoStack, redoStack);
                printFull(gameplay, undoStack, redoStack, user);
                if (state == 0)
                {
                    cout << setLeftAlignSize() << YELLOW_TEXT << "No step to redo" << RESET_FORMAT << endl;
                }
            }
            else
            {
                printFull(gameplay, undoStack, redoStack, user);
                cout << endl
                     << setLeftAlignSize() << YELLOW_TEXT << "Redo feature is disabled. Please start a new game and enable it!" << RESET_FORMAT << endl;
            }
        }
    }
}

void startPrevGame(Gameplay &gameplay, User &user)
{

    int key = 0;
    int moved = 0;

    getPrevBoard(gameplay, user);

    // Check for saved game
    if (gameplay.size == 0)
    {
        cout << setLeftAlignSize() << YELLOW_TEXT << "No saved game. Press any key to go to menu..." << RESET_FORMAT << endl;
        getch();
        return;
    }

    // Set up game
    string undoRedoSelections[] = {
        "Enable",
        "Disable"};

    gameplay.canUndoRedo = generateSelections(undoRedoSelections, 2, "Use undo/redo feature?", "") == 1 ? true : false;
    gameplay.startTime = convertTimeToLong(high_resolution_clock::now());

    // Set up undo and redo stacks
    Stack undoStack;
    Stack redoStack;
    undoStack.init();
    redoStack.init();

    // Add first stack
    undoStack.push(gameplay);
    printFull(gameplay, undoStack, redoStack, user);

    // Set eternal playing mode
    bool eternal = false;

    while (true)
    {
        key = getch();

        if (key == 224)
        {
            key = getch();
            moved = 0;

            if (key == KEYUP)
            {
                moveUp(gameplay, moved);
            }
            else if (key == KEYDOWN)
            {
                moveDown(gameplay, moved);
            }
            else if (key == KEYLEFT)
            {
                moveLeft(gameplay, moved);
            }
            else if (key == KEYRIGHT)
            {
                moveRight(gameplay, moved);
            }

            // Only fill random number if player moved
            if (moved == 1)
            {
                fillRandomNumber(gameplay);
                undoStack.push(gameplay);

                // Empty redoStack when player starts adding new moves
                if (!redoStack.empty())
                {
                    cleanStack(redoStack);
                }

                gameplay.step += 1;
            }

            printFull(gameplay, undoStack, redoStack, user);

            if (gameOver(gameplay) && !eternal)
            {
                gameOverPopup(10);
                printFull(gameplay, undoStack, redoStack, user);

                char choice = 'y';

                cout << endl;
                cout << setLeftAlignSize() << "Game over. Do you want to continue playing? [Y/N] ";

                cin >> choice;

                choice = tolower(choice);
                if (choice == 'y')
                {
                    eternal = true;
                    cout << setLeftAlignSize() << GREEN_TEXT << "Use undo to continue playing!" << RESET_FORMAT << endl;

                }
                else
                {
                    cout << setLeftAlignSize() << "Game ended!" << endl;
                    endGame(gameplay, undoStack, redoStack, user);
                    break;
                }
            }
            else if (gameWon(gameplay) && !eternal)
            {
                // Game won popup
                gameWonPopup(10);
                printFull(gameplay, undoStack, redoStack, user);

                // Calculate elapsed time with startTime and saved extraTime
                milliseconds extraTime(gameplay.duration);
                storeAchievement(gameplay.size, gameplay.score, gameplay.step, calculateElapsedTimeString(convertLongToTime(gameplay.startTime), extraTime), user);

                char choice = 'y';
                int rankOfUser = -1;

                // Print leaderboard
                string leaderboard = getLeaderboard(user, rankOfUser, gameplay.score);
                stringstream ss(leaderboard);
                string line;

                while (getline(ss, line, '\n'))
                {
                    int lineLength = replaceAllRegex(line).length();
                    cout << setCenterAlignSize(lineLength) << line << endl;
                }

                if (rankOfUser != -1)
                {
                    cout << endl;
                    cout << setLeftAlignSize() << "You won at 2048. You rank is " << rankOfUser << "\n"
                         << setLeftAlignSize() << "Do you want to continue playing? [Y/N] ";
                }
                else
                {
                    cout << endl;
                    cout << setLeftAlignSize() << "You won at 2048. But you are not in top 20. Do you want to continue playing? [Y/N] ";
                }

                cin >> choice;

                choice = tolower(choice);

                if (choice == 'y')
                {
                    eternal = true;
                    cout << setLeftAlignSize() << GREEN_TEXT << "Press arrow keys to continue playing!" << RESET_FORMAT << endl;
                }
                else
                {
                    cout << setLeftAlignSize() << "Game ended!" << endl;
                    endGame(gameplay, undoStack, redoStack, user);
                    break;
                }
            }
        }
        else if (key == X_key)
        {
            cout << setLeftAlignSize() << "Game ended!" << endl;
            endGame(gameplay, undoStack, redoStack, user);
            break;
        }
        else if (key == S)
        {
            cout << setLeftAlignSize() << GREEN_TEXT << "Game saved!" << RESET_FORMAT << endl;
            saveBoard(gameplay, user);
            endGame(gameplay, undoStack, redoStack, user);
            break;
        }
        else if (key == U)
        {
            if (gameplay.canUndoRedo)
            {
                int state = undo(gameplay, undoStack, redoStack);
                printFull(gameplay, undoStack, redoStack, user);
                if (state == 0)
                {
                    cout << setLeftAlignSize() << YELLOW_TEXT << "No step to undo" << RESET_FORMAT << endl;
                }
            }
            else
            {
                printFull(gameplay, undoStack, redoStack, user);
                cout << endl
                     << setLeftAlignSize() << YELLOW_TEXT << "Undo feature is disabled. Please start a new game and enable it!" << RESET_FORMAT << endl;
            }
        }
        else if (key == R)
        {
            if (gameplay.canUndoRedo)
            {
                int state = redo(gameplay, undoStack, redoStack);
                printFull(gameplay, undoStack, redoStack, user);
                if (state == 0)
                {
                    cout << setLeftAlignSize() << YELLOW_TEXT << "No step to redo" << RESET_FORMAT << endl;
                }
            }
            else
            {
                printFull(gameplay, undoStack, redoStack, user);
                cout << endl
                     << setLeftAlignSize() << YELLOW_TEXT << "Redo feature is disabled. Please start a new game and enable it!" << RESET_FORMAT << endl;
            }
        }
    }
}