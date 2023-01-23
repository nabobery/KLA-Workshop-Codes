#include <bits/stdc++.h>
using namespace std;

ifstream in("../Milestone_Input/Milestone 7/Source.txt");
ifstream poi("../Milestone_Input/Milestone 7/POI.txt");
ofstream out("./output.txt");
ofstream t("./temp.txt");

#define ll long long int

ll distance(pair<int,int> p, pair<int,int> q){
    int x1 = p.first, x2 = q.first, y1 = p.second, y2 = q.second;
    double result = pow(x2 - x1, 2) + pow(y2 - y1, 2);
    return result;
}

class Polygon{
    public:
        vector<string> polygon;
        vector<pair<int,int>> coordinates;
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
};

class Solution
{
public:
    vector<string> header;
    vector<string> footer;
    vector<Polygon> polygons;
    Polygon match;
    Polygon matches[2];
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
            bool b = p.getCoordinates(4);
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
        int c = 0;
        while (getline(poi, line) && line != "endstr")
        {
            temp.push_back(line);
            while (getline(poi, line) && line != "endel")
            {
                temp.push_back(line);
            }
            if(c%2) matches[0].polygon = temp;
            else{
                matches[1].polygon = temp;
            }
            temp.clear();
            c++;
        }
        while (getline(poi, line))
        {
            continue;
        }
    }
    void solve()
    {
        for(int i = 0; i < polygons.size();i++){
            polygons[i].getCoordinates(4);
        }
        for(int i = 0; i < 2;i++){
            matches[i].getCoordinates(4);
        }
        for (auto it : header)
        {
            out << it << "\n";
        }
        pair<int,int> top_right1 = *max_element(matches[0].coordinates.begin(), matches[0].coordinates.end(), [](const auto& a, const auto& b) {
            return make_pair(a.first, -a.second) < make_pair(b.first, -b.second);
        });
        pair<int,int> top_right2 = *max_element(matches[1].coordinates.begin(), matches[1].coordinates.end(), [](const auto& a, const auto& b) {
            return make_pair(a.first, -a.second) < make_pair(b.first, -b.second);
        });
        ll dist = distance(top_right1,top_right2);
        for(int i = 0; i < polygons.size();i++){
            for(int j = i+1; j < polygons.size();j++){
                pair<int,int> top_right1 = *max_element(polygons[i].coordinates.begin(), polygons[i].coordinates.end(), [](const auto& a, const auto& b) {
                    return make_pair(a.first, -a.second) < make_pair(b.first, -b.second);
                });
                pair<int,int> top_right2 = *max_element(polygons[j].coordinates.begin(), polygons[j].coordinates.end(), [](const auto& a, const auto& b) {
                    return make_pair(a.first, -a.second) < make_pair(b.first, -b.second);
                });
                ll d = distance(top_right1,top_right2);
                if(d == dist && ((polygons[i].polygon[1] == "layer 1" && polygons[j].polygon[1] == "layer 2") || (polygons[j].polygon[1] == "layer 1" && polygons[i].polygon[1] == "layer 2"))){
                    for(auto it : polygons[i].polygon){
                        out<<it<<"\n";
                    }
                    for(auto it : polygons[j].polygon){
                        out<<it<<"\n";
                    }
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