
void add_edge(std::vector<int8_t> adj[], int src, int dest) //changed
{
    adj[src].push_back(dest);
    adj[dest].push_back(src);
}

void readThisNode(std::vector<int8_t> adj[], int currentNode){ //changed
  char result; //changed
  bool wallFront;
  bool wallRight;
  bool wallLeft;
  //Serial IO
  Serial.println("wallFront");
  while(1){
    if(Serial.available() > 0){
      result = Serial.read();
      break;
    }
  }
  // cout << "wallFront" << endl; //changed inputOutput
  // cin >> result;
  if(result == 't'){
    wallFront = 1;
  } else if(result == 'f') {
    wallFront = 0;
  }

  //Serial IO
  Serial.println("wallRight");
  while(1){
    if(Serial.available() > 0){
      result = Serial.read();
      break;
    }
  }

  // cout << "wallRight" << endl; //changed inputOutput
  // cin >> result;
  if(result == 't'){
    wallRight = 1;
  } else if(result == 'f') {
    wallRight = 0;
  }
  //Serial IO
  Serial.println("wallLeft");
  while(1){
    if(Serial.available() > 0){
      result = Serial.read();
      break;
    }
  }
  // cout << "wallLeft" << endl; //changed inputOutput
  // cin >> result;
  if(result == 't'){
    wallLeft = 1;
  } else if(result == 'f') {
    wallLeft = 0;
  }


  if(!wallLeft){
    if(facing == 'N'){
      if(Map[posx - 1][posy] == -1){ // the new node is empty
        Map[posx - 1][posy] = nextNode;
        add_edge(adj, currentNode, nextNode++);
      } else { //the new node is full
        add_edge(adj, currentNode, Map[posx - 1][posy]);
      }

    } else if (facing == 'E'){
      if(Map[posx][posy + 1] == -1){
        Map[posx][posy + 1] = nextNode;
        add_edge(adj, currentNode, nextNode++);
      } else {
        add_edge(adj, currentNode, Map[posx][posy + 1]);
      }

    } else if (facing == 'S'){
      if(Map[posx + 1][posy] == -1){
        Map[posx + 1][posy] = nextNode;
        add_edge(adj, currentNode, nextNode++);
      } else {
        add_edge(adj, currentNode, Map[posx + 1][posy]);
        //cout << "setColor " << posx - 199 << " " << posy - 200 << " r" << endl;
        //here is the place
      }

    } else if (facing == 'W'){
      if(Map[posx][posy - 1] == -1){
        Map[posx][posy - 1] = nextNode;
        add_edge(adj, currentNode, nextNode++);
      } else {
        add_edge(adj, currentNode, Map[posx][posy - 1]);
      }
    }

  }
  if(!wallFront){
    if(facing == 'N'){
      if(Map[posx][posy + 1] == -1){
        Map[posx][posy + 1] = nextNode;
        add_edge(adj, currentNode, nextNode++);
      } else {
        add_edge(adj, currentNode, Map[posx][posy + 1]);
      }

    } else if (facing == 'E'){
      if(Map[posx + 1][posy] == -1){
        Map[posx + 1][posy] = nextNode;
        add_edge(adj, currentNode, nextNode++);
      } else {
        add_edge(adj, currentNode, Map[posx + 1][posy]);
      }

    } else if (facing == 'S'){
      if(Map[posx][posy - 1] == -1){
        Map[posx][posy - 1] = nextNode;
        add_edge(adj, currentNode, nextNode++);
      } else {
        add_edge(adj, currentNode, Map[posx][posy - 1]);
      }

    } else if (facing == 'W'){
      if(Map[posx - 1][posy] == -1){
        Map[posx - 1][posy] = nextNode;
        add_edge(adj, currentNode, nextNode++);
      } else {
        add_edge(adj, currentNode, Map[posx - 1][posy]);
      }
    }

  }
  if(!wallRight){
    if(facing == 'N' ){
      if(Map[posx + 1][posy] == -1){
        Map[posx + 1][posy] = nextNode;
        add_edge(adj, currentNode, nextNode++);
      } else {
        add_edge(adj, currentNode, Map[posx + 1][posy]);
      }

    } else if (facing == 'E'){
      if(Map[posx][posy - 1] == -1){
        Map[posx][posy - 1] = nextNode;
        add_edge(adj, currentNode, nextNode++);
      } else {
        add_edge(adj, currentNode, Map[posx][posy - 1]);
      }

    } else if (facing == 'S'){
      if(Map[posx - 1][posy] == -1){
        Map[posx - 1][posy] = nextNode;
        add_edge(adj, currentNode, nextNode++);
      } else {
        add_edge(adj, currentNode, Map[posx - 1][posy]);
      }

    } else if (facing == 'W'){
      if(Map[posx][posy + 1] == -1){
        Map[posx][posy + 1] = nextNode;
        add_edge(adj, currentNode, nextNode++);
      } else {
        add_edge(adj, currentNode, Map[posx][posy + 1]);
      }
    }
  }
}

bool BFS(std::vector<int8_t> adj[], int src, int dest, int v, int pred[], int dist[])//changed
{
    std::list<int8_t> queue;//changed
    bool visited[v] = {};

    for (int i = 0; i < v; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    //start with the src point
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);

    // standard BFS algorithm
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < adj[u].size(); i++) {
            if (visited[adj[u][i]] == false) {
                visited[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1;
                pred[adj[u][i]] = u;
                queue.push_back(adj[u][i]);
                if (adj[u][i] == dest)
                    return true;
            }
        }
    }

    return false;
}

int dirCharToValue(char c){
  if(c == 'N'){
    return 0;
  } else if(c == 'E'){
    return 1;
  } else if(c == 'S'){
    return 2;
  } else if(c == 'W'){
    return 3;
  }
  return 0; //changed
}
//update facing
void turnTo(char to){
  if(facing == to){
    return;
  }
  //N:0 E:1 S:2 W:3 positive turn is right, negative turn is left ( to minus  from )
  int turnAmount =  dirCharToValue(to) - dirCharToValue(facing);
  if(abs(turnAmount) == 3){
    turnAmount = turnAmount * -1 / 3;
  }
  if(turnAmount > 0){
    for(int i = 0; i < turnAmount; i++){
      //turnRight
      // string result;
      // cout << "turnRight" << endl; //changed inputOutput
      // cin >> result;
      //Serial IO
      Serial.println("turnRight");
    }
  } else if(turnAmount < 0){
    for(int i = 0; i < abs(turnAmount); i++){
      //turnLeft
      // string result;
      // cout << "turnLeft" << endl; //changed inputOutput
      // cin >> result;
      //Serial IO
      Serial.println("turnLeft");
    }
  }
  facing = to;
}
//start and end must be connected by only 1 step
void moveOneCord(int startPos, int endPos){
  if(startPos == endPos){
    return;
  }
  //start pos and endPos recorded the node's position
  char endPosFacing; //N, E, S, W absolute direction
  // if the endPos (node) is at the cord
  if(Map[posx][posy + 1] == endPos){
    endPosFacing = 'N';
    posy = posy + 1;
  }
  else if(Map[posx + 1][posy] == endPos){
    endPosFacing = 'E';
    posx = posx + 1;
  }
  else if(Map[posx][posy - 1] == endPos){
    endPosFacing = 'S';
    posy = posy - 1;
  }
  else if(Map[posx - 1][posy] == endPos){
    endPosFacing = 'W';
    posx = posx - 1;
  }

  turnTo(endPosFacing);
  // string result;
  // cout << "moveForward" << endl; //changed inputOutput
  // cin >> result;
  //Serial IO
  Serial.println("moveForward");
}

void moveToNode(std::vector<int8_t> adj[], int destination, int v, std::list<int8_t> st, bool t){ //changed 
  if(destination == currentNode){
    return;
  }
  int pred[v], dist[v];
  //BFS from currentNode to dest
  if (BFS(adj, currentNode, destination, v, pred, dist) == false) {
      // cout << "Given source and destination" //changed
      //      << " are not connected";
      return;
  }

  // vector path stores the shortest path
  std::vector<int8_t> path; //changed
  int crawl = destination;
  path.push_back(crawl);
  while (pred[crawl] != -1) {
      path.push_back(pred[crawl]);
      crawl = pred[crawl];
  }

  //each path next to each other must be conncted
  for (int i = path.size() - 1; i >= 0; i--){
    moveOneCord(currentNode, path[i]);
    currentNode = path[i];

    if(std::find(st.begin(),st.end(), currentNode) != st.end() && !t){
      readThisNode(adj, currentNode); //dangerous
      moveToNode(adj,destination,v,st,true); //if it is the second lit, use true //read second time problem here
      return;
    }
  }
}

void DFS(std::vector<int8_t> adj[], int src, int v){ //changed
  std::list<int8_t> stack;
  bool visited[v] = {};

  for (int i = 0; i < v; i++) {
      visited[i] = false;
  }

  //start with the src point  or starting point for the robot
  visited[src] = true;
  stack.push_back(src);
  while(!stack.empty()){
    int now = stack.back(); //now is actually what the robot will move to
    moveToNode(adj,now,v,stack, false);// check if we are on the now, if then, dont move
    stack.pop_back();
    readThisNode(adj, now); //read and add nodes to the current node //non panic
    for(int i = 0; i < adj[now].size();i++){
      //adj[now][i] is the next node  place the priortised direction at the last adj[now][i]
      if(visited[adj[now][i]] == false){
        visited[adj[now][i]] = true;
        stack.push_back(adj[now][i]);
      }
    }
  }
  moveToNode(adj,0,v,stack, false);
  //changed
}

void mainLoop() //changed
{
    /// number of vertices ( no de )
    int v = 500;
    std::vector<int8_t> adj[v]; //changed
    // 200, 200 is the starting node ( node 0 );
    for(int i = 0 ; i < 200; i++){
      for(int j = 0; j < 200; j++){
        Map[i][j] = -1; //-1 means the cord has no node
      }
    }
    //read node 0; // 200, 200 is the starting node ( node 0 );
    Map[100][100] = 0;
    DFS(adj, 0, v);
}


