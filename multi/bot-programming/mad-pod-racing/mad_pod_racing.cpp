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

public:
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
std::istream& operator>>(std::istream& is, Vector2<T>& rhs)
{
   is >> rhs.x >> rhs.y;
   return is;
}

template <class T>
std::ostream& operator<<(std::ostream& os, Vector2<T> const& rhs)
{
   os << rhs.x << ' ' << rhs.y;
   return os;
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

template <class T>
bool operator!=(Vector2<T>& lhs, Vector2<T> & rhs)
{
   return lhs.x != rhs.x || lhs.y != rhs.y;
}

int main()
{

   while (true) 
   {
      int x;
      int y;
      int next_checkpoint_x; // x position of the next check point
      int next_checkpoint_y; // y position of the next check point
      int next_checkpoint_dist; // distance to the next checkpoint
      int next_checkpoint_angle; // angle between your pod orientation and the direction of the next checkpoint
      std::cin >> x >> y >> next_checkpoint_x >> next_checkpoint_y >> next_checkpoint_dist >> next_checkpoint_angle; std::cin.ignore();
      int opponent_x;
      int opponent_y;
      std::cin >> opponent_x >> opponent_y; std::cin.ignore();
      
      std::cout << next_checkpoint_x << " " << next_checkpoint_y << " 80" << std::endl;
   }
}

// https://files.magusgeek.com/csb/csb_en.html