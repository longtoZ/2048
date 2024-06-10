#include "continueGame.h"
using namespace std;

void saveBoard(Gameplay &gameplay, User &user)
{
    int **&board = gameplay.board;
    int &score = gameplay.score;
    int &step = gameplay.step;
    int &n = gameplay.size;
    long long duration = gameplay.duration + calculateDurationInMilliseconds(gameplay.startTime);

    string fullPath = FILE_PATH + string(user.username) + "_prevboard.bin";

    ofstream ofile;
    ofile.open(fullPath, ios::binary);

    if (!ofile.is_open())
    {
        cerr << "Error: Cannot open file " << fullPath << endl;
    }

    // Save duration, score, step and size
    ofile.write((char *)&duration, sizeof(duration));
    ofile.write((char *)&score, sizeof(score));
    ofile.write((char *)&step, sizeof(step));
    ofile.write((char *)&n, sizeof(n));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            ofile.write((char *)&board[i][j], sizeof(board[i][j]));
        }
    }

    ofile.close();
}

void getPrevBoard(Gameplay &gameplay, User &user)
{
    string line;
    long long duration = 0;
    int n = 0, score = 0, step = 0;

    // Initialize size for board
    gameplay.size = 0;

    string fullPath = FILE_PATH + string(user.username) + "_prevboard.bin";

    ifstream ifile;
    ifile.open(fullPath, ios::binary);

    if (!ifile.is_open())
    {
        cerr << "Error: Cannot open file " << fullPath << endl;
    }

    // Get duration, score, step and size
    ifile.read((char *)&duration, sizeof(duration));

    if (ifile.eof())
    {
        cout << setLeftAlignSize() << "No previous game found!" << endl;
        return;
    }

    ifile.read((char *)&score, sizeof(score));
    ifile.read((char *)&step, sizeof(step));
    ifile.read((char *)&n, sizeof(n));

    // Generate board
    gameplay.size = n;
    gameplay.emptyLeft = gameplay.size * gameplay.size;
    gameplay.board = createEmptyBoard(gameplay.size);
    gameplay.emptyPos = createEmptyPos(gameplay.emptyLeft);
    gameplay.score = score;
    gameplay.step = step;
    gameplay.duration = duration;
    int emptyCount = 0;

    // Insert data into board
    int num;
    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < n; j++)
        {
            ifile.read((char *)&num, sizeof(num));

            if (num == 0)
            {
                gameplay.emptyPos[emptyCount][0] = i;
                gameplay.emptyPos[emptyCount][1] = j;
                emptyCount++;
            }
            else
            {
                gameplay.emptyLeft--;
            }

            gameplay.board[i][j] = num;
        }
    }

    ifile.close();
}