#pragma once 
#include <string>
#include <vector>

using namespace std;

class User {
    private:
    string username;
    string hashedpassword;
    vector<string> posts;
    vector<string> friends;
    public:
    User(const string &username, const string hashedpassword);

    void addPost(const string &post);
    void addFriend(const string &friendUsername);
    void removeFriend(const string &friendUsrname);

    const string& getUsername() const;
    const vector<string>& getPosts() const;
    const vector<string>& getFriends() const;
    const string& getHashedPassword() const;
    
};
