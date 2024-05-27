#include "continueGame.h"
using namespace std;

#define FILE_PATH "./database/user/"

void saveBoard(Gameplay &gameplay, User &user) {
    int** &board = gameplay.board;
    int &score = gameplay.score;
    int &step = gameplay.step;
    int &n = gameplay.size;

    string fullPath = FILE_PATH + string(user.username) + "/prevboard.bin";

    ofstream ofile;
    ofile.open(fullPath, ios::binary);

    if (!ofile.is_open()) {
        cerr << "Error: Cannot open file " << fullPath << endl;
    }

    // Save score, step and size
    ofile.write((char*)&score, sizeof(score));
    ofile.write((char*)&step, sizeof(step));
    ofile.write((char*)&n, sizeof(n));

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            ofile.write((char*)&board[i][j], sizeof(board[i][j]));
        }
    }

    ofile.close();
}

void getPrevBoard(Gameplay &gameplay, User &user) {
    string line;
    int n = 0, score = 0, step = 0;

    // Initialize size for board
    gameplay.size = 0;

    string fullPath = FILE_PATH + string(user.username) + "/prevboard.bin";

    ifstream ifile;
    ifile.open(fullPath, ios::binary);

    if (!ifile.is_open()) {
        cerr << "Error: Cannot open file " << fullPath << endl;
    }

    // Get score, step and size
    ifile.read((char*)&score, sizeof(score));

    if (ifile.eof()) {
        cout << "No previous game found!" << endl;
        return;
    }

    ifile.read((char*)&step, sizeof(step));
    ifile.read((char*)&n, sizeof(n));

    // Generate board
    gameplay.size = n;
    gameplay.emptyLeft = gameplay.size*gameplay.size;
    gameplay.board = createEmptyBoard(gameplay.size);
    gameplay.emptyPos = createEmptyPos(gameplay.emptyLeft);
    gameplay.score = score;
    gameplay.step = step;
    int emptyCount = 0;

    // Insert data into board
    int num;
    for (int i=0; i<n; i++) {

        for (int j=0; j<n; j++) {
            ifile.read((char*)&num, sizeof(num));

            if (num == 0) {
                gameplay.emptyPos[emptyCount][0] = i;
                gameplay.emptyPos[emptyCount][1] = j;
                emptyCount++;
            } else {
                gameplay.emptyLeft--;
            }

            gameplay.board[i][j] = num;
        }
    }

    ifile.close();

}