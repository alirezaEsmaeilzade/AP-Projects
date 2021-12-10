#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#define rand_number_default 11
#define encrypt "encrypt"
#define decrypt "decrypt"
#define simple "simple"
#define complicated "complicated"
string read_character_of_file(string input_file_name){
  string line_of_input;
  char character_of_file;
  ifstream input_file;
  input_file.open(input_file_name);
  while(input_file.get(character_of_file))
    line_of_input += character_of_file; 
  return line_of_input;
}
vector<int> read_decrypt_numaber_of_file(string input_file_name){
  int input_descrypt_words;
  char character_of_file;
  vector<int> decrypt_numbers;
  ifstream input_file;
  input_file.open(input_file_name);
  while(input_file>>input_descrypt_words)
    decrypt_numbers.push_back(input_descrypt_words);
  return decrypt_numbers;
}
string decrypt_simple(vector <int> descrypt_words, string password){
  int select_character_From_Password;
  string decrypt_words;
  for(int i = 0; i <descrypt_words.size(); i++){
    select_character_From_Password = i % password.size();
    char change_ASCII_to_character = descrypt_words[i] - (int)password[select_character_From_Password]; 
    decrypt_words += change_ASCII_to_character;
  }
  return decrypt_words;
}
vector<int> encrypt_simple(string line_of_input, string password){
  int select_character_From_Password;
  vector<int> encrypt_number;
  for(int i = 0; i < line_of_input.size(); i++){
    select_character_From_Password = i % password.size(); 
    encrypt_number.push_back((int)password[select_character_From_Password] + (int)line_of_input[i]);
  }
  return encrypt_number;
}
int return_key_for_rand(string password){
  int key = 0;
  for(int i = 0; i < password.size(); i++)
    key += (int)password[i];
  return key;
}
vector<int> return_made_random_number_for_encrypt(int size, string password){
  vector<int> random_number;
  srand(return_key_for_rand(password));
  for(int i = 0; i < size ; i++){
    int push_random_number = rand() % (rand_number_default);
    random_number.push_back(push_random_number);
  }
  return random_number;
}
vector<int> encrypt_complicated(string line_of_input, string password){
  int push_random_number;
  vector<int> encrypt_number;
  vector<int> random_number = return_made_random_number_for_encrypt(line_of_input.size(), password);
  for(int i = 0; i < line_of_input.size(); i++){
    int push_random_encrypted_number = random_number[i % rand_number_default] + (int)line_of_input[i];
    encrypt_number.push_back(push_random_encrypted_number);
  }
  return encrypt_number;   
}
string decrypt_complicated(vector <int>encrypt_numbers, string password){
  string decrypt_words;
  vector<int> random_number = return_made_random_number_for_encrypt(encrypt_numbers.size(), password);
  for(int i = 0; i <encrypt_numbers.size(); i++){
    char changeASCII_toCharacter = encrypt_numbers[i] - random_number[i % rand_number_default];
    decrypt_words += changeASCII_toCharacter;
  }
  return decrypt_words;    
}
void write_encrypt_in_output_file(string output_file_name, vector<int> encrypt_numbers){
  ofstream output_file;
  output_file.open(output_file_name);
  for(int i = 0; i < encrypt_numbers.size(); i++)
    output_file<< encrypt_numbers[i] << endl;
}
void write_decrypt_in_output_file(string output_file_name, string decrypt_words){
  ofstream output_file;
  output_file.open(output_file_name);
  output_file<< decrypt_words;
}
bool check_command(string way_to_cryptography, string read_or_write, string input_file_name){
  ifstream input_file;
  input_file.open(input_file_name);
  if(!input_file.is_open()){
    cout<<"Error opening file, check input file exit or no"<<endl;
    return false;
  }
  if(read_or_write != encrypt && read_or_write != decrypt){
    cout<<"Your command is false, please enter again"<<endl;
    return false;
  } 
  if(way_to_cryptography != simple && way_to_cryptography != complicated){
    cout<<"Your way_to_cryptograghy is false, please enter again"<<endl;
    return false;
  }
  return true; 
}
void command(string password, string way_to_cryptography, string read_or_write, string input_file, string output_file){
  if(check_command(way_to_cryptography, read_or_write, input_file)){
    if(read_or_write == encrypt){
      if(way_to_cryptography == simple)
        write_encrypt_in_output_file(output_file, encrypt_simple(read_character_of_file(input_file), password));
      else
        write_encrypt_in_output_file(output_file, encrypt_complicated(read_character_of_file(input_file), password));
    }
    else{
      if(way_to_cryptography == simple)
        write_decrypt_in_output_file(output_file, decrypt_simple(read_decrypt_numaber_of_file(input_file), password));
      else
        write_decrypt_in_output_file(output_file, decrypt_complicated(read_decrypt_numaber_of_file(input_file), password));
    }
  }
}
int main(){
  string password, way_to_cryptography, read_or_write, input_file, output_file;
  cin>> read_or_write>> way_to_cryptography>> password>> input_file>> output_file;
  command(password, way_to_cryptography, read_or_write, input_file, output_file);
  return 0;
}