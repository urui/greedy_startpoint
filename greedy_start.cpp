#include<iostream>
#include<vector>
#include<fstream>
#include<cassert>
#include<algorithm>
#include<set>
#include<list>
using namespace std;
typedef pair<int,int> edge;


/**
* split関数
* @param string str 分割したい文字列
* @param string delim デリミタ
* @return list<string> 分割された文字列
*/
list<string> split(string str, string delim)
{
    list<string> result;
    int cutAt;
    while( (cutAt = str.find_first_of(delim)) != str.npos )
    {
        if(cutAt > 0)
        {
            result.push_back(str.substr(0, cutAt));
        }
        str = str.substr(cutAt + 1);
    }
    if(str.length() > 0)
    {
        result.push_back(str);
    }
return result;
}

vector < pair<int,int> > pairread(string filename)
 {
  ifstream ifs(filename);
  string str;

    if(ifs.fail()) {
      cerr << "File do not exist.\n";
	           }
  vector < pair<int,int> > reader;
  string a;
  string b;

    while(getline(ifs,str)){
      list<string> strList = split(str, " ");
      string a = strList.front();
      string b = strList.back();
      reader.push_back(make_pair(atoi(a.c_str()),atoi(b.c_str())));
      strList.clear();
	}

  ifs.close();
  cout << "reader " <<endl;
  return reader;
}


vector<edge> greedy_removal(int n, vector<edge> g,double mean,int max){
  vector<int> deg(n,0);
  vector< list<int> > adj_list(n);
  cout << "1" <<endl;
  for(edge e : g){
    deg[e.first]++; deg[e.second]++;
    adj_list[e.first].push_back(e.second);
    adj_list[e.second].push_back(e.first);
  }
  cout << "2"<< endl;
  vector<edge> res;
  set<int> frontier;
  int f,t;
  f=0;
  t=0;
  max=0;

  for(;;){
    t = t+1;
    int v = -1;
    if(max<frontier.size()){
      max = frontier.size();
      }
    f = f+frontier.size();
    for(int x : frontier){
      if( v<0 || deg[v] > deg[x] )v = x;
     }

    int u = -1;
    if(v<0){
      //case: frontier is empty
      for(int i=0;i<n;i++){
	if(deg[i]>=0 && (u<0 || deg[u] > deg[i]) )u = i;
      }
      if(u<0){
        cout << "mean size " << endl;
        mean =(double)f/(double)t;
        cout << mean << endl;
        cout << "max size" << endl;
        cout << max <<endl;
       break;
        }
    }else{
      for(int x : adj_list[v]){
	if(deg[x]>=0 && frontier.count(x)==0 && (u<0 || deg[u] > deg[x]))u = x;
      }
    }

    vector< pair<int,int> > priority;
    for(int x : adj_list[u]){
      if(frontier.count(x)){
	priority.push_back( make_pair(deg[x],x) );
        deg[x]--;
	if(deg[x]==0){
	  frontier.erase(x); deg[x]--;
	}
      }else deg[x]--;
    }
    sort(priority.begin(),priority.end());

    for(auto p : priority){
      res.push_back( make_pair(u, p.second) );
    }

    if(deg[u])frontier.insert(u);
    else deg[u]--;
  }
  return res;
}

int main(){
  int n,max;
  double mean;
  string fin,fout;
  cout << "input nodenumber" << endl;
  cin >>n;
  cout << "input filename" << endl;
  cin >> fin;
  cout << "input outputname" << endl;
  cin >> fout;
  vector<edge>g = pairread(fin);
  vector<edge> res = greedy_removal(n,g,mean,max);
  ofstream ofs(fout);
  for(edge e : res){
    ofs << e.first+1 << " " << e.second+1 << endl;
  }

}
