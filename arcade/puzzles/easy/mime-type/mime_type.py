n = int(input())
q = int(input())
mime = {}
for i in range(n):
   ext, mt = input().split()
   mime[ext.lower()] = mt
for i in range(q):
   fname = input()
   ext = "" if fname.endswith('.') or '.' not in fname else fname.rsplit('.', 1)[-1]
   if ext.lower() in mime:
      print(mime[ext.lower()])
   else:
      print("UNKNOWN")