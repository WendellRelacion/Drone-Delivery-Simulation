#include "SimulationModel.h"

#include "DroneFactory.h"
#include "HelicopterFactory.h"
#include "HumanFactory.h"
#include "PackageFactory.h"
#include "RobotFactory.h"
#include "RechargeStationFactory.h"
#include "BatteryFactory.h"

#include "DataCollectorSingleton.h"

SimulationModel::SimulationModel(IController& controller)
    : controller(controller) {
  entityFactory.AddFactory(new DroneFactory());
  entityFactory.AddFactory(new PackageFactory());
  entityFactory.AddFactory(new RobotFactory());
  entityFactory.AddFactory(new HumanFactory());
  entityFactory.AddFactory(new HelicopterFactory());
  entityFactory.AddFactory(new RechargeStationFactory());
  entityFactory.AddFactory(new BatteryFactory());
}

SimulationModel::~SimulationModel() {
  // Delete dynamically allocated variables
  for (auto& [id, entity] : entities) {
    // DataCollectorSingleton::getInstance().logData(entity->getDetails());

    delete entity;
  }
  delete graph;

  // DataCollectorSingleton::getInstance().saveToCSV("output.csv");
}

IEntity* SimulationModel::createEntity(JsonObject& entity) {
  std::string name = entity["name"];
  JsonArray position = entity["position"];
  std::cout << name << ": " << position << std::endl;

  IEntity* myNewEntity = nullptr;
  if (myNewEntity = entityFactory.CreateEntity(entity)) {
    // Call AddEntity to add it to the view
    myNewEntity->linkModel(this);
    controller.addEntity(*myNewEntity);
    entities[myNewEntity->getId()] = myNewEntity;

    // If the entity created is a recharge station,
    // keep track of this in the "rechargeStations" vector
    std::string type = entity["type"];
    if (type.compare("rechargeStation") == 0) {
      rechargeStations.push_back(myNewEntity);
    }
  }

  return myNewEntity;
}

void SimulationModel::removeEntity(int id) { removed.insert(id); }

// Schedules a Delivery for an object in the scene
void SimulationModel::scheduleTrip(JsonObject& details) {
  std::string name = details["name"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];
  std::cout << name << ": " << start << " --> " << end << std::endl;

  Robot* receiver = nullptr;

  for (auto& [id, entity] : entities) {
    if (name == entity->getName()) {
      if (Robot* r = dynamic_cast<Robot*>(entity)) {
        if (r->requestedDelivery) {
          receiver = r;
          break;
        }
      }
    }
  }

  Package* package = nullptr;

  for (auto& [id, entity] : entities) {
    if (name + "_package" == entity->getName()) {
      if (Package* p = dynamic_cast<Package*>(entity)) {
        if (p->requiresDelivery) {
          package = p;
          break;
        }
      }
    }
  }

  if (receiver && package) {
    package->initDelivery(receiver);
    std::string strategyName = details["search"];
    package->setStrategyName(strategyName);
    scheduledDeliveries.push_back(package);
    controller.sendEventToView("DeliveryScheduled", details);
  }
}

const routing::IGraph* SimulationModel::getGraph() { return graph; }

/// Updates the simulation
void SimulationModel::update(double dt) {
  for (auto& [id, entity] : entities) {
    entity->update(dt);
    controller.updateEntity(*entity);
  }
  for (int id : removed) {
    removeFromSim(id);
  }
  removed.clear();
}

void SimulationModel::stop(void) { controller.stop(); }

void SimulationModel::removeFromSim(int id) {
  IEntity* entity = entities[id];
  if (entity) {
    // DataCollectorSingleton::getInstance().logData(entity->getDetails());
    for (auto i = scheduledDeliveries.begin(); i != scheduledDeliveries.end();
         ++i) {
      if (*i == entity) {
        scheduledDeliveries.erase(i);
        break;
      }
    }
    controller.removeEntity(*entity);
    entities.erase(id);
    delete entity;
  }
}

IEntity* SimulationModel::findClosestRechargeStation(IEntity* entity) {
  // Find the closest recharge station to the entity
  IEntity* closestRechargeStation = nullptr;
  Vector3 entityPosition = entity->getPosition();
  double minDistance = INT_MAX;
  for (int i = 0; i < rechargeStations.size(); i++) {
    IEntity* station = rechargeStations[i];
    Vector3 stationPosition = station->getPosition();
    // Calculate using Euclidean distance formula
    double distance = sqrt(
      pow(entityPosition.x - stationPosition.x, 2) +
      pow(entityPosition.y - stationPosition.y, 2) +
      pow(entityPosition.z - stationPosition.z, 2));
    if (distance < minDistance) {
      minDistance = distance;
      closestRechargeStation = station;
    }
  }
  return closestRechargeStation;
}
