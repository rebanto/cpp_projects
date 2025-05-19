#ifndef AUTH_H
#define AUTH_H

#include <string>
#include <vector>
#include <utility>

struct User {
    int id;
    std::string username;
    std::string password;
};

std::string trim(const std::string& s);
std::vector<User> load_users(const std::string& filename);
int add_user(const std::string& username, const std::string& password);
int login_user(const std::string& username, const std::string& password);
std::pair<User, bool> auth();

#endif