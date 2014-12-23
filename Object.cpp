/**
 * @file: Object.cpp
 * @author Ethan Raymond
 * @Description: This file implements the Object class and its subclasses
 * @Honor Code: I pledge my honor that I have neither given nor received
    unauthorized aid on this work.
*/

#include "Object.h"
#include <cmath>

 /**
 *  Initializes an object with the provided properties.
 */
Object::Object(const std::string &name, double mass) :
        name_(name), mass_(mass) {}

/**
 *  Destroys this object.
 */
Object::~Object() {}

/**
 *  Returns the mass.
 */
double Object::getMass() const {
    return mass_;
}

/**
 *  Returns the name.
 */
std::string Object::getName() const {
    return name_;
}

/**
 * Sets the aggregate strategy as rigid or realistic
 */
void Object::setAggregateStrategy(AggregateStrategy *strategy) {}

/*
* Returns the strategy pointer
*/
AggregateStrategy* Object::getStrategy() const {
    return nullptr;
}

 /**
 *  Initializes an object with the provided properties.
 */
ImmobileObject::ImmobileObject(const std::string &name, double mass,
        const vector2 &pos) : Object(name, mass), position_(pos) {}

/**
 *  Destroys this object.
 */
ImmobileObject::~ImmobileObject() {}

/**
 *  An entry point for a visitor.
 */
void ImmobileObject::accept(Visitor& visitor) {
    visitor.visit(*this);
}

/**
 *  Implementation of the prototype. Returns a dynamically allocated deep
 *  copy of this object.
 */
ImmobileObject* ImmobileObject::clone() const {
    return new ImmobileObject(*this);
}

/**
 *  Returns the position vector.
 */
vector2 ImmobileObject::getPosition() const {
    return position_;
}

/**
 *  Returns the velocity vector.
 */
vector2 ImmobileObject::getVelocity() const {
    return 0;
}

/**
 *  Sets the position vector.
 */
void ImmobileObject::setPosition(const vector2& pos) {
    position_ = pos;
}

/**
 *  Returns the velocity vector.
 */
void ImmobileObject::setVelocity(const vector2& vel) {}

/**
 *  Returns true if this object is member-wise equal to rhs.
 */
bool ImmobileObject::operator==(const Object &rhs) const {
    if (dynamic_cast<const ImmobileObject*> (&rhs) != nullptr) {
        return (getName() == rhs.getName() && getMass() == rhs.getMass()
            && position_ == rhs.getPosition());
    }
    return false;
}

/**
 *  Returns !(*this == rhs).
 */
bool ImmobileObject::operator!=(const Object &rhs) const {
    return !(*this == rhs);
}

 /**
 *  Initializes an object with the provided properties.
 */
SimpleObject::SimpleObject(const std::string &name, double mass,
        const vector2 &pos, const vector2 &vel) : Object(name, mass),
            position_(pos), velocity_(vel) {}

/**
 *  Destroys this object.
 */
SimpleObject::~SimpleObject() {}

/**
 *  An entry point for a visitor.
 */
void SimpleObject::accept(Visitor &visitor) {
    visitor.visit(*this);
}

/**
 *  Implementation of the prototype. Returns a dynamically allocated deep
 *  copy of this object.
 */
SimpleObject* SimpleObject::clone() const {
    return new SimpleObject(*this);
}

/**
 *  Returns the position vector.
 */
vector2 SimpleObject::getPosition() const {
    return position_;
}

/**
 *  Returns the velocity vector.
 */
vector2 SimpleObject::getVelocity() const {
    return velocity_;
}

/**
 *  Sets the position vector.
 */
void SimpleObject::setPosition(const vector2 &pos) {
    position_ = pos;
}

/**
 *  Sets the velocity vector.
 */
void SimpleObject::setVelocity(const vector2 &vel) {
    velocity_ = vel;
}

/**
 *  Returns true if this object is member-wise equal to rhs.
 */
bool SimpleObject::operator==(const Object &rhs) const {
    if (dynamic_cast<const SimpleObject*>(&rhs) != nullptr) {
        return (getName() == rhs.getName() && getMass() == rhs.getMass()
            && position_ == rhs.getPosition());
    }
    return false;
}

/**
 *  Returns !(*this == rhs).
 */
bool SimpleObject::operator!=(const Object &rhs) const {
    return !(*this == rhs);
}

 /**
 *  Initializes an object with the provided properties.
 */
AggregateObject::AggregateObject(const std::string &name,
        std::vector<Object*> vec) : Object(name, getTotalMass(vec)),
            position_(getAveragePosition(vec)),
                velocity_(getAverageVelocity(vec)),vec_(vec),
                    strategy_(new RigidStrategy) {}

/**
 *  Destroys this object.
 */
AggregateObject::~AggregateObject() {}

/**
 *  An entry point for a visitor.
 */
void AggregateObject::accept(Visitor &visitor) {
    visitor.visit(*this);
}

/**
 *  Implementation of the prototype. Returns a dynamically allocated deep
 *  copy of this object.
 */
AggregateObject* AggregateObject::clone() const {
    return new AggregateObject(*this);
}

/**
 *  returns the position vector.
 */
vector2 AggregateObject::getPosition() const {
    return getAveragePosition(vec_);
}

/**
 *  Returns the velocity vector.
 */
vector2 AggregateObject::getVelocity() const {
    return getAverageVelocity(vec_);
}

/**
 * Sets the aggregate strategy as rigid or realistic
 */
void AggregateObject::setAggregateStrategy(AggregateStrategy *strategy) {
    if (strategy_ != nullptr) {
        delete strategy_;
        strategy_ = nullptr;
    }
    strategy_ = strategy;
}

/*
* Returns the strategy pointer
*/
AggregateStrategy* AggregateObject::getStrategy() const {
    return strategy_->clone();
}

/**
 *  Sets the position vector.
 */
void AggregateObject::setPosition(const vector2 &pos) {
    vector2 change = pos - position_;
    position_ = pos;
    std::for_each(begin(), end(), [&](Object *obj){
        obj->setPosition(obj->getPosition() + change);
    });
}

/**
 *  Sets the velocity vector.
 */
void AggregateObject::setVelocity(const vector2 &vel) {
    vector2 change = vel - velocity_;
    velocity_ = vel;
    std::for_each(begin(), end(), [&](Object *obj){
        obj->setVelocity(obj->getVelocity() + change);
    });
}

/**
 *  Returns true if this object is member-wise equal to rhs.
 */
bool AggregateObject::operator==(const Object &rhs) const {
    if (dynamic_cast<const AggregateObject*>(&rhs) != nullptr) {
        return (getName() == rhs.getName() && getMass() == rhs.getMass()
            && position_ == rhs.getPosition());
    }
    return false;
}

/**
 *  Returns !(*this == rhs).
 */
bool AggregateObject::operator!=(const Object &rhs) const {
    return !(*this == rhs);
}

/**
 * Iterator to begining of AggregateObject vector
 */
typename AggregateObject::iterator AggregateObject::begin() {
    return vec_.begin();
}

/**
 * Constant iterator to begining of AggregateObject vector
 */
typename AggregateObject::const_iterator AggregateObject::begin() const {
    return vec_.begin();
}

/**
 * Iterator to end of AggregateObject vector
 */
typename AggregateObject::iterator AggregateObject::end() {
    return vec_.end();
}

/**
 * Constant iterator to end of AggregateObject vector
 */
typename AggregateObject::const_iterator AggregateObject::end() const {
    return vec_.end();
}

/**
 * returns the average mass
 */
double AggregateObject::getTotalMass(std::vector<Object*> vec) const {
    double mass = 0;
    std::for_each(vec.begin(), vec.end(), [&](Object* obj){
        mass += obj->getMass();
    });
    return mass;
}

/**
 * returns the average position
 */
vector2 AggregateObject::getAveragePosition(std::vector<Object*> vec) const {
    vector2 pos;
    std::for_each(vec.begin(), vec.end(), [&](Object* obj){
        pos += obj->getMass() * obj->getPosition();
    });
    return pos / getTotalMass(vec);
}

/**
 * returns the average position
 */
vector2 AggregateObject::getAverageVelocity(std::vector<Object*> vec) const {
    vector2 vel;
    std::for_each(vec.begin(), vec.end(), [&](Object* obj){
        vel += obj->getMass() * obj->getVelocity();
    });
    return vel / getTotalMass(vec);
}