
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

//State statesStart[maxn] ;
//State statesEnd[maxn] ;

map < string , State > nodes ;


map < string , bool > mark ;
map < string , bool > markf ;
map < string , bool > markg ;


map < string , string > par ;
map < string , string > parf ;
map < string , string > parg ;

State states[maxn] ;
list < State > f , g ;
list < State > sts ;
int stateSize ;
int N ;
vector < State > soloutions ;

State null ;

State first , goal ;

//bool isF = true ;

//bool isBDS ;

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

void generateSolve ( State arrive ) {

  State cur = arrive ;
  soloutions.push_back ( arrive ) ;
  while ( cur.id != first.id ) {
    soloutions.push_back ( nodes[parf[cur.id]] ) ;
    cur = nodes[parf[cur.id]] ;
  }
  cur = arrive ;
  
  reverse ( soloutions.begin() , soloutions.end() ) ;
  
  while ( cur.id != goal.id ) {
    soloutions.push_back ( nodes[parg[cur.id]] ) ;
    cur = nodes[parg[cur.id]] ;
  }
  
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


State bfs ( State root ) {
  
  while ( !sts.empty () ) {
    State now = sts.front() ;
    sts.pop_front() ;
    vector < State > children ;
    children = successor ( now ) ;
    for ( int i = 0 ; i < children.size() ; i ++ ) {
      if ( !mark[children[i].id] ) {
	mark[children[i].id] = true ;
	par[children[i].id] = now.id ;
	sts.push_back ( children[i] ) ;
	if ( checkGoal ( children[i] ) )
	  return children[i] ;
      }
    }
  }

}


void bfsF () {
  
  State now = f.front() ;
  f.pop_front() ;
  vector < State > children ;
  children = successor ( now ) ;
  for ( int i = 0 ; i < children.size() ; i ++ ) {
    if ( !markf[children[i].id] ) {
      markf[children[i].id] = true ;
      parf[children[i].id] = now.id ;
      f.push_back ( children[i] ) ;
      states[stateSize] = children[i];
      stateSize ++ ;
    }
  }
}

void bfsG () {
 
  State now = g.front() ;
  g.pop_front() ;
  vector < State > children ;
  children = successor ( now ) ;
  for ( int i = 0 ; i < children.size() ; i ++ ) {
    if ( !markg[children[i].id] ) {
      markg[children[i].id] = true ;
      parg[children[i].id] = now.id ;
      g.push_back ( children[i] ) ;
      states[stateSize] = children[i];
      stateSize ++ ;
    }
  }
}

State checkArrive () {

  for ( int i = 0 ; i < stateSize ; i ++ ) {
    if ( markf[states[i].id] and markg[states[i].id] )
      return states[i] ;
  }

  return null ;
  
}

int bds ( State first , State goal ) {
 
  f.push_back ( first ) ;
  g.push_back ( goal ) ;
  markf[first.id] = true ;
  parf[first.id] = "-1" ;
  markg[goal.id] = true ;
  parf[goal.id] = "-1" ;

  State arrive ;
  arrive.id = "-0" ;
  while ( !f.empty() and !g.empty() ) {
    bfsF () ;
    bfsG () ;
   arrive = checkArrive() ;
   if ( arrive.id != "-0" ) {
     generateSolve ( arrive ) ;
     printSoloution () ;
     return 0 ;
   }
  }  
  return -1 ;
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
  null.id = "-0" ;

  first = Hash ( first ) ;

  states[0] = first ;

  stateSize ++ ;

  sts.push_back ( first ) ;
  
  goal = bfs ( first ) ;

  goal = Hash ( goal ) ;
  
  bds ( first , goal ) ;
  
 
  

  
  return 0 ;
}
