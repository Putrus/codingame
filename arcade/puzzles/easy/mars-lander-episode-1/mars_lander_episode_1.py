for i in range(int(input())):
   land_x, land_y = [int(j) for j in input().split()]

while True:
   x, y, h_speed, v_speed, fuel, rotate, power = [int(i) for i in input().split()]

   if y > 1500:
      print("0 3")
   elif y > 200:
      print("0 4")
   else:
      print("0 0")