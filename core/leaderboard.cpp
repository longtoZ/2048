#include "leaderboard.h"
using namespace std;

string leftCellString(string str, int length)
{
    int rightSpaces = length - str.length() - 1;
    string s = " " + str + string(rightSpaces, ' ');

    return s;
}

string leftCellNumber(int n, int length)
{
    int nCopy = n;
    int count = n == 0 ? 1 : 0;
    while (nCopy > 0)
    {
        nCopy /= 10;
        count++;
    }

    int rightSpaces = length - count - 1;
    string s = " " + to_string(n) + string(rightSpaces, ' ');

    return s;
}

void storeBestScore(User &user)
{

    Data bestScore;
    bool gotBestScore = false;

    string fullPath = FILE_PATH + string(user.username) + "_achievement.bin";

    ifstream inputFile(fullPath, ios::binary);

    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open file '" << fullPath << "' for reading." << endl;
        return;
    }

    while (true)
    {

        char *date = new char[DATE_SIZE];
        int size;
        int score;
        int step;
        char *interval = new char[INTERVAL_SIZE];

        inputFile.read(date, DATE_SIZE);
        inputFile.read((char *)(&size), sizeof(size));
        inputFile.read((char *)(&score), sizeof(score));
        inputFile.read((char *)(&step), sizeof(step));
        inputFile.read(interval, INTERVAL_SIZE);

        if (inputFile.eof())
        {
            break;
        }

        if (score > bestScore.score)
        {
            bestScore.date = date;
            bestScore.size = size;
            bestScore.score = score;
            bestScore.step = step;
            bestScore.interval = interval;
            gotBestScore = true;
        }
    }

    inputFile.close();

    if (gotBestScore)
    {
        string bestFullPath = FILE_PATH + string(user.username) + "_best.bin";

        ofstream outputFile(bestFullPath, ios::binary);

        if (!outputFile.is_open())
        {
            cerr << "Error: Could not open file '" << bestFullPath << "' for writing." << endl;
            return;
        }

        outputFile.write(bestScore.date, DATE_SIZE);
        outputFile.write((char *)(&bestScore.size), sizeof(bestScore.size));
        outputFile.write((char *)(&bestScore.score), sizeof(bestScore.score));
        outputFile.write((char *)(&bestScore.step), sizeof(bestScore.step));
        outputFile.write(bestScore.interval, INTERVAL_SIZE);

        outputFile.close();
    }
}

Data getBestScore(User &user)
{
    Data bestScore;
    string fullPath = FILE_PATH + string(user.username) + "_best.bin";

    ifstream inputFile(fullPath, ios::binary);

    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open file '" << fullPath << "' for reading." << endl;
        return bestScore;
    }

    bestScore.date = new char[DATE_SIZE];
    bestScore.interval = new char[INTERVAL_SIZE];

    inputFile.read(bestScore.date, DATE_SIZE);
    inputFile.read((char *)(&bestScore.size), sizeof(bestScore.size));
    inputFile.read((char *)(&bestScore.score), sizeof(bestScore.score));
    inputFile.read((char *)(&bestScore.step), sizeof(bestScore.step));
    inputFile.read(bestScore.interval, INTERVAL_SIZE);

    inputFile.close();

    return bestScore;
}

void storeAchievement(int size, int score, int step, string elapsed_time, User &user)
{
    string fullPath = FILE_PATH + string(user.username) + "_achievement.bin";

    ofstream outFile(fullPath, ios::app | ios::binary);

    if (!outFile.is_open())
    {
        cerr << "Error: Could not open file '" << fullPath << "' for appending." << endl;
        return;
    }

    // Seek to the end of the file
    outFile.seekp(ios::end);

    // Write the new data
    char *date = convertStringToChar(getCurrentDateTime());
    char *interval = convertStringToChar(elapsed_time);

    outFile.write(date, DATE_SIZE);
    outFile.write((char *)(&size), sizeof(size));
    outFile.write((char *)(&score), sizeof(score));
    outFile.write((char *)(&step), sizeof(step));
    outFile.write(interval, INTERVAL_SIZE);

    // Check for errors after write
    if (!outFile.good())
    {
        std::cerr << "Error: Error writing data to file." << std::endl;
        outFile.close();
        return;
    }

    outFile.close();

    storeBestScore(user);
}

void deleteAchievement(User &user)
{
    string fullLdbPath = FILE_PATH + string(user.username) + "_achievement.bin";
    string fullBestPath = FILE_PATH + string(user.username) + "_best.bin";

    ofstream ldbFile;
    ldbFile.open(fullLdbPath, ofstream::out | ofstream::trunc);

    if (!ldbFile)
    {
        return;
    }

    // Delete stored achievement
    ldbFile.flush();
    ldbFile.close();

    // Clear best achievement
    ofstream bestFile;
    bestFile.open(fullBestPath, ofstream::out | ofstream::trunc);

    if (!bestFile)
    {
        return;
    }

    bestFile.flush();
    bestFile.close();
}

string getAchievement(User &user)
{
    string leaderBoard = "";
    List list;
    list.init();

    string fullPath = FILE_PATH + string(user.username) + "_achievement.bin";

    ifstream inputFile(fullPath, ios::binary);

    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open file '" << fullPath << "' for reading." << endl;
    }

    while (true)
    {
        Data data;

        data.username = new char[USERNAME_SIZE];
        data.date = new char[DATE_SIZE];
        data.size;
        data.score;
        data.step;
        data.interval = new char[INTERVAL_SIZE];

        strcpy(data.username, user.username);
        inputFile.read(data.date, DATE_SIZE);
        inputFile.read((char *)(&data.size), sizeof(data.size));
        inputFile.read((char *)(&data.score), sizeof(data.score));
        inputFile.read((char *)(&data.step), sizeof(data.step));
        inputFile.read(data.interval, INTERVAL_SIZE);

        if (inputFile.eof())
        {
            break;
        }

        list.insertTail(data);
    }

    inputFile.close();
    list.sort();

    ListNode *curr = list.head;

    leaderBoard += "\n\n";
    leaderBoard += "+--------------------------------------------------------------------------------+\n";
    leaderBoard += "|                                   ACHIEVEMENT                                  |\n";
    leaderBoard += "+------+----------------------+-----------+-----------+-----------+--------------+\n";
    leaderBoard += "| Rank |         Date         |   Size    |   Score   |   Steps   |   Interval   |\n";
    leaderBoard += "+------+----------------------+-----------+-----------+-----------+--------------+\n";

    for (int i = 0; i < list.size; i++)
    {
        string rank = leftCellNumber(i + 1, 6);
        string date = formatDateStr((curr->data).date);
        string size = leftCellString(to_string((curr->data).size) + "x" + to_string((curr->data).size), 11);
        string score = leftCellNumber((curr->data).score, 11);
        string step = leftCellNumber((curr->data).step, 11);
        string interval = convertCharToString((curr->data).interval);

        leaderBoard += "|" + rank + "| " + date + "  |" + size + "|" + score + "|" + step + "| " + interval + "        |\n";
        curr = curr->next;
    }

    leaderBoard += "+------+----------------------+-----------+-----------+-----------+--------------+\n";

    cleanList(list);

    return leaderBoard;
}

string getLeaderboard(User &user, int &rankOfUser, int scoreToHighlight)
{
    string leaderBoard = "";

    List list;
    list.init();

    ifstream userFile;
    userFile.open(USER_FILE_PATH, ios::binary);

    if (!userFile)
    {
        cerr << "Error: Could not open file '" << USER_FILE_PATH << "' for reading." << endl;
    }

    while (true)
    {
        // Get username
        char *username = new char[USERNAME_SIZE];
        char *password = new char[PASSWORD_SIZE];

        userFile.read(username, USERNAME_SIZE);
        userFile.read(password, PASSWORD_SIZE);

        if (userFile.eof())
        {
            break;
        }

        // Access best.txt of each user
        string fullPath = FILE_PATH + string(username) + "_best.bin";

        ifstream bestScoreFile;
        bestScoreFile.open(fullPath, ios::binary);

        if (!bestScoreFile)
        {
            cerr << "Error: Could not open file '" << fullPath << "' for reading." << endl;
        }

        Data bestScoreData;

        bestScoreData.username = username;
        bestScoreData.date = new char[DATE_SIZE];
        bestScoreData.size;
        bestScoreData.score;
        bestScoreData.step;
        bestScoreData.interval = new char[INTERVAL_SIZE];

        bestScoreFile.read(bestScoreData.date, DATE_SIZE);
        bestScoreFile.read((char *)(&bestScoreData.size), sizeof(bestScoreData.size));
        bestScoreFile.read((char *)(&bestScoreData.score), sizeof(bestScoreData.score));
        bestScoreFile.read((char *)(&bestScoreData.step), sizeof(bestScoreData.step));
        bestScoreFile.read(bestScoreData.interval, INTERVAL_SIZE);

        if (!bestScoreFile.eof())
        {
            list.insertTail(bestScoreData);
        }

        bestScoreFile.close();
    }

    userFile.close();
    list.sort();

    // Print the global leaderboard
    ListNode *curr = list.head;
    int listSize = list.size > 20 ? 20 : list.size;

    leaderBoard += "\n\n";
    leaderBoard += "+---------------------------------------------------------------------------------------------------+\n";
    leaderBoard += "|                                          TOP 20 LEADERBOARD                                       |\n";
    leaderBoard += "+------+------------------+----------------------+-----------+-----------+-----------+--------------+\n";
    leaderBoard += "| Rank |       User       |         Date         |   Size    |   Score   |   Steps   |   Interval   |\n";
    leaderBoard += "+------+------------------+----------------------+-----------+-----------+-----------+--------------+\n";

    for (int i = 0; i < listSize && curr != nullptr; i++)
    {
        string displaySize = to_string((curr->data).size) + "x" + to_string((curr->data).size);
        string rank = leftCellNumber(i + 1, 6);
        string username = leftCellString(convertCharToString((curr->data).username), 18);
        string date = formatDateStr((curr->data).date);
        string size = leftCellString(displaySize, 11);
        string score = leftCellNumber((curr->data).score, 11);
        string step = leftCellNumber((curr->data).step, 11);
        string interval = convertCharToString((curr->data).interval);

        if (user.username != nullptr && strcmp((curr->data).username, user.username) == 0 && (curr->data).score == scoreToHighlight)
        {
            rankOfUser = i + 1;
            leaderBoard += WHITE_BACKGROUND_COLOR BLACK_TEXT "|" + rank + "|" + username + "| " + date + "  |" + size + "|" + score + "|" + step + "| " + interval + "        |" RESET_FORMAT "\n";
        }
        else
        {
            leaderBoard += "|" + rank + "|" + username + "| " + date + "  |" + size + "|" + score + "|" + step + "| " + interval + "        |\n";
        }

        curr = curr->next;
    }

    leaderBoard += "+------+------------------+----------------------+-----------+-----------+-----------+--------------+\n";

    cleanList(list);

    return leaderBoard;
}