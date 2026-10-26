use std::io;

macro_rules! parse_input {
   ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn main() {
   let mut input_line = String::new();
   io::stdin().read_line(&mut input_line).unwrap();
   let n = parse_input!(input_line, i32);
   for i in 0..n as usize {
      let mut input_line = String::new();
      io::stdin().read_line(&mut input_line).unwrap();
      let x = input_line.trim_matches('\n').to_string();
      let mut history = Vec::new();
      let mut num = x.parse::<u128>().unwrap();
      while !history.contains(&num) {
         history.push(num);
         num = num.to_string().chars()
            .filter(|c| c.is_ascii_digit())
            .map(|c| {
               let d: u128 = c.to_digit(10).unwrap().into();
               d * d
            })
            .sum();
      }
      if num == 1 {
         println!("{} :)", x);
      } else {
         println!("{} :(", x);
      }
   }
}
