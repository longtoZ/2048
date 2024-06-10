#include "user.h"

int userLogin(User &user)
{
    string tmpUsername;
    string tmpPassword;

    cout << endl
         << endl;
    cout << setLeftAlignSize() << "Press [x] + [Enter] to exit login menu!\n\n";

    cout << setLeftAlignSize() << "Username: ";
    cin >> tmpUsername;

    // Exit immediately
    if (tmpUsername == "x")
    {
        return -1;
    }

    cout << setLeftAlignSize() << "Password: ";
    cin >> tmpPassword;

    // Exit immediately
    if (tmpPassword == "x")
    {
        return -1;
    }

    // Check if user file exists
    if (!fileExist(USER_FILE_PATH))
    {
        createEmptyFile(USER_FILE_PATH);
    }

    ifstream ifile;
    ifile.open(USER_FILE_PATH, ios::binary);

    if (!ifile)
    {
        cout << RED_TEXT << "Error: Could not open file '" << USER_FILE_PATH << "' for reading." << RESET_FORMAT << endl;
        return -1;
    }

    cout << endl;
    while (true)
    {
        char *username = new char[USERNAME_SIZE];
        char *password = new char[PASSWORD_SIZE];

        ifile.read(username, USERNAME_SIZE);
        ifile.read(password, PASSWORD_SIZE);

        if (ifile.eof())
        {
            break;
        }

        if (strcmp(username, convertStringToChar(tmpUsername)) == 0 && strcmp(password, convertStringToChar(tmpPassword)) == 0)
        {
            user.username = username;
            user.password = password;
            cout << setLeftAlignSize() << GREEN_TEXT << "Login succesfully! Press any key to continue." << RESET_FORMAT << endl;
            getch();
            return 1;
        }
    }

    ifile.close();

    cout << setLeftAlignSize() << RED_TEXT << "User or password is incorrect! Press any key to try again." << RESET_FORMAT << endl;
    getch();
    return 2;
}

int userRegister(User &user)
{
    bool hasError = false;
    cout << endl
         << endl;
    cout << setLeftAlignSize() << "Press [x] + [Enter] to exit login menu!\n\n";

    string tmpUsername;
    string tmpPassword;
    string confirmPassword;

    cout << setLeftAlignSize() << "New username: ";
    getline(cin, tmpUsername);

    if (tmpUsername == "x")
    {
        return -1;
    }

    cout << setLeftAlignSize() << "New password: ";
    getline(cin, tmpPassword);

    if (tmpPassword == "x")
    {
        return -1;
    }

    cout << endl;
    if (tmpUsername.length() < 1 || tmpUsername.length() > 16)
    {
        cout << setLeftAlignSize() << YELLOW_TEXT << "Username's length must be greater than 1 and less than 16 character(s)! Press any key to try again." << RESET_FORMAT << endl;
        hasError = true;
    }

    if (hasSpecialChar(tmpUsername))
    {
        cout << setLeftAlignSize() << YELLOW_TEXT << "Username cannot contain any space or special character! Press any key to try again." << RESET_FORMAT << endl;
        hasError = true;
    }

    if (!isStrongPassword(tmpPassword))
    {
        cout << setLeftAlignSize() << YELLOW_TEXT << "Password's length must be greater than 8 and less than 32 character(s), " << endl;
        cout << setLeftAlignSize() << "and must contain at least one uppercase letter, one lowercase letter, one number, " << endl;
        cout << setLeftAlignSize() << "and one special character! Press any key to try again." << RESET_FORMAT << endl;
        hasError = true;
    }

    if (hasError)
    {
        getch();
        return 0;
    }

    cout << setLeftAlignSize() << "Confirm password: ";
    getline(cin, confirmPassword);

    cout << endl;
    if (tmpPassword != confirmPassword)
    {
        cout << setLeftAlignSize() << YELLOW_TEXT << "Password does not match! Press any key to try again." << RESET_FORMAT << endl;
        getch();
        return 0;
    }

    if (!fileExist(USER_FILE_PATH))
    {
        createEmptyFile(USER_FILE_PATH);
    }

    ifstream ifile;
    ifile.open(USER_FILE_PATH, ios::binary);

    if (!ifile.is_open())
    {
        cout << setLeftAlignSize() << RED_TEXT << "Error: Could not open file '" << USER_FILE_PATH << "' for reading." << RESET_FORMAT << endl;
        return -1;
    }

    while (true)
    {
        char *username = new char[USERNAME_SIZE];
        char *password = new char[PASSWORD_SIZE];

        ifile.read(username, USERNAME_SIZE);
        ifile.read(password, PASSWORD_SIZE);

        if (ifile.eof())
        {
            break;
        }

        if (convertCharToString(username) == tmpUsername)
        {
            cout << setLeftAlignSize() << YELLOW_TEXT << "Username already exists! Press any key to try again." << RESET_FORMAT << endl;
            getch();
            return 0;
        }
    }

    ofstream outputFile;
    outputFile.open(USER_FILE_PATH, ios::binary | ios::app);

    if (!outputFile.is_open())
    {
        cout << setLeftAlignSize() << RED_TEXT << "Error: Could not open file '" << USER_FILE_PATH << "' for writing." << RESET_FORMAT << endl;
        return -1;
    }

    // Seek to the end of the file
    outputFile.seekp(ios::end);

    outputFile.write(convertStringToChar(tmpUsername), USERNAME_SIZE);
    outputFile.write(convertStringToChar(tmpPassword), PASSWORD_SIZE);

    // Creater user data files
    createUserFiles(tmpUsername);

    cout << endl;
    cout << setLeftAlignSize() << GREEN_TEXT << "You have successfully created a new account!. Press any key to continue." << RESET_FORMAT << endl;
    getch();

    return 1;
}

int userDelete(User &user)
{

    string pre = "\n\nAre you sure you want to delete this account: " BOLD_TEXT YELLOW_TEXT UNDERLINE_TEXT + string(user.username) + RESET_FORMAT "\n";
    string post = "";
    string options[] = {"Yes", "No"};

    int chosen = generateSelections(options, 2, pre, post);

    if (chosen == 1)
    {
        // Delete user files: leaderboard.bin, prevboard.bin, best.bin
        deleteUserFiles(string(user.username));
        // Delete user info from user.bin
        deleteInfo(string(user.username));
        cout << setLeftAlignSize() << GREEN_TEXT << "You have successfully deleted your account! Press any key to go back." << RESET_FORMAT << endl;
        cleanUser(user);
        getch();
        return 1;
    }
    else if (chosen == 2)
    {
        return 2;
    }

    return -1;
}