#include "user.h"

#define USER_FILE_PATH "./database/user.txt"

int userLogin(User &user) {
    
    cout << endl << endl;
    cout << "Press [x] to exit login menu!\n\n";

    cout << "Username: ";
    cin >> user.username;

    // Exit immediately
    if (user.username == "x") {
        return -1;
    }
    
    cout << "Password: ";
    cin >> user.password;

    // Exit immediately
    if (user.password == "x") {
        return -1;
    }

    ifstream ifile;
    ifile.open(USER_FILE_PATH);

    if (!ifile) {
        return -1;
    }

    string line = "";

    while (getline(ifile, line)) {
        int space = line.find(' ', 0);

        string username = line.substr(0, space);
        string password = line.substr(space+1, line.length()-space-1);

        if (username == user.username && password == user.password) {
            return 1;
        }
    }

    ifile.close();

    return 2;
}

void userRegister() {
    cout << endl << endl;
    cout << "Press [x] to exit login menu!\n\n";

    User user;

    while (true) {
        cout << "New username: ";
        getline(cin, user.username);

        if (user.username == "x") {
            return ;
        }

        if (user.username.length() < 1 || user.username.length() > 16) {
            cout << YELLOW_TEXT << "Username's length must be greater than 1 and less than 16 character(s)! Press any key to try again." << RESET_FORMAT << endl;
            getch();
            continue;
        }

        if (hasSpecialChar(user.username)) {
            cout << YELLOW_TEXT << "Username cannot contain any special character! Press any key to try again." << RESET_FORMAT << endl;
            getch();
            continue;
        }

        break;
    }

    while (true) {
        cout << "New password: ";
        cin >> user.password;

        if (user.password == "x") {
            return;
        }

        if (user.password.length() < 8 || user.password.length() > 32) {
            cout << YELLOW_TEXT << "Password's length must be greater than 8 and less than 32 character(s)! Press any key to try again." << RESET_FORMAT << endl;
            getch();
        } else {
            break;
        }
    }
    
    ifstream ifile;
    ifile.open(USER_FILE_PATH);
    string line = "";

    while (getline(ifile, line)) {
        int space = line.find(' ', 0);

        string username = line.substr(0, space);
        string password = line.substr(space+1, line.length()-space-1);

        if (username == user.username) {
            cout << YELLOW_TEXT << "User has already existed! Press any key to try again." << RESET_FORMAT << endl;
            getch();
            return;
        }
    }


    ofstream ofile;
    ofile.open(USER_FILE_PATH, ios::app);

    if (!ofile) {
        return;
    }

    string data = user.username + " " + user.password + "\n";
    ofile << data;

    cout << endl;
    cout << GREEN_TEXT << "You have successfully created a new account!. Press any key to continue." << RESET_FORMAT << endl;
    getch();
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
            deleteDirectory("database\\user\\" + user.username);
            deleteInfo(user.username);
            cout << GREEN_TEXT << "You have successfully deleted your account! Press any key to go back." << RESET_FORMAT << endl;
            getch();
            return 1;
        } else if (key == N_KEY) {
            return 2;
        }

    }

    return -1;

}