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
	void push_bit(int);
	void set_bit(int);
	void clear_bit(int);
	void show_bit();
	bool query_bit(int);
	bool * bbegin();
	bool * bend();
    void operator=(bitvec);
    bitvec(const bitvec &);
	
	bool& operator[] (int i){
           bool *ptr=&(bv->value)+i;
            return *ptr;
	}

	~bitvec(){
    cout<<"\t\t\t\tdestroyed  ";
    show_bit();
    cout<< "\n";
    delete(bv);

    }
};

bool * bitvec :: bbegin(){
         return (&(bv->value));
    }
bool * bitvec :: bend(){
         return (&(bv->value)+size*sizeof(bvec));
    }
bitvec :: bitvec(const bitvec &tobj){
    int i;
    size=tobj.size;
    bv=(bvec *) :: operator new (sizeof(bvec) *size);
    bool *ptr=&(bv->value);
	bool *temp=&(tobj.bv->value);
	for(i=0;i<size;i++){
		*ptr=*temp;
		ptr+=sizeof(bvec);
		temp+=sizeof(bvec);
	}

}
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

void bitvec :: push_bit(int inc){
	int o_size=size,i;
	bvec *tv;
	while(inc > 0){//until required pushbits are alloted multiplies
        inc-=size;
        size*=2;
    }
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

bitvec operator^(bitvec &b1,bitvec &b2){
	int lsize,i;
	lsize= b1.size < b2.size ? b1.size : b2.size;
	bitvec ansvec= bitvec(lsize);
	for(i=0;i<lsize;i++){
		if(b1.query_bit(i) && b2.query_bit(i))
			ansvec.set_bit(i);
	}
	return ansvec;
}


bitvec operator+(bitvec &b1,bitvec &b2){
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

bitvec operator/(bitvec &b1,bitvec &b2){
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

void bitvec :: operator=(bitvec b2){
    int i;
    delete(bv);
    size=b2.size;
    bv=(bvec *) :: operator new (sizeof(bvec)*b2.size);
    bool *b1v,*b2v;
    b1v=&(bv->value);
    b2v=&(b2.bv->value);
    for(i=0;i<b2.size;i++){
        *b1v=*b2v;
        b2v+=sizeof(bvec);
        b1v+=sizeof(bvec);
    }

}

int main(){

	  bitvec bv1[2]=bitvec();
      bitvec b1,b2;
      cout<<"\n..1..\n";
	  bv1[0].show_bit();
	  bv1[0].set_bit(0);
	  bv1[0].set_bit(1);
	  bv1[0].show_bit();
	  bv1[0].set_bit(5);
	  bv1[0].show_bit();
      bv1[0].clear_bit(5);
	  bv1[0].push_bit(1);

	  cout<<"\n..2..\n";
	  bv1[1].show_bit();
	  bv1[1].set_bit(2);
	  bv1[1].set_bit(1);
	  bv1[1].show_bit();
	  bv1[1].set_bit(5);

	  cout<<"\n"<<bv1[0].query_bit(2);
	  cout<<"\n"<<bv1[0].query_bit(0);
	  cout<<"\n"<<bv1[0].query_bit(1)<<"\n";
 	  bv1[0].show_bit();
	  bv1[1].show_bit();
	  cout<<"copy constructor..\n";
	  b1=bitvec(bv1[0]);
	  b2=bitvec(bv1[1]);

	  cout<<" AND.. \n";
	  bitvec andbit= b1 ^ b2;
	  b1.show_bit();
	  b2.show_bit();
	  andbit.show_bit();

	  cout<<"\n OR.. \n";
      bitvec orbit= b1  + b2;
      b1.show_bit();
	  b2.show_bit();
	  orbit.show_bit();

	  cout<<"\n XOR.. \n";
      bitvec xorbit= b1 / b2;
	  b1.show_bit();
	  b2.show_bit();
	  xorbit.show_bit();

	  cout<<"subscript overloading\n";
 	  cout<< bv1[0][1] << "  "<<bv1[0][4];
      cout<<"\n";

 	  cout<<"= overloading\n";
 	  bv1[0]=bv1[1];
 	  bv1[0].show_bit();

      cout<<"\niterator.. b1\n ";
      bool *i;
      for( i=b1.bbegin();i<b1.bend();i++){
      cout<<*i;
        }
      cout<<"\n.. b2 ";
      for( i=b2.bbegin();i<b2.bend();i++){
      cout<<*i;
       }
       cout<<"\n";
 	 return 0;
}
