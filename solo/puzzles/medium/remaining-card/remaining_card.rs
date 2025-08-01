use std::io;

macro_rules! parse_input {
   ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

//1: 1
//2: 2
//3: 2
//4: 4
//5: 2
//6: 4
//7: 6
//8: 8
//9: 2
//10: 4
//11: 6
//12: 8
//13: 10
//14: 12
//15: 14
//16: 16
//17: 2
//18: 4
//19: 6
//20: 8
//21: 10
//22: 12
//23: 14
//24: 16
//25: 18
//26: 20
//27: 22
//28: 24
//29: 26
//30: 28
//31: 30
//32: 32
//33: 2
//34: 4
//35: 6
//36: 8
//37: 10
//38: 12
//39: 14
//40: 16

fn main() {
   let mut input_line = String::new();
   io::stdin().read_line(&mut input_line).unwrap();
   let n = parse_input!(input_line, i32);

   let mut p = 1;
   while p < n {
      p *= 2;
   }

   let mut result = 1
   if p != 1 {
      result = (n - p / 2) * 2;
   }
   println!("{}", result);
}
