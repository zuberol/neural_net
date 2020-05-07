#include "Neuron.h"
#include <math.h>
#include <random>

Neuron::Neuron(unsigned layer_num, unsigned neuron_num) : layer_num(layer_num), index_in_layer(neuron_num) {
/*
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> drop_random_numb(0.0, 1.0);
    bias = drop_random_numb(gen);*/

    bias = 1.0;
    delta =  0.0;
    old_delta = 0.0;

}
Neuron::~Neuron() {}

double Neuron::eta = 0.15;
double Neuron::alpha = 0.5;

    double Neuron::transfer_function(double x) {
        return tanh(x);
    }


double Neuron::transfer_function_derivative(double x) {
    return 1.0 - transfer_function(x) * transfer_function(x);
}

    double Neuron::z_sum() {
        double sum = 0.0;

        for(int input_num=0; input_num<inputs.size(); ++input_num){
            sum += *inputs[input_num] * (*previous_layer_weights[input_num]);
        }
        sum += bias;

        return sum;
    }


    void Neuron::feed_forward() {

        //first layer just passes
        if(layer_num == 0){
            for(int output_nb=0; output_nb<outputs.size(); ++output_nb){
                *outputs[output_nb] = *inputs[0];
            }
        }
        else{
        //compute activation and pass forward
            for(int output_nb=0; output_nb<outputs.size(); ++output_nb){
                *outputs[output_nb] = transfer_function(z_sum());
            }
        }
    }



    void Neuron::calculate_output_layer_delta(double &target) {

        double a = -(target - *outputs[0]);
        double b = transfer_function_derivative(*outputs[0]);

        delta = a * b;

    }


    void Neuron::calculate_hidden_layer_delta(){

        double var=0.0;

        //sum up (next_layer_delta * weight)
        for(unsigned delta_num=0; delta_num<next_layer_delta.size(); ++delta_num){
            var += (*next_layer_delta[delta_num]) * (*next_layer_weights[delta_num]);
        }

        delta = transfer_function_derivative(*outputs[0]) * var;

    }



    void Neuron::update_previous_layer_weights() {

        //if first layer called this function it simply does nothing
        double delta_weight;
        for(unsigned weight_num=0; weight_num<previous_layer_weights.size(); ++weight_num){
            delta_weight = eta * delta * (*inputs[weight_num]);
            *previous_layer_weights[weight_num] = *previous_layer_weights[weight_num] - delta_weight - alpha*old_delta;
            old_delta = delta_weight;
        }

    };



