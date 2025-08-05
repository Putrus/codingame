x,y,a,b=map(int,input().split())
while 1:input();print(('S'*(y>b)+'N'*(y<b))+('E'*(x>a)+'W'*(x<a)));a+=(x>a)-(x<a);b+=(y>b)-(y<b)