use std::io;

macro_rules! parse_input {
   ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn main() {
   let mut input_line = String::new();
   io::stdin().read_line(&mut input_line).unwrap();
   let inputs = input_line.split(" ").collect::<Vec<_>>();
   let w = parse_input!(inputs[0], i32);
   let h = parse_input!(inputs[1], i32);
   let mut diagram: Vec<String> = Vec::new();
   for i in 0..h as usize {
      let mut input_line = String::new();
      io::stdin().read_line(&mut input_line).unwrap();
      let line = input_line.trim_matches('\n').to_string();
      diagram.push(line);
   }

   for start in 0..w as usize {
      let mut j = start;
      for i in 1..h as usize {
         if j - 1> 0 && diagram[i].chars().nth(j - 1) == Some('-') {
            j -= 3;
         } else if j + 1 < diagram[i].len() && diagram[i].chars().nth(j + 1) == Some('-') {
            j += 3;
         }
      }

      if diagram.is_empty() {
         eprintln!("Diagram is empty!");
         return;
      }
      let first: &String = diagram.first().unwrap();
      let last: &String = diagram.last().unwrap();

      if first.chars().nth(start) != None && last.chars().nth(j) != None {
         let letter = first.chars().nth(start).unwrap();
         let number = last.chars().nth(j).unwrap();
         if letter != ' ' && number != ' ' {
            println!("{}{}", letter, number);
         }
      }
   }
}
