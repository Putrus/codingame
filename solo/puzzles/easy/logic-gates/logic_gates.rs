use std::io;
use std::collections::HashMap;

macro_rules! parse_input {
   ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn main() {
   let mut input_line = String::new();
   io::stdin().read_line(&mut input_line).unwrap();
   let n = parse_input!(input_line, i32);
   let mut input_line = String::new();
   io::stdin().read_line(&mut input_line).unwrap();
   let m = parse_input!(input_line, i32);
   let mut signals: HashMap<String, String> = HashMap::new();
   for i in 0..n as usize {
      let mut input_line = String::new();
      io::stdin().read_line(&mut input_line).unwrap();
      let inputs = input_line.split(" ").collect::<Vec<_>>();
      let input_name = inputs[0].trim().to_string();
      let input_signal = inputs[1].trim().to_string();
      signals.insert(input_name, input_signal);
   }
   for i in 0..m as usize {
      let mut input_line = String::new();
      io::stdin().read_line(&mut input_line).unwrap();
      let inputs = input_line.split(" ").collect::<Vec<_>>();
      let output_name = inputs[0].trim().to_string();
      let _type = inputs[1].trim().to_string();
      let input_name_1 = inputs[2].trim().to_string();
      let input_name_2 = inputs[3].trim().to_string();

      print!("{} ", output_name);
      if _type == "AND" {
         for j in 0..signals[&input_name_1].len() {
            if signals[&input_name_1].chars().nth(j).unwrap() == '-' && signals[&input_name_2].chars().nth(j).unwrap() == '-' {
               print!("-");
            } else {
               print!("_");
            }
         }
      } else if _type == "OR" {
         for j in 0..signals[&input_name_1].len() {
            if signals[&input_name_1].chars().nth(j).unwrap() == '-' || signals[&input_name_2].chars().nth(j).unwrap() == '-' {
               print!("-");
            } else {
               print!("_");
            }
         }
      } else if _type == "XOR" {
         for j in 0..signals[&input_name_1].len() {
            if signals[&input_name_1].chars().nth(j).unwrap() != signals[&input_name_2].chars().nth(j).unwrap() {
               print!("-");
            } else {
               print!("_");
            }
         }
      } else if _type == "NAND" {
         for j in 0..signals[&input_name_1].len() {
            if signals[&input_name_1].chars().nth(j).unwrap() == '-' && signals[&input_name_2].chars().nth(j).unwrap() == '-' {
               print!("_");
            } else {
               print!("-");
            }
         }
      } else if _type == "NOR" {
         for j in 0..signals[&input_name_1].len() {
            if signals[&input_name_1].chars().nth(j).unwrap() == '-' || signals[&input_name_2].chars().nth(j).unwrap() == '-' {
               print!("_");
            } else {
               print!("-");
            }
         }
      } else if _type == "NXOR" {
         for j in 0..signals[&input_name_1].len() {
            if signals[&input_name_1].chars().nth(j).unwrap() != signals[&input_name_2].chars().nth(j).unwrap() {
               print!("_");
            } else {
               print!("-");
            }
         }
      } else {
         eprintln!("Unknown gate type: {}", _type);
      }
      println!();
   }
}
