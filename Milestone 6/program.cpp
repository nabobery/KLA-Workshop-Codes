#include <bits/stdc++.h>
using namespace std;

ifstream in("../Milestone_Input/Milestone 6/Source.txt");
ifstream poi("../Milestone_Input/Milestone 6/POI.txt");
ofstream out("./output.txt");
ofstream t("./temp.txt");

#define ll long long int

ll distance(pair<int,int> p, pair<int,int> q){
    int x1 = p.first, x2 = q.first, y1 = p.second, y2 = q.second;
    ll result = pow(x2 - x1, 2) + pow(y2 - y1, 2);
    return result;
}

class Polygon{
    public:
        vector<string> polygon;
        vector<pair<int,int>> coordinates;
        vector<ll> lengths;

    vector<string> split (string s, string delimiter) {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        string token;
        vector<string> res;

        while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
            token = s.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back (token);
        }

        res.push_back (s.substr (pos_start));
        return res;
    }
    bool getCoordinates(int size){
        string line;
        for(auto it : polygon){
            if(it.find("xy") != string::npos){
                line = it;
                break;
            }
        }
        vector<string> temp = split(line, "  ");
        if(stoi(temp[1]) != (size+1)) return false;
        for(int i = 2; i < temp.size();i++){
            int found = temp[i].find(" ");
            pair<int,int> p;
            p.first = stoi(temp[i].substr(0, found));
            p.second = stoi(temp[i].substr(found+1));
            coordinates.push_back(p);
        }
        return true;
    }

    void getLengths(){
        int n = coordinates.size()-1;
        lengths.assign(n,0);
        for(int i = 0; i < n;i++){
            lengths[i] = distance(coordinates[i],coordinates[(i+1)%n]);
        }
    }
};

class Solution
{
public:
    vector<string> header;
    vector<string> footer;
    vector<Polygon> polygons;
    Polygon match;
    void Reader()
    {
        string line;
        while (getline(in, line) && line != "boundary")
        {
            header.push_back(line);
        }
        vector<string> temp;
        temp.push_back(line);
        while (getline(in, line) && line != "endstr")
        {
            Polygon p;
            temp.push_back(line);
            while (getline(in, line) && line != "endel")
            {
                temp.push_back(line);
            }
            temp.push_back(line);
            p.polygon = temp;
            bool b = p.getCoordinates(8);
            if(b){
                polygons.push_back(p);
            }
            temp.clear();
        }
        footer.push_back(line);
        while (getline(in, line))
        {
            footer.push_back(line);
        }
    }
    void ReaderTemplate()
    {
        string line;
        while (getline(poi, line) && line != "boundary")
        {
            continue;
        }
        vector<string> temp;
        temp.push_back(line);
        while (getline(poi, line) && line != "endstr")
        {
            temp.push_back(line);
            while (getline(poi, line) && line != "endel")
            {
                temp.push_back(line);
            }
            temp.push_back(line);
            match.polygon = temp;
            break;
        }
        poi.close();
    }
    void solve()
    {
        for(int i = 0; i < polygons.size();i++){
            polygons[i].getLengths();
        }
        match.getCoordinates(8);
        match.getLengths();
        sort(match.lengths.begin(), match.lengths.end());
        for (auto it : header)
        {
            out << it << "\n";
        }
        for(int i = 0; i < polygons.size();i++){
            sort(polygons[i].lengths.begin(), polygons[i].lengths.end());
            bool flag = true;
            double scaling_factor = ((double)polygons[i].lengths[0])/ match.lengths[0];
            for(int j = 1; j < polygons[i].lengths.size();j++){
                if(floor(abs(polygons[i].lengths[j] - (match.lengths[j]*scaling_factor))) > scaling_factor){
                    flag = false;
                    break;
                }
            }
            if(flag){
                cout<<scaling_factor<<"\n";
                for(auto it : polygons[i].polygon){
                    out<<it<<"\n";
                }
            }
        }
        for (auto it : footer)
        {
            out << it << "\n";
        }
    }
};



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if (!in.is_open())
    {
        cerr << "Could not open the file - '"
             << "\n";
        return EXIT_FAILURE;
    }
    Solution obj;
    obj.ReaderTemplate();
    obj.Reader();
    obj.solve();
    return 0;
}