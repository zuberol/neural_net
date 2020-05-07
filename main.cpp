#include <vector>
#include <iostream>
#include "Connection.h"
#include "Neuron.h"
#include "Net.h"
#include <cmath>

using namespace std;

void make_XOR_data(vector<double> & container, vector<double> & target){

    int n1;
    int n2;
    int t;

    if(container.size() != 2 && target.size() != 1){
        cout<<"Container size error"<<endl;
    }
    else{
        n1 = (int)(2.0 * rand() / double(RAND_MAX));
        n2 = (int)(2.0 * rand() / double(RAND_MAX));
        t = n1 ^ n2;

    }

    container[0] = n1;
    container[1] = n2;
    target[0] = t;

}


int main(){
    //
    vector<unsigned> topology;
    topology.push_back(2);
    topology.push_back(3);
    topology.push_back(1);

    Net neural_net(topology);

    vector <double> data;  data.push_back(0);  data.push_back(0);
    vector<double> target;  target.push_back(0);


    for(int i=0; i<10000; ++i){
        cout<<"Iteracja nr: "<<i<<endl;
        make_XOR_data(data, target);

        neural_net.Feed_forward(data);
        neural_net.Back_propagation(target);
        neural_net.print_result();

    }

}