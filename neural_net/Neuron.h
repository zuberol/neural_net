
#ifndef NEURAL_NET_NEURON_H
#define NEURAL_NET_NEURON_H

#include <vector>
#include <iostream>

using namespace std;

class Neuron{
public:
    Neuron(unsigned layer_num, unsigned index_in_layer);
    ~Neuron();
    vector<double *> inputs;
    vector<double *> outputs;
    vector<double *> next_layer_weights;
    vector<double *> previous_layer_weights;
    unsigned const index_in_layer;
    unsigned const layer_num ;

    void feed_forward();

    //Back_prop
    double transfer_function(double);
    static double transfer_function_derivative(double);
    double sum();

    void calculate_hidden_layer_delta();
    void calculate_output_layer_delta(double &target);
    void update_previous_layer_weights();               //todo   +/-

    double bias;
    static double eta;
    double delta;
    vector<double *> next_layer_delta;

};


#endif //NEURAL_NET_NEURON_H
