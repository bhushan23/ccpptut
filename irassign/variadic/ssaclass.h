#include <list>
#include <map>
#include <iostream>

class ssa_form{
  program pm;
  map <int,int> refering;
  int logical_reg_val;
public:
  ssa_form(){
  }
  ssa_form(program&);
  void print_instruction();
  int get_reg_operandindex(operand&);
};
