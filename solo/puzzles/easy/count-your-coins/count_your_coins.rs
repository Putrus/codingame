use std::io;

macro_rules! parse_input {
    ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

struct Coin {
   value: i32,
   count: i32,
}

fn main() {
   let mut input_line = String::new();
   io::stdin().read_line(&mut input_line).unwrap();
   let value_to_reach = parse_input!(input_line, i32);
   let mut input_line = String::new();
   io::stdin().read_line(&mut input_line).unwrap();
   let n = parse_input!(input_line, i32);
   let mut inputs = String::new();
   io::stdin().read_line(&mut inputs).unwrap();
   let mut coins: Vec<Coin> = Vec::new();
   for i in inputs.split_whitespace() {
      let count = parse_input!(i, i32);
      coins.push(Coin { value: 0, count });
   }
   let mut inputs = String::new();
   io::stdin().read_line(&mut inputs).unwrap();
   for (idx, i) in inputs.split_whitespace().enumerate() {
      let value = parse_input!(i, i32);
      coins[idx].value = value;
   }

   coins.sort_by(|a, b| a.value.cmp(&b.value));
   let mut i = 0;
   let mut result = 0;
   let mut total_value = 0;
   while i < coins.len() && total_value < value_to_reach {
      if coins[i].count == 0 {
         i += 1;
      } else {
         total_value += coins[i].value;
         coins[i].count -= 1;
         result += 1;
      }
   }

   if total_value >= value_to_reach {
      println!("{}", result);
   } else {
      println!("-1");
   }
}
