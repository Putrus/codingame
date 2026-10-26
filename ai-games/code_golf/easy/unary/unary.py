n=1;m='2';p=lambda e='':print(('0 ','00 ')[m<'1']+'0'*n,end=e)if m!='2'else e
for c in''.join(f'{ord(a):07b}'for a in input()):
 if c!=m:p(' ');m=c;n=1
 else:n+=1
p()