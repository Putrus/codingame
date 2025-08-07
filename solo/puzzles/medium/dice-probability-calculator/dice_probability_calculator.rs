use std::io;
use std::collections::HashMap;

macro_rules! parse_input {
   ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

struct Distribution {
   outcomes: HashMap<i32, f64>,
}

impl Distribution{
   pub fn new() -> Self {
      Distribution {
         outcomes: HashMap::new(),
      }
   }

   pub fn new_from_value(value: i32) -> Self {
      let mut outcomes = HashMap::new();
      outcomes.insert(value, 1.0);
      Distribution { outcomes }
   }

   pub fn new_from_dice(sides: i32) -> Self {
      let mut outcomes = HashMap::new();
      for i in 1..=sides {
         outcomes.insert(i, 1.0 / sides as f64);
      }
      Distribution { outcomes }
   }

   pub fn apply_operator(&self, other: &Distribution, operator: &str) -> Self {
      let mut new_outcomes = HashMap::new();
      for (a, a_probability) in &self.outcomes {
         for (b, b_probability) in &other.outcomes {
            let c = match operator {
               "+" => a + b,
               "-" => a - b,
               "*" => a * b,
               ">" => if a > b { 1 } else { 0 },
               _ => continue,
            };
            let new_probability = a_probability * b_probability;
            *new_outcomes.entry(c).or_insert(0.0) += new_probability;
         }
      }
      Distribution { outcomes: new_outcomes }
   }
}

struct Calculator {}

impl Calculator {
   pub fn new() -> Self {
      Calculator {}
   }

   fn precedence(op: &str) -> i32 {
      match op {
         ">" => 1,
         "+" | "-" => 2,
         "*" => 3,
         _ => 0,
      }
   }

   fn parse_to_rpn(&self, input: &str) -> Vec<String> {
      let mut output = Vec::new();
      let mut operators = Vec::new();
      let chars: Vec<char> = input.chars().collect();
      let mut i = 0;
      while i < chars.len() {
         if chars[i].is_ascii_digit() || chars[i] == 'd' {
            let mut j = i;
            while j < chars.len() && (chars[j].is_ascii_digit() || chars[j] == 'd') {
               j += 1;
            }
            output.push(input[i..j].to_string());
            i = j;
         } else if chars[i] == '(' {
            operators.push("(".to_string());
            i += 1;
         } else if chars[i] == ')' {
            while let Some(op) = operators.last() {
               if op == "(" {
                  break;
               }
               output.push(operators.pop().unwrap());
            }
            if operators.last() == Some(&"(".to_string()) {
               operators.pop();
            }
            i += 1;
         } else if "+-*>".contains(chars[i]) {
            let op = chars[i].to_string();
            while let Some(top) = operators.last() {
               if Self::precedence(top) >= Self::precedence(&op) {
                  output.push(operators.pop().unwrap());
               } else {
                  break;
               }
            }
            operators.push(op);
            i += 1;
         } else {
            i += 1;
         }
      }
      while let Some(op) = operators.pop() {
         output.push(op);
      }
      output
   }

   pub fn calculate(&self, expr: &str) -> Distribution {
      let rpn = self.parse_to_rpn(expr);
      let mut stack: Vec<Distribution> = Vec::new();
      for token in rpn {
         if token.chars().all(|c| c.is_ascii_digit()) {
            stack.push(Distribution::new_from_value(token.parse::<i32>().unwrap()));
         } else if token.starts_with('d') {
            let sides = token[1..].parse::<i32>().unwrap();
            stack.push(Distribution::new_from_dice(sides));
         } else {
            let right = stack.pop().unwrap();
            let left = stack.pop().unwrap();
            let result = left.apply_operator(&right, &token);
            stack.push(result);
         }
      }
      stack.pop().unwrap()
   }
}

fn main() {
   let mut input_line = String::new();
   io::stdin().read_line(&mut input_line).unwrap();
   let expr = input_line.trim_matches('\n').to_string();

   let calculator = Calculator{};
   let result = calculator.calculate(&expr);
   
   let mut outcomes: Vec<_> = result.outcomes.iter().collect();
   outcomes.sort_by_key(|&(outcome, _)| *outcome);
   for (outcome, probability) in outcomes {
      println!("{} {:.2}", outcome, probability * 100.0);
   }
}
