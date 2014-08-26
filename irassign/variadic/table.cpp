#include <vector>
#include <iostream>
#include "table.h"
using namespace std;

#define TOTAL_OPCODE 7

string opcode_table_arr[]={"LD","ST","mov","add","mul","div","sub"};
vector<string> symbol_table;

string opcode_table_getinst(int index){
  return opcode_table_arr[index];
}

int opcode_table_getindex(string& inst){
  int i;
  for(i=0;i<TOTAL_OPCODE;i++){
    if(inst.compare(opcode_table_arr[i])==0){
      return i;
    }
  }
  return -1;
}

int add_symbol(string& t){
  symbol_table.push_back(t);
  return symbol_table.size()-1;
}
int get_symbol_index(string& sym){
  int i;
  for(i=0;i<symbol_table.size();i++){
    if(sym.compare(symbol_table[i])==0){
      return i;//return index
    }
  }
  return -1;//symbol not found
}
string get_symbol(int index){
  return symbol_table[index];
}
