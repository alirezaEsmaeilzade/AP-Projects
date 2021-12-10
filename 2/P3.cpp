#include <iostream>
#include <vector>
using namespace std;
void check_sum_maximum(int &x, int y){
    if(x < y)
        x = y;
}
void initialize_gold_minds(vector<vector<int> >&gold_feilds,int row_input, int column_input){
    int initialize;
    for(int row = 0; row < row_input; row++){
        for(int column = 0; column < column_input; column++){
            cin>>initialize;
            gold_feilds[row].push_back(initialize);
        }
    }
}
void initialize_gold_mind_sums(vector<vector<int> >&sum_mind_gold, int row_input, int column_input){
    for(int row = 0; row < row_input; row++){
        for(int column = 0; column < column_input; column++){
        sum_mind_gold[row].push_back(0);
        }
    }
    
}
int find_maximum(vector<vector<int> >sum_mind_gold){
    int maximum = sum_mind_gold[0][0];
    for(int row = 0; row < sum_mind_gold.size(); row++){
        for(int column = 0; column < sum_mind_gold.size(); column++){
        if(sum_mind_gold[row][column] > maximum)
            maximum = sum_mind_gold[row][column];
        }
    }
    return maximum;
}
bool harvest_fields(int level, vector< vector <int> >&sum_mind_gold, vector<vector<int> >&gold_feilds,int mabda_row, int mabda_column, int current_row, int current_column, int row_move[], int column_move[],int row_input, int column_input, int current_sum){
    int save_gold_feilds_amount;
    current_sum += gold_feilds[current_row][current_column];
    check_sum_maximum(sum_mind_gold[mabda_row][mabda_column] ,current_sum);
    gold_feilds[current_row][current_column] = 0; 
    for(int move = 0; move < 4; move++){
        int new_row = current_row + row_move[move];
        int new_column = current_column + column_move[move];
        if (new_row < 0 || new_row >= row_input || new_column < 0 || new_column >= column_input)
            continue;
        if (gold_feilds[new_row][new_column] == 0)
            continue;
        current_sum += gold_feilds[new_row][new_column];
        save_gold_feilds_amount = gold_feilds[new_row][new_column];
        gold_feilds[new_row][new_column] = 0;
        check_sum_maximum(sum_mind_gold[mabda_row][mabda_column] ,current_sum);
        level++;
        if(harvest_fields(level, sum_mind_gold, gold_feilds, mabda_row, mabda_column, new_row, new_column, row_move, column_move, row_input, column_input, current_sum))
            return true;
        gold_feilds[new_row][new_column] = save_gold_feilds_amount;
        current_sum -= gold_feilds[new_row][new_column];
    }
    return false;
}
int tour_all_state(vector <vector<int> >&sum_mind_gold, vector<vector<int> >gold_feilds, int row_input, int column_input, int row_move[], int column_move[]){
    int row, column;
    vector<vector< int> > save_gold_feilds;
    save_gold_feilds = gold_feilds;
    for(row = 0; row < row_input; row++){
        for(column = 0; column < column_input; column++){
            if(gold_feilds[row][column] != 0){
                gold_feilds = save_gold_feilds;
                harvest_fields(1, sum_mind_gold, gold_feilds,row, column, row, column, row_move, column_move, row_input, column_input, 0);
            }
        }
    }
}

int main(){
    int row_move[4] = {0 , -1, 0, 1};
    int column_move[4] = {-1, 0, 1, 0}; 
    int row_input, column_input;
    cin>>row_input>>column_input;
    vector< vector<int> > gold_feilds(row_input);
    vector< vector<int> >sum_mind_gold(row_input);
    initialize_gold_minds(gold_feilds, row_input, column_input);
    initialize_gold_mind_sums(sum_mind_gold, row_input, column_input);
    tour_all_state(sum_mind_gold, gold_feilds, row_input, column_input, row_move, column_move);
    cout<<find_maximum(sum_mind_gold)<<endl;
    return 0; 
}