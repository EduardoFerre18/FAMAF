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
}

void Net::finish() {
}

void Net::handleMessage(cMessage *msg) {

    // All msg (events) on net are packets
    Packet *pkt = (Packet *) msg;

    // If this node is the final destination, send to App
    if (pkt->getDestination() == this->getParentModule()->getIndex()) {
        send(msg, "toApp$o");
        lnk0TimesUsed.record(lnk0Uses);
        for(int i = 0 ; i<8; i++){
            if(pkt->getSource() == i){
                pktHops[i].record(pkt->getHopCount());
                pktDuration[i].record(pkt->getArrivalTime() - pkt->getCreationTime());
            }
        }

    }
    // If not, forward the packet to some else... to who?
    else {
        // We send to link interface #0, which is the
        // one connected to the clockwise side of the ring
        // Is this the best choice? are there others?

        // sumo a la cant de veces que se manda a lnk0 y lo registro con el vector
        send(msg, "toLnk$o", 0);
        lnk0Uses++;

        // de momento no registro para lnk1 porque no lo usa por ahora
        // pero seria algo como esto

        //if(sendAntiClockwise){
        //send(msg, "tolnk$o", 1)
        //lnk1Uses++;
        //}

        // tipo, me parece que facilitaria tener al algoritmo que decida si
        // ir clockwise o anticlockwise y de ahi mandar para lnk0 o lnk1,
        // respectivamente (tipo para modularizar un cacho y aca nomas aumentar
        // las variables de cantidad de veces que se eligio mandar para ese
        // lado)
        // tambien mepa que mejor registrar en el vector esto de cant de veces
        // que se usa cada link en el nodo de destino, asi no hay 700 vectores
        // (porque cada nodo tendria su vector de esto y todos indicarian lo
        // mismo, mejor que lo tenga nomas el de destino), aparte, despues de
        // legar al destino no se va a mandar por ningun lnk asi que no va a
        // arruinar nada creo

        for(int i = 0 ; i<8; i++){
            if(pkt->getSource() == i){
                // cuento saltos en cada nodo que no es el destino y agrego esa
                // info al paquete
                pkt->setHopCount(pkt->getHopCount() + 1);
            }
        }
    }
}
