/**
 * @file: AggregateStrategy.h
 * @author Ethan Raymond
 * @Description: This file declares the aggregate strategy classes
 * @Honor Code: I pledge my honor that I have neither given nor received
    unauthorized aid on this work.
*/

#ifndef _AGGREGATE_STRATEGY_H_
#define _AGGREGATE_STRATEGY_H_

#include <vector>
#include "Vector.h"
#include "Universe.h"
#include "Object.h"

//Forward declaration
class Object;
class AggregateObject;

class AggregateStrategy {
public:

    /**
     * Destructor
     */
    virtual ~AggregateStrategy() = 0;

    /**
     * Clone method
     */
    virtual AggregateStrategy* clone() = 0;

    /**
     * Moves the Object for the given number of seconds
     */
    virtual void move(double seconds, AggregateObject &obj);

};

class RigidStrategy : public AggregateStrategy {
public:

    /**
     * Destructor
     */
    ~RigidStrategy();

    /**
     * Clone method
     */
    virtual AggregateStrategy* clone();

    /**
     * Moves the Object for the given number of seconds
     */
    void move(double seconds, AggregateObject &obj);

};

class RealisticStrategy : public AggregateStrategy {
public:

    /**
     * Destructor
     */
    ~RealisticStrategy();

    /**
     * Clone method
     */
    virtual AggregateStrategy* clone();

    /**
     * Moves the Object for the given number of seconds
     */
    void move(double seconds, AggregateObject &obj);

};

#endif