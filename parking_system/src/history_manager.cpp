#include "../include/history_manager.h"
#include <chrono>
#include "../include/cipher.h"
#include "../include/token_manager.h"
#include <iomanip>

HistoryManager::HistoryManager(const std::string& historyFile) 
    : historyFile(historyFile) {}

std::string HistoryManager::getCurrentTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void HistoryManager::logEvent(const std::string& plate, const std::string& eventType) {
    std::ofstream file(historyFile, std::ios::app);
    std::string encryptedLine = CaesarCipher::encrypt(
        getCurrentTimestamp() + "," + plate + "," + eventType
    );
    file << encryptedLine << std::endl;
    file.close();
}

std::vector<ParkingEvent> HistoryManager::getAllEvents() const {
    std::vector<ParkingEvent> events;
    std::ifstream file(historyFile);
    std::string line;

    while (std::getline(file, line)) {
        std::string decryptedLine = CaesarCipher::decrypt(line);
        auto tokens = TokenManager::split(decryptedLine);
        
        if (tokens.size() == 3) {
            events.push_back({tokens[0], tokens[1], tokens[2]});
        }
    }

    return events;
}

std::vector<ParkingEvent> HistoryManager::getEventsByPlate(const std::string& plate) const {
    std::vector<ParkingEvent> events;
    
    for (const auto& event : getAllEvents()) {
        if (event.plate == plate) {
            events.push_back(event);
        }
    }

    return events;
}

std::vector<ParkingEvent> HistoryManager::getEventsByDateRange(
    const std::string& startDate, const std::string& endDate) const {
    
    std::vector<ParkingEvent> events;
    
    for (const auto& event : getAllEvents()) {
        if (event.timestamp >= startDate && event.timestamp <= endDate) {
            events.push_back(event);
        }
    }

    return events;
}