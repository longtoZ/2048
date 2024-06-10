#include "handleRandom.h"

int ranIntTwoOrFour()
{
    srand(time(nullptr));
    return (int)(rand() % 10) % 2 == 0 ? 2 : 4;
}

int ranRange(int start, int end)
{
    srand(time(nullptr));
    return (int)(start + rand() % (end - start));
}

InitNumber ranNum()
{
    InitNumber in;

    // Generate 2 or 4
    srand(time(nullptr));

    in.num1 = (rand() % 10) < 8 ? 2 : 4;
    in.num2 = (rand() % 10) < 8 ? 2 : 4;

    return in;
}

Position ranPos(int n)
{
    Position p;

    int pos1, pos1_x, pos1_y, pos2, pos2_x, pos2_y;
    srand(time(nullptr));

    // Generate 2 random positions
    pos1 = rand() % (n * n - 1);
    pos2 = rand() % (n * n - 1);

    while (pos1 == pos2)
        pos2 = rand() % (n * n - 1);

    // Generate position in matrix
    pos1_x = pos1 / n;
    pos1_y = pos1 % n;

    pos2_x = pos2 / n;
    pos2_y = pos2 % n;

    // Update position
    p.pos1_x = pos1_x;
    p.pos1_y = pos1_y;
    p.pos2_x = pos2_x;
    p.pos2_y = pos2_y;

    return p;
}

void fillRandomNumber(Gameplay &gameplay)
{
    int n = gameplay.size;
    int **&board = gameplay.board;
    int **&emptyPos = gameplay.emptyPos;
    int &emptyLeft = gameplay.emptyLeft;

    int count = 0;

    // Update empty positions array
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == 0)
            {
                emptyPos[count][0] = i;
                emptyPos[count][1] = j;
                count++;
            }
        }
    }

    emptyLeft = count;

    // Find random empty position to add a new number
    int num = ranIntTwoOrFour();
    int randomPos = ranRange(0, emptyLeft);

    int randomPosX = emptyPos[randomPos][0];
    int randomPosY = emptyPos[randomPos][1];

    board[randomPosX][randomPosY] = num;
}