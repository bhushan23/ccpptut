    #include <iostream>
    using namespace std;

    class bvec{
        public:
            bool value;
      };

    class bitvec{
    public:
        int size;
        int index;
        bvec *bv;
        bitvec();
        bitvec(int);
        void push_back(bool );
        void push_bit();
        void push_bit(int);
        void set_bit(int);
        void clear_bit(int);
        void show_bit();
        bool query_bit(int);
        bool * bbegin();
        bool * bend();
        void operator=(bitvec &);

        bitvec(const bitvec &);

        bool& operator[] (int i){
               bool *ptr=&(bv->value)+i;
               return *ptr;
        }

        ~bitvec(){
         cout<<"\t\t\tdestroy ";
         show_bit();
         delete(bv);

        }
    bitvec& operator/(bitvec &b2){
        int lsize,hsize,i;
        int b2size=b2.index;
        if(index <= b2size){
            lsize=index;
            hsize=b2size;

        }else{
            hsize=index;
            lsize=b2size;

        }

        static bitvec ansvec= bitvec(hsize);
        ansvec.index=hsize;
        for(i=0;i<lsize;i++){
                if(query_bit(i) != b2.query_bit(i))
                    ansvec.set_bit(i);
                 else
                    ansvec.clear_bit(i);
            }
        if(hsize==index){

            for(i=lsize;i<hsize;i++){
                if(query_bit(i))
                   ansvec.set_bit(i);
                else
                    ansvec.clear_bit(i);
            }

        }else{


            for(i=lsize;i<hsize;i++){
                if(b2.query_bit(i))
                    ansvec.set_bit(i);
                else
                    ansvec.clear_bit(i);
            }
        }

        return ansvec;
    }


    bitvec& operator+(bitvec &b2){
        int lsize,hsize,i;
    if(index < b2.index){
            lsize=index;
            hsize=b2.index;
        }else{
            hsize=index;
            lsize=b2.index;
        }
         static bitvec ansvec= bitvec(hsize);
         ansvec.index=hsize;
        for(i=0;i<lsize;i++){
            if(query_bit(i) | b2.query_bit(i))
                ansvec.set_bit(i);
            else
                ansvec.clear_bit(i);
        }
        if(hsize==index){

            for(i=lsize;i<hsize;i++){
                if(query_bit(i))
                    ansvec.set_bit(i);
                else
                    ansvec.clear_bit(i);
            }
        }else{

            for(i=lsize;i<hsize;i++){
                if(b2.query_bit(i))
                    ansvec.set_bit(i);
                  else
                    ansvec.clear_bit(i);
            }
        }

        return ansvec;

    }

     bitvec& operator^(bitvec &b2){//why this works without passing reference and not other two
        int lsize,i;
        lsize= index < b2.index ? index : b2.index;

     static bitvec ansvec= bitvec(lsize);
     lsize== index? ansvec.index=index : ansvec.index=b2.index;
        for(i=0;i<lsize;i++){
            //cout<<query_bit(i)<<"  "<<ansvec.query_bit(i)<<"\n";
            if(query_bit(i) && b2.query_bit(i))
                ansvec.set_bit(i);
            else
                ansvec.clear_bit(i);
        }
       return ansvec;
    }

    };

    bool * bitvec :: bbegin(){
             return (&(bv->value));
        }
    bool * bitvec :: bend(){
             return (&(bv->value)+index*sizeof(bvec));
        }
    bitvec :: bitvec(const bitvec &tobj){
        int i;
        size=tobj.size;
        index=tobj.index;
        bv=(bvec *) :: operator new (sizeof(bvec) *size);
        bool *ptr=&(bv->value);
        bool *temp=&(tobj.bv->value);
        for(i=0;i<size;i++){
            *ptr=*temp;
            ptr+=sizeof(bvec);
            temp+=sizeof(bvec);
        }

    }
    void bitvec :: push_back(bool val){
        if(index >= size){
            push_bit();
        }
          bool *ptr=&(bv->value);
          ptr+=index;
          *ptr=val;
          index++;

    }
    bitvec :: bitvec(){
        int i;
        size=8;
        index=0;
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
        index=0;
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
        cout<<"bit pushed..";
        show_bit();
        //cout<<"..."<<bv<<".."<<tv<<"\n";


    }

    void bitvec :: push_bit(int inc){
        int o_size=size,i;
        bvec *tv;
        while(inc > 0){//until required pushbits are alloted multiplies
            inc-=size;
            size*=2;
        }
        tv=bv;

        bv=(bvec *) :: operator new (sizeof(bvec)*size);
        bool *ptr=&(tv->value);
        bool *newtemp=&(bv->value);
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
        delete(tv);
        //bv=tv;
        cout<<"bit pushed..";
        show_bit();


    }

    void bitvec :: set_bit(int bn){
        if(bn < index){
        bool *ptr=&(bv->value)+bn;
        *ptr=true;
        }else{

        cout<<"can not set bit "<<bn<<" not yet pushed\n";
        }
    }

    void bitvec :: clear_bit(int bn){
        if(bn < index){
        bool *ptr=&(bv->value)+bn;
        *ptr=false;
         }else{

        cout<<"can not clear bit "<<bn<<" not yet pushed\n";
        }
    }

    bool bitvec :: query_bit(int bn){
         if(bn < index){
        bool *ptr=&(bv->value)+bn;
        return *ptr;
         }else{
        cout<<"can not query bit "<<bn<<" not yet pushed\n";
        }
    }

    void bitvec :: show_bit(){
        int i;
       // cout<<"size.."<<size<<"\n";
        bool *ptr=&(bv->value);
        bool *temp=ptr;
        for(i=0;i<index;i++){
            ptr=temp+i;
            cout<<*ptr;
        }
        cout<<"\n";
    }



    void bitvec :: operator=( bitvec &b2){
        int i;
         int mysize=b2.size;
        index=b2.index;
        //cout<<mysize<<"..:\n";
        if(size < mysize){
                delete(bv);
                size=mysize;
                bv=(bvec *) :: operator new (sizeof(bvec)*mysize);
        }
                bool *b1v,*b2v;
                b1v=&(bv->value);
                b2v=&(b2.bv->value);
                for(i=0;i<mysize;i++){
                    //cout<<"\ninside exec "<<i<<" size"<<size<<"  "<<b2.size;
                    *b1v=*b2v;
                    b2v+=1;
                    b1v+=1;

                }
                if(size > mysize){
                    for(i=mysize;i<size;i++){
                        *b1v=false;
                        b1v+=1;
                    }
                }

    }

    int main(){

          bitvec bv1=bitvec();
          bitvec bv2=bitvec();
          bitvec bv3=bitvec();
          bitvec bv4=bitvec();
          bitvec b1=bitvec(),b2=bitvec(),b3=bitvec(),b4=bitvec();

          for(int i=0;i<8;i++){
            bv1.push_back(true);
            bv2.push_back(false);
            bv3.push_back(false);
            bv4.push_back(false);
          }

          bv1.set_bit(0);
          bv1.clear_bit(1);
          bv1.clear_bit(5);
          bv4.push_bit();

        //2nd
          bv2.set_bit(0);
          bv2.set_bit(2);
          bv2.set_bit(3);
         // bv2.push_bit();

          bv3.set_bit(0);
          bv3.set_bit(1);
          bv3.set_bit(4);

          bv4.set_bit(0);
          bv4.set_bit(3);
          bv4.set_bit(5);

          b1=bv1;
          b2=bv2;
          b3=bv3;
          b4=bv4;


          cout<<" AND.. \n";
          b1.show_bit();
          b2.show_bit();
          b3.show_bit();
          b4.show_bit();
          bitvec andbit= b1 ^ b2 ^b3 ^b4;

          andbit.show_bit();

          cout<<"\n OR.. \n";
          b1.show_bit();
          b2.show_bit();
          b3.show_bit();
          b4.show_bit();
          bitvec orbit=bitvec();
          orbit= b1  + b2 +b3+b4;
          orbit.show_bit();

          cout<<" XOR.. \n";
          b1.show_bit();
          b2.show_bit();
          b3.show_bit();
          b4.show_bit();
          bitvec xorbit= bitvec();
          xorbit=bv1/bv2;

          xorbit.show_bit();

          cout<<"subscript overloading\n";
          cout<< bv1[1] << "  "<<bv1[4];
          cout<<"\n mixed \n";

          b1.show_bit();
          b2.show_bit();
          b3.show_bit();
          b4.show_bit();
          bitvec mix=bitvec();
          mix= b1  + b2 ^ b3 / b4;
            mix.show_bit();

          b1=bv1;
          b2=bv2;
          b3=bv3;
          b4=bv4;
          cout<<"\niterator.. b1   ";
          bool *i;
          for( i=b1.bbegin();i<b1.bend();i++){
          cout<<*i;
            }
          cout<<"\n.. b2 ";
          for( i=b2.bbegin();i<b2.bend();i++){
          cout<<*i;
           }
           cout<<"\n";
            b1.set_bit(15);
         return 0;
    }
