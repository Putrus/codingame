use std::io;

macro_rules! parse_input {
   ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn main() {
   let mut input_line = String::new();
   io::stdin().read_line(&mut input_line).unwrap();
   let n = parse_input!(input_line, i32);
   let mut inputs = String::new();
   io::stdin().read_line(&mut inputs).unwrap();
   let mut segments = Vec::new();
   for i in inputs.split_whitespace() {
      let a = parse_input!(i, i32);
      segments.push(a);
   }

   let mut left = 0;
   let mut right = segments.len() - 1;
   let mut max_area = 0;
   while left != right {
      let height = i32::min(segments[left], segments[right]);
      let width = (right - left) as i32;
      let area = height * width;
      if area > max_area {
         max_area = area;
      }
      if segments[left] < segments[right] {
         left += 1;
      } else {
         right -= 1;
      }
   }
   println!("{}", max_area);
}
