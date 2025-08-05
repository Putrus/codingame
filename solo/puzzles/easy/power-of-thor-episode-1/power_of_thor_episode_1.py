x, y, tx, ty = map(int, input().split())
while True:
   input()
   print(('S' * (y > ty) + 'N' * (y < ty)) + ('E' * (x > tx) + 'W' * (x < tx)))
   ty += y > ty or -(y < ty)
   tx += x > tx or -(x < tx)