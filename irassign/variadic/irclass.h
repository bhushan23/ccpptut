#include <cassert>
#include <vector>
#include <list>
#include <iostream>

using namespace std;
enum operandtype{reg=0,sym,con};
enum opcodeenum {ld=0,ST,mov,add,mul,div,sub};
class operand{
  operandtype type;
  union data{
    int value;
    int index;
  }odata;
 public:
  operand(){
  }
  operand(operandtype, string);//symbol register
  operand(operandtype,int); //constant
  void print_opcode();
  operandtype get_operandtype();
  void set_data(int);
  int get_data();
  
};

class instruction{
  opcodeenum opcodeno;
  operand destination;
  vector< operand > source;
 public:
  instruction(){}
  operand get_source_operand(int);
  int get_source_count();
  void add_source_operand(operand&);
  void set_opcodeno(opcodeenum);
  opcodeenum get_opcodeno();
  void set_destination_operand(operand&);
  operand get_destination_operand();
  void print_instruction();
  bool check_src_operand_correctness(opcodeenum,int);
  template <class Copcode,class...Csrc>
  instruction (Copcode opcode,Csrc...src){
    int total_src=sizeof...(src);
    if(check_src_operand_correctness(opcode,total_src-1)){//opcode and source operand error check
      opcodeno=opcode;
      operand tmpop[total_src]={src...};
      destination=tmpop[0];
      for(int i=1;i<total_src;i++)
	source.push_back(tmpop[i]);
    }else{
        cout<<"Error...Invalid Arguments\n";
	assert(false);
    }
  }

};

class program{
  list< instruction > inst;
  
 public:
  list <instruction> :: iterator get_begin_inst();
  list <instruction> :: iterator get_end_inst();
  void print_instruction();
  void add_instruction(instruction& );
};
