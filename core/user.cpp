#include "user.h"

#define USER_FILE_PATH "./database/user.bin"

int userLogin(User &user) {
    string tmpUsername;
    string tmpPassword;

    cout << endl << endl;
    cout << "Press [x] to exit login menu!\n\n";

    cout << "Username: ";
    cin >> tmpUsername;

    // Exit immediately
    if (tmpUsername == "x") {
        return -1;
    }
    
    cout << "Password: ";
    cin >> tmpPassword;

    // Exit immediately
    if (tmpPassword == "x") {
        return -1;
    }

    ifstream ifile;
    ifile.open(USER_FILE_PATH, ios::binary);

    if (!ifile) {
        cout << RED_TEXT << "Error: Could not open file '" << USER_FILE_PATH << "' for reading." << RESET_FORMAT << endl;
        return -1;
    }

    while (true) {
        char* username = new char[USERNAME_SIZE];
        char* password = new char[PASSWORD_SIZE];

        ifile.read(username, USERNAME_SIZE);
        ifile.read(password, PASSWORD_SIZE);

        if (strcmp(username, convertStringToChar(tmpUsername)) == 0 && strcmp(password, convertStringToChar(tmpPassword)) == 0) {
            user.username = username;
            user.password = password;
            cout << GREEN_TEXT << "\nLogin succesfully! Press any key to continue." << RESET_FORMAT << endl;
            getch();
            return 1;
        }

        if (ifile.eof()) {
            break;
        }
    }

    ifile.close();

    cout << RED_TEXT << "\nUser or password is incorrect! Press any key to try again." << RESET_FORMAT << endl;
    getch();
    return 2;
}

int userRegister(User &user) {
    bool hasError = false;
    cout << endl << endl;
    cout << "Press [x] to exit login menu!\n\n";

    string tmpUsername;
    string tmpPassword;


    cout << "New username: ";
    getline(cin, tmpUsername);

    if (tmpUsername == "x") {
        return -1;
    }

    cout << "New password: ";
    getline(cin, tmpPassword);

    if (tmpPassword == "x") {
        return -1;
    }

    if (tmpUsername.length() < 1 || tmpUsername.length() > 16) {
        cout << YELLOW_TEXT << "Username's length must be greater than 1 and less than 16 character(s)! Press any key to try again." << RESET_FORMAT << endl;
        hasError = true;
    }

    if (hasSpecialChar(tmpUsername)) {
        cout << YELLOW_TEXT << "Username cannot contain any special character! Press any key to try again." << RESET_FORMAT << endl;
        hasError = true;
    }

    if (tmpPassword.length() < 8 || tmpPassword.length() > 32) {
        cout << YELLOW_TEXT << "Password's length must be greater than 8 and less than 32 character(s)! Press any key to try again." << RESET_FORMAT << endl;
        hasError = true;
    } 

    if (hasError) {
        getch();
        return 0;
    }
    
    if (!fileExist(USER_FILE_PATH)) {
        createEmptyFile(USER_FILE_PATH);
    }

    ifstream ifile;
    ifile.open(USER_FILE_PATH, ios::binary);

    if (!ifile.is_open()) {
        cout << RED_TEXT << "Error: Could not open file '" << USER_FILE_PATH << "' for reading." << RESET_FORMAT << endl;
        return -1;
    }

    while (true) {
        char* username = new char[USERNAME_SIZE];
        char* password = new char[PASSWORD_SIZE];

        ifile.read(username, USERNAME_SIZE);

        if (strcmp(username, convertStringToChar(tmpUsername)) == 0) {
            cout << YELLOW_TEXT << "Username already exists! Press any key to try again." << RESET_FORMAT << endl;
            getch();
            return 0;
        }

        if (ifile.eof()) {
            break;
        }
    }

    ofstream outputFile;
    outputFile.open(USER_FILE_PATH, ios::binary | ios::app);

    if (!outputFile.is_open()) {
        cout << RED_TEXT << "Error: Could not open file '" << USER_FILE_PATH << "' for writing." << RESET_FORMAT << endl;
        return -1;
    }

    // Seek to the end of the file
    outputFile.seekp(ios::end);

    outputFile.write(convertStringToChar(tmpUsername), USERNAME_SIZE);
    outputFile.write(convertStringToChar(tmpPassword), PASSWORD_SIZE);

    // Creater user data files
    createUserFiles(tmpUsername);

    cout << endl;
    cout << GREEN_TEXT << "You have successfully created a new account!. Press any key to continue." << RESET_FORMAT << endl;
    getch();

    return 1;
}

int userDelete(User& user) {

    int key = 0;

    while (true) {
        system("cls");

        cout << endl << endl;
        cout << YELLOW_TEXT <<
            "Are you sure you want to delete this account: " << BOLD_TEXT << UNDERLINE_TEXT << user.username << RESET_FORMAT << "\n" <<
            YELLOW_TEXT << "\t Yes - [y]\n"
            "\t No - [n]\n" << RESET_FORMAT;
        cout << endl;

        key = getch();

        if (key == Y) {
            deleteDirectory("database\\user\\" + string(user.username));
            deleteInfo(string(user.username));
            cout << GREEN_TEXT << "You have successfully deleted your account! Press any key to go back." << RESET_FORMAT << endl;
            cleanUser(user);
            getch();
            return 1;
        } else if (key == N_KEY) {
            return 2;
        }
    }

    return -1;

}