#include "../include/cipher.h"

char CaesarCipher::shiftChar(char ch, int shift, bool encrypt) {
    if (!std::isalpha(ch)) return ch;

    char base = std::isupper(ch) ? 'A' : 'a';
    int shiftAmount = encrypt ? shift : -shift;
    
    return static_cast<char>((((ch - base + shiftAmount) % 26 + 26) % 26) + base);
}

std::string CaesarCipher::encrypt(const std::string& text, int shift) {
    std::string encrypted;
    for (char ch : text) {
        encrypted += shiftChar(ch, shift, true);
    }
    return encrypted;
}

std::string CaesarCipher::decrypt(const std::string& text, int shift) {
    std::string decrypted;
    for (char ch : text) {
        decrypted += shiftChar(ch, shift, false);
    }
    return decrypted;
}