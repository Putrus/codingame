message = input()

b = ''.join(f'{ord(char):07b}' for char in message)
current = '2'

count = 0
for c in b:
   if c != current:
      if current == '0':
         print("00 " + "0" * count + " ", end='')
      elif current == '1':
         print("0 " + "0" * count + " ", end='')
      current = c
      count = 1
   else:
      count += 1

if current == '0':
   print("00 " + "0" * count)
elif current == '1':
   print("0 " + "0" * count)