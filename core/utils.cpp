#include "utils.h"

#define FILE_PATH "./database/user/"

int** createEmptyBoard(int n) {
    int** board = new int*[n];

    for (int i=0; i<n; i++) {
        board[i] = new int[n];
    }

    return board;
}

int** createEmptyPos(int n) {
    int** emptyPos = new int*[n];

    for (int i=0; i<n; i++) {
        emptyPos[i] = new int[2];
    }

    return emptyPos;

}

string getCurrentDateTime() {
    // Get current time
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    
    // Format time
    stringstream ss;
    ss << put_time(localtime(&now_time), "%d%m%Y_%H%M%S");
    return ss.str();
}

char* convertStringToChar(const string& str) {
    char* charArray = new char[str.length() + 1];
    strcpy(charArray, str.c_str());
    return charArray;
}

bool compareByScore(const Data &a, const Data &b) {
    return (a.score > b.score);
}

void storeBestScore(User &user) {

    Data bestScore;
    string line = "";
    bool gotBestScore = false;

    string fullPath = FILE_PATH + user.username + "/leaderboard.txt";

    ifstream ifile;
    ifile.open(fullPath);

    if (!ifile) {
        return;
    }
    
    while (getline(ifile, line)) {
        int first_space = line.find(' ', 0);
        int second_space = line.find(' ', first_space+1);
        int third_space = line.find(' ', second_space+1);
        int fourth_space = line.find(' ', third_space+1);

        // Parse date
        string date = line.substr(0, first_space);

        // Parse size
        int size = stoi(line.substr(first_space+1, second_space-first_space-1));

        // Parse score
        int score = stoi(line.substr(second_space+1, third_space-second_space-1));

        // Parse step
        int step = stoi(line.substr(third_space+1, second_space-third_space-1));

        // Parse interval
        string interval = line.substr(fourth_space+1, line.length()-fourth_space-1);

        if (score > bestScore.score) {
            bestScore.date = date;
            bestScore.size = size;
            bestScore.score = score;
            bestScore.step = step;
            bestScore.interval = interval;
            gotBestScore = true;
        }
    }

    ifile.close();

    if (gotBestScore) {
        string bestFullPath= FILE_PATH + user.username + "/best.txt";

        ofstream ofile;
        ofile.open(bestFullPath);

        ofile << bestScore.date << " " << bestScore.size << " " << bestScore.score << " " << bestScore.step << " " << bestScore.interval << endl;

        ofile.close();
    }

}   

Data getBestScore(User &user) {
    Data bestScore;
    string line = "";
    string fullPath = FILE_PATH + user.username + "/best.txt";

    ifstream ifile;
    ifile.open(fullPath);

    if (!ifile) {
        return bestScore;
    }

    getline(ifile, line);
    ifile.close();

    if (line != "") {

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

        bestScore.date = date;
        bestScore.size = size;
        bestScore.score = score;
        bestScore.step = step;
        bestScore.interval = interval;

    }

    return bestScore;

}


string calculate_elapsed_time_string(const high_resolution_clock::time_point& start_time) {
  // Get the ending time
  auto end_time = high_resolution_clock::now();

  // Calculate elapsed time in seconds
  duration<double> elapsed_seconds = end_time - start_time;

  // Convert to minutes and remaining seconds
  int minutes = static_cast<int>(elapsed_seconds.count() / 60);
  int seconds = static_cast<int>(elapsed_seconds.count() - minutes * 60);

  // Create a string stream for formatting
  std::stringstream ss;

  // Format the time string with leading zeros for minutes and seconds (00:00)
  ss << std::setfill('0') << std::setw(2) << minutes << ":"
     << std::setw(2) << seconds;

  return ss.str();
}

void createDirectory(const string& path) {
    string command = "md " + path + " >nul 2>&1";
    int return_code = system(command.c_str());

    if (return_code == 0) {
        // cout << "Directory \"" << path << "\" created successfully." << endl;
    } else {
        // cerr << "Error creating directory " << path << endl;
    }
}

void deleteInfo(string username) {
    string oldFile = "./database/user.txt";
    string newFile = "./database/updatedUser.txt";

    ifstream ifile;
    ofstream ofile;
    ifile.open(oldFile);
    ofile.open(newFile);

    string line = "";

    if (!ifile || !ofile)
        return;
    
    while (getline(ifile, line)) {
        if (line.find(username, 0) > line.length()) {
            ofile << line << endl;
        }
    }

    ifile.close();
    ofile.close();

    remove(oldFile.c_str());
    rename(newFile.c_str(), oldFile.c_str());
} 

void deleteDirectory(const string& path) {
    string command = "rmdir /s /q " + path + " >nul 2>&1";
    int return_code = system(command.c_str());

    if (return_code == 0) {
        // cout << "Directory \"" << path << "\" deleted successfully." << endl;
    } else {
        // cerr << "Error deleting directory " << path << endl;
    }
}

bool hasSpecialChar(const string& str) {
    for (char c : str) {
        if (!isalnum(c)) {
            return true;
        }
    }
    return false;
}