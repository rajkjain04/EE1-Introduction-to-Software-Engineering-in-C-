#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <string>

int rowcoltoi(int row, int col, int rowlen);
bool merge_num(std::vector<int>& v, int bi, int ei);
void rotate_anti_clock(std::vector<int>& v);
bool game_over(const std::vector<int>& v);
void print_grid(const std::vector<int>& vector);

int main(){

  std::string filename;
  std::cout << "Enter the name of the file containing the game" << std::endl;
  std::cin >> filename;
  std::ifstream infile;

  infile.open(filename.c_str());

  std::vector<int> vector;


  if(!infile.is_open()){
    std::cout << "File not found, so using default start configuration" << std::endl;

    for(int i = 0; i < 15; i++){
      vector.push_back(0);
    }
    vector.push_back(2);
  }
  int tmp;
  while(infile >> tmp){
    vector.push_back(tmp);
  }
  print_grid(vector);

  std::cout << std::endl;

  while(game_over(vector)){

    int x = 0;
    int value;
    int z = std::sqrt(vector.size());

    std::cout << "Please enter any one of the commands (w/a/s/d)" << std::endl;

    std::string command;

    std::cin >> command;

    if(command == "w" || command == "W"){
      rotate_anti_clock(vector);

      for(int i = 0; i < z; i++){
        value = merge_num(vector, (z * i), ((z * i) + z));
        x = x + value;
      }

      rotate_anti_clock(vector);
      rotate_anti_clock(vector);
      rotate_anti_clock(vector);
    }

    if(command == "a" || command == "A"){
      for(int i = 0; i < z; i++){
        value = merge_num(vector, (z * i), ((z * i) + z));
        x = x + value;
      }
    }

    if(command == "s" || command == "S"){
      rotate_anti_clock(vector);
      rotate_anti_clock(vector);
      rotate_anti_clock(vector);

      for(int i = 0; i < z; i++){
        value = merge_num(vector, (z * i), ((z * i) + z));
        x = x + value;
      }
      rotate_anti_clock(vector);
    }

    if(command == "d" || command == "D"){
      rotate_anti_clock(vector);
      rotate_anti_clock(vector);

      for(int i = 0; i < z; i++){
        value = merge_num(vector, (z * i), ((z * i) + z));
        x = x + value;
      }
      rotate_anti_clock(vector);
      rotate_anti_clock(vector);
    }

    if(x != 0){
      int z = std::sqrt(vector.size());
      std::vector <int> dummy;
      int count = 0;

      for(int i = 0; i < vector.size(); i++){
        if(vector[i] == 0){
          dummy.push_back(i);
          count++;
        }
      }

      int position;
      int generator = rand() % count;
      position = generator;

      vector[dummy[position]] = 2;

      print_grid(vector);
    }



    std::cout << std::endl;
    std::cout << std::endl;
  }

  std::cout << "Game Over, no more possible moves left" << std::endl;
  return 0;
}

int rowcoltoi(int row, int col, int rowlen){
  return ((row * rowlen) + col);
}

bool merge_num(std::vector<int>& v, int bi, int ei){
  std::vector<int> temp, dummy, storage;

  for(int i = 0; i < v.size(); i++){
    storage.push_back(v[i]);
  }

  for(int i = bi; i < ei; i++){
    if(v[i] != 0){
      temp.push_back(v[i]);
    }
    v[i] = 0;
  }
  temp.push_back(0);

  for(int i = 0; i < (temp.size() - 1); i++){
    if(temp[i] == temp[i + 1]){
      dummy.push_back(2 * temp[i]);
      i++;
    }
    else{
      dummy.push_back(temp[i]);
    }
  }

  for(int i = 0; i < dummy.size(); i++){
    v[i + bi] = dummy[i];
  }

  int count = 0;
  for(int i = 0; i < v.size(); i++){
    if(v[i] != storage[i]){
      count++;
    }
  }
  if(count != 0){
    return true;
  }
  else{
    return false;
  }
}
void rotate_anti_clock(std::vector<int>& v){
  std::vector<int> storage;
  int z = std::sqrt(v.size());
  for(int i = 0; i < z; i++){
    for(int j = 0; j < z; j++){
      int change = z - 1 - i;
      int k = rowcoltoi(j, change, z);
      storage.push_back(v[k]);
    }
  }
  v = storage;
}
bool game_over(const std::vector<int>& v){
  for(int i = 0; i < v.size(); i++){
    if(v[i] == 0){
      return true;
    }
  }
  int z = std::sqrt(v.size());
  for(int i = 0; i < (z - 1); i++){
    for(int j = 0; j < z; j++){
      if(v[(z * i) + j] == v[(z * i) + j + z]){
        return true;
      }
    }
  }
  for(int i = 0; i < z; i++){
    for(int j = 0; j < (z - 1); j++){
      if(v[(z * i) + j] == v[(z * i) + j + 1]){
        return true;
      }
    }
  }
  return false;
}
void print_grid(const std::vector<int>& v){
  int z = std::sqrt(v.size());
  for(int i = 0; i < z; i = i + 1){
    for(int j = 0; j < z; j = j + 1){
      int k = rowcoltoi(i, j, z);
      std::cout<<v[k]<<"\t";
    }
    std::cout<<std::endl;
  }
}
