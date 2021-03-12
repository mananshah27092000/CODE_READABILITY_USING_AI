#include "./create_graph.cpp"

int main(int argc, char** argv){
   
    string type = (argc>1) ? argv[1] : "results";
    string setter = (argc>2)? argv[2] : "setter.cpp";
    
    if(type == "nodes"){
        
        string cand = "candidate/";
        cand += ((argc>3)? argv[3] : "candidate1.cpp"); 
        
        string setter_file = read_file(setter);
        string cand_file = read_file(cand);
        
        int sz = 10; // number of max nodes in graph
        vector<vector<int>> setter_graph(sz,vector<int> ()), cand_graph(sz, vector<int> ());
        cout<<endl<<"Setter code details";
        create_graph(setter_graph,setter_file);
        
        print_seperator();
        
        cout<<"Candidate code details";
        create_graph(cand_graph,cand_file);

        run_all_search(setter_graph,cand_graph);

    }else{

        string temp = argv[3];
        int total = ((argc>3)? (int)(temp[0]-'0') : 2);
        
        string setter_file = read_file(setter);

        vector<pair<int,int>> results;
        for(int i = 1 ;i<=total;i++){

            string tt(1,i+'0');
            string cand = "candidate/candidate" + tt + ".cpp";
            string cand_file = read_file(cand);

            int sz = 10;
            vector<vector<int>> setter_graph(sz,vector<int> ()), cand_graph(sz, vector<int> ());
            
            create_graph(setter_graph,setter_file,0);
            create_graph(cand_graph,cand_file,0);

            int cnt_exp = 0;
            vector<int> ans = ordering(setter_graph,cand_graph, cnt_exp);
            results.push_back({solution_cost(cand_graph,ans),i});

        }
        sort(results.begin(),results.end());

        print_seperator();
        cout<<"The transformation cost of candidate solutions(increasing order) with setter solution is:\n";
        cout<<endl;
        cout<<" Candidate   Cost"<<endl;
        for(auto itr:results){
            cout<<"    "<<itr.second<<"          "<<itr.first<<endl;
        }
        print_seperator();
    }
    return 0;

}