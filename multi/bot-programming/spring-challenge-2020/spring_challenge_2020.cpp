#include <iostream>
#include <string>
#include <cmath>

template <class T>
class Vector2
{
public:
   Vector2();
   Vector2(T x, T y);
   Vector2(Vector2 const& other);
   Vector2(T value);
   virtual ~Vector2();
   Vector2 operator+(const Vector2& rhs);
   Vector2 operator-(const Vector2& rhs);
   Vector2 operator*(T num);
   Vector2& operator+=(Vector2 const& rhs);
   Vector2& operator-=(Vector2 const& rhs);
   Vector2& operator*=(T num);
   T distance(const Vector2& other);
   Vector2 closest(const Vector2& first, const Vector2& second);

   T x;
   T y;
};

template <class T>
Vector2<T>::Vector2() : x((T)0), y((T)0) {}

template <class T>
Vector2<T>::Vector2(T x, T y) : x(x), y(y) {}

template <class T>
Vector2<T>::Vector2(const Vector2& other) : x(other.x), y(other.y) {}

template <class T>
Vector2<T>::Vector2(T value) : x(value), y(value) {}

template <class T>
Vector2<T>::~Vector2() {}

template <class T>
Vector2<T> Vector2<T>::operator+(Vector2 const& rhs)
{
   return { this->x + rhs.x, this->y + rhs.y };
}

template <class T>
Vector2<T> Vector2<T>::operator-(Vector2 const& rhs)
{
   return { this->x - rhs.x, this->y - rhs.y };
}

template <class T>
Vector2<T> Vector2<T>::operator*(T num)
{
   return { this->x * num, this->y * num };
}

template <class T>
Vector2<T>& Vector2<T>::operator+=(Vector2 const& rhs)
{
   this->x += rhs.x;
   this->y += rhs.y;

   return *this;
}

template <class T>
Vector2<T>& Vector2<T>::operator-=(Vector2 const& rhs)
{
   this->x -= rhs.x;
   this->y -= rhs.y;

   return *this;
}

template <class T>
Vector2<T>& Vector2<T>::operator*=(T num)
{
   this->x *= num;
   this->y *= num;

   return *this;
}

template <class T>
T Vector2<T>::distance(const Vector2& other)
{
   T dx = this->x - other.x;
   T dy = this->y - other.y;

   return std::sqrt(dx * dx + dy * dy);
}

template <class T>
Vector2<T> Vector2<T>::closest(const Vector2& first, const Vector2& second)
{
   T dist_first = this->distance(first);
   T dist_second = this->distance(second);

   return (dist_first < dist_second) ? first : second;
}

template <class T>
std::ostream& operator<<(std::ostream& os, Vector2<T> const& vec)
{
   os << vec.x << ' ' << vec.y;

   return os;
}

template <class T>
std::istream& operator>>(std::istream& is, Vector2<T>& vec)
{
   is >> vec.x >> vec.y;

   return is;
}

template <class T>
bool operator==(Vector2<T> const& lhs, Vector2<T> const& rhs)
{
   return lhs.x == rhs.x && lhs.y == rhs.y;
}

template <class T>
bool operator!=(Vector2<T> const& lhs, Vector2<T> const& rhs)
{
   return lhs.x != rhs.x || lhs.y != rhs.y;
}

struct Pellet
{
   Vector2<int> position;
   int value;
};

std::istream& operator>>(std::istream& is, Pellet& pellet)
{
   is >> pellet.position >> pellet.value;
   return is;
}

int main()
{
   int width; // size of the grid
   int height; // top left corner is (x=0, y=0)
   std::cin >> width >> height; std::cin.ignore();
   for (int i = 0; i < height; i++)
   {
      std::string row;
      std::getline(std::cin, row); // one line of the grid: space " " is floor, pound "#" is wall
   }

   // game loop
   while (1)
   {
      int my_score;
      int opponent_score;
      std::cin >> my_score >> opponent_score; std::cin.ignore();
      int visible_pac_count; // all your pacs and enemy pacs in sight
      std::cin >> visible_pac_count; std::cin.ignore();
      int mine_pac_id = 0;
      Vector2<int> mine_pac_position;
      for (int i = 0; i < visible_pac_count; i++)
      {
         int pac_id; // pac number (unique within a team)
         bool mine; // true if this pac is yours
         int x; // position in the grid
         int y; // position in the grid
         std::string type_id; // unused in wood leagues
         int speed_turns_left; // unused in wood leagues
         int ability_cooldown; // unused in wood leagues
         std::cin >> pac_id >> mine >> x >> y >> type_id >> speed_turns_left >> ability_cooldown; std::cin.ignore();
         if (mine)
         {
            mine_pac_id = pac_id;
            mine_pac_position = {x, y};
         }
      }
      int visible_pellet_count; // all pellets in sight
      std::cin >> visible_pellet_count; std::cin.ignore();
      Pellet target{{width, height}, 0};
      int target_distance = std::numeric_limits<int>::max();
      for (int i = 0; i < visible_pellet_count; i++)
      {
         Pellet pellet;
         std::cin >> pellet; std::cin.ignore();
         int distance = mine_pac_position.distance(pellet.position);
         if (pellet.value > target.value || (pellet.value == target.value && distance < target_distance))
         {
            target = pellet;
            target_distance = distance;
         }
      }

      std::cout << "MOVE " << mine_pac_id << " " << target.position << std::endl;
   }
}