
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



struct Map {
  int cell[7][7];
};
struct Car {
  int x , y , len ;
  char vh ;
};

struct State {
  Map map;
  Car cars[40];
  int parent ;
};

State states[100000] ;
int stateSize ;
int N ;
vector < State > soloutions ;

// pair < pair < int , int > , pair < char , int > > car[20] ;

bool equal ( State x , State y ) {
  for ( int i = 1 ; i < 7 ; i ++ ) {
    for ( int j = 1 ; j < 7 ; j ++ ) {
      if ( x.map.cell[i][j] != y.map.cell[i][j] )
      return false ;
    }
  }
return true ;
}

bool NotReapitingState ( State child ) {
  for ( int i = 0 ; i < stateSize ; i ++ ) {
    if ( equal(child , states[i]) )
      return false ;
  }
  return true ;
}
bool checkGoal ( int x ) {
  for ( int i = states[x].cars[1].y + states[x].cars[1].len ; i < 7 ; i ++ ) {
    if (states[x].map.cell[states[x].cars[1].x][i] != 0)
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

vector <State> successor( int x ) {
  vector < State > childsState ;
  Map map = states[x].map ;
  for ( int i = 1  ; i <= N ; i ++ ) {
    Car car = states[x].cars[i] ;
    if ( car.vh == 'h' ) {
      //cout << endl;
      //print(map);
      for (int k = 1 ; k < 5 ; k ++) {
        if ( checkMove ( car , map , k , 0 ) and car.y-k > 0  ) {
            State newState = states[x] ;
            for ( int loc = car.y ; loc < car.y + car.len ; loc ++ ) {
              newState.map.cell[car.x][loc] = 0 ;
            }
            for ( int loc = car.y ; loc < car.y + car.len ; loc ++ ) {
              newState.map.cell[car.x][loc-k] = i ;
            }
            newState.cars[i].y = newState.cars[i].y - k ;
            newState.parent = x;
            if ( NotReapitingState ( newState ) )
            childsState.push_back ( newState ) ;
        }else break ;
      }
      //cout << endl;
      //print(map);
      for (int k = 1 ; k < 5 ; k ++) {
        if ( checkMove ( car , map , k , 1 )and car.y+car.len+k-1 < 7 ) {
            State newState = states[x] ;
            for ( int loc = car.y ; loc < car.y + car.len ; loc ++ ) {
              newState.map.cell[car.x][loc] = 0 ;
            }
            for ( int loc = car.y ; loc < car.y + car.len ; loc ++ ) {
              newState.map.cell[car.x][loc+k] = i ;
            }
            newState.cars[i].y = newState.cars[i].y + k ;
            newState.parent = x;
            if ( NotReapitingState ( newState ) )
            childsState.push_back ( newState ) ;
        }else break;
    }
  }
    else if ( car.vh == 'v' ) {
       for (int k = 1 ; k < 5 ; k ++) {

        if ( checkMove ( car , map , k , 1 ) and car.x - k > 0 ) {
            State newState = states[x] ;
            for ( int loc = car.x ; loc < car.x + car.len ; loc ++ ) {
              newState.map.cell[loc][car.y] = 0 ;
            }
            for ( int loc = car.x ; loc < car.x + car.len ; loc ++ ) {
              newState.map.cell[loc-k][car.y] = i ;
            }
            newState.cars[i].x = newState.cars[i].x - k ;
            newState.parent = x;
            if ( NotReapitingState ( newState ) )
            childsState.push_back ( newState ) ;
        }else break ;
      }
      for (int k = 1 ; k < 5 ; k ++) {
        if ( checkMove ( car , map , k , 0 ) and car.x+car.len+k-1 < 7 ) {
            State newState = states[x] ;
            for ( int loc = car.x ; loc < car.x + car.len ; loc ++ ) {
              newState.map.cell[loc][car.y] = 0 ;
            }
            for ( int loc = car.x ; loc < car.x + car.len ; loc ++ ) {
              newState.map.cell[loc+k][car.y] = i ;
            }
            newState.cars[i].x = newState.cars[i].x + k ;

            newState.parent = x;
            if ( NotReapitingState ( newState ) )
            childsState.push_back ( newState ) ;
        }else break ;
    }
  }
  }
  return childsState ;
}

void generateSolve ( int x ) {
  int cnt = x ;
  while ( states[cnt].parent != -1 ) {
    soloutions.push_back ( states[cnt] ) ;
    cnt = states[cnt].parent ;
  }
  soloutions.push_back ( states[cnt] ) ;
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
int main () {

  ios::sync_with_stdio(0);cin.tie(0) ;
  cin >> N ;
  for ( int i = 0 ; i < N ; i ++ ) {
    int n , x , y , len ;
    char vh ;
    cin >> n >> x >> y >> vh >> len ;
    states[0].cars[n].x = x ;
    states[0].cars[n].y = y ;
    states[0].cars[n].vh = vh ;
    states[0].cars[n].len = len ;
    if ( vh == 'v') {
    for ( int j = x ; j < x + len ; j ++ )
      states[0].map.cell[j][y] = n ;
    }
    if ( vh == 'h') {
    for ( int j = y ; j < y + len ; j ++ )
      states[0].map.cell[x][j] = n ;
    }
  }
  stateSize ++ ;
  states[0].parent = -1;

  //BFS
  int bfsConuter = 0;
  vector <State> childeren;

  while (true){ //bfs
    childeren = successor(bfsConuter);
    for (int i = 0; i < childeren.size(); i ++){
      states[stateSize] = childeren[i];
      if ( checkGoal ( stateSize ) ) {
        generateSolve( stateSize ) ;
        printSoloution() ;
        bfsConuter = -1;
        break;

      }
      stateSize++;
    }
    if (bfsConuter == -1) break;
    bfsConuter++;
  }

  
  return 0 ;
}
