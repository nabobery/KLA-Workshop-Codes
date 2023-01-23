#include <bits/stdc++.h>
using namespace std;

ifstream in("../Milestone_input/Milestone 2/Source.txt");
ifstream poi("../Milestone_input/Milestone 2/POI.txt");
ofstream out("./output.txt");
ofstream t("./temp.txt");

class Polygon{
    public:
        vector<string> polygon;
        vector<pair<int,int>> coordinates;
        vector<pair<double,double>> lenangles;

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
    void getCoordinates(){
        string line;
        for(auto it : polygon){
            if(it.find("xy") != string::npos){
                line = it;
                break;
            }
        }
        vector<string> temp = split(line, "  ");
        for(int i = 2; i < temp.size();i++){
            int found = temp[i].find(" ");
            pair<int,int> p;
            p.first = stoi(temp[i].substr(0, found));
            p.second = stoi(temp[i].substr(found+1));
            coordinates.push_back(p);
        }
    }
    double distance(pair<int,int> p, pair<int,int> q){
        int x1 = p.first, x2 = q.first, y1 = p.second, y2 = q.second;
        double result = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
        return round(result * 1000.0) / 1000.0;
    }
    double angle(pair<int,int> p, pair<int,int> q, pair<int,int> r){
        double result = atan2(r.second - p.second, r.second - p.first) -
                atan2(q.second - p.second, q.first - p.first);
        return round(result * 10.0) / 10.0;
    }
    void getlenangles(){
        int n = coordinates.size()-1;
        pair<double,double> p;
        lenangles.assign(n,p);
        for(int i = 0; i < n;i++){
            lenangles[i].first = distance(coordinates[i],coordinates[(i+1)%n]);
            lenangles[i].second = angle(coordinates[i], coordinates[(i+n-1)%n], coordinates[(i+1)%n]);
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
            polygons.push_back(p);
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
    }
    void solve()
    {
        for(int i = 0; i < polygons.size();i++){
            polygons[i].getCoordinates();
            polygons[i].getlenangles();
        }
        match.getCoordinates();
        match.getlenangles();
        // && abs(a.second - b.second) <= 0.1)
        auto cmp = [](pair<double,double> a, pair<double,double> b) { return (a.first == b.first)  ;};
        sort(match.lenangles.begin(), match.lenangles.end());
        for (auto it : header)
        {
            out << it << "\n";
        }
        for(int i = 0; i < polygons.size();i++){
            sort(polygons[i].lenangles.begin(), polygons[i].lenangles.end());
            bool flag = true;
            for(int j = 0; j < polygons[i].lenangles.size();j++){
                if(!cmp(polygons[i].lenangles[j], match.lenangles[j])){
                    flag = false;
                    break;
                }
            }
            if(flag){
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
    if (!in.is_open())
    {
        cerr << "Could not open the file - '"
             << "\n";
        return EXIT_FAILURE;
    }
    Solution obj;
    obj.Reader();
    obj.ReaderTemplate();
    obj.solve();
    return 0;
}