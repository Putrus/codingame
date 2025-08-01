use std::io;

macro_rules! parse_input {
   ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn main() {
   loop {
      let mut highest = 0;
      let mut id = 0;
      for i in 0..8 as usize {
         let mut input_line = String::new();
         io::stdin().read_line(&mut input_line).unwrap();
         let mountain_h = parse_input!(input_line, i32);
         if mountain_h > highest {
            highest = mountain_h;
            id = i;
         }
      }
      println!("{}", id);
   }
}
