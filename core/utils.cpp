#include "utils.h"

int **createEmptyBoard(int n)
{
    int **board = new int *[n];

    for (int i = 0; i < n; i++)
    {
        board[i] = new int[n];
    }

    return board;
}

int **createEmptyPos(int n)
{
    int **emptyPos = new int *[n];

    for (int i = 0; i < n; i++)
    {
        emptyPos[i] = new int[2];
    }

    return emptyPos;
}

string getCurrentDateTime()
{
    // Get current time
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);

    // Format time
    stringstream ss;
    ss << put_time(localtime(&now_time), "%d%m%Y_%H%M%S");
    return ss.str();
}

char *convertStringToChar(string str)
{
    char *charArray = new char[str.length() + 1];
    strcpy(charArray, str.c_str());
    return charArray;
}

string convertCharToString(char *charArray)
{
    string str(charArray);
    return str;
}

string calculateElapsedTimeString(const high_resolution_clock::time_point &start_time, const milliseconds &extraTime)
{
    auto end_time = high_resolution_clock::now();

    auto duration = end_time - start_time + extraTime;
    auto elapsed_seconds = duration_cast<seconds>(duration).count();

    int minutes = static_cast<int>(elapsed_seconds / 60);
    int seconds = static_cast<int>(elapsed_seconds % 60);

    stringstream ss;

    ss << setfill('0') << setw(2) << minutes << ":"
       << setw(2) << seconds;

    return ss.str();
}

long long convertTimeToLong(const high_resolution_clock::time_point &current_time)
{
    auto duration = current_time.time_since_epoch();

    auto millis = duration_cast<milliseconds>(duration).count();

    return millis;
}

high_resolution_clock::time_point convertLongToTime(long long milliseconds)
{
    std::chrono::milliseconds duration(milliseconds);

    std::chrono::high_resolution_clock::time_point time_point(duration);

    return time_point;
}

long long calculateDurationInMilliseconds(long long start)
{
    auto start_time = convertLongToTime(start);
    auto now = high_resolution_clock::now();

    auto duration = now - start_time;

    auto millis = duration_cast<milliseconds>(duration).count();

    return millis;
}

string replaceAll(string &original, string &toReplace, string &replacement)
{
    string result = original;
    int pos = result.find(toReplace);

    while (pos != (int)string::npos)
    {
        result.replace(pos, toReplace.length(), replacement);
        pos = result.find(toReplace, pos + replacement.length());
    }

    return result;
}

void createEmptyFile(string path)
{
    ofstream file(path, ios::binary);
    file.close();
}

bool fileExist(string name)
{
    ifstream f(name.c_str());
    return f.good();
}

void createUserFiles(string username)
{
    string fullPath = FILE_PATH + username;
    createEmptyFile(fullPath + "_achievement.bin");
    createEmptyFile(fullPath + "_best.bin");
    createEmptyFile(fullPath + "_prevboard.bin");
}

void deleteUserFiles(string username)
{
    string fullPath = FILE_PATH + username;
    remove((fullPath + "_achievement.bin").c_str());
    remove((fullPath + "_best.bin").c_str());
    remove((fullPath + "_prevboard.bin").c_str());
}

void deleteInfo(string username)
{
    string oldFile = "./database/user.bin";
    string newFile = "./database/updatedUser.bin";

    ifstream ifile;
    ofstream ofile;

    ifile.open(oldFile, ios::binary);
    ofile.open(newFile, ios::binary);

    if (!ifile || !ofile)
    {
        cout << "Error: Could not open file for reading or writing." << endl;
        return;
    }

    while (true)
    {
        char *tmpUsername = new char[USERNAME_SIZE];
        char *tmpPassword = new char[PASSWORD_SIZE];

        ifile.read(tmpUsername, USERNAME_SIZE);
        ifile.read(tmpPassword, PASSWORD_SIZE);

        if (ifile.eof())
            break;

        if (strcmp(tmpUsername, convertStringToChar(username)) != 0)
        {
            ofile.write(tmpUsername, USERNAME_SIZE);
            ofile.write(tmpPassword, PASSWORD_SIZE);
        }
    }

    ifile.close();
    ofile.close();

    remove(oldFile.c_str());
    rename(newFile.c_str(), oldFile.c_str());
}

bool hasSpecialChar(string &str)
{
    for (char c : str)
    {
        if (!isalnum(c))
        {
            return true;
        }
    }
    return false;
}

string formatDateStr(char *date)
{
    string str = date;
    string formattedDate = str.substr(0, 2) + "-" + str.substr(2, 2) + "-" + str.substr(4, 4) + " " + str.substr(9, 2) + ":" + str.substr(11, 2) + ":" + str.substr(13, 2);
    return formattedDate;
}

int generateSelections(string options[], int n, string pre, string post, string align)
{
    int chosen = 0;
    int maxLength = 0;

    for (int i = 0; i < n; i++)
    {
        if (options[i].length() > maxLength)
        {
            maxLength = options[i].length();
        }
    }

    while (true)
    {
        preventPlaying();
        system("cls");

        stringstream ssPre(pre);
        string preLine;

        while (getline(ssPre, preLine, '\n'))
        {
            int lineLength = replaceAllRegex(preLine).length();

            if (align == "left")
                cout << setLeftAlignSize() << preLine << endl;
            else if (align == "center")
                cout << setCenterAlignSize(lineLength) << preLine << endl;
        }
        cout << endl;

        for (int i = 0; i < n; i++)
        {
            if (i == chosen)
            {
                cout << setLeftAlignSize() << BOLD_TEXT WHITE_BACKGROUND_COLOR BLACK_TEXT TAB_WIDTH_2 "> " << options[i] << setw(maxLength - options[i].length() + 2) << " <" << RESET_FORMAT << endl
                     << endl;
            }
            else
            {
                cout << setLeftAlignSize() << TAB_WIDTH_2 "  " << options[i] << setw(maxLength - options[i].length() + 2) << "  " << endl
                     << endl;
            }
        }

        stringstream ssPost(post);
        string postLine;

        cout << endl;
        while (getline(ssPost, postLine, '\n'))
        {
            int lineLength = replaceAllRegex(postLine).length();

            if (align == "left")
                cout << setLeftAlignSize() << postLine << endl;
            else if (align == "center")
                cout << setCenterAlignSize(lineLength) << postLine << endl;
        }

        int key = getch();

        if (key == ENTER)
        {
            break;
        }
        else if (key == KEYDOWN)
        {
            chosen = chosen < n - 1 ? chosen + 1 : 0;
        }
        else if (key == KEYUP)
        {
            chosen = chosen > 0 ? chosen - 1 : n - 1;
        }
    }

    return chosen + 1;
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

string setLeftAlignSize()
{
    ScreenSize screenSize = getScreenSize();
    int consoleWidth = screenSize.width;

    int leftAlignSize = 0;

    if (consoleWidth < 150) {
        leftAlignSize = 4;
    } else if (consoleWidth < 200) {
        leftAlignSize = consoleWidth / 4;
    } else {
        leftAlignSize = consoleWidth / 3.6;
    }

    return string(leftAlignSize, ' ');
}

string setCenterAlignSize(int length) 
{
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
    int consoleWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;

    if (length >= consoleWidth) {
        return "";
    } else {
        return string((consoleWidth - length) / 2, ' ');
    }
}

bool isStrongPassword(string password) {
    if (password.length() < 8 || password.length() > 32){
        return false;
    }

    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    for (char c : password) {
        if (isupper(c)) {
            hasUpper = true;
        } else if (islower(c)) {
            hasLower = true;
        } else if (isdigit(c)) {
            hasDigit = true;
        } else if (ispunct(c)) {
            hasSpecial = true;
        }
    }

    return hasUpper && hasLower && hasDigit && hasSpecial;
}

ScreenSize getScreenSize() {
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
    int consoleWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
    int consoleHeight = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;

    ScreenSize screenSize;
    screenSize.width = consoleWidth;
    screenSize.height = consoleHeight;

    return screenSize;
}

string replaceAllRegex(string input) {
    regex ansiEscapeSequence("(\\x1b\\[.+?m|\\033\\[.+?m)");

    string result = regex_replace(input, ansiEscapeSequence, "");

    return result;
}

void sleepIgnoreInput(int miliseconds) {
    Sleep(miliseconds);
    while (_kbhit()) {
        _getch();
    }
}