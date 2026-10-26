use std::io;
use std::collections::HashMap;

macro_rules! parse_input {
   ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn main() {
   let mut input_line = String::new();
   io::stdin().read_line(&mut input_line).unwrap();
   let order = input_line.trim_matches('\n').to_string();
   let mut input_line = String::new();
   io::stdin().read_line(&mut input_line).unwrap();
   let side = input_line.trim_matches('\n').to_string();

   let mut ids: HashMap<char, usize> = HashMap::new();
   ids.insert('U', 0);
   ids.insert('L', 1);
   ids.insert('D', 2);
   ids.insert('R', 3);

   let mut folding: Vec<usize> = vec![1; 4];
   eprintln!("{:?}", folding);

   for i in 0..order.len() as usize {
      let c = order.chars().nth(i).unwrap();
      let i = *ids.get(&c).unwrap();
      let size = folding.len();
      folding[(i + 2) % size] += folding[i];
      folding[(i + 1) % size] *= 2;
      folding[(i + 3) % size] *= 2;
      folding[i] = 1;
   }

   eprintln!("{:?}", folding);
   let s = side.chars().nth(0).unwrap();
   println!("{}", folding[ids[&s]]);
}
