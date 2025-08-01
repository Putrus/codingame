use std::io;

macro_rules! parse_input {
   ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn main() {
   let mut input_line = String::new();
   io::stdin().read_line(&mut input_line).unwrap();
   let n = parse_input!(input_line, i32); // the number of temperatures to analyse
   let mut inputs = String::new();
   io::stdin().read_line(&mut inputs).unwrap();
   let mut temperature = 0;
   let mut min = 5526;
   for i in inputs.split_whitespace() {
      let t = parse_input!(i, i32);
      if i32::abs(0 - t) < min || (i32::abs(0 - t) == min && t > temperature) {
         min = i32::abs(0 - t);
         temperature = t;
      }
   }
   println!("{}", temperature);
}
