#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
class graph
{
  vector < vector <int> > adj_list;
  vector < bool > visited;
  vector < set<int> > dominator;
  vector <int> idom;
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
  bool dset_available(int i){
    return visited[i];
  }
  void cal_idom();
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
}

graph :: graph(int n){
  counter=0;
  for(int i=0;i<=n+1;i++){
    create_node();
    dominator[i].insert(i);
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
 * Iterate through graph until dominator set is unchanged
 */

void graph :: find_dominator(int start, int end){
  bool change_flag=false;
  create_edge(start,0);
  create_edge(end+1,end);
  
  do{//iterate until dominator set of all node is unchanged
    
    change_flag = intersect_dominator();
    if(change_flag == false){//if dominator set is unchanged cross check
    
      change_flag = intersect_dominator();
      
    }
    
     
  }while( change_flag );
}
/*
void graph :: cal_idom(){
  int i=0,cur,incur;
  set <int> :: iterator it;
  for( i = 0; i < dominator.size(); ++i){
    set <int> :: iterator itend = dominator[i].end();
    set <int> tmpset = dominator[i] , set_diff, tmp1,tempop;
    tmpset.erase(i);
    it=tmpset.begin();
    if( tmpset.size() == 1){
      idom[i]=*it;
    }else{
      for(it = tmpset.begin() ; it != itend ; ++it){
	cur = *it;
	set_diff = dominator[cur];
	if ( cur  == i){
	  //break;
	}else{
	  cout<<cur<<"  ";
	  for(set <int> :: iterator in_it = tmpset.begin() ; it != itend ; ++it){
	    incur = *in_it;
	    if( incur != i && incur != cur){
	      set_difference(set_diff.begin(),set_diff.end(),dominator[incur].begin(),dominator[i].end(),inserter(tempop,tempop.begin());
			     set_diff=tempop;
			     }
	  }

	}
      }
    }
    cout<<"\n";
  }
  }*/

void graph :: cal_idom(){
     
 
  set <int> :: iterator it;
  
  int i,cur,j,cur1;
  int isize=dominator.size();
  cout<<"\ninside whole "<<isize;
  for( i = 0; i < isize; ++i){
    cout<<"\ninside "<<i;
  
    set <int> alldom;
    set <int> tmpset = dominator[i];
    set <int> :: iterator itend = tmpset.end();
    vector<bool> rpflag(adj_list.size(),0);

    tmpset.erase(i);
    it=tmpset.begin();
    if( tmpset.size() == 1){
      idom[i]=*it;
      //      cout<<" Only one idom "<<idom[i] ;
    }else{
      for(it = tmpset.begin() ; it != itend ; ++it){
	cur= *it;
	
	set <int> :: iterator it1end = dominator[cur].end();
	for(set <int> :: iterator it1 = dominator[cur].begin(); it1 != it1end; ++it1){
	  cur1= *it1;
	  //cout<<"\n..working "<<cur;
	  if(alldom.find(cur1) != alldom.end()){//repeated 
	    rpflag[cur1]=true;
	    //cout<<"\nrepeated "<<cur;
	  }else{
	    alldom.insert(cur1);
	    //  cout<<"\ninsert "<<cur;
	  }
	  
	}
      }
      
    
      for(j = 0; j < rpflag.size(); ++j){
	if(rpflag[j] == true){
	  alldom.erase(j);
	}
      }
      if(alldom.size() == 1){
	it=alldom.begin();
      	idom[i] = *it;
      }
    }
      
    
    //cout<<" " <<alldom.size();
    // print_set(alldom.begin(), alldom.end());
  }

  for(i=0; i< idom.size(); ++i){
    cout<<i<<" "<<idom[i]<<"\n";
  }
	
}
int main()
{
  int i,n,temp,nodei,src=1;
  freopen("indom", "r", stdin);
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
  return 0;
}
