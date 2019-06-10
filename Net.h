#ifndef NEURAL_NET_NET_H
#define NEURAL_NET_NET_H

#include "Neuron.h"
#include "Connection.h"
#include <vector>
using namespace std;

typedef vector<Neuron> Layer;
typedef vector<Connection *> Neuron_c;
typedef vector<Neuron_c> Layer_c;

class Net{
public:
    explicit Net(const vector<unsigned> &topology);
    ~Net();

    void Feed_forward(vector<double> &inputs);
    void Back_propagation(vector<double> &targets);
    void print_result();

private:
    vector<unsigned> const topology;
    vector<double *> Inputs;
    vector<double *> Outputs;
    double cost;
    double calculate_cost(vector<double> &targets);
    vector<Layer> net_matrix;  //[layer][neuron]
    vector<Layer_c> matrix_of_connections; //[layer][neuron][connection]
};


#endif //NEURAL_NET_NET_H
