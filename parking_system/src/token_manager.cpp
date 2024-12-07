#include "../include/token_manager.h"

std::string TokenManager::generateToken(size_t length) {
    const std::string chars = 
        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, chars.size() - 1);

    std::string token;
    token.reserve(length);
    
    std::generate_n(std::back_inserter(token), length, 
        [&]() { return chars[distribution(generator)]; });
    
    return token;
}

std::vector<std::string> TokenManager::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

std::string TokenManager::join(const std::vector<std::string>& tokens, char delimiter) {
    std::string result;
    for (size_t i = 0; i < tokens.size(); ++i) {
        result += tokens[i];
        if (i < tokens.size() - 1) result += delimiter;
    }
    return result;
}