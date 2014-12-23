/**
 * @file: Universe.cpp
 * @author Ethan Raymond
 * @Description: This file implements the Universe class
 * @Honor Code: I pledge my honor that I have neither given nor received
    unauthorized aid on this work.
*/

#include "Universe.h"

Universe *Universe::myInstance = nullptr;

/**
 *  Calculates the force vector between obj1 and obj2. The direction of the
 *  result is as experienced by obj1. Negate the result to obtain force
 *  experianced by obj2.
 */
vector2 Universe::getForce(const Object& obj1, const Object& obj2) {
    double constant = Universe::G * (obj1.getMass() * obj2.getMass());
    vector2 tmp(obj2.getPosition() - obj1.getPosition());
    if (obj1.getPosition() != obj2.getPosition()) {
        tmp =  tmp.normalize() * constant / tmp.normSq();
    }
    return tmp;
}

/**
* Creates an instance of the Universe class
*/
Universe *Universe::instance() {
    if (myInstance == nullptr) {
        myInstance = new Universe();
    }
    return myInstance;
}

/**
 *  Releases all the dynamic objects still registered with the Universe.
 */
Universe::~Universe() {
    release(objects_);
    myInstance = nullptr;
}

/**
 *  Registers an Object with the universe. The Universe will clean up this
 *  object when it deems necessary.
 */
void Universe::addObject(Object* ptr) {
    objects_.push_back(ptr);
}

/**
 *  Returns the begin iterator to the actual Objects. The order of itetarion
 *  will be the same as that over getSnapshot()'s result as long as no new
 *  objects are added to either of the containers.
 */
typename Universe::iterator Universe::begin() {
    return objects_.begin();
}

/**
 *  Returns the begin iterator to the actual Objects. The order of itetarion
 *  will be the same as that over getSnapshot()'s result as long as no new
 *  objects are added to either of the containers.
 */
typename Universe::const_iterator Universe::begin() const {
    return objects_.begin();
}

/**
 *  Returns the end iterator to the actual Objects. The order of itetarion
 *  will be the same as that over getSnapshot()'s result as long as no new
 *  objects are added to either of the containers.
 */
typename Universe::iterator Universe::end() {
    return objects_.end();
}

/**
 *  Returns the end iterator to the actual Objects. The order of itetarion
 *  will be the same as that over getSnapshot()'s result as long as no new
 *  objects are added to either of the containers.
 */
typename Universe::const_iterator Universe::end() const {
    return objects_.end();
}

/**
 *  Returns a container of copies of all the Objects registered with the
 *  Universe. This should be used as the source of data for computing the
 *  next step in the simulation
 */
std::vector<Object*> Universe::getSnapshot() const {
    std::vector<Object*> tmp;
    tmp.reserve(objects_.size());
    std::for_each(begin(), end(), [&](Object *obj){
        tmp.push_back(obj->clone());
    });
    return tmp;
}

/**
 *  Advances the simulation by the provided time step. For this assignment,
 *  you may assume that the first registered object is a "sun" and its
 *  position should not be affected by any of the other objects.
 */
void Universe::stepSimulation(double seconds) {
    std::vector<Object*> tmp;
    MoverVisitor mover(seconds);
    for (size_t i = 0; i < objects_.size(); ++i) {
        objects_[i]->accept(mover);
        tmp.push_back(mover.getObject());
    }
    swap(tmp);
}

/**
 *  Swaps the contants of the provided container with the Universe's Object
 *  store and releases the old Objects.
 */
void Universe::swap(std::vector<Object*>& snapshot) {
    objects_.swap(snapshot);
    release(snapshot);
}

/**
 *  Calls delete on each pointer and removes it from the container.
 */
void Universe::release(std::vector<Object*>& objects) {
    std::for_each(objects.begin(), objects.end(),
        std::default_delete<Object>());
    objects.clear();
}

/**
* Private constructor
*/
Universe::Universe() {}
