#include <iostream>
#include <vector>
#include <utility>
using namespace std;

void initailize_inputs(vector<int> &inputs){
    int input;
    while(cin>> input){
        inputs.push_back(input);
    }
}

void cross_each_num_in_prevent_index(vector<int> &inputs, int curr_num_index, int save_num, int i = 0){
    if(i == curr_num_index + 1)
        return;
    inputs[i] *= save_num;
    cross_each_num_in_prevent_index(inputs, curr_num_index, save_num, i + 1);
}

void find_changed_array(vector<int> &inputs, int curr_num_index = 1, int save_num = 1, int pre_cross = 1, int curr_cross = 1){
    if(curr_num_index < 2){
        swap(inputs[0], inputs[1]);
        pre_cross = inputs[0] * inputs[1];
        curr_cross = pre_cross;
    }
    if(curr_num_index != 1)
        inputs[curr_num_index] = pre_cross;
    if(curr_num_index >= inputs.size() - 1)
        return;
    save_num = inputs[curr_num_index + 1];
    inputs[curr_num_index + 1] = curr_cross;
    pre_cross = curr_cross;
    cross_each_num_in_prevent_index(inputs, curr_num_index, save_num);
    curr_cross = pre_cross * save_num;
    find_changed_array(inputs, curr_num_index + 1, save_num, pre_cross, curr_cross);
}

void display(vector <int> inputs, int curr_num_index = 0){
    if(inputs.size() == curr_num_index){
        cout<<endl;
        return;
    }
    else{
        cout<<inputs[curr_num_index];
        if(curr_num_index != inputs.size() - 1)
            cout<<' ';
        display(inputs, curr_num_index + 1);
    }
}

int main(){
    vector <int> inputs;
    initailize_inputs(inputs);
    find_changed_array(inputs);
    display(inputs);
    return 0;
}