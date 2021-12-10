#include <iostream>
#include <string>
#include <functional>
using namespace std;
unsigned long int generatePasswordHash(string  password){
    return hash<string>() (password);
}
bool check_password_correct(unsigned long int hashed_number, string password){
    if(hashed_number == generatePasswordHash(password))
        return true;
    else
        return false;
}
bool decrypt_password(unsigned long int hashed_number, string &password, string alphebet, int numbers, int level = 0){
    if(level == numbers){
            if(check_password_correct(hashed_number, password))
                return true;
            else
                return false;
    }
    for(int i = 0; i < 26; i++){
        password[level] = alphebet[i];
        if(decrypt_password(hashed_number, password, alphebet, numbers, level + 1))
            return true;    
    }
    return false;
}
  
int main(){
    char word;
    string alphebet, password;
    unsigned long int hashed_number;
    int numbers;
    cin>>numbers;
    for(int i = 0; i < 26; i++){
        cin>>word;
        alphebet.push_back(word);
    }
    cin>>hashed_number;
    for(int i = 0; i < numbers; i++){
        password.push_back('a');
    }
    if(decrypt_password(hashed_number, password, alphebet, numbers))
        cout<<password<<endl;
    else
        cout<<"NOT_FOUND"<<endl;
    return 0;
}