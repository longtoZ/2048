#include "readBin.h"

void writeUsersToFile(string& filename, List& users) {
    ofstream outFile(filename, ios::binary | ios::out);
    if (!outFile.is_open()) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    ListNode* curr = users.head;
    while (curr != nullptr) {
        outFile.write(reinterpret_cast<const char*>(&(curr->data)), sizeof(Data));
        if (!outFile) {
            cerr << "Error writing user data to file." << endl;
            return;
        }
    }

    outFile.close();
}

void readUsersFromFile(string& filename, Data users[], int& totalUsers) {
    std::ifstream inFile(filename, std::ios::binary | std::ios::in);
    if (!inFile.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }

    inFile.read((char*)(&totalUsers), sizeof(totalUsers));

    int numUsersRead = 0;
    while (inFile.read((char*)(&users[numUsersRead]), sizeof(Data)) && numUsersRead < totalUsers) {
        numUsersRead++;
    }

    inFile.close();
}