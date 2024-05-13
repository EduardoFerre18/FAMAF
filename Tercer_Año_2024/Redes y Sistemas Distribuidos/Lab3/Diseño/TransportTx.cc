#ifndef TRANSPORTTX
#define TRANSPORTTX

#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class TransportTx: public cSimpleModule {
private:
    cQueue buffer;
    cMessage *endServiceEvent;
    simtime_t serviceTime;
    cOutVector bufferSizeVector;
    cOutVector packetDropVector;
    bool waiting;
public:
    TransportTx();
    virtual ~TransportTx();
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(TransportTx);

TransportTx::TransportTx() {
    endServiceEvent = NULL;
    waiting = false;
}

TransportTx::~TransportTx() {
    cancelAndDelete(endServiceEvent);
}

void TransportTx::initialize() {
    buffer.setName("buffer");
    bufferSizeVector.setName("BufferSizeTx");
    packetDropVector.setName("PacketDropTx");
    endServiceEvent = new cMessage("endService");
}

void TransportTx::finish() {
}

void TransportTx::handleMessage(cMessage *msg) {

    // if msg is signaling an endServiceEvent
    if (msg == endServiceEvent) {
        // si no esta esperando y hay paquetes para enviar,
        // enviar paquete y esperar el ack
        if (!waiting && !buffer.isEmpty()) {
            // dequeue packet
            cPacket* pkt = (cPacket*) buffer.pop();
            // send packet
            send(pkt, "toOut$o");
            waiting = true;
            // start new service
            serviceTime = pkt->getDuration();
            scheduleAt(simTime() + serviceTime, endServiceEvent);
        }
    } else {
        if (buffer.getLength() >= par("bufferSize").intValue()) {
            // dropeo el paquete
            delete(msg);
            this->bubble("packet dropped");
            packetDropVector.record(1);
        } else {
            // el paquete es un ack
            if(msg->getKind() == 2){
                waiting = false;
                delete msg;
            }
            // el paquete viene de gen
            else{
                buffer.insert(msg);
                bufferSizeVector.record(buffer.getLength());
            }
            // if the server is idle
            if (!endServiceEvent->isScheduled()) {
                // start the service
                scheduleAt(simTime(), endServiceEvent);
            }
        }
    }
}

#endif /* TRANSPORTTX */
