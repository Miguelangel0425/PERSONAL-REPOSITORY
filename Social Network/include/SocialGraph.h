#pragma once 
#include <unordered_map>
#include "User.h"

using namespace std;

class SocialGraph{
    private:
    unordered_map<string, User> users;

    public:
    bool addUser(const std::string& username, const std::string& password);
    bool addConnection(const std::string& user1, const std::string& user2);
    bool addPost(const std::string& username, const std::string& post);
    bool userExists(const std::string& username) const;
    bool verifyPassword(const std::string& username, const std::string& password) const;
    const std::string getUserHashedPassword(const std::string& username) const;
    std::vector<std::string> getUserPosts(const std::string& username) const;
    std::vector<std::string> getUserFriends(const std::string& username) const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    

    bool areFriends(const std::string& user1, const std::string& user2) const;
    bool addFriend(const std::string& user1, const std::string& user2);
};