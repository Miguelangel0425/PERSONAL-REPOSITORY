#ifndef CIPHER_H
#define CIPHER_H
#include <string>

class CaesarCipher {
public:
    static std::string encrypt(const std::string& text, int shift = 3);
    static std::string decrypt(const std::string& text, int shift = 3);

private:
    static char shiftChar(char ch, int shift, bool encrypt);
};

#endif // CAESAR_CIPHER_H