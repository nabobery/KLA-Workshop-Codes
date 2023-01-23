#include <bits/stdc++.h>
using namespace std;

ifstream in("../Milestone_input/Milestone 1/Format_Source.txt");
ofstream out("./output.txt");

class Solution{
    public:
        vector<string> header;
        vector<string> footer;
        vector<vector<string>> polygons;
    void Reader(){
        string line;
        while(getline(in,line) && line != "boundary"){ 
            header.push_back(line);
        }
        vector<string> temp;
        temp.push_back(line);
        while (getline(in,line) && line != "endstr")
        {
            temp.push_back(line);
            while (getline(in,line) && line != "endel")
            {
                temp.push_back(line);
            }
            temp.push_back(line);
            polygons.push_back(temp);
            temp.clear();
        }
        footer.push_back(line);
        while (getline(in,line))
        {
            footer.push_back(line);
        }
        
    }

    void solve(){
        for(auto it : header){
            out<<it<<"\n";
        }
        for(int i = 0; i < 2;i++){
            for(auto it : polygons[i]){
                out<<it<<"\n";
            }
        }
        for(auto it : footer){
            out<<it<<"\n";
        }
    }
};

int main(){
    if (!in.is_open())
    {
        cerr << "Could not open the file - '" << "\n";
        return EXIT_FAILURE;
    }
    Solution obj;
    obj.Reader();
    obj.solve();
    return 0;
}