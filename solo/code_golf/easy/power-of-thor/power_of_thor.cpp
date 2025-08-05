#include<iostream>
main(){int i,j,x,y;std::cin>>i>>j>>x>>y;for(;;){printf("%s%s\n",j>y?"S":j<y?"N":"",i>x?"E":i<x?"W":"");x+=x<i-x>i;y+=y<j-(y>j);}}