#include "Net.h"
#include "Neuron.h"
#include <vector>
#include "Connection.h"
#include <random>
#include <math.h>


typedef vector<Neuron> Layer;
typedef vector<Connection *> Neuron_c;
typedef vector<Neuron_c> Layer_c;

Net::Net(const vector<unsigned> &topolog) : topology(topolog) {
    unsigned numLayers = topology.size();

    //create layers and add them to the net_matrix
    for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum) {
        net_matrix.push_back(Layer());

        //create neurons
        for (unsigned neuron_num = 0; neuron_num < topology[layerNum]; ++neuron_num) {
            net_matrix.back().push_back(Neuron(layerNum, neuron_num));
        }
    }

    //make Connection objects and with their help connect Hidden layers
    for(unsigned layerNum=0; layerNum<numLayers - 1; ++layerNum){
        //make connection layers
        matrix_of_connections.push_back(Layer_c());
        for(unsigned neuron_numb=0; neuron_numb<topology[layerNum]; ++neuron_numb){
            //make new Neuron_c vector
            matrix_of_connections.back().push_back(Neuron_c());
            for(unsigned neuron_to_connect=0; neuron_to_connect<topology[layerNum+1]; ++neuron_to_connect){
                //make output vectors for each Neuron in layer
                matrix_of_connections.back().back().push_back(new Connection(net_matrix[layerNum][neuron_numb], net_matrix[layerNum + 1][neuron_to_connect]));
            }
        }
    }


    //make and initialize Nets Outputs
    for(unsigned neuron_num=0; neuron_num<topology.back(); ++neuron_num){

        //make space on heap
        Outputs.push_back(new double());    //free in ~Net()
        net_matrix.back()[neuron_num].outputs.push_back(Outputs.back());

    }

    //make and initialize Nets Inputs
    for(unsigned neuron_num=0; neuron_num<topology.front(); ++neuron_num){

        //make space on heap
        Inputs.push_back(new double());    //free in ~Net()
        net_matrix.front()[neuron_num].inputs.push_back(Inputs.back());

    }

}

Net::~Net() {
    unsigned numLayers = topology.size();

    //free Connections objects (stored in matrix_of_connections)
    for(unsigned layerNum=0; layerNum<numLayers - 1; ++layerNum){
        for(unsigned neuron_numb=0; neuron_numb<topology[layerNum]; ++neuron_numb){
            for(unsigned neuron_to_connect=0; neuron_to_connect<topology[layerNum+1]; ++neuron_to_connect){
                delete matrix_of_connections[layerNum][neuron_numb][neuron_to_connect];
              //  cout<<"#free_connections"<<endl;
            }
        }
    }

    //free outputs and inputs of neurons
    for(unsigned layerNum=0; layerNum<numLayers; ++layerNum){
        for(unsigned neuron_numb=0; neuron_numb<topology[layerNum]; ++neuron_numb){
            unsigned long num_outputs =  net_matrix[layerNum][neuron_numb].outputs.size();
            //cout<<"num_outputs_"<<num_outputs<<endl;

            for(unsigned activation_num=0; activation_num<num_outputs; ++activation_num){

                //cout<<"free_outputs_nb_"<<activation_num<<endl;
                delete net_matrix[layerNum][neuron_numb].outputs[activation_num];

            }
        }
    }

}

void Net::Feed_forward(vector<double> &inputs){

    //initialize inputs
    for(unsigned input_num=0; input_num<topology[0]; ++input_num){
        *Inputs[input_num] = inputs[input_num];
    }

    //feed through net
    for(unsigned layerNum=0; layerNum<topology.size(); ++layerNum){
        for(unsigned neuron_numb=0; neuron_numb<topology[layerNum]; ++neuron_numb){
            net_matrix[layerNum][neuron_numb].feed_forward();
        }
    }

}

void Net::Back_propagation(vector<double> &targets) {

    // 1. Calculate overall net error
    cost = calculate_cost(targets);

    // 2. Calculate output_layer gradients for each neuron (node)
    for(unsigned output_neuron_num=0; output_neuron_num<topology.back(); ++output_neuron_num){
        net_matrix.back()[output_neuron_num].calculate_output_layer_delta(targets[output_neuron_num]);
    }

    // 3. Calculate hidden_layers gradients for each neuron (node)
    for(unsigned hidden_layer_num = (unsigned)topology.size()-2; hidden_layer_num>0; --hidden_layer_num){
        //for each neuron
        for(unsigned neuron_num=0; neuron_num<topology[hidden_layer_num]; ++neuron_num){
            net_matrix[hidden_layer_num][neuron_num].calculate_hidden_layer_delta();
        }
    }

    // 4. Update every weight   //todo inna petla, z gory na dol jest tam
    for(unsigned layer_num=0; layer_num<topology.size(); ++layer_num){
        for(unsigned neuron_num=0; neuron_num<topology[layer_num]; ++neuron_num){
            net_matrix[layer_num][neuron_num].update_previous_layer_weights();
        }
    }

    

}

double Net::calculate_cost(vector<double> &targets) {

    if(targets.size() != Outputs.size()){
        cout<<"calculate cost error"<<endl;
    }

    //Use RMS to compute cost
    double total_cost = 0.0;
    double var;
    for(int output_num=0; output_num<Outputs.size(); ++output_num){
        var = (*Outputs[output_num]) - targets[output_num];
        total_cost += var * var;    //squared

    }

    total_cost /=topology.back();
    total_cost = sqrt(total_cost);

    //total_cost = total_cost/2; //todo

    //cost = cost/Outputs.size();
    //cost = sqrt(cost);

    return total_cost;

}

void Net::print_result() {
    cout<<*Inputs[0]<<" "<<*Inputs[1]<<" -> "<<*Outputs[0]<<endl;

    if(cost > 0.8){
        cout<<"                    |________________________________________|cost: "<<cost<<endl<<endl;
    }
    else if(cost > 0.4){
        cout<<"                    |____________________|cost: "<<cost<<endl<<endl;
    }
    else if(cost > 0.2){
        cout<<"                    |__________cost: "<<cost<<endl<<endl;
    }
    else{
        cout<<"                    |cost: "<<cost<<endl<<endl;
    }

}

