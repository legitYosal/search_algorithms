	
//In the Name of God

#include <bits/stdc++.h>
#include <cstdio>
#include <chrono>
using namespace std ;
using namespace std::chrono;

#define X first
#define Y second
//#define int long long

typedef long long ll ;
typedef long double ld ;
typedef long long int lli ;


const int maxn = 1e6 + 10 ;

struct Map {
  int cell[7][7];
};
struct Car {
  int x , y , len ;
  char vh ;
};

struct State {
  string id ;
  Map map;
  Car cars[40];
  //int parent ;
};

State states[maxn] ;
int stateSize ;
int N ;
vector < State > soloutions ;
stack < State > sts ;
map < string , string > par ;
map < string , State > nodes ;
map < string , bool > mark ;
State first ;
State goal ;
// pair < pair < int , int > , pair < char , int > > car[20] ;

State Hash ( State node ) {
  string key = "" ;
  for ( int i = 1 ; i <= N ; i ++ ) {
    key += to_string(node.cars[i].x) ;
    key += to_string(node.cars[i].y) ;
    key += to_string(node.cars[i].len) ;
    key += node.cars[i].vh ;
  }
  node.id = key ;
  //nodes[key] = node ;
  return node ;
}

bool checkGoal ( State node ) {
  for ( int i = node.cars[1].y + node.cars[1].len ; i < 7 ; i ++ ) {
    if (node.map.cell[node.cars[1].x][i] != 0)
      return false;
  }
  return true;
}
bool checkMove ( Car car , Map map , int p , int arrow ) {
  if ( arrow == 0 ) {
    if ( car.vh == 'h' ) {
      for ( int i = 1 ; i < p + 1 ; i ++ ) {
        if ( map.cell[car.x][car.y-i] != 0 )
	  return false ;
      }
    }
    else {
      for ( int i = 1 ; i < p + 1 ; i ++ ) {
        if ( map.cell[car.x+car.len+i-1][car.y] != 0 )
	  return false ;
      }
    }
  }
  else  {
    if ( car.vh == 'h' ) {
      for ( int i = 1 ; i < p + 1 ; i ++ ) {
        if ( map.cell[car.x][car.y+car.len +i-1] != 0 )
	  return false ;
      }
    }
    else {
      for ( int i = 1 ; i < p + 1 ; i ++ ) {
        if ( map.cell[car.x-i][car.y] != 0 )
	  return false ;
      }
    }
  }
  return true ;
}


vector <State> successor( State node ) {
  vector < State > childsState ;
  Map map = node.map ;
  for ( int i = 1  ; i <= N ; i ++ ) {
    Car car = node.cars[i] ;
    if ( car.vh == 'h' ) {
      for (int k = 1 ; k < 5 ; k ++) {
        if ( checkMove ( car , map , k , 0 ) and car.y-k > 0  ) {
	  State newState = node ;
	  for ( int loc = car.y ; loc < car.y + car.len ; loc ++ ) {
	    newState.map.cell[car.x][loc] = 0 ;
	  }
	  for ( int loc = car.y ; loc < car.y + car.len ; loc ++ ) {
	    newState.map.cell[car.x][loc-k] = i ;
	  }
	  newState.cars[i].y = newState.cars[i].y - k ;
	  
	  newState = Hash ( newState ) ;
	  nodes[node.id] = node ;
	  childsState.push_back ( newState ) ;
	  
        }else break ;
      }
      for (int k = 1 ; k < 5 ; k ++) {
        if ( checkMove ( car , map , k , 1 )and car.y+car.len+k-1 < 7 ) {
	  State newState = node ;
	  for ( int loc = car.y ; loc < car.y + car.len ; loc ++ ) {
	    newState.map.cell[car.x][loc] = 0 ;
	  }
	  for ( int loc = car.y ; loc < car.y + car.len ; loc ++ ) {
	    newState.map.cell[car.x][loc+k] = i ;
	  }
	  newState.cars[i].y = newState.cars[i].y + k ;
	  newState = Hash ( newState ) ;
	  nodes[node.id] = node ;
	  childsState.push_back ( newState ) ;
	   
        }else break;
      }
    }
    else if ( car.vh == 'v' ) {
      for (int k = 1 ; k < 5 ; k ++) {

        if ( checkMove ( car , map , k , 1 ) and car.x - k > 0 ) {
	  State newState = node ;
	  for ( int loc = car.x ; loc < car.x + car.len ; loc ++ ) {
	    newState.map.cell[loc][car.y] = 0 ;
	  }
	  for ( int loc = car.x ; loc < car.x + car.len ; loc ++ ) {
	    newState.map.cell[loc-k][car.y] = i ;
	  }
	  newState.cars[i].x = newState.cars[i].x - k ;
	  newState = Hash ( newState ) ;
	  nodes[node.id] = node ;
          childsState.push_back ( newState ) ;
	  
        }else break ;
      }
      for (int k = 1 ; k < 5 ; k ++) {
        if ( checkMove ( car , map , k , 0 ) and car.x+car.len+k-1 < 7 ) {
	  State newState = node ;
	  for ( int loc = car.x ; loc < car.x + car.len ; loc ++ ) {
	    newState.map.cell[loc][car.y] = 0 ;
	  }
	  for ( int loc = car.x ; loc < car.x + car.len ; loc ++ ) {
	    newState.map.cell[loc+k][car.y] = i ;
	  }
	  newState.cars[i].x = newState.cars[i].x + k ;
	  
	  newState = Hash ( newState ) ;
	  nodes[node.id] = node ;
	  childsState.push_back ( newState ) ;
	  
	  
	}else break ;
      }
    }
  }
  return childsState ;
}

void generateSolve ( State goal ) {

  State cur = goal ;
  soloutions.push_back ( goal ) ;
  while ( cur.id != first.id ) {
    soloutions.push_back ( nodes[par[cur.id]] ) ;
    cur = nodes[par[cur.id]] ;
  }
  
  reverse ( soloutions.begin() , soloutions.end() ) ;
}

void printSoloution () {
  int past = 0 ;
  for ( int now = 1 ; now < soloutions.size() ; now ++ ) {
    for ( int j = 1 ; j <= N ; j ++ ) {
      if ( soloutions[now].cars[j].x != soloutions[past].cars[j].x ) {
	int dis = soloutions[now].cars[j].x - soloutions[past].cars[j].x ;
	if ( dis > 0 )
	  cout << j << " " << "d" << " " <<  dis << endl ;
	else
	  cout << j << " " << "u" << " " <<  -dis << endl ;
	break ;
      }
      else if ( soloutions[now].cars[j].y != soloutions[past].cars[j].y ) {
	int dis = soloutions[now].cars[j].y - soloutions[past].cars[j].y ;
	if ( dis > 0 )
	  cout << j << " " << "r" << " " <<  dis << endl ;
	else
	  cout << j << " " << "l" << " " <<  -dis << endl ;
	break ;
      }
    }
    past = now ;
  }
  cout << 1 << " " << "r" << " " << 5 - soloutions[soloutions.size()-1].cars[1].y << endl ;

}

//DFS
void dfs () {

  sts.push ( first ) ;
  while ( !sts.empty() ) {
    State cur ;
    cur = sts.top() ;
    sts.pop () ;
    if ( !mark[cur.id] ) {
      mark[cur.id] = true ;
      if ( checkGoal ( cur ) ) {
	generateSolve ( cur ) ;
	printSoloution () ;
	return ;
      }
    }
    
    vector < State > children ;
    children = successor ( cur ) ;
    
    for ( int i = 0 ; i < children.size() ; i ++ ) {
      if ( !mark[children[i].id] ) {
	par[children[i].id] = cur.id ;
	sts.push ( children[i] ) ;

      }
    }
    
  }
}


int32_t main () {

  ios::sync_with_stdio(0);cin.tie(0) ;
  cin >> N ;
  for ( int i = 0 ; i < N ; i ++ ) {
    int n , x , y , len ;
    char vh ;
    cin >> n >> x >> y >> vh >> len ;
    first.cars[n].x = x ;
    first.cars[n].y = y ;
    first.cars[n].vh = vh ;
    first.cars[n].len = len ;
    if ( vh == 'v') {
      for ( int j = x ; j < x + len ; j ++ )
	first.map.cell[j][y] = n ;
    }
    if ( vh == 'h') {
      for ( int j = y ; j < y + len ; j ++ )
	first.map.cell[x][j] = n ;
    }
  }
  
  first = Hash ( first ) ;

  dfs () ;

 
  return 0 ;
}

