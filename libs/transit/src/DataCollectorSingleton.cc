#include "DataCollectorSingleton.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "util/json.h"

using namespace std;

// Initialize the singleton instance as nullptr
DataCollectorSingleton* DataCollectorSingleton::instance = nullptr;

// Private constructor to prevent external instantiation
DataCollectorSingleton::DataCollectorSingleton() {}

// Get the singleton instance, creating it if it doesn't exist
DataCollectorSingleton* DataCollectorSingleton::getInstance() {
  if (instance == nullptr) {
    instance = new DataCollectorSingleton();
  }
  return instance;
}

// Log package data with formatted deltaTime
void DataCollectorSingleton::logPackageData(const JsonObject& data,
      double deltaTime, double distanceTraveled) {
  std::ostringstream deltaTimeStream;
  deltaTimeStream << std::fixed << std::setprecision(2) << deltaTime;
  std::string formattedDeltaTime = deltaTimeStream.str();

  JsonObject modifiedData = data;
  modifiedData["deltaTime"] = formattedDeltaTime;
  modifiedData["distanceTraveled"] = distanceTraveled;

  loggedPackageData.push_back(modifiedData);
}

// Log drone data
void DataCollectorSingleton::logDroneData(const JsonObject& data,
      double batteryLevel, double distanceTraveled) {
  std::ostringstream batteryDataStream;
  batteryDataStream << std::fixed << std::setprecision(2) << batteryLevel;
  std::string formattedBatteryLevel = batteryDataStream.str();

  JsonObject modifiedData = data;
  modifiedData["batteryPercentage"] = formattedBatteryLevel;
  modifiedData["distanceTraveled"] = distanceTraveled;

  // Use the class scope for the member variable
  loggedDroneData.push_back(modifiedData);
}

// Save data to CSV file
void DataCollectorSingleton::saveToCSV(const std::string& filename) const {
  std::ofstream outputFile(filename);

  if (outputFile.is_open()) {
    // Names of the data collected
    std::vector<std::string> relevantFields = {
        "direction", "id",    "name",  "position", "radius",
        "rotation",  "scale", "speed", "type", "distanceTraveled"};

    // Add deltaTime and battery percentage fields if saving package data
    if (filename == "Package-Data-1.csv") {
      relevantFields.push_back("deltaTime");
    } else if (filename == "Drone-Data-1.csv") {
      relevantFields.push_back("batteryPercentage");
    }

    // Write header
    for (const auto& field : relevantFields) {
      outputFile << field << ",";
    }
    outputFile << std::endl;

    // Write data
    const auto& dataList =
        (filename == "Package-Data.csv") ? loggedPackageData : loggedDroneData;
    for (const auto& data : dataList) {
      // cout << "dataList" << data << endl;
      for (const auto& field : relevantFields) {
        outputFile << (data.contains(field) ? data[field] : "N/A") << ",";
      }
      outputFile << std::endl;
    }

    std::cout << "Data successfully saved to " << filename << std::endl;
  }
}
