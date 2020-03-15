
//In the Name of God

#include <bits/stdc++.h>
#include <cstdio>
#include <chrono>
using namespace std ;
using namespace std::chrono;

#define X first
#define Y second
//#define int long long
#define TRANSITION_COST 1
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
  //int Gval;
  //int Hval;
  //int parent ;
};

State states[maxn] ;
int stateSize ;
int N ;
vector < State > soloutions ;
//list < State > sts ;
map < string , int > Gval ;
map < string , int > Hval ;
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
  nodes[key] = node ;
  return node ;
}
void print (Map map) {
  cout << "map :" << endl;
  for ( int i = 1 ; i < 7 ; i ++ ) {
    for ( int j = 1 ; j < 7 ; j ++ ){
      cout << map.cell[i][j] << " " ;
      if (map.cell[i][j] < 10){
        cout << ' ';
      }
    }
  cout << endl ;
  }
}
int heuristic(State node){
  // return 0;
  int x, y;
  int car;
  vector <int> blocked;
  vector <int> stack;
  for (int i = node.cars[1].y + node.cars[1].len; i < 7; i ++){
    car = node.map.cell[node.cars[1].x][i];
    if ( car != 0 and car != 1){
      // because they all are verticall then just add it to in main path
      if (find(blocked.begin(), blocked.end(), car) == blocked.end()){
        blocked.push_back(car);
        stack.push_back(car);
      }
      while (!stack.empty()){
        car = stack.back();
        stack.pop_back();

        x = node.cars[car].x;
        y = node.cars[car].y;
        if (node.cars[car].vh == 'v'){
          if (x - 1 > 0 and node.map.cell[x-1][y] != 0 and node.map.cell[x-1][y] != 1)
            if (find(blocked.begin(), blocked.end(), node.map.cell[x-1][y]) == blocked.end()){
              // it wasnt in blocked list
              stack.push_back(node.map.cell[x-1][y]);
              blocked.push_back(node.map.cell[x-1][y]);
            }
          if (x + node.cars[car].len < 7 and node.map.cell[x + node.cars[car].len][y] != 0 and node.map.cell[x + node.cars[car].len][y] != 1)
            if (find(blocked.begin(), blocked.end(), node.map.cell[x + node.cars[car].len][y]) == blocked.end()){
              // it wasnt in blocked list
              stack.push_back(node.map.cell[x + node.cars[car].len][y]);
              blocked.push_back(node.map.cell[x + node.cars[car].len][y]);
            }
        }
        else if (node.cars[car].vh == 'h'){
          if (y - 1 > 0 and node.map.cell[x][y - 1] != 0 and node.map.cell[x][y - 1] != 1)
            if (find(blocked.begin(), blocked.end(), node.map.cell[x][y - 1]) == blocked.end()){
              // it wasnt in blocked list
              stack.push_back(node.map.cell[x][y -1]);
              blocked.push_back(node.map.cell[x][y -1]);
            }
          if (y + node.cars[car].len < 7 and node.map.cell[x][y + node.cars[car].len] != 0 and node.map.cell[x][y + node.cars[car].len] != 1)
            if (find(blocked.begin(), blocked.end(), node.map.cell[x][y + node.cars[car].len]) == blocked.end()){
              // it wasnt in blocked list
              stack.push_back(node.map.cell[x][y + node.cars[car].len]);
              blocked.push_back(node.map.cell[x][y + node.cars[car].len]);
            }
        }
      }

    }
  }
  return blocked.size() / 2;
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
	  Hval[newState.id] = heuristic(newState);
	  Gval[newState.id] = TRANSITION_COST + Gval[node.id] ;
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
	  Hval[newState.id] = heuristic(newState);
	  Gval[newState.id] = TRANSITION_COST + Gval[node.id] ;
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
	  Hval[newState.id] = heuristic(newState);
	  Gval[newState.id] = TRANSITION_COST + Gval[node.id] ;
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
	  Hval[newState.id] = heuristic(newState);
	  Gval[newState.id] = TRANSITION_COST + Gval[node.id] ;
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


multiset<pair<int , string>>sts;

State bfs ( State root ) {
  int minVal;
  int index;

  sts.insert(make_pair(0 , root.id ));
   //heuristic
  while ( sts.size () ) {

    pair<int , string> now = *sts.begin() ;
    sts.erase(sts.begin());
    minVal = Gval[now.Y] + Hval[now.Y] ;
    index = 0 ;
    vector < State > children ;

    children = successor ( nodes[now.Y] ) ;
    for ( int i = 0 ; i < children.size() ; i ++ ) {
      if ( !mark[children[i].id] ) {
      	mark[children[i].id] = true ;
      	par[children[i].id] = now.Y ;
        sts.insert(make_pair(Hval[children[i].id] +  Gval[children[i].id], children[i].id ) );
        if ( checkGoal ( children[i] ) )
      	  return children[i] ;
      }
    }
  }

}

int main () {

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
  auto start = high_resolution_clock::now();

  first = Hash ( first ) ;
  //cout << first.id << endl ;
  print(first.map);
  par[first.id] = "-1" ;
  Gval[first.id] = 0 ;

  //states[0] = first ;

  //stateSize ++ ;

	// int rt = heuristic(first);
	// cout << rt << " is the esential moves" << endl;
  // //sts.insert ( { heuristic(first) , first.id } ) ;
  goal = bfs ( first ) ;

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken by search: "
          << duration.count() << " microseconds" << endl;

  generateSolve ( goal ) ;
  printSoloution() ;

  cout << "depth of soloutions:"
          << soloutions.size() << " layers " << endl;

  cout << "number of nodes: "
          << nodes.size() << " nodes " << endl;

  cout << "number of visited nodes "
          << mark.size() << " nodes " << endl;

  cout << " all states are: "
          << sts.size() << "states" << endl;
  return 0 ;
}
