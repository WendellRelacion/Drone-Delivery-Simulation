#ifndef DATACOLLECTORSINGLETON_H
#define DATACOLLECTORSINGLETON_H

#include <iostream>
// #include <mutex>
#include <vector>

#include "util/json.h"

/**
 *@brief Singleton method for collecting data and storing to csv
 **/
class DataCollectorSingleton {
 private:
  static DataCollectorSingleton* instance;
  std::vector<JsonObject> loggedPackageData;
  std::vector<JsonObject> loggedDroneData;
  DataCollectorSingleton();

 public:
  /**
   * @brief Get instance of DataCollectorSingleton
   * @return DataCollectorSingleton instance
   */
  static DataCollectorSingleton* getInstance();

  /**
   * @brief log data to the collector for a package
   * @param data to log from the JSON format containing the object's information
   * @param deltaTime is the time since the last data log
   * @param distanceTraveled is the distance traveled by the package
   */
  void logPackageData(const JsonObject& data, double deltaTime,
    double distanceTraveled);

  /**
   * @brief Log data to the collector for a drone
   * @param data to log from the JSON format containing the object's information
   * @param batteryLevel is the battery level of the drone
   * @param distanceTraveled is the distance traveled by the drone
   */
  void logDroneData(const JsonObject& data, double batteryLevel,
    double distanceTraveled);

  /**
   * @brief save logged data to a csv file
   * @param filename is the name of the csv file.
   */
  void saveToCSV(const std::string& filename) const;
};

#endif  // DATACOLLECTORSINGLETON_H
