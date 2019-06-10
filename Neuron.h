
#ifndef NEURAL_NET_NEURON_H
#define NEURAL_NET_NEURON_H

#include <vector>
#include <iostream>

using namespace std;

class Neuron{
public:
    Neuron(unsigned layer_num, unsigned index_in_layer);
    ~Neuron();

    //Neuron atributes
    unsigned const index_in_layer;
    unsigned const layer_num ;
    vector<double *> inputs;
    vector<double *> outputs;   // outputs basically == activation
    static double eta;          //learning rate // 0.15
    static double alpha;        //momentum      // 0.5
    double bias;
    double delta;
    double old_delta;

    //Feed_forward
    void feed_forward();
    double transfer_function(double);
    double z_sum();

    //Back_prop
    vector<double *> next_layer_delta;
    vector<double *> next_layer_weights;
    vector<double *> previous_layer_weights;
    void calculate_hidden_layer_delta();
    void calculate_output_layer_delta(double &target);
    double transfer_function_derivative(double);
    void update_previous_layer_weights();



};


#endif //NEURAL_NET_NEURON_H
