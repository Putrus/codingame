#include<stdlib.h>
int main(){int n,i,t,c=999;scanf("%d",&n);for(;i<n;i++){scanf("%d",&t);if(abs(t)<abs(c)||(abs(t)==abs(c)&&t>0))c=t;}if(!n)c=0;printf("%d\n",c);}