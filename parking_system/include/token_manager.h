#ifndef TOKEN_MANAGER_H
#define TOKEN_MANAGER_H

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <random>

class TokenManager {
public:
    static std::string generateToken(size_t length = 16);
    static std::vector<std::string> split(const std::string& str, char delimiter = ',');
    static std::string join(const std::vector<std::string>& tokens, char delimiter = ',');
};

#endif // TOKEN_MANAGER_H