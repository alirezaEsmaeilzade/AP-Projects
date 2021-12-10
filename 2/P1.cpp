#include <iostream>
#include <string>
using namespace std;

string reverse(string input, int i){
    if(i <= 0){
        string a;
        a.push_back(input[i]);
        return a;
    }
    return input[i] + reverse(input, i - 1);
}

string encrypt(string input,int from, int to){
    if(to - from - 1 == 0){
        string a;
        a.push_back(input[to - 1]);
        return a;
    }
    int size = input.size() / 2;
    string begin = input.substr(from, size);
    string end = input.substr(size, to);
    begin = reverse(begin, begin.size() - 1);
    end = reverse(end, end.size() -1);
    return encrypt(end, 0, end.size()) + encrypt(begin, 0, begin.size());
}

int main(){
    string input;
    cin>>input;
    cout<<encrypt(input, 0, input.size())<<endl;
    return 0;
}