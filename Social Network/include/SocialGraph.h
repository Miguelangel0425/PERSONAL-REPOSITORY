#pragma once 
#include <unordered_map>
#include "User.h"

using namespace std;

class SocialGraph{
    private:
    unordered_map<string, User> users;

    public:
    bool addUser(const string& username, const string& password);
    bool addConnection(const string& user1, const string& user2);
    bool addPost(const string& username, const string& post);

    bool userExists(const string& username) const;
    bool verifyPassword(const string& username , const string& password) const;

    vector<string> getUserPosts(const string& username) const;
    vector<string> getUserFriends(const string& username) const;
    const string getUserHashedPassword(const string& username) const;

    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);

};