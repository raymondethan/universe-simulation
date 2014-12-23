/**
 * @file: Visitor.h
 * @author Ethan Raymond
 * @Description: This file declares the Visitor class and its subclasses
 * @Honor Code: I pledge my honor that I have neither given nor received
    unauthorized aid on this work.
*/

#ifndef _VISITOR_H_
#define _VISITOR_H_

#include <ostream>
#include <vector>
#include "Object.h"
#include "Universe.h"

// Forward declaration.
class Object;
class ImmobileObject;
class SimpleObject;
class AggregateObject;

/**
 *  Abstract base class for the Visitor pattern.
 *
 *  Krzysztof Zienkiewicz
 */
class Visitor {
public:

    /**
     *  Pure virtual destructor. A necessary no-op since this is a base class.
     */
    virtual ~Visitor() = 0;

    /**
     *  The worker method of the visitor. For this assignment, Object is the
     *  only concrete class we can visit.
     */
    virtual void visit(ImmobileObject& object);

    /**
     *  The worker method of the visitor. For this assignment, Object is the
     *  only concrete class we can visit.
     */
    virtual void visit(SimpleObject& object);

    /**
     *  The worker method of the visitor. For this assignment, Object is the
     *  only concrete class we can visit.
     */
    virtual void visit(AggregateObject& object);
};

/**
 *  A visitor that accepts an ostream reference during construction. Its visit
 *  method simply prints out the object's name.
 */
class PrintVisitor : public Visitor {
public:

    /**
     *  Construct a visitor that prints to the provided ostream.
     */
    PrintVisitor(std::ostream& os);

    /**
     *  Prints the object's name.
     */
    virtual void visit(ImmobileObject& object);

    /**
     *  Prints the object's name.
     */
    virtual void visit(SimpleObject& object);

    /**
     *  Prints the object's name.
     */
    virtual void visit(AggregateObject& object);

private:
    /**
     *  Reference to the ostream.
     */
    std::ostream& os_;
};


/**
 *  A visitor that accepts an ostream reference during construction. Its visit
 *  method simply prints out the object's name.
 */
class MoverVisitor : public Visitor {
public:

    /**
     * Constructor
     */
    MoverVisitor(double seconds);

    /**
     *  Returns the modified copy
     */
    Object* getObject();

    /**
     *  Moves the simple object.
     */
    virtual void visit(SimpleObject &object);

    /**
     *  Does nothing for an immobile object.
     */
    virtual void visit(ImmobileObject &object);

    /**
     *  Moves the aggregate object.
     */
    virtual void visit(AggregateObject &object);

private:

    /**
     * Number of seconds to step
     */
    double seconds_;

    /**
     * A copy of the Object to modify without changing the snapshot
     */
    Object* copy;

};

#endif
