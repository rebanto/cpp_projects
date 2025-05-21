#include "auth.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    if (start == string::npos || end == string::npos) return "";
    return s.substr(start, end - start + 1);
}

vector<User> load_users(const string& filename) {
    vector<User> users;
    ifstream fin(filename);
    string line;
    map<int, double> balances;
    ifstream fin_bal("finances.csv");
    string bal_line;
    while (getline(fin_bal, bal_line)) {
        stringstream ss(bal_line);
        string id_str, bal_str;
        if (!getline(ss, id_str, ',')) continue;
        if (!getline(ss, bal_str, ',')) continue;
        try {
            int id = stoi(trim(id_str));
            double bal = stod(trim(bal_str));
            balances[id] = bal;
        } catch (...) {
            continue;
        }
    }
    fin_bal.close();

    while (getline(fin, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;
        stringstream ss(line);
        string id_str, username, password;
        if (!getline(ss, id_str, ',')) continue;
        if (!getline(ss, username, ',')) continue;
        if (!getline(ss, password, ',')) continue;
        id_str = trim(id_str);
        username = trim(username);
        password = trim(password);
        if (id_str.empty() || username.empty() || password.empty()) continue;
        try {
            int id = stoi(id_str);
            double bal = balances.count(id) ? balances[id] : 0.0;
            users.push_back({id, username, password, bal});
        } catch (...) {
            continue;
        }
    }
    return users;
}

int add_user(const string& username, const string& password) {
    vector<User> users = load_users("users.csv");
    for (const auto& user : users) {
        if (user.username == username) {
            cout << "Username already exists.\n";
            return -1;
        }
    }
    int new_id = users.empty() ? 1 : users.back().id + 1;
    ofstream fout("users.csv", ios::out | ios::app);
    fout << new_id << "," << username << "," << password << endl;
    fout.close();

    ofstream fout_finances("finances.csv", ios::out | ios::app);
    fout_finances << new_id << "," << 0 << endl;
    fout_finances.close();

    return new_id;
}

int login_user(const string& username, const string& password) {
    vector<User> users = load_users("users.csv");
    for (const auto& user : users) {
        if (user.username == username && user.password == password) {
            return user.id;
        }
    }
    return -1;
}

pair<User, bool> auth() {
    char action;
    string username, password;
    int id;

    cout << "Welcome to the Budget Manager!\n";

    do {
        cout << "Log in or sign up (L/S):\t";
        cin >> action;
        action = (char) tolower(action);
        if (action != 'l' && action != 's') {
            cout << "\nIncorrect input!\n";
        }
    } while (action != 'l' && action != 's');

    if (action == 'l') {
        cout << "\nLOGIN\nEnter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        vector<User> users = load_users("users.csv");
        for (const auto& user : users) {
            if (user.username == username && user.password == password) {
                cout << "Login successful!" << endl;
                return {user, true};
            }
        }
        cout << "Login failed. Incorrect username or password.\n";
        return {User{}, false};
    } else if (action == 's') {
        cout << "\nSIGN UP\nEnter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        int new_id = add_user(username, password);
        if (new_id != -1) {
            cout << "Sign up successful!" << endl;
            return {User{new_id, username, password, 0.00}, true};
        } else {
            return {User{}, false};
        }
    }

    return {User{}, false};
}

void save_user(const int& id, double balance) {
    map<int, double> balances;
    ifstream fin_bal("finances.csv");
    string line;
    while (getline(fin_bal, line)) {
        stringstream ss(line);
        string id_str, bal_str;
        if (!getline(ss, id_str, ',')) continue;
        if (!getline(ss, bal_str, ',')) continue;
        try {
            int uid = stoi(trim(id_str));
            double bal = stod(trim(bal_str));
            balances[uid] = bal;
        } catch (...) {
            continue;
        }
    }
    fin_bal.close();

    balances[id] = balance;

    ofstream fout_bal("finances.csv", ios::out | ios::trunc);
    for (const auto& pair : balances) {
        fout_bal << pair.first << "," << pair.second << endl;
    }
    fout_bal.close();
}