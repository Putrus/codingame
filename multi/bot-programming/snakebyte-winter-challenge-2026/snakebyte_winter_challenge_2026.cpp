#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

int main()
{
    int my_id, width, height;
    std::cin >> my_id; std::cin.ignore();
    std::cin >> width; std::cin.ignore();
    std::cin >> height; std::cin.ignore();
    for (int i = 0; i < height; i++) 
    {
        std::string row;
        getline(std::cin, row);
    }
    int snakebots_per_player;
    std::cin >> snakebots_per_player; std::cin.ignore();
    for (int i = 0; i < snakebots_per_player; i++)
    {
        int my_snakebot_id;
        std::cin >> my_snakebot_id; std::cin.ignore();
    }
    for (int i = 0; i < snakebots_per_player; i++)
    {
        int opp_snakebot_id;
        std::cin >> opp_snakebot_id; std::cin.ignore();
    }
    srand(time(NULL));
    std::array<std::string, 4> directions = { "UP", "DOWN", "LEFT", "RIGHT" };
    // game loop
    while (1)
    {
        int power_source_count;
        std::cin >> power_source_count; std::cin.ignore();
        for (int i = 0; i < power_source_count; i++)
        {
            int x;
            int y;
            std::cin >> x >> y; std::cin.ignore();
        }
        int snakebot_count;
        std::cin >> snakebot_count; std::cin.ignore();
        for (int i = 0; i < snakebot_count; i++)
        {
            int snakebot_id;
            std::string body;
            std::cin >> snakebot_id >> body; std::cin.ignore();
            std::cerr << body << std::endl;

            std::cout << snakebot_id << " " << directions[std::rand() % 4] << ";";
        }

        std::cout << "WAIT" << std::endl;
    }
}
