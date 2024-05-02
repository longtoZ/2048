#include "leaderboard.h"
using namespace std;

#define FILE_PATH "./database/user/"
#define USER_FILE_PATH "./database/user.txt"

string leftCellString(string str, int length) {
    int rightSpaces = length - str.length() - 1;
    string s = " " + str + string(rightSpaces, ' ');

    return s;
}

string leftCellNumber(int n, int length) {
    int nCopy = n;
    int count = n == 0 ? 1 : 0;
    while (nCopy > 0) {
        nCopy /= 10;
        count++;
    }

    int rightSpaces = length-count-1;
    string s = " " + to_string(n) + string(rightSpaces, ' ');

    return s;
}

void storeAchievement(int size, int score, int step, string elapsed_time, User &user) {
    string fullPath = FILE_PATH + user.username + "/leaderboard.txt";

    ofstream ofile;
    ofile.open(fullPath, ios::app);

    if (!ofile) {
        return;
    }

    string data = getCurrentDateTime() + " " + to_string(size) + " " + to_string(score) + " " + to_string(step) + " " + elapsed_time + "\n";
    ofile << data;

    ofile.close();

    storeBestScore(user);
}

void deleteAchievement(User &user) {
    string fullLdbPath = FILE_PATH + user.username + "/leaderboard.txt";
    string fullBestPath = FILE_PATH + user.username + "/best.txt";

    // Clear all achievement
    ofstream ldbFile;
    ldbFile.open(fullLdbPath, ofstream::out | ofstream::trunc);

    if (!ldbFile) {
        return;
    }

    ldbFile.flush();
    ldbFile.close();

    // Clear best achievement
    ofstream bestFile;
    bestFile.open(fullBestPath, ofstream::out | ofstream::trunc);

    if (!bestFile) {
        return;
    }

    bestFile.flush();
    bestFile.close();

}

void getAchievement(User &user) {
    List list;

    list.init();

    string fullPath = FILE_PATH + user.username + "/leaderboard.txt";

    string line;
    ifstream ifile;
    ifile.open(fullPath);

    if (!ifile) {
        return;
    }

    printf("\t+--------------------------------------------------------------------------------+\n");
    printf("\t|                                   ACHIEVEMENT                                  |\n");
    printf("\t+------+----------------------+-----------+-----------+-----------+--------------+\n");
    printf("\t| Rank |         Date         |   Size    |   Score   |   Steps   |   Interval   |\n");
    printf("\t+------+----------------------+-----------+-----------+-----------+--------------+\n");

    while (getline(ifile, line)) {

        Data data;

        // Parse date
        string day = line.substr(0,2);
        string month = line.substr(2,2);
        string year = line.substr(4,4);

        string hour = line.substr(9,2);
        string minute = line.substr(11,2);
        string second = line.substr(13,2);

        string date = day + "-" + month + "-" + year + " " + hour + ":" + minute + ":" + second;

        int first_space = line.find(' ', 0);
        int second_space = line.find(' ', first_space+1);
        int third_space = line.find(' ', second_space+1);
        int fourth_space = line.find(' ', third_space+1);

        // Parse size
        int size = stoi(line.substr(first_space+1, second_space-first_space-1));

        // Parse score
        int score = stoi(line.substr(second_space+1, third_space-second_space-1));

        // Parse step
        int step = stoi(line.substr(third_space+1, second_space-third_space-1));

        // Parse interval
        string interval = line.substr(fourth_space+1, line.length()-fourth_space-1);

        data.date = date;
        data.size = size;
        data.score = score;
        data.step = step;
        data.interval = interval;

        list.insertTail(data);

    }

    ifile.close();
    list.sort();

    ListNode* &curr = list.head;

    for (int i=0; i<list.size; i++) {
        const char* rank = convertStringToChar(leftCellNumber(i+1, 6));
        const char* date = convertStringToChar((curr->data).date);
        const char* size = convertStringToChar(leftCellString(to_string((curr->data).size) + "x" + to_string((curr->data).size), 11));
        const char* score = convertStringToChar(leftCellNumber((curr->data).score, 11));
        const char* step = convertStringToChar(leftCellNumber((curr->data).step, 11));
        const char* interval = convertStringToChar((curr->data).interval);

        curr = curr->next;

        printf("\t|%s| %s  |%s|%s|%s| %s        |\n", rank, date, size, score, step, interval);

    }
    printf("\t+------+----------------------+-----------+-----------+-----------+--------------+\n");

    cleanList(list);
}

void getLeaderboard() {
    List list;
    list.init();

    string line = "";
    ifstream userFile;
    userFile.open(USER_FILE_PATH);

    if (!userFile) return;

    printf("\t+---------------------------------------------------------------------------------------------------+\n");
    printf("\t|                                          TOP 10 LEADERBOARD                                       |\n");
    printf("\t+------+------------------+----------------------+-----------+-----------+-----------+--------------+\n");
    printf("\t| Rank |       User       |         Date         |   Size    |   Score   |   Steps   |   Interval   |\n");
    printf("\t+------+------------------+----------------------+-----------+-----------+-----------+--------------+\n");

    while (getline(userFile, line)) {
        // Get username
        string username = line.substr(0, line.find(' ', 0));

        Data data;

        // Access best.txt of each user
        string fullPath = FILE_PATH + username + "/best.txt";
        string bestScoreLine = "";

        ifstream bestScoreFile;
        bestScoreFile.open(fullPath);

        if (!bestScoreFile) return;

        getline(bestScoreFile, bestScoreLine);
        bestScoreFile.close();

        if (bestScoreLine != "") {
            // Parse date
            string day = bestScoreLine.substr(0,2);
            string month = bestScoreLine.substr(2,2);
            string year = bestScoreLine.substr(4,4);

            string hour = bestScoreLine.substr(9,2);
            string minute = bestScoreLine.substr(11,2);
            string second = bestScoreLine.substr(13,2);

            string date = day + "-" + month + "-" + year + " " + hour + ":" + minute + ":" + second;

            int first_space = bestScoreLine.find(' ', 0);
            int second_space = bestScoreLine.find(' ', first_space+1);
            int third_space = bestScoreLine.find(' ', second_space+1);
            int fourth_space = bestScoreLine.find(' ', third_space+1);

            // Parse size
            int size = stoi(bestScoreLine.substr(first_space+1, second_space-first_space-1));

            // Parse score
            int score = stoi(bestScoreLine.substr(second_space+1, third_space-second_space-1));

            // Parse step
            int step = stoi(bestScoreLine.substr(third_space+1, second_space-third_space-1));

            // Parse interval
            string interval = bestScoreLine.substr(fourth_space+1, bestScoreLine.length()-fourth_space-1);

            data.username = username;
            data.date = date;
            data.size = size;
            data.score = score;
            data.step = step;
            data.interval = interval;

            list.insertTail(data);
        }


    }

    userFile.close();
    list.sort();

    // Print the global leaderboard
    ListNode* &curr = list.head;
    int listSize = list.size > 10 ? 10 : list.size;

    for (int i=0; i<listSize; i++) {
        string displaySize = to_string((curr->data).size) + "x" + to_string((curr->data).size);

        const char* rank = convertStringToChar(leftCellNumber(i+1, 6));
        const char* username = convertStringToChar(leftCellString((curr->data).username, 18));
        const char* date = convertStringToChar((curr->data).date);
        const char* size = convertStringToChar(leftCellString(displaySize, 11));
        const char* score = convertStringToChar(leftCellNumber((curr->data).score, 11));
        const char* step = convertStringToChar(leftCellNumber((curr->data).step, 11));
        const char* interval = convertStringToChar((curr->data).interval);

        curr = curr->next;

        printf("\t|%s|%s| %s  |%s|%s|%s| %s        |\n", rank, username, date, size, score, step, interval);

    }
    printf("\t+------+------------------+----------------------+-----------+-----------+-----------+--------------+\n");

    cleanList(list);
}