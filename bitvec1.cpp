#include <iostream>
using namespace std;

class bvec{
    public:
        bool value;
  };

class bitvec{
public:
	int size;
	bvec *bv;
	 bitvec();
	 bitvec(int);
	void push_bit();
	void set_bit(int);
	void clear_bit(int);
	void show_bit();
};

bitvec :: bitvec(){
	int i;
	size=8;
	bv=(bvec *)  :: operator new (sizeof(bvec)*size);
	bool *ptr=&(bv->value);
	bool *temp=ptr;
	for(i=0;i<size;i++){
		ptr=temp+i;
		*ptr=false;
	}	
}
bitvec :: bitvec(int s){
	int i;
	size=s;
	bv=(bvec *) :: operator new (sizeof(bvec)*size);
	bool *ptr=&(bv->value);
	bool *temp=ptr;
	for(i=0;i<size;i++){
		ptr=temp+i;
		*ptr=false;
	}
}
void bitvec :: push_bit(){
	int o_size=size,i;
	bvec *tv;
	size*=2;
	tv=(bvec *) :: operator new (sizeof(bvec)*size);
	bool *ptr=&(bv->value);
	bool *newtemp=&(tv->value);
	bool *temp=ptr;
	

	for(i=0;i<o_size;i++){
		ptr=temp+i;
		*newtemp=*ptr;
		newtemp+=sizeof(bvec);
	}
	for(i=o_size;i<size;i++){
		*newtemp=false;
		newtemp+=sizeof(bvec);

	}
	delete(bv);
	bv=tv;
	show_bit();


}

void bitvec :: set_bit(int bn){
	bool *ptr=&(bv->value)+bn;
	*ptr=true;
}

void bitvec :: clear_bit(int bn){
	bool *ptr=&(bv->value)+bn;
	*ptr=false;
}


void bitvec :: show_bit(){
	int i;
	bool *ptr=&(bv->value);
	bool *temp=ptr;
	for(i=0;i<size;i++){
		ptr=temp+i;
		cout<<*ptr;
	}
	cout<<"\n";
}
int main(){

	  bitvec bv1[2]=bitvec();// (bitvec *):: operator new (sizeof(bitvec)*size);
	  bv1[0].show_bit();
	  bv1[0].set_bit(0);
	  bv1[0].set_bit(1);
	  bv1[0].show_bit();
	  bv1[0].set_bit(5);
	  bv1[0].show_bit();
	  bv1[0].push_bit();
	  bv1[0].push_bit();
	return 0;

}  