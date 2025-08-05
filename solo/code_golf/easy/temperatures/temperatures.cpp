#include <iostream>
using namespace std;int main(){int c=999,n,i,t;cin>>n;for(i=0;i<n;i++){cin>>t;if(abs(t)<abs(c)||(abs(t)==abs(c)&&t>0)){c=t;}}if(c==999){c=0;}cout<<c;}