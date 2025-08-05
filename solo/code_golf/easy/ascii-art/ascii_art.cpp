#include <iostream>
#include <vector>
using namespace std;int main(){int l,h,i,j,d=0;char u;cin>>l>>h;cin.ignore();string t,o;getline(cin,t);vector<string>a,r;for(;i<h;i++){getline(cin,o);a.push_back(o);r.push_back("");}for(char c:t){u=toupper(c);d=u-'A';if(d<0||d>26){d=26;}for(i=0;i<r.size();++i){for(j=d*l;j<d*l+l;++j){r[i]+=a[i][j];}}}for(auto&w:r){cout<<w<<endl;}}