
#include "irclass.h"
#include "ssaclass.h"
#include <iostream>
using namespace std;

int main(){
  program p;
  operand op1=operand(reg,"r0");
  operand op2=operand(reg,"r1");
  operand op3=operand(reg,"r2");
  operand op4=operand(sym,"A");
  operand op5=operand(con,5);
  instruction ir=instruction(mov,op1,op5);
  instruction ir1=instruction(mov,op2,op1);
  instruction ir2=instruction(add,op3,op2,op1);
  instruction ir3=instruction(add,op2,op3,op1);
  instruction ir4=instruction(LD,op1,op4);
  instruction ir5=instruction(ST,op4,op2);
  p.add_instruction(ir);
  p.add_instruction(ir1);
  p.add_instruction(ir2);
  p.add_instruction(ir3);
  p.add_instruction(ir4);
  p.add_instruction(ir5);
  p.print_instruction();

  ssa_form sf=ssa_form(p);
  cout<<"\n..SSA Form..\n";
  sf.print_instruction();
 
  return 0;
}
