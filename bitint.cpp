#include <iostream>
#define BITS 32

using namespace std;
class bitvec{
    public:
        int blocks;
        int index;
        int *bb;
        bitvec();
        bitvec(int );
        bitvec(const bitvec &);
        ~bitvec();
        void push_bit(bool);
        void show_bit();
        void set_bit(int);
        void clear_bit(int);
        bool query_bit(int);
        bitvec& operator&(bitvec&);
        bitvec& operator|(bitvec&);
        bitvec& operator^(bitvec&);
        void operator=(bitvec&);
        bool operator[](int);
};
bitvec::bitvec(){
    blocks=1;
    index=0;
    bb=new int;
    bb[0]=0;
}
bitvec::bitvec(int s){
    blocks=s/BITS + 1 ;
    index=0;
    bb=new int[blocks];
    for(int i=0;i<blocks;i++)
    bb[i]=0;
}
bitvec :: ~bitvec(){
    delete(bb);
}
bitvec :: bitvec(const bitvec &b2){
    blocks=b2.blocks;
    index=b2.index;
    bb=new int[blocks];
    for(int i=0;i<blocks;i++){
        bb[i]=b2.bb[i];
    }
}
void bitvec::push_bit(bool val){

    if(index >= blocks * BITS){
            //double
            cout<<"\ndoubling..\n";
            int i;
            int *bt=bb;
            bb=new int[blocks*2];
            for(i=0;i<blocks;i++)
                bb[i]=bt[i];
            for(i=blocks;i<blocks*2;i++)
                bb[i]=0;
            blocks=blocks*2;
            delete(bt);
        }
     int temp,blno;
     if(val){
        temp=1;
        temp=temp<<index;
     }else
        temp=0;
     blno=index/BITS;
     bb[blno]=bb[blno] | temp;
     index++;
}

void bitvec :: show_bit(){
   
            for(int i=index-1;i>=0;i--){
             cout<<query_bit(i);
       
             
    }
    cout<<"\n";
}

void bitvec :: set_bit(int bn){
     if(bn >= index)
        cout<<".set not pushed\n";
    else{
    int sval=bn%BITS;
    int temp=1,bnum;
    temp=temp<<sval;
    bnum=bn/BITS;
   // cout<<"..b "<<temp<<" "<<bb[bnum]<<"  ";

    bb[bnum]=bb[bnum] | temp;
    //cout<<"..as"<<bb[bnum]<<"\n";

    }
}

void bitvec :: clear_bit(int bn){

    if(bn >= index)
        cout<<".clear not pushed\n";
    else{
    int sval=bn%BITS;
    int temp=1,bnum;
    temp=temp<<sval;
    temp=~temp;
    bnum=bn/BITS;

    bb[bnum]=bb[bnum] & temp;
    //cout<<"..as"<<bb[bnum]<<"\n";

    }
}

bool bitvec :: query_bit(int bn){

    if(bn >= index)
        cout<<".q  not pushed\n";
    else{
    int sval=bn%BITS;
    int temp=1,bnum;
    temp=temp<<sval;
    bnum=bn/BITS;
    temp=bb[bnum] & temp;
    temp=temp>>sval;
   // cout<<"..Bit is "<< temp<<"\n";
    if(temp)
        return true;
    else
        return false;
    }
}

bitvec& bitvec :: operator&(bitvec& b2){
    int lsize,i,lblocks;
    lsize = index < b2.index ? index : b2.index;
    static bitvec ansbv= bitvec(lsize);
    lsize == index? ansbv.index=index : ansbv.index=b2.index;
    lblocks= blocks < b2.blocks ? blocks : b2.blocks ;
    for(i=0;i<lblocks;i++){
        ansbv.bb[i]=bb[i]&b2.bb[i];
        //cout<<"\n..and of "<<bb[i] <<"  "<<b2.bb[i]<< " is "<<ansbv.bb[i];
    }
return ansbv;
}

bitvec& bitvec :: operator|(bitvec& b2){
    int hsize,i,lblocks;
    hsize = index > b2.index ? index : b2.index;
    static bitvec ansbv= bitvec(hsize);
    hsize == index? ansbv.index=index : ansbv.index=b2.index;
    lblocks= blocks > b2.blocks ? blocks : b2.blocks ;
    for(i=0;i<lblocks;i++){
        ansbv.bb[i]=bb[i]|b2.bb[i];
       // cout<<"\n..or of "<<bb[i] <<"  "<<b2.bb[i]<< " is "<<ansbv.bb[i];
    }
return ansbv;
}
bitvec& bitvec :: operator^(bitvec& b2){
    int hsize,i,lblocks;
    hsize = index > b2.index ? index : b2.index;
    static bitvec ansbv= bitvec(hsize);
    hsize == index? ansbv.index=index : ansbv.index=b2.index;
    lblocks= blocks > b2.blocks ? blocks : b2.blocks ;
    for(i=0;i<lblocks;i++){
        ansbv.bb[i]=bb[i]^b2.bb[i];
       // cout<<"\n..or of "<<bb[i] <<"  "<<b2.bb[i]<< " is "<<ansbv.bb[i];
    }
return ansbv;
}

bool bitvec :: operator[](int in){
    return (query_bit(in));
}
void bitvec :: operator=(bitvec &b2){
    int i;
    if(blocks < b2.blocks){
        delete(bb);
        bb=new int[b2.blocks];
    }
    for(i=0;i<b2.blocks;i++){
        bb[i]=b2.bb[i];
    }
    if(blocks > b2.blocks){
        for(i=b2.blocks;i<blocks;i++){
            bb[i]=0;
        }
    }


    blocks=b2.blocks;
    index=b2.index;


}


int main(){
bitvec bv1=bitvec();
bitvec bv2=bitvec();
bitvec bv3=bitvec();
bitvec bv4=bitvec();
//bitvec b11=bitvec(bv);

for(int i=0;i<8;i++){
    bv1.push_bit(false);
    bv2.push_bit(false);
    bv3.push_bit(false);
    bv4.push_bit(false);
}
bv1.set_bit(1);
bv1.set_bit(2);
bv1.set_bit(3);
bv1.set_bit(7);
bv1.set_bit(4);
bv1.clear_bit(7);

bv2.set_bit(1);
bv2.set_bit(3);
bv2.set_bit(4);
bv2.set_bit(5);

bv3.set_bit(1);
bv3.set_bit(2);
bv3.set_bit(3);
bv3.set_bit(7);

bv4.set_bit(1);
bv4.set_bit(2);
bv4.set_bit(3);
bv4.set_bit(5);

bitvec bans=bitvec();

bans=bv1&bv2&bv3&bv4;
cout<<"\nAND\n";
bv1.show_bit();
bv2.show_bit();
bv3.show_bit();
bv4.show_bit();
cout<<"----------\n";
bans.show_bit();

bans=bv1|bv2|bv3|bv4;
cout<<"\nOR\n";
bv1.show_bit();
bv2.show_bit();
bv3.show_bit();
bv4.show_bit();
cout<<"----------\n";
bans.show_bit();


bans=bv1^bv2^bv3^bv4;
cout<<"\nXOR\n";
bv1.show_bit();
bv2.show_bit();
bv3.show_bit();
bv4.show_bit();
cout<<"----------\n";
bans.show_bit();

cout<<"\n\n subscript Overloading \n";
cout<<bv1[0]<<"   "<<bv1[1]<<"\n";

for(int i=8;i<40;i++)
    bv1.push_bit(false);
 bv1.push_bit(true);
bv1.show_bit();
return 0;
}
