#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

#include <iostream>
#include <vector>
#include <regex>
#include <unordered_set>

namespace DataValidationLib {
    class DLL_EXPORT Validator {
    public:
        static bool IsPositive(int number) { return number > 0; }
        static bool IsInRange(int number, int min, int max) { return number >= min && number <= max; }
        static bool IsValidString(const std::string& input, int minLength, int maxLength) {
            return !input.empty() && input.length() >= minLength && input.length() <= maxLength;
        }
        static bool IsAlpha(const std::string& input) {
            return std::regex_match(input, std::regex("^[a-zA-Z]+$"));
        }
        static bool IsValidEmail(const std::string& email) {
            return std::regex_match(email, std::regex(R"(^[^\s@]+@[^\s@]+\.[^\s@]+$)"));
        }
        static bool IsStrongPassword(const std::string& password) {
            return std::regex_match(password, std::regex("^(?=.*[A-Z])(?=.*\d).{8,}$"));
        }
        static bool IsFutureDate(time_t date) { return date > time(0); }
        template <typename T>
        static bool IsNotEmpty(const std::vector<T>& array) { return !array.empty(); }
        template <typename T>
        static bool HasNoDuplicates(const std::vector<T>& list) {
            std::unordered_set<T> uniqueElements(list.begin(), list.end());
            return uniqueElements.size() == list.size();
        }
        static bool IsValidIP(const std::string& ip) {
            return std::regex_match(ip, std::regex(R"(^([0-9]{1,3}\.){3}[0-9]{1,3}$)"));
        }
        static bool IsValidCreditCard(const std::string& cardNumber) {
            int sum = 0;
            bool alternate = false;
            for (int i = cardNumber.size() - 1; i >= 0; --i) {
                int n = cardNumber[i] - '0';
                if (alternate) {
                    n *= 2;
                    if (n > 9) n -= 9;
                }
                sum += n;
                alternate = !alternate;
            }
            return (sum % 10 == 0);
        }
    };
}