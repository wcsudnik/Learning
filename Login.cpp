/*
 *Basic Password storing program
 *Takes user input for Username, Password, and Security question,
 *then hashes them and stores them to a text file.
 *
 *FEATURES TO ADD:
 *Unique users - "This username is taken feature"
 *--Need an algorithm faster than O(N) for user lookup.
 *  Might look into hashmaps for O(1) lookup
 *designated Sign in vs Sign up feature
 *--Basic TUI
 *Hide password input
 *--Might require changing terminal flags but try to find workaround
 *Require password to have Capitals + special chars
*/
#include <iostream>
#include <functional>
#include <fstream>
struct User {
    std::string Username;
    std::string Password;
    std::string SecurityQuestion;
};
struct HashedUser {
    size_t HashedUsername;
    size_t HashedPassword;
    size_t HashedSecurityQuestion;
};
void LoadUsers(User* user) {
    std::cout<<"Username?\n";
    std::cin>>user->Username;
    std::cout<<"Password?\n";
    std::cin>>user->Password;
    std::cout<<"Mothers maiden name?\n";
    std::cin>>user->SecurityQuestion;
}
void UserHash(const User* user, HashedUser* hashedUser) {
    std::hash<std::string> h;
    hashedUser->HashedUsername = h(user->Username);
    hashedUser->HashedPassword = h(user->Password);
    hashedUser->HashedSecurityQuestion = h(user->SecurityQuestion);
}
void fileWrite(const HashedUser* hashedUser,User* user) {
    std::ofstream outFile("./users.txt", std::ios::app);
    outFile << hashedUser->HashedUsername << std::endl;
    outFile << hashedUser->HashedPassword << std::endl;
    outFile << hashedUser->HashedSecurityQuestion << std::endl;
}
int main() {
    User user{};
    HashedUser hashedUser{};
    LoadUsers(&user);
    UserHash(&user, &hashedUser);
    fileWrite(&hashedUser, &user);
}


