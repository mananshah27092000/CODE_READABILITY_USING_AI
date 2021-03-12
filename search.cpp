#include "utilities.cpp"

int solution_cost(vector<vector<int>> cand_graph, vector<int> ans){
    int n = cand_graph.size();
    vector<int> depth(n,-1);
    int max_depth = 0;

    for(int i = 0;i<cand_graph.size();i++){
        if(depth[i]==-1)depth[i] = 0;
        for(int j = 0;j<cand_graph[i].size();j++){
            if(depth[cand_graph[i][j]]==-1){
                depth[cand_graph[i][j]] = depth[i] + 1;
            }
        }
    }
    for(int i: depth)max_depth = max(max_depth,i);

    // cout<<"Depth ";
    // for(int i: depth)cout<<i<<" ";
    // cout<<endl;

    int cost = 0;
    for(int i = 0; i<ans.size();i++){
        cost += (ans[i] ? 0 : max_depth - depth[i]);        
    }
    return cost;
}

int next_expected_value(vector<vector<int>> &setter_graph, vector<vector<int>> &cand_graph,
            int &c, int &r){
    if(r>=cand_graph.size())return 1;
    if(c>=setter_graph.size())return 0;

    if(setter_graph[r].size()==0){
        r++;
        return 0;
    }
    int there_setter = 0;
    for(int i: setter_graph[c])if(i==-1) there_setter = 1;

    int there_cand = 0;
    for(int i: cand_graph[r])if(i==-1) there_cand = 1;

    if((setter_graph[c].size() - there_setter) == (cand_graph[r].size()-there_cand)){
        c++;
        r++;

        return 1;
    }else{
        r++;

    }
    return 0;
}
int push_alter(int a){
    if(a==1)return 0;
    else return 1;
}

vector<int> ordering(vector<vector<int>> &setter_graph, vector<vector<int>> &cand_graph
                , int &cnt){
    int n = cand_graph.size();
    stack<vector<int>> st;
    int current_setter_node = 0;
    int current_cand_node = 0;
    
    int c = next_expected_value(setter_graph,cand_graph,current_setter_node,current_cand_node);
    st.push({push_alter(c)});
    st.push({c});

    while(!st.empty()){
        vector<int> last = st.top();
        st.pop();
        cnt++;

        // constrain violation check
        int cnt0 = 0, cnt1 = 0;
        int r = setter_graph.size();
        for(int i : last)if(i==0)cnt0++;
        for(int i : last)if(i==1)cnt1++;
        
        if(last.size()==n){
            if(is_graph_match(setter_graph,cand_graph,last))return last;
        }else if(! (n-cnt0<r || cnt1>r)){
            c = next_expected_value(setter_graph,cand_graph,current_setter_node,current_cand_node);
            last.push_back(push_alter(c));
            st.push(last);
            last.pop_back();
            last.push_back(c);
            st.push(last);
            last.pop_back();
        }
    }
}


vector<int> backtrack(vector<vector<int>> &setter_graph, vector<vector<int>> &cand_graph
                , int &cnt){
    int n = cand_graph.size();
    stack<vector<int>> st;
    
    st.push({0});
    st.push({1});
    while(!st.empty()){
        vector<int> last = st.top();
        st.pop();
        cnt++;

        // constrain violation check
        int cnt0 = 0, cnt1 = 0;
        int r = setter_graph.size();
        for(int i : last)if(i==0)cnt0++;
        for(int i : last)if(i==1)cnt1++;
        
        if(last.size()==n){
            if(is_graph_match(setter_graph,cand_graph,last))return last;
        }else if(! (n-cnt0<r || cnt1>r)){
            last.push_back(1);
            st.push(last);
            last.pop_back();
            last.push_back(0);
            st.push(last);
            last.pop_back();
        }
    }
}

vector<int> dfs(vector<vector<int>> &setter_graph, vector<vector<int>> &cand_graph
                , int &cnt){
    int n = cand_graph.size();
    stack<vector<int>> st;
    
    st.push({0});
    st.push({1});
    while(!st.empty()){
        vector<int> last = st.top();
        st.pop();
        cnt++;

        if(last.size()==n){
            if(is_graph_match(setter_graph,cand_graph,last))return last;
        }else{
            last.push_back(1);
            st.push(last);
            last.pop_back();
            last.push_back(0);
            st.push(last);
            last.pop_back();
        }
    }
}

vector<int> bfs(vector<vector<int>> &setter_graph, vector<vector<int>> &cand_graph
                , int &cnt){
    
    int n = cand_graph.size();
    queue<vector<int>> que;
    
    que.push({0});
    que.push({1});
    while(!que.empty()){
        vector<int> last = que.front();
        que.pop();
        cnt++;

        if(last.size()==n){
            if(is_graph_match(setter_graph,cand_graph,last))return last;
        }else{
            last.push_back(0);
            que.push(last);
            last.pop_back();
            last.push_back(1);
            que.push(last);
            last.pop_back();
        }
    }

}


void run_all_search(vector<vector<int>> setter_graph, vector<vector<int>> cand_graph){
    
    int cnt_exp = 0;
    auto ans = bfs(setter_graph,cand_graph, cnt_exp);    
    print_seperator();
    cout<<"  Number of node expanded in BFS search: "<<cnt_exp<<endl;
    cout<<"  Candidate solution goodness: "<<solution_cost(cand_graph,ans)<<endl;

    cnt_exp = 0;
    ans = dfs(setter_graph,cand_graph, cnt_exp);
    print_seperator();
    cout<<"  Number of node expanded in DFS search: "<<cnt_exp<<endl;
    cout<<"  Candidate solution goodness: "<<solution_cost(cand_graph,ans)<<endl;

    cnt_exp = 0;
    ans = backtrack(setter_graph,cand_graph, cnt_exp);
    print_seperator();
    cout<<"  Number of node expanded in Nodetrack: "<<cnt_exp<<endl;
    cout<<"  Candidate solution goodness: "<<solution_cost(cand_graph,ans)<<endl;

    cnt_exp = 0;
    ans = ordering(setter_graph,cand_graph, cnt_exp);
    print_seperator();
    cout<<"  Number of node expanded in Valorder:"<<cnt_exp<<endl;
    cout<<"  Candidate solution goodness: "<<solution_cost(cand_graph,ans)<<endl;


    print_seperator();

    

}