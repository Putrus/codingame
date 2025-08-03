use std::io;
use std::collections::HashMap;

macro_rules! parse_input {
   ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn main() {
   let mut input_line = String::new();
   io::stdin().read_line(&mut input_line).unwrap();
   let n = parse_input!(input_line, i32); // Number of elements which make up the association table.
   let mut input_line = String::new();
   io::stdin().read_line(&mut input_line).unwrap();
   let q = parse_input!(input_line, i32); // Number Q of file names to be analyzed.
   let mut mime: HashMap<String, String> = HashMap::new();
   for i in 0..n as usize {
      let mut input_line = String::new();
      io::stdin().read_line(&mut input_line).unwrap();
      let inputs = input_line.split(" ").collect::<Vec<_>>();
      let ext = inputs[0].trim().to_string(); // file extension
      let mt = inputs[1].trim().to_string(); // MIME type.
      mime.insert(ext.to_lowercase(), mt);
   }
   for i in 0..q as usize {
      let mut input_line = String::new();
      io::stdin().read_line(&mut input_line).unwrap();
      let fname = input_line.trim_matches('\n').to_string(); // One file name per line.
      let ext = if fname.contains('.') {
         fname.split('.').last().unwrap_or("").to_lowercase()
      } else {
         String::new()
      };
      if let Some(mt) = mime.get(&ext) {
         println!("{}", mt);
      } else {
         println!("UNKNOWN");
      }
   }
}
