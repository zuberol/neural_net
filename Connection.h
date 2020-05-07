#ifndef NEURAL_NET_CONNECTION_H
#define NEURAL_NET_CONNECTION_H

#include "Neuron.h"

class Connection{
    public:
        Connection(Neuron &neuronA, Neuron &neuronB);
        double weight;
        int index_A;
        int index_B;
        int layerA;
        int layerB;
    private:
        void connect_neurons(Neuron &neuronA, Neuron &neuronB);
};



#endif //NEURAL_NET_CONNECTION_H
