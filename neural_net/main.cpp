/*
#include <vector>
#include <iostream>
#include "Connection.h"
#include "Neuron.h"
#include "Net.h"

using namespace std;

int main(){

    vector<unsigned> topology;
    topology.push_back(2);
    topology.push_back(10);
    topology.push_back(5);
    topology.push_back(5);
    topology.push_back(1);

    Net neural_net(topology);

    double data [4][3];
    data[0][0] = 1.0;    data[0][1] = 1.0;    data[0][2] = 0.0;
    data[1][0] = 0.0;    data[1][1] = 1.0;    data[1][2] = 1.0;
    data[2][0] = 1.0;    data[2][1] = 0.0;    data[2][2] = 1.0;
    data[3][0] = 0.0;    data[3][1] = 0.0;    data[3][2] = 0.0;

    vector<double> data1;
    vector<double> target1;
    data1.push_back(data[0][0]);
    data1.push_back(data[0][1]);
    target1.push_back(data[0][2]);

    vector<double> data2;
    vector<double> target2;
    data2.push_back(data[1][0]);
    data2.push_back(data[1][1]);
    target2.push_back(data[1][2]);

    vector<double> data3;
    vector<double> target3;
    data3.push_back(data[2][0]);
    data3.push_back(data[2][1]);
    target3.push_back(data[2][2]);

    vector<double> data4;
    vector<double> target4;
    data4.push_back(data[3][0]);
    data4.push_back(data[3][1]);
    target4.push_back(data[3][2]);

    for(unsigned i=0; i<2000; ++i){

        neural_net.Feed_forward(data1);
        neural_net.Back_propagation(target1);
        neural_net.print_result();

        neural_net.Feed_forward(data2);
        neural_net.Back_propagation(target2);
        neural_net.print_result();

        neural_net.Feed_forward(data3);
        neural_net.Back_propagation(target3);
        neural_net.print_result();

        neural_net.Feed_forward(data4);
        neural_net.Back_propagation(target4);
        neural_net.print_result();

        cout<<"Iteration======:"<<i*4+1<<endl;
    }

}*/
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

    vector<unsigned> topology;
    topology.push_back(2);
    topology.push_back(3);
    topology.push_back(1);

    Net neural_net(topology);

    vector <double> data;
    data.push_back(0);
    data.push_back(0);

    vector<double> target;
    target.push_back(0);


    for(int i=0; i<10000; ++i){
        cout<<"Iteracja nr: "<<i<<endl;
        make_XOR_data(data, target);
        neural_net.Feed_forward(data);
        neural_net.Back_propagation(target);
        neural_net.print_result();
    }


}