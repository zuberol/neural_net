#include "Connection.h"
#include <random>
#include <iostream>

Connection::Connection(Neuron &neuronA, Neuron &neuronB) {

    //initialize neurons output weights by ref
    neuronA.next_layer_weights.push_back(&weight);
    neuronB.previous_layer_weights.push_back(&weight);


    //initialize index'es
    index_A = neuronA.index_in_layer;
    index_B = neuronB.index_in_layer;
    layerA = neuronA.layer_num;
    layerB = neuronB.layer_num;

    weight = random() / double(RAND_MAX);


    connect_neurons(neuronA, neuronB);  //outA == inB & delta_B for neuronA

}

void Connection::connect_neurons(Neuron &neuronA, Neuron &neuronB){

    //make them
    neuronA.outputs.push_back(new double());   //free in ~Net()
    double* &ref = neuronA.outputs.back();
    neuronB.inputs.push_back(ref);

    //give neuronA acces to neuronB's delta
    neuronA.next_layer_delta.push_back(&neuronB.delta);

}
