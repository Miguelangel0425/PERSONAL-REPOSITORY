#ifndef HISTORY_MANAGER_H
#define HISTORY_MANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "../include/token_manager.h"
#include "../include/cipher.h"

struct ParkingEvent {
    std::string timestamp;
    std::string plate;
    std::string eventType;
};

class HistoryManager {
public:
    HistoryManager(const std::string& historyFile);
    
    void logEvent(const std::string& plate, const std::string& eventType);
    std::vector<ParkingEvent> getAllEvents() const;
    std::vector<ParkingEvent> getEventsByPlate(const std::string& plate) const;
    std::vector<ParkingEvent> getEventsByDateRange(
        const std::string& startDate, const std::string& endDate) const;

private:
    std::string historyFile;
    std::string getCurrentTimestamp() const;
};

#endif // HISTORY_MANAGER_H