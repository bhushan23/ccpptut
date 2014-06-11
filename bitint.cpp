#include <iostream>
#include <limits>
#define BITS 32
using namespace std;
class bitvec{
    public:
        int blocks;
        int index;
        int *bb;
        bitvec();
        bitvec(int );
        void push_bit(bool);
        void show_bit();
        void set_bit(int);
        void clear_bit(int);
        bool query_bit(int);
        bitvec& operator&(bitvec&);
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
void bitvec::push_bit(bool val){

    if(index >= blocks * sizeof(int)){
            //expand
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
    int mint=numeric_limits<int>::max(),ans;
    cout<<index<<"\n";
    for(int i=0;i<blocks;i++){
        ans=bb[i] & mint;
        cout<<"..."<<ans;
    }
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
    cout<<"..as"<<bb[bnum]<<"\n";

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
    cout<<"..Bit is "<< temp<<"\n";
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
        cout<<"\n..and of "<<bb[i] <<"  "<<b2.bb[i]<< " is "<<ansbv.bb[i];
    }

}
bitvec& bitvec :: operator|(bitvec& b2){
    int hsize,i,lblocks;
    hsize = index > b2.index ? index : b2.index;
    static bitvec ansbv= bitvec(hsize);
    lsize == index? ansbv.index=index : ansbv.index=b2.index;
    lblocks= blocks > b2.blocks ? blocks : b2.blocks ;
    for(i=0;i<lblocks;i++){
        ansbv.bb[i]=bb[i]&b2.bb[i];
        cout<<"\n..and of "<<bb[i] <<"  "<<b2.bb[i]<< " is "<<ansbv.bb[i];
    }

}

int main(){
bitvec bv=bitvec();
bitvec bv1=bitvec();
bv.push_bit(true);
bv.push_bit(false);
bv.push_bit(true);
bv.push_bit(true);
bv.query_bit(1);
bv.clear_bit(2);
bv.show_bit();
bv1.push_bit(true);
bv1.push_bit(false);
bv1.push_bit(true);
bv1.push_bit(true);
bv&bv1;
/*
int a=4,b=5;
int c=a&b;
cout<<c<<"\n";
cout<<"  "<< sizeof(bv.bb)<<"  "<<sizeof(bv.bb[0])<<"  ";
//cout<<bv.blocks<<" "<<bv.bb[0];

*/


return 0;
}
