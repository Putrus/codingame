use std::io;

macro_rules! parse_input {
   ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn main() {
   let mut input_line = String::new();
   io::stdin().read_line(&mut input_line).unwrap();
   let n = parse_input!(input_line, i32); // the number of mountains
   let mut inputs = String::new();
   io::stdin().read_line(&mut inputs).unwrap();
   let mut max_height = 0;
   let mut heights = Vec::new();
   for i in inputs.split_whitespace() {
      let height = parse_input!(i, i32);
      heights.push(height);
      if height > max_height {
         max_height = height;
      }
   }

   for i in (0..=max_height).rev() {
      for k in 0..heights.len() as i32 {
         let mut height = heights[k as usize];
         if height < i {
            let mut higher_exists = false;
            for j in k + 1..heights.len() as i32 {
               if heights[j as usize] >= i {
                  higher_exists = true;
                  break;
               }
            }
            if higher_exists {
               for j in 0..height * 2 {
                  print!(" ");
               }
            }
         } else {
            for j in 0..i - 1 {
               print!(" ");
            }
            print!("/");
            for j in 0..(height - i) * 2 {
               print!(" ");
            }
            print!("\\");

            let mut higher_exists = false;
            for j in k + 1..heights.len() as i32 {
               if heights[j as usize] >= i {
                  higher_exists = true;
                  break;
               }
            }
            if higher_exists {
               for j in 0..i - 1 {
                  print!(" ");
               }
            }
         }
      }
      print!("\n");
   }
}
