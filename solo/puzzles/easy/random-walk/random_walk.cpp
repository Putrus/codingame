#include <iostream>

enum Direction : int
{
   Up = 0,
   Down,
   Left,
   Right
};

struct Position
{
   int x;
   int y;

   Position& operator+=(Direction dir)
   {
      switch(dir)
      {
         case Up: --y; break;
         case Down: ++y; break;
         case Left: --x; break;
         case Right: ++x; break;
      }
      return *this;
   }
};

class RandomDirectionGenerator
{
public:
   RandomDirectionGenerator(int a, int b, int m) : a(a), b(b), m(m), d(0) {}

   Direction generate()
   {
      d = (a * d + b) % m;
      return static_cast<Direction>(d % 4);
   }

private:
   int a;
   int b;
   int m;
   int d;
};

int main()
{
    int a, b, m;
    std::cin >> a >> b >> m; std::cin.ignore();
    Position position = { 0, 0 };
    RandomDirectionGenerator generator(a , b, m);
    int steps = 0;
    do
    { 
       position += generator.generate(); 
       ++steps;
    } while(position.x != 0 || position.y != 0);

    std::cout << steps << std::endl;
}
