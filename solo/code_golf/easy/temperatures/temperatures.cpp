#include<iostream>
int main(){int c=99,n,i,t;std::cin>>n;for(;i<n;i++){std::cin>>t;if(abs(t)<abs(c)||(abs(t)==abs(c)&&t>0))c=t;}std::cout<<(n?c:0);}