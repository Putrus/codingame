#include<iostream>
main(){int c=999,n,t;std::cin>>n;c=n?c:0;while(n--){std::cin>>t;c=abs(t)<abs(c)||t==abs(c)?t:c;}std::cout<<c;}