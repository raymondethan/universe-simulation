/**
 * @file: Object.h
 * @author Ethan Raymond
 * @Description: This file declares the Object class and subclasses
 * @Honor Code: I pledge my honor that I have neither given nor received
    unauthorized aid on this work.
*/

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <string>
#include "Vector.h"
#include "Visitor.h"
#include "AggregateStrategy.h"

// Forward declaration.
class Visitor;
class AggregateStrategy;

/**
 *  Representation of objects suitable for use in the simulation. For this
 *  assignment, this will be the only allowable type. In the future, however,
 *  this class will serve as the abstract base class of the composite pattern.
 *
 *  Krzysztof Zienkiewicz
 */
class Object {
public:

    typedef std::vector<Object*>::iterator iterator;
    typedef std::vector<Object*>::const_iterator const_iterator;

    /**
     *  Initializes an object with the provided properties.
     */
    Object(const std::string &name, double mass);

    /**
     *  Destroys this object.
     */
    virtual ~Object();

    /**
     *  An entry point for a visitor.
     */
    virtual void accept(Visitor &visitor) = 0;

    /**
     *  Implementation of the prototype. Returns a dynamically allocated deep
     *  copy of this object.
     */
    virtual Object* clone() const = 0;

    /*
    * Returns the strategy pointer
    */
    virtual AggregateStrategy* getStrategy() const;

    /**
     *  Returns the mass.
     */
    virtual double getMass() const;

    /**
     *  Returns the name.
     */
    virtual std::string getName() const;

    /**
     *  Returns the position vector.
     */
    virtual vector2 getPosition() const = 0;

    /**
     *  Returns the velocity vector.
     */
    virtual vector2 getVelocity() const = 0;

    /**
     * Sets the aggregate strategy as rigid or realistic
     */
    virtual void setAggregateStrategy(AggregateStrategy *strategy);

    /**
     *  Sets the position vector.
     */
    virtual void setPosition(const vector2 &pos) = 0;

    /**
     *  Sets the velocity vector.
     */
    virtual void setVelocity(const vector2 &vel) = 0;

    /**
     *  Returns true if this object is member-wise equal to rhs.
     */
    virtual bool operator==(const Object &rhs) const = 0;

    /**
     *  Returns !(*this == rhs).
     */
    virtual bool operator!=(const Object &rhs) const = 0;

private:

    /**
     *  Name of the object.
     */
    std::string name_;

    /**
     *  Mass of the object in kilograms.
     */
    double mass_;

};

class ImmobileObject : public Object {
public:

    /**
     *  Initializes an object with the provided properties.
     */
    ImmobileObject(const std::string &name, double mass, const vector2 &pos);

    /**
     *  Destroys this object.
     */
    ~ImmobileObject();

    /**
     *  An entry point for a visitor.
     */
    virtual void accept(Visitor &visitor);

    /**
     *  Implementation of the prototype. Returns a dynamically allocated deep
     *  copy of this object.
     */
    virtual ImmobileObject* clone() const;

    /**
     *  Returns the position vector.
     */
    virtual vector2 getPosition() const;

    /**
     *  Returns the velocity vector.
     */
    virtual vector2 getVelocity() const;

    /**
     *  Sets the position vector.
     */
    virtual void setPosition(const vector2 &pos);

    /**
     *  Returns the velocity vector.
     */
    virtual void setVelocity(const vector2 &vel);

    /**
     *  Returns true if this object is member-wise equal to rhs.
     */
    bool operator==(const Object &rhs) const;

    /**
     *  Returns !(*this == rhs).
     */
    bool operator!=(const Object &rhs) const;

private:

    /**
     *  Position vector of the object in meters.
     */
    vector2 position_;

};

class SimpleObject : public Object {
public:

    /**
     *  Initializes an object with the provided properties.
     */
    SimpleObject(const std::string& name, double mass, const vector2 &pos,
           const vector2 &vel);

    /**
     *  Destroys this object.
     */
    ~SimpleObject();

    /**
     *  An entry point for a visitor.
     */
    virtual void accept(Visitor &visitor);

    /**
     *  Implementation of the prototype. Returns a dynamically allocated deep
     *  copy of this object.
     */
    virtual SimpleObject* clone() const;

    /**
     *  returns the position vector.
     */
    virtual vector2 getPosition() const;

    /**
     *  Returns the velocity vector.
     */
    virtual vector2 getVelocity() const;

    /**
     *  Sets the velocity vector.
     */
    virtual void setPosition(const vector2 &vel);

    /**
     *  Sets the velocity vector.
     */
    virtual void setVelocity(const vector2 &vel);

    /**
     *  Returns true if this object is member-wise equal to rhs.
     */
    bool operator==(const Object &rhs) const;

    /**
     *  Returns !(*this == rhs).
     */
    bool operator!=(const Object &rhs) const;

private:

    /**
     *  Position vector of the object in meters.
     */
    vector2 position_;

    /**
     *  Velocity vector of the object in meters/second.
     */
    vector2 velocity_;
};

class AggregateObject : public Object {
public:

    /**
     *  Initializes an object with the provided properties.
     */
    AggregateObject(const std::string &name, std::vector<Object*> vec);

    /**
     *  Destroys this object.
     */
    ~AggregateObject();

    /**
     * Iterator to begining of AggregateObject vector
     */
    iterator begin();

    /**
     * Constant iterator to begining of AggregateObject vector
     */
    const_iterator begin() const;

    /**
     * Iterator to end of AggregateObject vector
     */
    iterator end();

    /**
     * Constant iterator to end of AggregateObject vector
     */
    const_iterator end() const;

    /**
     *  An entry point for a visitor.
     */
    virtual void accept(Visitor &visitor);

    /**
     *  Implementation of the prototype. Returns a dynamically allocated deep
     *  copy of this object.
     */
    virtual AggregateObject* clone() const;

    /**
     *  returns the position vector.
     */
    virtual vector2 getPosition() const;

    /**
     *  Returns the velocity vector.
     */
    virtual vector2 getVelocity() const;

    /**
     * Sets the aggregate strategy as rigid or realistic
     */
    virtual void setAggregateStrategy(AggregateStrategy *strategy);

    /*
    * Returns the strategy pointer
    */
    virtual AggregateStrategy* getStrategy() const;

    /**
     *  Sets the position vector.
     */
    virtual void setPosition(const vector2 &pos);

    /**
     *  Sets the velocity vector.
     */
    virtual void setVelocity(const vector2 &vel);

    /**
     *  Returns true if this object is member-wise equal to rhs.
     */
    bool operator==(const Object &rhs) const;

    /**
     *  Returns !(*this == rhs).
     */
    bool operator!=(const Object &rhs) const;

private:

    /**
     *  Position vector of the object in meters.
     */
    vector2 position_;
    
    /**
     *  Velocity vector of the object in meters/second.
     */
    vector2 velocity_;

    /**
     * Vector containing the objects
     */
    std::vector<Object*> vec_;

    /**
     * Strategy
     **/
    AggregateStrategy* strategy_;

    //Private methods to initialize private data members

    /**
     * returns the average mass
     */
    double getTotalMass(std::vector<Object*> vec) const;

    /**
     * returns the average position
     */
    vector2 getAveragePosition(std::vector<Object*> vec) const;

    /**
     * returns the average position
     */
     vector2 getAverageVelocity(std::vector<Object*> vec) const;
};

#endif
