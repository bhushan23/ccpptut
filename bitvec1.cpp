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
	bool query_bit(int);
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

bool bitvec :: query_bit(int bn){
	bool *ptr=&(bv->value)+bn;
	return *ptr;
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

bitvec operator^(bitvec b1,bitvec b2){
	int lsize,i;
	lsize= b1.size < b2.size ? b1.size : b2.size;
	bitvec ansvec= bitvec(lsize);
	for(i=0;i<lsize;i++){
		if(b1.query_bit(i) && b2.query_bit(i))
			ansvec.set_bit(i);
	}
	return ansvec;
}


bitvec operator+(bitvec b1,bitvec b2){
	int lsize,hsize,i;
	if(b1.size < b2.size){
		lsize=b1.size;
		hsize=b2.size;
	}else{
		hsize=b1.size;
		lsize=b2.size;
	}	
	
	bitvec ansvec= bitvec(hsize);
	for(i=0;i<lsize;i++){
		if(b1.query_bit(i) || b2.query_bit(i))
			ansvec.set_bit(i);
	}
	if(hsize==b1.size){
		for(i=lsize;i<hsize;i++){
			if(b1.query_bit(i))
				ansvec.set_bit(i);//by default storing 0 so no need of calling clear_bit
		}
	}else{
		for(i=lsize;i<hsize;i++){
			if(b1.query_bit(i))
				ansvec.set_bit(i);//by default storing 0 so no need of calling clear_bit
		}
	}

	return ansvec;

}

bitvec operator/(bitvec b1,bitvec b2){
	int lsize,hsize,i;
	if(b1.size < b2.size){
		lsize=b1.size;
		hsize=b2.size;
	}else{
		hsize=b1.size;
		lsize=b2.size;
	}	
	
	bitvec ansvec= bitvec(hsize);
	for(i=0;i<lsize;i++){
		if(b1.query_bit(i) != b2.query_bit(i))
			ansvec.set_bit(i);
	}
	if(hsize==b1.size){
		for(i=lsize;i<hsize;i++){
			if(b1.query_bit(i))
				ansvec.set_bit(i);//by default storing 0 so no need of calling clear_bit
		}
	}else{
		for(i=lsize;i<hsize;i++){
			if(b1.query_bit(i))
				ansvec.set_bit(i);//by default storing 0 so no need of calling clear_bit
		}
	}

	return ansvec;
}
int main(){

	  bitvec bv1[2]=bitvec();// (bitvec *):: operator new (sizeof(bitvec)*size);
	  bv1[0].show_bit();
	  bv1[0].set_bit(0);
	  bv1[0].set_bit(1);
	  bv1[0].show_bit();
	  bv1[0].set_bit(5);
	  bv1[0].show_bit();
	    bv1[0].clear_bit(5);
	  bv1[0].push_bit();

	  cout<<"\n..2..\n";
	  bv1[1].show_bit();
	  bv1[1].set_bit(2);
	  bv1[1].set_bit(1);
	  bv1[1].show_bit();
	  bv1[1].set_bit(5);
	 
	cout<<"\n"<<bv1[0].query_bit(2);
	cout<<"\n"<<bv1[0].query_bit(0);
	cout<<"\n"<<bv1[0].query_bit(1);
 	bv1[0].show_bit();
	 bv1[1].show_bit();
	 bitvec andbit= bv1[0] ^ bv1[1];
	 cout<<"\n AND..  ";
	 andbit.show_bit();
 bitvec orbit= bv1[0]  + bv1[1];
	 cout<<"\n OR..  ";
	 orbit.show_bit();
	  bitvec xorbit= bv1[0] / bv1[1];
	 cout<<"\n XOR..  ";
	 xorbit.show_bit();
	return 0;

}  