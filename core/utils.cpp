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

void createDirectory(string path) {
    path = replaceAll(path.substr(2, path.length() - 2), "/", "\\");
    string command = "md " + path + " >nul 2>&1";
    int return_code = system(command.c_str());

    if (return_code == 0) {
        cout << "Directory \"" << path << "\" created successfully." << endl;
    } else {
        cerr << "Error creating directory " << path << endl;
    }
}

string replaceAll(const string& original, const string& toReplace, const string& replacement) {
    // Create a copy of the original string to work with
    string result = original;

    // Find the first occurrence of the substring to replace
   size_t pos = result.find(toReplace);

    // Loop until no more occurrences are found
    while (pos != string::npos) {
        // Replace the found substring with the replacement string
        result.replace(pos, toReplace.length(), replacement);

        // Find the next occurrence of the substring to replace
        pos = result.find(toReplace, pos + replacement.length());
    }

    // Return the modified string
    return result;
}

void createEmptyFile(string path) {
    path = replaceAll(path.substr(2, path.length() - 2), "/", "\\");
    string command = "copy NUL " + path + " >nul 2>&1";
    int return_code = system(command.c_str());

    if (return_code == 0) {
        cout << "File \"" << path << "\" created successfully." << endl;
    } else {
        cerr << "Error creating file " << path << endl;
        cout << command << endl;
    }
}

bool fileExist (const string& name) {
    ifstream f(name.c_str());
    return f.good();
}

void createUserFiles(const string& username) {
    string fullPath = FILE_PATH + username;
    createDirectory(fullPath);
    createEmptyFile(fullPath + "/leaderboard.bin");
    createEmptyFile(fullPath + "/best.bin");
    createEmptyFile(fullPath + "/prevboard.bin");
}

void deleteInfo(string username) {
    string oldFile = "./database/user.bin";
    string newFile = "./database/updatedUser.bin";

    ifstream ifile;
    ofstream ofile;

    ifile.open(oldFile, ios::binary);
    ofile.open(newFile, ios::binary);

    if (!ifile || !ofile) {
        cout << "Error: Could not open file for reading or writing." << endl;
        return;
    }

    while (!ifile.eof()) {
        char* tmpUsername = new char[USERNAME_SIZE];
        char* tmpPassword = new char[PASSWORD_SIZE];

        ifile.read(tmpUsername, USERNAME_SIZE);
        ifile.read(tmpPassword, PASSWORD_SIZE);

        if (strcmp(tmpUsername, convertStringToChar(username)) != 0) {
            ofile.write(tmpUsername, USERNAME_SIZE);
            ofile.write(tmpPassword, PASSWORD_SIZE);
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

char* formatDateChar(char* date) {
    string str = date;
    string formattedDate = str.substr(0, 2) + "-" + str.substr(2, 2) + "-" + str.substr(4, 4) + " " + str.substr(9, 2) + ":" + str.substr(11, 2) + ":" + str.substr(13, 2);
    return convertStringToChar(formattedDate);
}

int generateSelections(string options[], int n, string pre, string post) {
    int chosen = 0;
    int maxLength = 0;

    for (int i=0; i<n; i++) {
        if (options[i].length() > maxLength) {
            maxLength = options[i].length();
        }
    }

    while (true) {
        system("cls");

        cout << pre << endl;

        for (int i=0; i<n; i++) {
            if (i == chosen) {
                cout << BOLD_TEXT << WHITE_BACKGROUND_COLOR << BLACK_TEXT << "\t> " << options[i] << setw(maxLength - options[i].length() + 2) << " <" << RESET_FORMAT << endl << endl;
            } else {
                cout << "\t  " << options[i] << endl << endl;
            }
        }

        cout << post << endl;

        int key = getch();

        if (key == ENTER) {
            break;
        } else if (key == KEYDOWN) {
            chosen = chosen < n-1 ? chosen+1 : 0; 
        } else if (key == KEYUP) {
            chosen = chosen > 0 ? chosen-1 : n-1;
        }
    }

    return chosen+1;
}