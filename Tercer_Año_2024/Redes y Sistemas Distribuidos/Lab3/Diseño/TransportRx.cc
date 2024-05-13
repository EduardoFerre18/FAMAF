#ifndef TRANSPORTRX
#define TRANSPORTRX

#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class TransportRx: public cSimpleModule {
private:
    cQueue buffer;
    cMessage *endServiceEvent;
    simtime_t serviceTime;
    cOutVector bufferSizeVector;
    cOutVector packetDropVector;
public:
    TransportRx();
    virtual ~TransportRx();
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(TransportRx);

TransportRx::TransportRx() {
    endServiceEvent = NULL;
}

TransportRx::~TransportRx() {
    cancelAndDelete(endServiceEvent);
}

void TransportRx::initialize() {
    buffer.setName("buffer");
    bufferSizeVector.setName("BufferSizeRx");
    packetDropVector.setName("PacketDropRx");
    endServiceEvent = new cMessage("endService");
}

void TransportRx::finish() {
}

void TransportRx::handleMessage(cMessage *msg) {

    // if msg is signaling an endServiceEvent
    if (msg == endServiceEvent) {
        // if packet in buffer, send next one
        if (!buffer.isEmpty()) {
            // dequeue packet
            cPacket *pkt = (cPacket*) buffer.pop();
            // pkt es feedback
            if(pkt->getKind() == 2){
                send(pkt, "toOut$o");
            }
            // pkt son datos para el sink
            else{
                send(pkt, "toApp");
            }
            // start new service
            serviceTime = pkt->getDuration();
            scheduleAt(simTime() + serviceTime, endServiceEvent);
        }
    } else { // if msg is a data packet
        // si no hay espacio en el buffer, lo ignoro y borro
        if (buffer.getLength() >= par("bufferSize").intValue()) {
            // dropeo el paquete
            delete(msg);
            this->bubble("packet dropped");
            packetDropVector.record(1);
        } else { // si hay espacio, lo tomo
            // enqueue the packet
            cPacket* ack = new cPacket("ack", 2, 0);
            buffer.insert(ack);
            buffer.insert(msg);
            bufferSizeVector.record(buffer.getLength());
            // if the server is idle
            if (!endServiceEvent->isScheduled()) {
                // start the service
                scheduleAt(simTime(), endServiceEvent);
            }
        }
    }
}

#endif /* TRANSPORTRX */

