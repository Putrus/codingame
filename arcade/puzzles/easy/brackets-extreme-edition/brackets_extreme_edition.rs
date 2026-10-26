use std::io;
use std::collections::HashMap;

macro_rules! parse_input {
   ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn main() {
   let mut input_line = String::new();
   io::stdin().read_line(&mut input_line).unwrap();
   let expression = input_line.trim().to_string();
   let mut stack = Vec::new();
   let pairs: HashMap<char, char> = [('(', ')'), ('[', ']'), ('{', '}')].iter().cloned().collect();

   for bracket in expression.chars() {
      if pairs.contains_key(&bracket) {
         stack.push(bracket);
      } else if bracket == ')' || bracket == ']' || bracket == '}' {
         if stack.is_empty() {
            println!("false");
            return;
         }

         let open_bracket = stack.pop().unwrap();
         if pairs[&open_bracket] != bracket {
            println!("false");
            return;
         }
      }
   }

   if stack.is_empty() {
      println!("true");
   } else {
      println!("false");
   }
}
