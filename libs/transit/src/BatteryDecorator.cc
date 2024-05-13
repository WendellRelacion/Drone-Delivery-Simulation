#include "BatteryDecorator.h"

BatteryDecorator::BatteryDecorator(IEntity* entity)
  : IEntityDecorator(entity) {}

BatteryDecorator::~BatteryDecorator() {
  if (battery) delete battery;
  if (rechargeRoute) delete rechargeRoute;
}

void BatteryDecorator::update(double dt) {
  if (model && entity && !battery) {
    // Add the model that this decorator wraps to the simulation
    // std::cout << "[BatteryDecorator] Adding entity " <<
    //     this->entity->getName() <<  " to model" << std::endl;
    IEntity* wrappedEntity = this->getEntity();
    this->entity->linkModel(model);
    model->getController().addEntity(*this->entity);
    model->addToEntities(this->entity);

    // Find the associated battery and set the battery pointer to it
    std::string name = this->entity->getName();
    std::map<int, IEntity*> entities = model->getEntities();
    for (auto& [id, entity] : entities) {
      // std::cout << "[BatteryDecorator] searching entities, found " <<
      //     entity->getName() << std::endl;
      if (entity->getName().compare(name + "_Battery") == 0) {
        // std::cout << "[BatteryDecorator] Found battery for " <<
        //     name << std::endl;
        this->battery = dynamic_cast<Battery*>(entity);
      }
    }
  }

  // Check to make sure battery has associated drone
  if (entity && battery) {
    Battery* battery = this->battery;
    // Battery low, route to charging station
    if (battery->getBattery() <= 20 && !battery->getIsCharging()) {
      // std::cout << "[Battery] low: " <<
      //     battery->getBattery() << "%" << std::endl;
      // If battery has not found a route, find one
      if (this->getRechargeRoute() == nullptr) {
        // std::cout << "[Battery] finding route" << std::endl;
        IEntity* closestStation = model->findClosestRechargeStation(battery);
        this->setRechargeRoute(
          new BeelineStrategy(
            battery->getPosition(),
            closestStation->getPosition()));
      } else {  // Otherwise, move towards the route
          // Check if the route is complete, then set charging to true
          if (this->getRechargeRoute()->isCompleted()) {
            // std::cout << "[Battery] route complete" << std::endl;
            battery->setIsCharging(true);
            this->setRechargeRoute(nullptr);
          } else {  // Otherwise, move towards the recharge station
            // std::cout << "[Battery] moving to recharge station" << std::endl;
            this->getRechargeRoute()->move(battery, dt);
            entity->setPosition(battery->getPosition());
          }
      }
      battery->setBattery(battery->getBattery() - 0.01);
    } else if (battery->getBattery() <= 80 && battery->getIsCharging()) {
      // Battery charging, stay at charging station
      // std::cout << "[Battery] charging: " <<
      //     battery->getBattery() << "%" << std::endl;
      battery->setBattery(battery->getBattery() + 0.1);
      entity->setPosition(battery->getPosition());
    } else {  // Battery okay, continue as normal
      battery->setIsCharging(false);
      // std::cout << "[Battery] good: " <<
      //     battery->getBattery() << "%" << std::endl;
      entity->update(dt);
      battery->update(dt);
      battery->setPosition(entity->getPosition());
      battery->setDirection(entity->getDirection());
      // Only decrement the battery if the drone is moving
      // if(this->entity() != nullptr &&
      //    !this->getRechargeRoute()->isCompleted()) {}
      battery->setBattery(battery->getBattery() - 0.01);
    }
    // Log battery and drone details
    if (tickCount == 500) {
      DataCollectorSingleton* instance = DataCollectorSingleton::getInstance();
      const JsonObject& details = entity->getDetails();
      double batteryLevel = battery->getBattery();
      double distanceTraveled = entity->getDistanceTraveled();
      // std::cout << "[BatteryDecorator] distance traveled=" <<
      //     distanceTraveled << std::endl;
      instance->logDroneData(details, batteryLevel, distanceTraveled);
      instance->saveToCSV("Drone-Data.csv");
      tickCount = 0;
    }
    tickCount++;
  }
}

IEntity* BatteryDecorator::getEntity() {
  return this->battery;
}

IStrategy* BatteryDecorator::getRechargeRoute() {
  return this->rechargeRoute;
}
void BatteryDecorator::setRechargeRoute(IStrategy* newRechargeRoute) {
  this->rechargeRoute = newRechargeRoute;
}
