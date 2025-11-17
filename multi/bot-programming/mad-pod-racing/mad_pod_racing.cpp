#include <iostream>
#include <cmath>
#include <vector>

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

std::vector<double> getLineParameters(Vector2<double> p1, Vector2<double> p2)
{
   double a = (p2.y - p1.y) / (p2.x - p1.x);
   double b = p1.y - a * p1.x;
   return { a, b };
}

class Pod
{
public:
   Vector2<int> position;
   Vector2<int> velocity;
   int angle;
   int next_check_point_id;
};

std::istream& operator>>(std::istream& is, Pod& pod)
{
   is >> pod.position >> pod.velocity >> pod.angle >> pod.next_check_point_id;
   return is;
}

constexpr int POD_SIZE = 2;

int main()
{
   int laps;
   std::cin >> laps; std::cin.ignore();
   int checkpoint_count;
   std::cin >> checkpoint_count; std::cin.ignore();

   std::vector<Vector2<int>> checkpoints;
   for (int i = 0; i < checkpoint_count; i++)
   {
      Vector2<int> checkpoint;
      std::cin >> checkpoint; std::cin.ignore();
      checkpoints.push_back(checkpoint);
   }

   while (1)
   {
      Pod pods[POD_SIZE];
      Pod opponents[POD_SIZE];
      
      for (int i = 0; i < POD_SIZE; i++)
      {
         std::cin >> pods[i]; std::cin.ignore();
      }
      for (int i = 0; i < POD_SIZE; i++)
      {
         std::cin >> opponents[i]; std::cin.ignore();
      }
      std::cout << checkpoints[pods[0].next_check_point_id] << " 75" << std::endl;
      std::cout << checkpoints[pods[1].next_check_point_id] << " 75" << std::endl;
   }
}