#include <iostream>
#include <vector>
#include <cstdarg>
#include <cassert>
#include "irclass.h"
#include "table.h"
using namespace std;
int opcode_par_cnt[]={1,1,1,2,2,2,2};
operand :: operand(operandtype otype,string t){//for symbol and register
  if(otype==reg){//register
    type=reg;
    odata.index=t[1]-48; //Need to change code for index having more than 9
  }else{//Symbol
    type=sym;
    odata.index=add_symbol(t);
  }
}
operand :: operand(operandtype otype,int val){//for index based
  switch(otype){
  case reg:
    type=reg;
    odata.index=val;
   break;
  case sym:
    type=sym;
    odata.index=val;
    break;
  case con:
    type=con;
    odata.value=val;
    break;
  }

}
void operand :: set_data(int d){
  if(type==con)
    odata.value=d;
  else
    odata.index=d;

}
int operand :: get_data(){
  if(type==con)
    return odata.value;
  else{
    return odata.index;
  }
}
void operand :: print_opcode(){
    switch(type){
    case 0://reg
      cout<<"r"<<odata.index;
      break;
    case 1:
      cout<<get_symbol(odata.index);
      break;
    case 2:
      cout<<odata.value;
      break;
    default:
      cout<<"..";
      break;
    };
  }

operandtype operand :: get_operandtype(){
  return type;
}

void instruction :: print_instruction(){
    cout<<opcode_table_getinst(opcodeno)<<" ";
    destination.print_opcode();
    for(int i=0;i<source.size();i++){
    cout<<" ";
    source[i].print_opcode();
    }
  }

operand instruction :: get_source_operand(int i){
  if(i <source.size())
  return source[i];
  else
    assert(false);
    
}
void instruction :: set_opcodeno(opcodeenum i){
  opcodeno=i;
}

opcodeenum instruction :: get_opcodeno(){
 return opcodeno;
}
void instruction :: set_destination_operand(operand& op){
  destination=op;
}

operand instruction :: get_destination_operand(){
  return destination;
}


void instruction :: add_source_operand(operand& op){
  source.push_back(op);
}
int instruction :: get_source_count(){
  return source.size();
}

bool instruction :: check_src_operand_correctness(opcodeenum opcode,int src){
  if(opcode_par_cnt[opcode]==src)
    return true;
  return false;
}

list <instruction > :: iterator program :: get_begin_inst(){
  return inst.begin();
}

list <instruction > :: iterator program :: get_end_inst(){
  return inst.end();
}

void program :: print_instruction(){

  for(list <instruction> :: iterator it=inst.begin();it != inst.end();++it){
    it->print_instruction();
    cout<<"\n";
  }

}


void program ::  add_instruction(instruction& in){
    inst.push_back(in);
}

