#ifndef SINK
#define SINK

#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Sink : public cSimpleModule {
private:
    cStdDev delayStats;
    cOutVector delayVector;
    cOutVector packetUsedVector;
    long packetsProcessed;
public:
    Sink();
    virtual ~Sink();
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(Sink);

Sink::Sink() {
}

Sink::~Sink() {
}

void Sink::initialize(){
    // stats and vector names
    delayStats.setName("TotalDelay");
    delayVector.setName("Delay");
    packetUsedVector.setName("PacketUsed");
    packetsProcessed = 0; // inicializo la cuenta de los paquetes procesados
}

void Sink::finish(){
    // stats record at the end of simulation
    double packetsPerSecond = packetsProcessed / simTime().dbl(); // calculo paquetes recibidos por segundo
    recordScalar("Packets per second received", packetsPerSecond); // registro el valor
    recordScalar("Avg delay", delayStats.getMean());
    recordScalar("Number of packets", delayStats.getCount());
}

void Sink::handleMessage(cMessage * msg) {
    // compute queuing delay
    simtime_t delay = simTime() - msg->getCreationTime();
    // update stats
    delayStats.collect(delay);
    delayVector.record(delay);
    packetsProcessed++;
    packetUsedVector.record(packetsProcessed);
    // delete msg
    delete(msg);
}

#endif /* SINK */
