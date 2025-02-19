#include "User.h"
#include "User.h"
#include <algorithm>

User::User(const std::string &username, const std::string hashedpassword) 
: username(username), hashedpassword(hashedpassword) {}

void User::addPost(const std::string &post){
    posts.push_back(post);
}

void User::addFriend(const std::string &friendUsername){
    friends.push_back(friendUsername);
}

void User::removeFriend(const std::string &friendUsrname){
    auto it = std::find(friends.begin(), friends.end(), friendUsrname);
    if(it != friends.end()){
        friends.erase(it);
    }
}

const std::string& User::getUsername() const{
    return username;
}

const std::vector<std::string>& User::getPosts() const{
    return posts;
}

const std::vector<std::string>& User::getFriends() const{
    return friends;
}

const std::string& User::getHashedPassword() const{
    return hashedpassword;
}
