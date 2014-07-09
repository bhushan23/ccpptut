#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <cstdio>
#include <algorithm>
#include <bitset>
#include <queue>

using namespace std;
class graph
{
  vector < vector <int> > adj_list;
  vector < bool > visited;
  vector < set<int> > dominator;
  vector < bool > dominator_bit;
  vector <int> idom;
  vector < set <int> > df;
  
public:
  int counter;
  graph(int);
  void create_node();
  int get_dest(int,int);
  void create_edge(int,int);
  int list_size(int);
  void bt_fn(int,int);
  void find_dominator(int,int);
  void print_dominator();
  bool intersect_dominator();
  bool intersect_dominator_bit();
  bool dset_available(int i){
    return visited[i];
  }
  bool dominator_check(int,int);
  void cal_idom();
  void natural_loop();
  void cal_df();
  void print_df();

  
  set<int> :: iterator get_beg_dominator(int i){
    return dominator[i].begin();
  }

  
  set<int> :: iterator get_end_dominator(int i){
    return dominator[i].end();
  }

  set<int> get_dominator_list(int i){
    return dominator[i];
  }
};
void graph :: create_node(){
  vector <int> temp;
  set <int> stemp;
  
  adj_list.push_back(temp);
  dominator.push_back(stemp);
  visited.push_back(false);
  idom.push_back(-1);
  df.push_back(stemp);
}

bool graph :: dominator_check(int tocheck, int inset){
  //int size=dominator[inset].size();
  if( dominator[inset]. find(tocheck) != dominator[inset].end())
    return true;
  return false;

}
graph :: graph(int n){
  counter=0;

  for(int i=0;i<=n+1;i++){
    create_node();
    dominator[i].insert(i);
  }
  int total_bool_block= n/8 + 1;
  while( total_bool_block-- ){
    dominator_bit.push_back(false);
  }
}
int graph :: get_dest(int i,int j){
  if(j < adj_list[i].size())
    return (adj_list[i][j]);
  return -1;
}
void graph :: create_edge( int src, int dest)
{  
  adj_list[src].push_back(dest);
  
}
int graph :: list_size(int i){
  return (adj_list[i].size());
}
void graph :: print_dominator(){
  int i,total;
  set <int> :: iterator it,it_end;
  total = dominator.size();
  cout<<"Node : Its Dominators";
  for( i = 0; i < total; ++i){
    cout<<"\n"<<i<< " : ";
    it_end = dominator[i].end();
    
    for( it = dominator[i].begin(); it != it_end; ++it){
      cout<<" "<<*it;
    }
    
  }
}

void print_set(set <int> :: iterator it, set <int> :: iterator end){
 
  for(; it!= end; ++it){
    cout<<" "<<*it;
  }
}

/*
 * for each node, intersects dominator set of its all predecessor
 * and assigns this set along with itself to its dominator set
 * return true if dominator set is change otherwise return false
 */

bool graph :: intersect_dominator(){
  int total=adj_list.size();
  int total_pred,pred;
  bool change_flag=false;
  counter++;
  for(int i = 0; i < total; ++i){
    set<int> result_set;
    total_pred=adj_list[i].size();

    for(int j = 0; j < total_pred; ++j){

      if(visited[adj_list[i][j]]){
	result_set=get_dominator_list(adj_list[i][j]);
	break;
      }
    }
       
    for(int j = 0; j < total_pred; ++j){

      set<int> :: iterator it,itend;
      set<int>  temp,temp1;
      pred = adj_list[i][j];
    
      if( visited[pred] ){//if we have calculated dominator
	itend = get_end_dominator(pred);
	temp = get_dominator_list(pred);
	set_intersection(result_set.begin(),result_set.end(),
			 temp.begin(),temp.end(),inserter (temp1,temp1.begin()));
	result_set=temp1;
	    
      }
    }
  
    result_set.insert(i);
    if(dominator[i] != result_set){
      change_flag=true;
      dominator[i].clear();
      dominator[i] = result_set;
    }
    visited[i]=true;
  }
   return change_flag;
}
/*

bool graph :: intersect_dominator_bit(vector <bitset < 6 >> &dom_bit){
  int total=adj_list.size();
  int total_pred,pred;
  bool change_flag=false;
  bitset <total_pred> tmpbit;
      
  counter++;
  for(int i = 0; i < total; ++i){
    total_pred=adj_list[i].size();

    if(total_pred == 1 && visited[adj_list[i][0]]){
      tmpbit = dom_bit[i];
      //dom_bit[i].reset();
      dom_bit[i] = dom_bit[ adj_list[i][0] ];
      
    }else{
      tmpbit.reset();
      tmpbit.flip();
      
      for(int j = 0; j < total_pred; ++j){
	pred = adj_list[i][j];
    
	if( visited[pred] ){//if we have calculated dominator

	  tmpbit = tmpbit & dom_bit[pred];
	  tmpbit.set(i);
	  dom_bit[i] = tmpbit;
	}
      }
    }
    
    if(tmpbit != dom_bit[i]){
      change_flag=true;
    }
    visited[i]=true;
    }
   return change_flag;
   }*/
/* 
 * Iterate through graph until dominator set is unchanged
 */



void graph :: find_dominator(int start, int end){
  bool change_flag=false;
  create_edge(start,0);
  create_edge(end+1,end);
  int total= adj_list.size();
  do{//iterate until dominator set of all node is unchanged
    
    change_flag = intersect_dominator();
    
  }while( change_flag );
  
}

//void graph :: add_loop_predecessor(int src, int tail, )

void graph :: add_loop_member(int src,int tail){

  set <int> loop;
  int size= adj_list.size();
  bitset <size> flag;
  queue <int> itq;
  
  loop.insert(src);
  loop.insert(tail);
  flag.set(src);
  flag.set(tail);

  for(i = 0;i < adj_list[i].size(); ++i){
    itq.push( adj_list[tail][i] );
  }
  //add_loop_predecessor(src, tail, loop, flag);

  while( !itq.empty() ){
    elem = itq.pop();
    if( !flag.test(elem) ){
      flag.set(elem);
      for(i = 0;i < adj_list[elem].size(); ++i){
	itq.push( adj_list[elem][i] );
  }
    }
  }
  
}

void graph :: natual_loop(){
  int i,size=adj_list.size();
  for(i = 0;i < size;++i){
    lsize = adj_list[i].size();
    for(j = 0;j < lsize; ++j){
      if( dominator_check( adj_list[i][j], i) ){//backedge exists
	add_loop_members(i,adj_list[i][j]);
      }
    }
  }
}
/* 
 * Function : calculate Immediate Dominant of node
 * Algorithm: Iterate Through all nodes
 *               add dominanator set of all dominators of current node to set DSET
 *               remove Repeating nodes from DSET
 * Returns: void  
 */
void graph :: cal_idom(){
     
 
  set <int> :: iterator it;
  
  int i,cur,j,cur1;
  int isize=dominator.size();
  
  for( i = 0; i < isize; ++i){
   
    set <int> alldom;
    set <int> tmpset = dominator[i];
    set <int> :: iterator itend = tmpset.end();
    vector<int> removable;

    tmpset.erase(i);
    it=tmpset.begin();
    if( tmpset.size() == 1){
      idom[i]=*it;
    }else{//more than 2 predecessor
      
      for(it = tmpset.begin() ; it != itend ; ++it){
	cur= *it;
	set <int> :: iterator it1end = dominator[cur].end();

	for(set <int> :: iterator it1 = dominator[cur].begin(); it1 != it1end; ++it1){
	  cur1= *it1;

	  if(alldom.find(cur1) != alldom.end()){//repeated nodes 
	    removable.push_back(cur1);

	  }else{
	    alldom.insert(cur1);
	  }
	  
	}
      }
      
    
      for(j = 0; j < removable.size(); ++j){
	  alldom.erase(removable[j]);
      }
      if(alldom.size() == 1){//Can removal lead to only 1 node in alldom ? Otherwise assign first node of alldom to idom[i]
	it=alldom.begin();
      	idom[i] = *it;
      }
    }   
  }
  cout<<"\nIdom \n";
  for(i=0; i< idom.size(); ++i){
    cout<<i<<" : "<<idom[i]<<"\n";
  }
	
}
/* 
 * Function : calculates Dominance frontier of all nodes
 * Algorithm : Nodes having more than 1 predecessor are selected,
 *             iterate through predecessor say temp:
 *                 until temp != idom(Current Node):    
 *                     Dominance_Frontier(temp) = Current Node
 *                     go to idom of temp                                        
 * Returns : void
 */
void graph :: cal_df(){
  int i,j,size,temp;
  size=adj_list.size();

  for(i = 0; i < size; ++i){
    if(adj_list[i].size() > 1){//predessessor 
      
      for(j = 0; j < adj_list[i].size(); ++j){
	temp = adj_list[i][j];
	
	while( temp != idom[i] ){
	  df[temp].insert(i);
	  temp=idom[temp];
	  if(temp == -1)//-1 is for node having no idom
	    break;
	}
      }

    }
  }
  cout<<"DF \n";
  print_df();
}

void graph :: print_df(){
  int i;
  int size=df.size();
  for(i = 0; i < size; ++i){
    cout<<"\n"<<i<<" : ";
    print_set(df[i].begin(),df[i].end());
  }
}
int main()
{
  int i,n,temp,nodei,src=1;
  freopen("inmih", "r", stdin);
  cin>>n;
  graph g1= graph(n);
  i=0;

  while(i++ < n){
    cin>>nodei;
    while(1){
      cin>>temp;
      if(temp==0){
	break;
      }else{
	g1.create_edge(temp,nodei);
      }
    }
  }
  g1.find_dominator(src,n);
  cout<<g1.counter<<"\n";
  g1.print_dominator();
  g1.cal_idom();
  g1.cal_df();
  return 0;
}
