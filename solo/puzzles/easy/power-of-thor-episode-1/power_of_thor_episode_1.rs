use std::io;

macro_rules! parse_input {
   ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn main() {
   let mut input_line = String::new();
   io::stdin().read_line(&mut input_line).unwrap();
   let inputs = input_line.split(" ").collect::<Vec<_>>();
   let light_x = parse_input!(inputs[0], i32); // the X position of the light of power
   let light_y = parse_input!(inputs[1], i32); // the Y position of the light of power
   let initial_tx = parse_input!(inputs[2], i32); // Thor's starting X position
   let initial_ty = parse_input!(inputs[3], i32); // Thor's starting Y position
   let mut tx = initial_tx;
   let mut ty = initial_ty;
   loop {
      let mut input_line = String::new();
      io::stdin().read_line(&mut input_line).unwrap();
      let remaining_turns = parse_input!(input_line, i32); // The remaining amount of turns Thor can move. Do not remove this line.

      if (light_y < ty) {
         print!("N");
         --ty;
      } else if (light_y > ty) {
         print!("S");
         ty += 1;
      }

      if (light_x < tx) {
         print!("W");
         --tx;
      } else if (light_x > tx) {
         print!("E");
         tx += 1;
      }
      println!();
   }
}
