#include "Universe.h"
#include "Object.h"
#include <memory>
#include <iostream>
#include <cassert>
#include "Visitor.h"
#include <cstdlib>
#include <sstream>

#include "AggregateStrategy.h"

// IPC code. Poorly written to give the grad students a hard time.
void writeString(std::string str) {
    const char* s = str.c_str();
    std::cout.write(s, str.length());
    std::cout.put(0);
    std::cout.flush();
}

void writeOpcode(char op) {
    std::cout.put(op);
    std::cout.flush();
}

void writeInt(int i) {
    std::cout.write((char*) &i, 4);
    std::cout.flush();
}

void writeFlush() {
    std::cout.put(0);
    std::cout.flush();
}

void drawCircle(int x, int y, int r) {
    writeOpcode(1);
    int d = r / 2;
    writeInt(x - d);
    writeInt(y - d);
    writeInt(2 * r);
    writeInt(2 * r);
}

void drawString(std::string str, int x, int y) {
    writeOpcode(2);
    writeString(str);
    writeInt(x);
    writeInt(y);
}

double minx, miny, maxx, maxy;
int sw, sh;

int convertX(double x) {
    double range = maxx - minx;
    return sw * (x - minx) / range;
}

int convertY(double y) {
    double range = maxy - miny;
    return sh * (maxy - y) / range;
}

class UgradDrawerVisitor : public Visitor {
public:

    void visit(SimpleObject& object) {
        drawCircle(convertX(object.getPosition()[0]),
                   convertY(object.getPosition()[1]), 10);
        drawString(object.getName(), convertX(object.getPosition()[0]),
                   convertY(object.getPosition()[1]));
    }

    void visit(ImmobileObject& object) {
        drawCircle(convertX(object.getPosition()[0]),
                   convertY(object.getPosition()[1]), 20);
        drawString(object.getName(), convertX(object.getPosition()[0]),
                   convertY(object.getPosition()[1]));
    }

    void visit(AggregateObject& object) {
        for (AggregateObject::const_iterator i = object.begin();
                            i != object.end(); ++i)
            (**i).accept(*this);
    }

};

// end IPC code.

SimpleObject* makeSimpleObject(std::string n, double m = 0,
                               vector2 p = vector2(), vector2 v = vector2()) {

    return new SimpleObject(n, m, p, v);
}

ImmobileObject* makeImmobileObject(std::string n, double m = 0,
                                   vector2 p = vector2()) {
    return new ImmobileObject(n, m, p);
}

AggregateObject* makeAggregateObject(std::string n, std::vector<Object*> v) {
    return new AggregateObject(n, v);
}

vector2 makeVector2(double x = 0, double y = 0) {
    vector2 v;
    v[0] = x;
    v[1] = y;
    return v;
}

void createUniverse() {
    Object* sun = makeImmobileObject("sun", 1.98892e30);


    vector2 position = makeVector2(149597870700.0, 0);
    vector2 velocity = makeVector2(0, 29788.4676);
    Object* obj1 = makeSimpleObject("earth1", 5.9742e24, position, velocity);

    position = makeVector2(-149597870700.0, 0);
    velocity = makeVector2(0, -29788.4676);
    Object* obj2 = makeSimpleObject("earth2", 5.9742e24, position, velocity);

    velocity = makeVector2(-29788.4676, 0);
    position = makeVector2(0, 149597870700.0);
    vector2 dx = makeVector2(10000, 0);
    vector2 dy = makeVector2(0, 10000);

    Object* r1 = makeSimpleObject("r1", 1.49355e24, position + dy, velocity);
    Object* r2 = makeSimpleObject("r2", 1.49355e24, position - dx, velocity);
    Object* r3 = makeSimpleObject("r3", 1.49355e24, position - dy, velocity);
    Object* r4 = makeSimpleObject("r4", 1.49355e24, position + dx, velocity);

    std::vector<Object*> rigidV;
    rigidV.push_back(r1);
    rigidV.push_back(r2);
    rigidV.push_back(r3);
    rigidV.push_back(r4);
    AggregateObject* rigid = makeAggregateObject("rigid", rigidV);
    rigid->setAggregateStrategy(new RigidStrategy());

    velocity = makeVector2(29788.4676, 0);
    position = makeVector2(0, -149597870700.0);

    Object* f1 = makeSimpleObject("f1", 1.49355e24, position + dy, velocity);
    Object* f2 = makeSimpleObject("f2", 1.49355e24, position - dx, velocity);
    Object* f3 = makeSimpleObject("f3", 1.49355e24, position - dy, velocity);
    Object* f4 = makeSimpleObject("f4", 1.49355e24, position + dx, velocity);

    std::vector<Object*> realV;
    realV.push_back(f1);
    realV.push_back(f2);
    realV.push_back(f3);
    realV.push_back(f4);
    AggregateObject* real = makeAggregateObject("real", realV);
    real->setAggregateStrategy(new RealisticStrategy());


    Universe* u(Universe::instance());
    u->addObject(sun);
    u->addObject(obj1);
    u->addObject(obj2);
    u->addObject(rigid);
    u->addObject(real);
}

void visitorTest() {
    std::stringstream stream;
    Universe* u(Universe::instance());

    PrintVisitor printer(stream);
    for (Universe::iterator i = u->begin(); i != u->end(); ++i)
        (*i)->accept(printer);

    stream.flush();
    if (stream.str() != "sunearth1earth2rigidr1r2r3r4realf1f2f3f4") {
        std::cerr << "Failed visitor test.";
        std::exit(1);
    }
}


void test(const double step = 100) {
    Universe* u(Universe::instance());

    maxx = 200000000000.0;
    maxy = maxx;
    minx = -maxx;
    miny = -maxy;

    sw = sh = 500;

    const double year_s = 31554195.932106005998594489072144;

    UgradDrawerVisitor v;

    for (double time = 0; time < year_s; time += step) {
        u->stepSimulation(step);
        for (Universe::const_iterator i = u->begin(); i != u->end(); ++i)
            (**i).accept(v);
        writeFlush();
    }
}

int getIntSize() {
    return sizeof(int);
}

bool isLittleEndian() {
    unsigned int num = 1;
    char* ptr = (char*) &num;
    return *ptr == 1;
}

void assertPreconditions() {
    if (!isLittleEndian()) {
        std::cerr << "Incompatible byte order detected." << std::endl;
        std::exit(1);
    }

    if (getIntSize() != 4) {
        std::cerr << "Incompatible integer size detected." << std::endl;
        std::exit(1);
    }
}

int main(int argc, const char* argv[]) {
    std::auto_ptr<Universe> u(Universe::instance());
    createUniverse();

    if (argc == 1) {
        assertPreconditions();
        visitorTest();

    } else
        test();

    return 0;
}
