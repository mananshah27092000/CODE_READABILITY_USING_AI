#include <bits/stdc++.h>
using namespace std;


void print_seperator(){
    cout<<endl;
    for(int i = 0;i<80;i++)cout<<"*";
    cout<<endl<<endl;
}

void compress_graph(vector<vector<int>> &graph){
    bool brk = false;
    int index = 0;
    for(auto i : graph){       
        for(auto j:i){
            if(j==-1)brk = true;
            if(brk)break;
        }
        index++;
        if(brk){
            graph.erase(graph.begin()+index,graph.end());
            break;
        }
    }
}
void print_graph(vector<vector<int>> graph){
    print_seperator();
    cout<<"The graph according to fun() and mapping: "    <<endl;
    int index = 0;
    // bool brk = false;
    
    for(auto i : graph){
        cout<<index<<" --> ";
        if(i.size()==0){
            cout<<"This varible is for temporary use such as for iterating loop";
        }
        for(auto j:i){
            cout<<j<<" ";
            // if(j==-1)brk = true;
            // if(brk)break;
        }
        cout<<endl;
        index++;
        // if(brk){
        //     graph.erase(graph.begin()+index,graph.end());
        //     break;
        // }
    }
    cout<<"Number of nodes in graph: "<<graph.size()<<endl;
    cout<<"-1 denotes the variable which is returned by fun()"<<endl;
}

// read only fun() method from given file
string read_file(string file_name){
    char ch;
    fstream fin(file_name, fstream::in);
    string s = "";  // to store fun() as string
    while (fin >> noskipws >> ch) {

        if(ch=='f'){
            if(fin >> noskipws >> ch && ch=='u' && fin >> noskipws >> ch && ch=='n'){

                int count = 0;
                int inc = 0;
                while(fin>>noskipws>>ch){
                    s+=ch;
                    if(count==0 && ch=='{')inc = 1;
                    if(ch=='{')count++;
                    if(ch=='}')count--;
                    if(count==0 && inc==1)break;
                }
            }
            
        }
    }
    return s;
}

// check whether the string is a data type or not
bool is_datatype(string current){
    if(current == "double" || current == "int" || current == " float" || current == "string" || current == "char")
        return true;
    return false;
}

// removes extra charachters from varibles
string modify(string s){
    if(s==";")return s;
    string ans = "";
    for(char i : s){
        if(i=='[' || i==';' || i==',' || i==')')break;
        ans+=i;
    }
    return ans;
}

// get next word (it also truncates the spaces and newline characters)
string get_word(vector<char> arr,int &i){
    string current = "";
    while(i<arr.size() && (arr[i] != ' ' && arr[i]!='\n')){
        current.push_back(arr[i]);
        i++;
    }
    while((arr[i] == ' ' || arr[i]=='\n'))i++;

    return modify(current);
}

// returns the word after newline character 
string get_first_word(vector<char> arr, int &i){
    while(i>=0 && arr[i]!='\n')i--;

    while(arr[i]=='\n' || arr[i]== ' ')i++;

    return get_word(arr,i);
}

void remove_node(vector<vector<int>> &cand_graph, int node){
    vector<int> next_nodes(cand_graph[node].begin(),cand_graph[node].end());

    for(int i = 0; i<node ;i++){
        bool there = false;
        for(int j = 0;j<cand_graph[i].size();j++){
            if(cand_graph[i][j]==node){
                there = true;
                cand_graph[i].erase(cand_graph[i].begin()+j);
                j--;
            }else if(cand_graph[i][j]>node){
                cand_graph[i][j]--;
            }
        }
        if(there){
            for(auto add : next_nodes){
                cand_graph[i].push_back(add-1);
            }
        }
    }
    cand_graph.erase(cand_graph.begin() + node);
    compress_graph(cand_graph);
}

bool compare_graph(vector<vector<int>> setter_graph, vector<vector<int>> cand_graph){
    // cout<<"m0"<<endl;
    // cout<<setter_graph.size()<<" "<<cand_graph.size()<<endl;
    if(setter_graph.size()!=cand_graph.size())return false;
    // cout<<"m1"<<endl;

    for(int i = 0;i < setter_graph.size();i++)
        if(setter_graph[i].size()!=cand_graph[i].size())return false;
    // cout<<"m2"<<endl;
    for(int i =0;i<setter_graph.size();i++){
        for(int j = 0; j<setter_graph[i].size();j++){
            if(setter_graph[i][j]!=cand_graph[i][j])return false;
        }
    }
    return true;
}

bool is_graph_match(vector<vector<int>> setter_graph, vector<vector<int>> cand_graph,vector<int> values){
    for(int i = values.size()-1;i>=0;i--){
        if(!values[i]){
            remove_node(cand_graph,i);
        }
    }
    // print_graph(setter_graph);
    // print_graph(cand_graph);
    // cout<<"yes"<<endl;
    bool cmp =  compare_graph(setter_graph,cand_graph);
    return cmp;
}


