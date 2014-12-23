/**
 * @file: AggregateStrategy.h
 * @author Ethan Raymond
 * @Description: This file declares the AggregateStrategy classes
 * @Honor Code: I pledge my honor that I have neither given nor received
    unauthorized aid on this work.
*/

#include "AggregateStrategy.h"

/**
 * Destructor
 */
AggregateStrategy::~AggregateStrategy() {}

/**
 * Moves the Object for the given number of seconds
 */
void AggregateStrategy::move(double seconds, AggregateObject &obj) {}

/**
 * Destructor
 */
RigidStrategy::~RigidStrategy() {}

/**
 * Clone method
 */
AggregateStrategy* RigidStrategy::clone() {
    return new RigidStrategy(*this);
}

/**
 * Moves the Object for the given number of seconds
 */
void RigidStrategy::move(double seconds, AggregateObject &obj) {
    Universe* univ(Universe::instance());
    vector2 totalForce;
    std::for_each(univ->begin(), univ->end(), [&](Object* otherObj){
        totalForce += Universe::getForce(obj, *otherObj);
    });
    vector2 accel = totalForce / obj.getMass();
    vector2 changeVel = accel * seconds;
    vector2 vel = obj.getVelocity() + changeVel;
    obj.setVelocity(vel);
    vector2 pos = obj.getPosition() + vel * seconds;
    obj.setPosition(pos);
}

/**
 * Destructor
 */
RealisticStrategy::~RealisticStrategy() {}

/**
 * Clone method
 */
AggregateStrategy* RealisticStrategy::clone() {
    return new RealisticStrategy(*this);
}

/**
 * Moves the Object for the given number of seconds
 */
void RealisticStrategy::move(double seconds, AggregateObject &obj) {
    Universe* univ(Universe::instance());
    std::for_each(obj.begin(), obj.end(), [&](Object* innerObj){
        vector2 totalForce;
        std::for_each(univ->begin(), univ->end(), [&](Object* otherObj){
            if (*otherObj != obj) {
                totalForce += Universe::getForce(*innerObj, *otherObj);
            }
        });
        std::for_each(obj.begin(), obj.end(), [&](Object* innerObjSecond){
            totalForce += Universe::getForce(*innerObj, *innerObjSecond);
        });
        vector2 accel = totalForce / innerObj->getMass();
        vector2 changeVel = accel * seconds;
        vector2 vel = innerObj->getVelocity() + changeVel;
        innerObj->setVelocity(vel);
        vector2 pos = innerObj->getPosition() + vel * seconds;
        innerObj->setPosition(pos);
    });
}