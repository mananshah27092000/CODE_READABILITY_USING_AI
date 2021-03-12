#include "search.cpp"

map<string,int> graph_map;
int cnt = 0;

void get_fun_params(vector<char> arr, int &i){
    while(arr[i]!='(')i++;
    i++;

    while(arr[i]!=')'){
        string type = get_word(arr,i);
        // cout<<type<<endl;
        string param = get_word(arr,i);
        // cout<<param<<endl;
        graph_map[param] = cnt++;       
        if(arr[i]==',') i+=2;
    }

}

// arr stores the whole code file in 1D vector
// graph is the graph between dependent variables
void getdependency(vector<char> arr, vector<vector<int>> &graph){
    int n = arr.size();
    int i = 0;

    string current = "";

    get_fun_params(arr,i);
    
    while(i<n){
        
        
        current = get_word(arr,i);

        if(is_datatype(current)){
                current = get_word(arr,i);   //considering only declaration as int a ;
                graph_map[current] = cnt++;
                // cout<< current<<endl;
        }
        
        // If there is assignment then there are only 2 cases, they are
        // int a ;  // space in declaration
        // a = b + c ; // any operation will only consider 2 operands with the shown spaces
        
        if(current == "="){
            string first = get_first_word(arr,i);
            // cout<<"difj"<<endl;
            // cout<<first<<endl;
            // considering operation as a = b + c ;
            int child = graph_map[first];
            // cout<<child<<endl;
            current = get_word(arr,i);  //removing '='
            // cout<<current<<endl;
            current = get_word(arr,i);
            // cout<<current<<endl;

            int parent1 = -1;
            if(graph_map.find(current) != graph_map.end()){
                parent1= graph_map[current];
                graph[parent1].push_back(child);
            }
            // cout<<parent1<<endl;
            // cout<<current<<"sdf"<<endl;    
            current = get_word(arr,i); //removing operator
            // cout<<current<<endl;
            
            if(current != ";"){

                current = get_word(arr,i);
                // cout<<current<<endl;

                int parent2 = -1;
                if(graph_map.find(current) != graph_map.end()){
                    parent2= graph_map[current];
                    graph[parent2].push_back(child);
                }
                // cout<<parent2<<endl;    
            }
        }    
    }

    for(int i = 0;i<graph.size();i++){
        
        for(int j = 0;j<graph[i].size();j++){
            if(graph[i][j] == i){
                graph[i].erase(graph[i].begin()+j);
                j--;
            }
        }
    }
}

// to mark which variable is returned
void mark_end(vector<char> arr, vector<vector<int>> &graph){
    string s;
    int i =0;
    int n = arr.size();
    while(i<n){
        s = get_word(arr,i);
        if(s=="return"){
            s = get_word(arr,i);
            graph[graph_map[s]].push_back(-1);
        }
    }
}

// Print the mapping for given code
void print_map(){
    print_seperator();
    cout<<"Variable to value mapping:"<<endl;
    for(auto i = graph_map.begin();i!= graph_map.end(); i++){
        cout<<i->second<<" = "<<i->first<<endl; 
    }
}

// Prints the graph


void create_graph(vector<vector<int>> &graph,string file, int aa = 1){
    cnt = 0;
    graph_map.clear();

    if(aa){
        print_seperator();
        cout<<"The fun() code:"<<endl<<"fun";
        cout<<file<<endl;
    }
    vector<char> a(file.begin(),file.end());

    getdependency(a,graph);
    
    mark_end(a,graph);
    
    
    compress_graph(graph);
    if(aa){
        print_map();
        print_graph(graph);
    }
}

