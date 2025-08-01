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
      let line = input_line.trim_matches('\n').to_string();
      let mut result = 0;
      let mut j = 0;

      while j < line.len() {
         let mut sub = &input_line[j..j+3];
         if sub.chars().nth(0) == Some('f') || (sub.len() == 2 && sub.chars().nth(1) == Some('f')) {
            result += 1;
            j += 3;
         } else {
            j += 1;
         }
      }
      println!("{}", result);
   }
}
