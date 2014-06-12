    #include <iostream>
    #define BITS 32

    using namespace std;
    class bitvec{

            int blocks;
            int index;
            int *bb;
            int cindex; //for iterator
        public:
            bitvec();
            bitvec(int);
            bitvec(const bitvec &);
            ~bitvec();
            void push_bit(bool);
            void show_bit();
            void set_bit(int);
            void clear_bit(int);
            bool query_bit(int);
            bitvec operator&(const bitvec&);
            bitvec operator|(const bitvec&);
            bitvec operator^(const bitvec&);
            bitvec& operator=(const bitvec&);
            int operator[](int);
            //for iterator
            bool getbegin();
            bool getend();
            int itbegin();
            int itend();
            bool next();
            bool previous();
            void setit(int);
    };

    bitvec::bitvec(){
        blocks=1;
        index=0;
        cindex=0;
        bb=new int;
        bb[0]=0;
    }
    bitvec::bitvec(int s){
        blocks=s/BITS + 1 ;
        index=0;
        cindex=0;
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

    bitvec bitvec :: operator&(const bitvec& b2){
        int lsize,i,lblocks;
        lsize = index < b2.index ? index : b2.index;
         bitvec ansbv= bitvec(lsize);
        lsize == index? ansbv.index=index : ansbv.index=b2.index;
        lblocks= blocks < b2.blocks ? blocks : b2.blocks ;
        for(i=0;i<lblocks;i++){
            ansbv.bb[i]=bb[i]&b2.bb[i];
            //cout<<"\n..and of "<<bb[i] <<"  "<<b2.bb[i]<< " is "<<ansbv.bb[i];
        }
    return ansbv;
    }

    bitvec bitvec :: operator|(const bitvec& b2){
        int hsize,i,lblocks;
        hsize = index > b2.index ? index : b2.index;
         bitvec ansbv= bitvec(hsize);
        hsize == index? ansbv.index=index : ansbv.index=b2.index;
        lblocks= blocks > b2.blocks ? blocks : b2.blocks ;
        for(i=0;i<lblocks;i++){
            ansbv.bb[i]=bb[i]|b2.bb[i];
           // cout<<"\n..or of "<<bb[i] <<"  "<<b2.bb[i]<< " is "<<ansbv.bb[i];
        }
    return ansbv;
    }
    bitvec bitvec :: operator^(const bitvec& b2){
        int hsize,i,lblocks;
        hsize = index > b2.index ? index : b2.index;
        bitvec ansbv= bitvec(hsize);
        hsize == index? ansbv.index=index : ansbv.index=b2.index;
        lblocks= blocks > b2.blocks ? blocks : b2.blocks ;
        for(i=0;i<lblocks;i++){
            ansbv.bb[i]=bb[i]^b2.bb[i];
           // cout<<"\n..or of "<<bb[i] <<"  "<<b2.bb[i]<< " is "<<ansbv.bb[i];
        }
    return ansbv;
    }

    int bitvec :: operator[](int in) {
        cout<<"in [] \n";
        int o;
        if(query_bit(in))
            o= 1;
        else
            o=0;
        return o;
    }

    bitvec& bitvec :: operator=(const bitvec& b2){
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
        return *this;
    }

    bool bitvec :: getbegin(){
       return query_bit(0);
    }

    bool bitvec :: getend(){
       return query_bit(index-1);
    }

    int bitvec :: itbegin(){
    return 0;
    }

    int bitvec :: itend(){
    return index;
    }
    bool bitvec :: next(){
         return query_bit(cindex++);
    }
    bool bitvec :: previous(){
        if(cindex==0){
            cout<<"\n You are at beginning\n";
        }else
        return query_bit(--cindex);
    }
    void bitvec :: setit(int i){
        cindex=i;
    }



    int main(){
    bitvec bv1=bitvec();
    bitvec bv2=bitvec();
    bitvec bv3=bitvec();
    bitvec bv4=bitvec();


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

    bitvec band=bitvec();
    bitvec bor=bitvec();
    bitvec bxor=bitvec();

    band=bv1&bv2&bv3&bv4;
    cout<<"\nAND\n";
    bv1.show_bit();
    bv2.show_bit();
    bv3.show_bit();
    bv4.show_bit();
    cout<<"----------\n";
    band.show_bit();

    bor=bv1|bv2|bv3|bv4;
    cout<<"\nOR\n";
    bv1.show_bit();
    bv2.show_bit();
    bv3.show_bit();
    bv4.show_bit();
    cout<<"----------\n";
    bor.show_bit();


    bxor=bv1^bv2^bv3^bv4;

    cout<<"\nXOR\n";
    bv1.show_bit();
    bv2.show_bit();
    bv3.show_bit();
    bv4.show_bit();
    cout<<"----------\n";
    bxor.show_bit();

    cout<<"\n\n subscript Overloading \n";
    cout<<bv1[0]<<"   "<<bv1[1]<<"\n";

    for(int i=8;i<40;i++)
     bv1.push_bit(false);
     for(int i=8;i<40;i++)
     bv2.push_bit(false);
      bv2.push_bit(false);
     bv2.set_bit(20);
     bv1.set_bit(20);
     bv2.set_bit(22);
     bv1.push_bit(true);
     bv1.show_bit();
    bitvec bvaa=bitvec();
    bvaa=bv1 & bv2;
    cout<<"and of \n";
    bv1.show_bit();
    bv2.show_bit();
    cout<<"----------\n";
    bvaa.show_bit();
    cout<<"Iterator\n";

    for(int i=bv1.itbegin();i<bv1.itend();i++){
        cout<<bv1.next();
    }
    cout<<"\n";
/*
    bitvec *bp1, *bp2;
    bp1 = & (bv1 ^ bv2);
    bp2 = & (bv3 ^ bv4);
*/

    cout<"\n\n";
    bitvec be1=bitvec();
    bitvec be2=bitvec();
    bitvec be3=bitvec();
    bitvec be4=bitvec();
    be1=be2=be3=be4=bv3show_bit();

    be1.show_bit();
    be2.show_bit();
    be3.show_bit();
    be4.show_bit();

    return 0;
    }
