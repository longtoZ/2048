#include "continueGame.h"
using namespace std;

#define FILE_PATH "./database/user/"

void saveBoard(Gameplay &gameplay, User &user) {
    int** &board = gameplay.board;
    int &score = gameplay.score;
    int &step = gameplay.step;
    int &n = gameplay.size;

    string fullPath = FILE_PATH + user.username + "/prevboard.txt";

    ofstream ofile;
    ofile.open(fullPath);

    if (!ofile) {
        return;
    }

    ofile << to_string(score) + "\n";
    ofile << to_string(step) + "\n";
    ofile << to_string(n) + "\n";

    for (int i=0; i<n; i++) {
        string line = "";
        for (int j=0; j<n; j++) {
            line += to_string(board[i][j]) + " ";
        }
        line += "\n";

        ofile << line;
    }

    ofile.close();
}

void getPrevBoard(Gameplay &gameplay, User &user) {
    string line;
    int n = 0, score = 0, step = 0;

    // Initialize size for board
    gameplay.size = 0;

    string fullPath = FILE_PATH + user.username + "/prevboard.txt";

    ifstream ifile;
    ifile.open(fullPath);

    if (!ifile) {
        return;
    }

    // Get score, step and size
    getline(ifile, line);

    // Check if file is empty
    if (line == "")
        return;

    score = stoi(line);
    getline(ifile, line);
    step = stoi(line);
    getline(ifile, line);
    n = stoi(line);

    // Generate board
    gameplay.size = n;
    gameplay.emptyLeft = gameplay.size*gameplay.size;
    gameplay.board = createEmptyBoard(gameplay.size);
    gameplay.emptyPos = createEmptyPos(gameplay.emptyLeft);
    gameplay.score = score;
    gameplay.step = step;
    int emptyCount = 0;

    // Insert data into board
    for (int i=0; i<n; i++) {
        getline(ifile, line);

        int start = 0;
        int end = line.find(' ', start);

        for (int j=0; j<n; j++) {
            int num = stoi(line.substr(start, end-start));

            if (num == 0) {
                gameplay.emptyPos[emptyCount][0] = i;
                gameplay.emptyPos[emptyCount][1] = j;
                emptyCount++;
            } else {
                gameplay.emptyLeft--;
            }

            gameplay.board[i][j] = num;

            start = end + 1;
            end = line.find(' ', start);
        }
    }

    ifile.close();

}