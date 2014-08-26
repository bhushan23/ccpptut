// erasing from set
#include <iostream>
#include <set>

int main ()
{
  std::set<int> myset;
  std::set<int>::iterator it;

  // insert some values:
  for (int i=1; i<20; i++) myset.insert(i*10);  // 10 20 30 40 50 60 70 80 90

  for(int i=1; i<15; ++i)
    myset.erase(i*10);

  for( it = myset.begin(); it != myset.end(); ++it){
                                            // "it" points now to 20
  std::cout<<"\n..."<<*it;
  }/*
  myset.erase (*it++);
  std::cout<<"..."<<*it<<"\n";
 

  it = myset.find (60);
  myset.erase (it, myset.end());
   */
  std::cout << "\nmyset contains:";
  for (it=myset.begin(); it!=myset.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
