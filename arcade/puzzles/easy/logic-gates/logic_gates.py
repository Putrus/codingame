n = int(input())
m = int(input())
inputs = {}
logic = { '_' : False, '-' : True }
l = [ '_', '-' ]
for i in range(n):
   input_name, input_signal = input().split()
   inputs[input_name] = input_signal
for i in range(m):
   output_name, _type, input_name_1, input_name_2 = input().split()
   result = ""
   for a, b in zip(inputs[input_name_1], inputs[input_name_2]):
      if _type == "AND":
         result += l[logic[a] and logic[b]]
      if _type == "OR":
         result += l[logic[a] or logic[b]]
      if _type == "XOR":
         result += l[logic[a] != logic[b]]
      if _type == "NAND":
         result += l[not (logic[a] and logic[b])]
      if _type == "NOR":
         result += l[not (logic[a] or logic[b])]
      if _type == "NXOR":
         result += l[logic[a] == logic[b]]

   print("{} {}".format(output_name, result))