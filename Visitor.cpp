/**
 * @file: Visitor.cpp
 * @author Ethan Raymond
 * @Description: This file implements the Visitor class and its subclasses
 * @Honor Code: I pledge my honor that I have neither given nor received
    unauthorized aid on this work.
*/

#include "Visitor.h"

/**
 *  Pure virtual destructor. A necessary no-op since this is a base class.
 */
Visitor::~Visitor() {}

/**
 *  The worker method of the visitor. For this assignment, Object is the
 *  only concrete class we can visit.
 */
void Visitor::visit(ImmobileObject& object) {}

/**
 *  The worker method of the visitor. For this assignment, Object is the
 *  only concrete class we can visit.
 */
void Visitor::visit(SimpleObject& object) {}

/**
 *  The worker method of the visitor. For this assignment, Object is the
 *  only concrete class we can visit.
 */
void Visitor::visit(AggregateObject& object) {}

/**
 *  Construct a visitor that prints to the provided ostream.
 */
PrintVisitor::PrintVisitor(std::ostream& os) : os_(os) {}

/**
 *  Prints the immobile object's name.
 */
void PrintVisitor::visit(ImmobileObject& object) {
    os_ << object.getName();
}

/**
 *  Prints the simple object's name.
 */
void PrintVisitor::visit(SimpleObject& object) {
    os_ << object.getName();
}

/**
 *  Prints the aggregate object's name.
 */
void PrintVisitor::visit(AggregateObject& object) {
    std::string name = object.getName();
    std::for_each(object.begin(), object.end(), [&](Object* obj){
        name += obj->getName();
    });
    os_ << name;
}


/**
 * Constructor
 */
MoverVisitor::MoverVisitor(double seconds) :
    seconds_(seconds), copy(nullptr) {};

Object* MoverVisitor::getObject() {
    return copy;
}

/**
 *  Moves the simple object.
 */
void MoverVisitor::visit(SimpleObject &object){
    Universe* univ(Universe::instance());
    copy = object.clone();
    vector2 totalForce;
    std::for_each(univ->begin(), univ->end(), [&](Object* otherObj){
        totalForce += Universe::getForce(*copy, *otherObj);
    });
    vector2 accel = totalForce / object.getMass();
    vector2 changeVel = accel * seconds_;
    vector2 vel = object.getVelocity() + changeVel;
    copy->setVelocity(vel);
    vector2 pos = object.getPosition() + vel * seconds_;
    copy->setPosition(pos);
}

/**
 *  Does nothing for an immobile object.
 */
void MoverVisitor::visit(ImmobileObject &object) {
    copy = object.clone();
}

/**
 *  Moves the aggregate object.
 */
void MoverVisitor::visit(AggregateObject &object){
    copy = object.clone();
    copy->getStrategy()->move(seconds_,
        *(dynamic_cast<AggregateObject*> (copy)));
}