use std::io;

macro_rules! parse_input {
   ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn main() {
   let mut input_line = String::new();
   io::stdin().read_line(&mut input_line).unwrap();
   let n = parse_input!(input_line, i32);
   let mut v: Vec<i32> = Vec::new();
   for i in 0..n as usize {
      let mut input_line = String::new();
      io::stdin().read_line(&mut input_line).unwrap();
      let pi = parse_input!(input_line, i32);
      v.push(pi);
   }

   v.sort();

   let mut min: i32 = i32::MAX;
   for i in 1..n as usize {
      let diff = i32::abs(v[i] - v[i - 1]);
      if diff < min {
         min = diff;
      }
   }

   println!("{}", min);
}
