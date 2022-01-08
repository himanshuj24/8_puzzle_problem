#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <chrono>

using namespace std;
using namespace std::chrono;

void DFS();
void DLS();
void IDS();
void rebuild_path();
int wrongtile();
int manhattan();
void A_star_wrongtile(string startstate, string goalstate);
void A_star_manhattan(string startstate, string goalstate);

class node
{
  public:
  string state;
  string action_string;
  string parent;
  int path_cost;
    
  string child_node(string state_temp, string action_string)
  {
      //Action for right
      if(action_string=="right")
      {
        int null_pos;
        for(int i=0;i<9;i++)
        {
            if(state_temp.substr(i,1)=="0")
                {
                    null_pos=i;
                    break;
                }
        }
//        cout<<null_pos<<endl;
        if (null_pos!=0&&null_pos!=3&&null_pos!=6)
        {
            int temp=state_temp.at(null_pos-1);
            state_temp.at(null_pos-1)=state_temp.at(null_pos);
            state_temp.at(null_pos)=temp;
            return state_temp;
        }
        else 
            {
                //cout<<"Operation not possible";
                return "no";
            }
       }
        
       //Action for left
      if(action_string=="left")
      {
        int null_pos;
        for(int i=0;i<9;i++)
        {
            if(state_temp.substr(i,1)=="0")
                {
                    null_pos=i;
                    break;
                }
        }
        if (null_pos!=2&&null_pos!=5&&null_pos!=8)
        {
            int temp=state_temp.at(null_pos+1);
            state_temp.at(null_pos+1)=state_temp.at(null_pos);
            state_temp.at(null_pos)=temp;
            return state_temp;
        }
        else 
            {
                //cout<<"Operation not possible";
                return "no";
            }
      }
      //Action for up
      if(action_string=="up")
      {
        int null_pos;
        for(int i=0;i<9;i++)
        {
            if(state_temp.substr(i,1)=="0")
                {
                    null_pos=i;
                    break;
                }
        }
        if (null_pos!=6&&null_pos!=7&&null_pos!=8)
        {
            int temp=state_temp.at(null_pos+3);
            state_temp.at(null_pos+3)=state_temp.at(null_pos);
            state_temp.at(null_pos)=temp;
            return state_temp;
        }
        else 
            {
                //cout<<"Operation not possible";
                return "no";
            }
       }
       
      //Action for down
      if(action_string=="down")
      {
        int null_pos;
        for(int i=0;i<9;i++)
        {
            if(state_temp.substr(i,1)=="0")
                {
                    null_pos=i;
                    break;
                }
        }
        
        if (null_pos!=0&&null_pos!=1&&null_pos!=2)
        {
            int temp=state_temp.at(null_pos-3);
            state_temp.at(null_pos-3)=state_temp.at(null_pos);
            state_temp.at(null_pos)=temp;
        return state_temp;
        }
        else 
            {
                //cout<<"Operation not possible";
                return "no";
            }
       }
 
    return "ignore";
 }
  
};

void visualise(string state);                   //Visualise function will take input of state as a string, and output will be a 3*3 matrix

string input_state;                             //User will give input state using command line
string goal_state="123804765";                  //As defined in the problem statement

float time_DLS;
float time_IDS;
float time_A_wrongtile;
float time_A_manhattan;

int main()
{
  cout<<"Enter the input state: "<<endl;
  getline(cin,input_state);
  cout<<"Input State Is: "<<input_state<<endl;
  cout<<"Goal State Is: "<<goal_state<<endl;
  node root;
  root.state=input_state;
  visualise(root.state);
  //DFS();
//   cout<<"--------------------Depth Limited Search--------------------"<<endl;
//   DLS();
//   IDS();
  cout<<"--------------------A* with Wrong Tiles--------------------"<<endl;
  A_star_wrongtile(input_state,goal_state);
  cout<<"--------------------A* with Manhattan--------------------"<<endl;
  A_star_manhattan(input_state,goal_state);
  
//  cout<<"Time of execution for Depth Limited Search is : "<<(time_DLS)/1000<<" milliseconds. "<<endl;
//  cout<<"Time of execution for Iterative Deepening Search is : "<<(time_IDS)/1000<<" milliseconds. "<<endl;
  cout<<"Time of execution for A* search with wrong tile is : "<<(time_A_wrongtile)/1000<<" milliseconds. "<<endl;
  cout<<"Time of execution for A* search with manhattan distance is : "<<(time_A_manhattan)/1000<<" milliseconds. "<<endl;
  
  return 0;
}

void visualise(string state)
{
    cout<<"***************************************"<<endl;
    for(int i=0;i<9;i++)
    {
        cout<<"|"<<state.substr(i,1)<<"|"<<state.substr(i+1,1)<<"|"<<state.substr(i+2,1)<<"|"<<endl;
        i=i+2;
    }
}

void DFS()
{
    stack<node> frontier;
    node root;
    root.state=input_state;
    root.parent= "";
    root.action_string= "";
    root.path_cost=1;
    stack<string> direction;
    node current_node;
    
    string action[4]={"left","right","up","down"};
    
    frontier.push(root);
    int flag=-1;
    
    while (frontier.size()>0&&flag==-1)
    {
        current_node=frontier.top();
        frontier.pop(); 
        direction.push(current_node.action_string);
        if (current_node.state==goal_state)
        {
            flag=1;
            break;
        }
        for(int i=0;i<4;i++)
        {
            string child_state= current_node.child_node(current_node.state,action[i]);
            if(child_state!="no")
            {
                node child_node;
                child_node.state=child_state;
                current_node.action_string=action[i];
                child_node.parent=current_node.state;
                frontier.push(child_node);
            }
        }
    }
    if (flag==1)
    {
        while(direction.size()>0)
            {
                cout<<direction.top()<<endl;
                direction.pop();
            }
    }
}

void DLS()
{
    auto start=high_resolution_clock::now();
//    cout<<"--------------------Depth Limited Search--------------------"<<endl;
    int depth, depth_counter;
    cout<<"Enter the depth till which you want to search."<<endl;
    cin>>depth;
    stack<node> frontier;
    node root;
    root.state=input_state;
    root.parent= "";
    root.action_string= "";
    root.path_cost=1;
    stack<string> direction;
    stack<int> direction_depth;
    node current_node;
    
    string action[4]={"left","right","up","down"};
    
    frontier.push(root);
    int flag=-1;
    int step_counter=0;
        
    while (frontier.size()>0&&(flag==-1||flag==0))
    {
        current_node=frontier.top();
        frontier.pop(); 
        if (direction.size()>0)
        {
            while (true)
            {
                if(direction_depth.top()>=depth_counter)
                {
                    direction.pop();
                    direction_depth.pop();
                }  
                else
                    break;
            }
        }
        direction.push(current_node.action_string);
        direction_depth.push(depth_counter);
        if (current_node.state==goal_state)
        {
            flag=1;
            visualise(current_node.state);
            cout<<"REACHED GOAL STATE!"<<endl;
            break;
        }
        else 
        {
            if (depth_counter>depth)
            flag=0;
            else
            {   
                int temp_for_action;
               for(int i=0;i<4;i++)
                {
                    string child_state= current_node.child_node(current_node.state,action[i]);
                    if(child_state!="no")
                        {
                            node child_node;
                            child_node.state=child_state;
                            current_node.action_string=action[i];
                            child_node.parent=current_node.state;
                            frontier.push(child_node);
                            depth_counter=depth_counter+1;
                            temp_for_action=i;
                        }
                } 
                visualise(current_node.state);
            }
        }                
    }
    if (flag==1)
    {
        while(direction.size()>0)
            {
                cout<<direction.top()<<endl;
                direction.pop();
            }
            
    }
    auto stop=high_resolution_clock::now();
    auto duration= duration_cast<microseconds>(stop - start);
    time_DLS=duration.count();
    
}

void IDS()
{
    auto start=high_resolution_clock::now();
    int depth, depth_counter;
    cout<<"Enter the depth till which you want to search."<<endl;
    cin>>depth;
    stack<node> frontier;
    node root;
    root.state=input_state;
    root.parent= "";
    root.action_string= "";
    root.path_cost=1;
    stack<string> direction;
    stack<int> direction_depth;
    node current_node;
    
    string action[4]={"left","right","up","down"};
    
    frontier.push(root);
    int flag=-1;
    int step_counter=0;
        
    while (frontier.size()>0&&(flag==-1||flag==0))
    {
        current_node=frontier.top();
        frontier.pop(); 
        if (direction.size()>0)
        {
            while (true)
            {
                if(direction_depth.top()>=depth_counter)
                {
                    direction.pop();
                    direction_depth.pop();
                }  
                else
                    break;
            }
        }
        direction.push(current_node.action_string);
        direction_depth.push(depth_counter);
        if (current_node.state==goal_state)
        {
            flag=1;
            visualise(current_node.state);
            cout<<"REACHED GOAL STATE!"<<endl;
            break;
        }
        else 
        {
            if (depth_counter>depth)
            flag=0;
            else
            {   
                int temp_for_action;
               for(int i=0;i<4;i++)
                {
                    string child_state= current_node.child_node(current_node.state,action[i]);
                    if(child_state!="no")
                        {
                            node child_node;
                            child_node.state=child_state;
                            current_node.action_string=action[i];
                            child_node.parent=current_node.state;
                            frontier.push(child_node);
                            depth_counter=depth_counter+1;
                            temp_for_action=i;
                        }
                } 
                visualise(current_node.state);
            }
        }                
    }
    if (flag==1)
    {
        while(direction.size()>0)
            {
                cout<<direction.top()<<endl;
                direction.pop();
            }
    }
    auto stop=high_resolution_clock::now();
    auto duration= duration_cast<microseconds>(stop - start);
    time_IDS=duration.count();
}

int wrongtile(string parent_state, string child_state)
{
    int wrong_tile=0;
    for(int i=0;i<9;i++)
    {
        if(child_state[i]!=parent_state[i])
            wrong_tile=wrong_tile+1;
    }
    return wrong_tile;
}

int manhattan(string parent_state, string child_state)
{
    int manhattan_dist=0;
    for (int i=0;i<9;i++)
    {
        for (int j=0; j<9;j++)
        {
            if (parent_state[i]==child_state[j])
            {
                manhattan_dist=manhattan_dist+abs(i-j);
            }
        }
    }
    return manhattan_dist;
}

struct Prior_Node{
int priority;
node state;
};

struct Direction_Node{
string child;
string action;
};

struct CompareNode {
    bool operator()(Prior_Node const& p1, Prior_Node const& p2)
    {
        // return "true" if "p1" is ordered
        // before "p2", for example:
        return p1.priority > p2.priority;
    }
};

void A_star_wrongtile(string startstate, string goalstate)
{
    auto start=high_resolution_clock::now();
 priority_queue<Prior_Node, vector<Prior_Node>, CompareNode> frontier;
    Prior_Node priority_root = Prior_Node();
    node root;
    root.state=startstate;
    root.parent= "";
    root.action_string= "";
    root.path_cost=0;
    
    priority_root.priority = wrongtile(startstate, goalstate);
    priority_root.state = root;
    frontier.push(priority_root);
    set<string> visited;
    map<string, int> fScore;
    map<string, string> directions;
    fScore.insert(pair<string,int>(startstate,wrongtile(startstate, goalstate)));
    directions.insert(pair<string,string>(startstate,""));
    int flag=0;
    while( frontier.size()>0&&flag==0)
    {
        Prior_Node current_node = frontier.top();
        frontier.pop();
        if(current_node.state.state==goalstate)
        {
            flag=1;
            string current;
            current = current_node.state.state;
            while(current != "")
            {             
                visualise(current);
                cout<<"\n";
                current = directions.at(current);
            }
            cout<<endl;
            cout<<"Reached goal state!"<<endl;
            break;
        }
        else
        {
            string action[4]={"left","right","up","down"};
            for (int i=0; i<4;i++)
            {
                string child_state= current_node.state.child_node(current_node.state.state,action[i]);
                if(child_state!="no" && !(visited.find(child_state) != visited.end()))
                    {
                        int child_heuristic_1 = current_node.state.path_cost + 1;
                        int child_heuristic_2 = wrongtile(child_state, goalstate);
                        node child_node;
                        child_node.state=child_state;
                        child_node.parent= current_node.state.state;
                        child_node.action_string= action[i];
                        child_node.path_cost=child_heuristic_1;
                        fScore.insert(pair<string,int>(child_state,child_heuristic_1 + child_heuristic_2));
                        Prior_Node new_priority_node = Prior_Node();
                        new_priority_node.priority = child_heuristic_1 + child_heuristic_2;
                        new_priority_node.state = child_node;
                        directions.insert(pair<string,string>(child_node.state,current_node.state.state));
                        frontier.push(new_priority_node);
                    }
            }
        }
        
    }
    auto stop=high_resolution_clock::now();
    auto duration= duration_cast<microseconds>(stop - start);
    time_A_wrongtile=duration.count();
}

void A_star_manhattan(string startstate, string goalstate)
{
    auto start=high_resolution_clock::now();
    priority_queue<Prior_Node, vector<Prior_Node>, CompareNode> frontier;
    Prior_Node priority_root = Prior_Node();
    node root;
    root.state=startstate;
    root.parent= "";
    root.action_string= "";
    root.path_cost=0;
    
    priority_root.priority = manhattan(startstate, goalstate);
    priority_root.state = root;
    frontier.push(priority_root);
    set<string> visited;
    map<string, int> fScore;
    map<string, string> directions;
    fScore.insert(pair<string,int>(startstate,manhattan(startstate, goalstate)));
    directions.insert(pair<string,string>(startstate,""));
    int flag=0;
    while( frontier.size()>0&&flag==0)
    {
        Prior_Node current_node = frontier.top();
        frontier.pop();
        if(current_node.state.state==goalstate)
        {
            flag=1;
            string current;
            current = current_node.state.state;
            while(current != "")
            {
                visualise(current);
                cout<<"\n";
                current = directions.at(current);
            }
            cout<<endl;
            cout<<"Reached goal state!"<<endl;
            break;
        }
        else
        {
            string action[4]={"left","right","up","down"};
            for (int i=0; i<4;i++)
            {
                string child_state= current_node.state.child_node(current_node.state.state,action[i]);
                if(child_state!="no" && !(visited.find(child_state) != visited.end()))
                    {
                        int child_heuristic_1 = current_node.state.path_cost + 1;
                        int child_heuristic_2 = manhattan(child_state, goalstate);
                        node child_node;
                        child_node.state=child_state;
                        child_node.parent= current_node.state.state;
                        child_node.action_string= action[i];
                        child_node.path_cost=child_heuristic_1;
                        fScore.insert(pair<string,int>(child_state,child_heuristic_1 + child_heuristic_2));
                        Prior_Node new_priority_node = Prior_Node();
                        new_priority_node.priority = child_heuristic_1 + child_heuristic_2;
                        new_priority_node.state = child_node;
                        directions.insert(pair<string,string>(child_node.state,current_node.state.state));
                        frontier.push(new_priority_node);
                    }
            }
        }
        
    }
    auto stop=high_resolution_clock::now();
    auto duration= duration_cast<microseconds>(stop - start);
    time_A_manhattan=duration.count();
}