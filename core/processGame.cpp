#include "processGame.h"

void createBoard(Gameplay &gameplay)
{
    int n = gameplay.size;
    int **&board = gameplay.board;
    int **&emptyPos = gameplay.emptyPos;
    int &emptyLeft = gameplay.emptyLeft;

    // Generate 2 random positions and 2 random numbers
    Position p = ranPos(n);
    InitNumber in = ranNum();

    // Empty positions count
    int emptyCount = 0;

    // Insert number into board
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == p.pos1_x && j == p.pos1_y)
            {
                board[i][j] = in.num1;
                emptyLeft--;
            }
            else if (i == p.pos2_x && j == p.pos2_y)
            {
                board[i][j] = in.num2;
                emptyLeft--;
            }
            else
            {
                board[i][j] = 0;
                emptyPos[emptyCount][0] = i;
                emptyPos[emptyCount][1] = j;
                emptyCount++;
            }
        }
    }
}

void moveLeft(Gameplay &gameplay, int &moved)
{

    int n = gameplay.size;
    int **&board = gameplay.board;
    int &score = gameplay.score;

    for (int i = 0; i < n; i++)
    {

        // Use two pointers to traverse through the array and combine two same numbers
        int idx = 0;

        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == board[i][idx])
            {
                if (j != idx)
                {
                    board[i][idx] *= 2;
                    score += board[i][idx];
                    board[i][j] = 0;
                    idx = j + 1;
                    moved = 1;
                }
            }
            else
            {
                if (board[i][j] != 0)
                {
                    idx = j;
                }
            }
        }

        // Use two pointers to traverse and push non-zero numbers to the left
        int swapIdx = 0;
        int j = 0;

        while (j < n)
        {
            if (board[i][j] != 0)
            {
                if (swapIdx != j)
                {
                    int tmp = board[i][swapIdx];
                    board[i][swapIdx] = board[i][j];
                    board[i][j] = tmp;
                    moved = 1;
                }
                swapIdx++;
            }
            j++;
        }
    }
}

void moveRight(Gameplay &gameplay, int &moved)
{

    int n = gameplay.size;
    int **&board = gameplay.board;
    int &score = gameplay.score;

    for (int i = 0; i < n; i++)
    {

        // Use two pointers to traverse through the array and combine two same numbers
        int idx = n - 1;

        for (int j = n - 1; j >= 0; j--)
        {
            if (board[i][j] == board[i][idx])
            {
                if (j != idx)
                {
                    board[i][idx] *= 2;
                    score += board[i][idx];
                    board[i][j] = 0;
                    idx = j - 1;
                    moved = 1;
                }
            }
            else
            {
                if (board[i][j] != 0)
                {
                    idx = j;
                }
            }
        }

        // Use two pointers to traverse and push non-zero numbers to the right
        int swapIdx = n - 1;
        int j = n - 1;

        while (j >= 0)
        {
            if (board[i][j] != 0)
            {
                if (swapIdx != j)
                {
                    int tmp = board[i][swapIdx];
                    board[i][swapIdx] = board[i][j];
                    board[i][j] = tmp;
                    moved = 1;
                }
                swapIdx--;
            }
            j--;
        }
    }
}

void moveUp(Gameplay &gameplay, int &moved)
{

    int n = gameplay.size;
    int **&board = gameplay.board;
    int &score = gameplay.score;

    for (int j = 0; j < n; j++)
    {

        // Use two pointers to traverse through the array and combine two same numbers
        int idx = 0;

        for (int i = 0; i < n; i++)
        {
            if (board[i][j] == board[idx][j])
            {
                if (i != idx)
                {
                    board[idx][j] *= 2;
                    score += board[i][j];
                    board[i][j] = 0;
                    idx = i + 1;
                    moved = 1;
                }
            }
            else
            {
                if (board[i][j] != 0)
                {
                    idx = i;
                }
            }
        }

        // Use two pointers to traverse and push non-zero numbers to the top
        int swapIdx = 0;
        int i = 0;

        while (i < n)
        {
            if (board[i][j] != 0)
            {
                if (swapIdx != i)
                {
                    int tmp = board[swapIdx][j];
                    board[swapIdx][j] = board[i][j];
                    board[i][j] = tmp;
                    moved = 1;
                }
                swapIdx++;
            }
            i++;
        }
    }
}

void moveDown(Gameplay &gameplay, int &moved)
{

    int n = gameplay.size;
    int **&board = gameplay.board;
    int &score = gameplay.score;

    for (int j = 0; j < n; j++)
    {

        // Use two pointers to traverse through the array and combine two same numbers
        int idx = n - 1;

        for (int i = n - 1; i >= 0; i--)
        {
            if (board[i][j] == board[idx][j])
            {
                if (i != idx)
                {
                    board[idx][j] *= 2;
                    score += board[idx][j];
                    board[i][j] = 0;
                    idx = i - 1;
                    moved = 1;
                }
            }
            else
            {
                if (board[i][j] != 0)
                {
                    idx = i;
                }
            }
        }

        // Use two pointers to traverse and push non-zero numbers to the bottom
        int swapIdx = n - 1;
        int i = n - 1;

        while (i >= 0)
        {
            if (board[i][j] != 0)
            {
                if (swapIdx != i)
                {
                    int tmp = board[swapIdx][j];
                    board[swapIdx][j] = board[i][j];
                    board[i][j] = tmp;
                    moved = 1;
                }
                swapIdx--;
            }
            i--;
        }
    }
}

void endGame(Gameplay &gameplay, Stack &undoStack, Stack &redoStack, User &user)
{
    // Calculate elapsed time with startTime and saved extraTime
    milliseconds extraTime(gameplay.duration);
    string elapsed_time = calculateElapsedTimeString(convertLongToTime(gameplay.startTime), extraTime);

    char choice = 'y';
    cout << setLeftAlignSize() << YELLOW_TEXT << "Game ended. Do you want to store the current achievement? [Y/N] " << RESET_FORMAT;

    cin >> choice;

    choice = tolower(choice);

    if (choice == 'y')
    {
        // Store achievement
        storeAchievement(gameplay.size, gameplay.score, gameplay.step, elapsed_time, user);
        cout << setLeftAlignSize() << GREEN_TEXT << "Achievement saved. Press any key to go back to menu." << RESET_FORMAT;
        getch();
    }

    // Clean up used linked lists and pointers
    cleanBoard(gameplay);
    cleanEmptyPos(gameplay);
    cleanStack(undoStack);
    cleanStack(redoStack);
}

bool gameOver(Gameplay &gameplay)
{

    int n = gameplay.size;
    int **&board = gameplay.board;

    // Compare all numbers with surrounding ones, if there is no same number -> Game over
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == 0)
            {
                return false;
            }
            else
            {
                if (i < n - 1 && board[i][j] == board[i + 1][j])
                {
                    return false;
                }

                if (j < n - 1 && board[i][j] == board[i][j + 1])
                {
                    return false;
                }
            }
        }
    }

    return true;
}

bool gameWon(Gameplay &gameplay)
{
    int n = gameplay.size;
    int **&board = gameplay.board;

    // If there is a cell with value 2048 -> Game won
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == 2048)
            {
                return true;
            }
        }
    }

    return false;
}

int undo(Gameplay &gameplay, Stack &undoStack, Stack &redoStack)
{
    if (!undoStack.empty() && (undoStack.head)->next != nullptr)
    {

        // Push stack from undoStack to redoStack
        Gameplay next = undoStack.top();
        undoStack.pop();
        redoStack.push(next);

        // Set current gameplay with the top stack of undoStack
        Gameplay prev = undoStack.top();

        for (int i = 0; i < prev.size; i++)
        {
            for (int j = 0; j < prev.size; j++)
            {
                gameplay.board[i][j] = prev.board[i][j];
            }
        }

        for (int i = 0; i < prev.emptyLeft; i++)
        {
            gameplay.emptyPos[i][0] = prev.emptyPos[i][0];
            gameplay.emptyPos[i][1] = prev.emptyPos[i][1];
        }

        gameplay.size = prev.size;
        gameplay.emptyLeft = prev.emptyLeft;
        gameplay.score = prev.score;
        gameplay.size = prev.size;
        gameplay.step = prev.step;

        return 1;
    }
    else
    {
        return 0;
    }
}

int redo(Gameplay &gameplay, Stack &undoStack, Stack &redoStack)
{
    if (!redoStack.empty())
    {

        // Push stack from redoStack to undoStack
        Gameplay prev = redoStack.top();
        redoStack.pop();
        undoStack.push(prev);

        // Set current gameplay with the top stack of undoStack
        Gameplay next = undoStack.top();

        for (int i = 0; i < next.size; i++)
        {
            for (int j = 0; j < next.size; j++)
            {
                gameplay.board[i][j] = next.board[i][j];
            }
        }

        for (int i = 0; i < next.emptyLeft; i++)
        {
            gameplay.emptyPos[i][0] = next.emptyPos[i][0];
            gameplay.emptyPos[i][1] = next.emptyPos[i][1];
        }

        gameplay.size = next.size;
        gameplay.emptyLeft = next.emptyLeft;
        gameplay.score = next.score;
        gameplay.size = next.size;
        gameplay.step = next.step;

        return 1;
    }
    else
    {
        return 0;
    }
}