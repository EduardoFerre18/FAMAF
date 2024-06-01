#ifndef NET
#define NET

#include <string.h>
#include <omnetpp.h>
#include <packet_m.h>

using namespace omnetpp;

int lnk0Uses;
int lnk1Uses;

class Net: public cSimpleModule {
private:
    cOutVector pktHops[8];
    cOutVector pktDuration[8];
    cOutVector lnk0TimesUsed;
    cOutVector lnk1TimesUsed;
    cMessage *sendEchoEvent;
    simtime_t table[2];
public:
    Net();
    virtual ~Net();
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(Net);

#endif /* NET */

Net::Net() {
}

Net::~Net() {
}

void Net::initialize() {
    table[0] = 1;
    table[1] = 1;
    lnk0TimesUsed.setName("envios por lnk0");
    lnk1TimesUsed.setName("envios por lnk1");
    lnk0Uses = 0;
    lnk1Uses = 0;
    for(int i = 0 ; i<8; i++){
        // nombres para vectores que cuentan saltos
        char nombrePktHops[9 + sizeof(char)];
        std::sprintf(nombrePktHops, "Hops de %d", i);
        pktHops[i].setName(nombrePktHops);
        // nombres para vectores de duracion de paquetes
        char nombrePktDuration[13 + sizeof(char)];
        std::sprintf(nombrePktDuration, "duracion de %d", i);
        pktDuration[i].setName(nombrePktDuration);
    }

    sendEchoEvent = new cMessage("echoEvent");
    scheduleAt(2, sendEchoEvent);

}

void Net::finish() {
}

void Net::handleMessage(cMessage *msg) {
    if(msg == sendEchoEvent){
        Packet *echo0 = new Packet("echo0");
        echo0->setSource(this->getParentModule()->getIndex());
        // el destino de un paquete echo es el mismo nodo por el que salio
        echo0->setDestination(this->getParentModule()->getIndex());
        Packet *echo1 = new Packet("echo1");
        echo1->setSource(this->getParentModule()->getIndex());
        echo1->setDestination(this->getParentModule()->getIndex());
        send(echo0, "toLnk$o", 0);
        send(echo1, "toLnk$o", 1);
        scheduleAt(simTime() + 2, sendEchoEvent);
    }
    else{
        Packet *pkt = (Packet *) msg;
        // veo si estoy en destino
        if (pkt->getDestination() == this->getParentModule()->getIndex()) {
            // veo si tengo echo y de que enlace es,
            // y pongo la demora del enlace en table
            if(strcmp(pkt->getName(), "echo0") == 0){
                simtime_t delta = simTime() - pkt->getCreationTime();
                std::cout << delta <<"\n";
                table[0] = delta;
                delete pkt;
            }
            else if(strcmp(pkt->getName(), "echo1") == 0){
                simtime_t delta = simTime() - pkt->getCreationTime();
                std::cout << delta <<"\n";
                table[1] = delta;
                delete pkt;
            }
            // si no es echo, son datos para la app
            else{
                send(msg, "toApp$o");
                lnk0TimesUsed.record(lnk0Uses);
                lnk1TimesUsed.record(lnk0Uses);
                for(int i = 0 ; i<8; i++){
                    if(pkt->getSource() == i){
                        pktHops[i].record(pkt->getHopCount());
                        pktDuration[i].record(pkt->getArrivalTime() - pkt->getCreationTime());
                    }
                }
            }
        }
        // si no estoy en destino
        else {
            // si estoy en la fuente, tomo el enlace mas rapido
            if(pkt->getSource() == this->getParentModule()->getIndex()){
                pkt->setHopCount(pkt->getHopCount() + 1);
                if(table[0] < table[1]){
                    send(msg, "toLnk$o", 0);
                    lnk0Uses++;
                }
                else{
                    send(msg, "toLnk$o", 1);
                    lnk1Uses++;
                }
            }
            // si no estoy en la fuente
            else{
                for(int i = 0 ; i<8; i++){
                    if(pkt->getSource() == i){
                        // cuento saltos en cada nodo que no es el destino y agrego esa
                        // info al paquete
                        pkt->setHopCount(pkt->getHopCount() + 1);
                    }
                }
                if(strcmp(pkt->getName(), "echo0") == 0){
                    send(msg, "toLnk$o", 1);
                    lnk1Uses++;
                }
                else if(strcmp(pkt->getName(), "echo1") == 0){
                    send(msg, "toLnk$o", 0);
                    lnk0Uses++;
                }
                // si no es un echo, tengo que enviar
                // por el enlace distinto del enlace
                // por el que llego el paquete
                // (para evitar loops)
                else if(pkt->arrivedOn("toLnk$i", 1)){
                    send(msg, "toLnk$o", 0);
                    lnk0Uses++;
                }
                else if(pkt->arrivedOn("toLnk$i", 0)){
                    send(msg, "toLnk$o", 1);
                    lnk1Uses++;
                }
            }
        }
    }
}
