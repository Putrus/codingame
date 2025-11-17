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

int main()
{
   std::vector<Vector2<double>> checkpoint_list;
   std::vector<Vector2<double>> position_list;

   int checkpoint_index = 0;
   int frame_index = 0;
   int boost_used = 0;

   std::vector<double> line_parameters;
   std::vector<double> new_destination(2);

   while (true)
   {
      Vector2<double> pod_position;
      Vector2<double> next_checkpoint_position;
      int next_checkpoint_distance, next_checkpoint_angle;

      std::cin >> pod_position >> next_checkpoint_position >> next_checkpoint_distance >> next_checkpoint_angle;
      Vector2<double> opponent_position;

      std::cin >> opponent_position;
      double checkpoint_distance = next_checkpoint_distance;
      double opponent_next_checkpoint_distance = next_checkpoint_position.distance(opponent_position);

      if (checkpoint_list.empty())
      {
         checkpoint_list.push_back(next_checkpoint_position);
         checkpoint_index++;
      } 
      else if (checkpoint_list[checkpoint_index - 1] != next_checkpoint_position)
      {
         checkpoint_list.push_back(next_checkpoint_position);
         checkpoint_index++;
      }

      if (checkpoint_index >= 2)
      {
         std::vector<double> new_line_parameters = getLineParameters(checkpoint_list[checkpoint_index - 1], checkpoint_list[checkpoint_index - 2]);

         if (line_parameters != new_line_parameters)
         {
            line_parameters = new_line_parameters;
            Vector2<double> delta = checkpoint_list[checkpoint_index - 1] - checkpoint_list[checkpoint_index - 2];

            double delta_r = std::sqrt(delta.x * delta.x + delta.y * delta.y);

            double new_delta_x = std::abs(600.0 * delta.x / delta_r);
            double new_delta_y = std::abs(600.0 * delta.y / delta_r);

            if (delta.x < 0 && delta.y < 0)
            {
               new_destination[0] = checkpoint_list[checkpoint_index - 1].x + new_delta_x;
               new_destination[1] = checkpoint_list[checkpoint_index - 1].y + new_delta_y;
            } 
            else if (delta.x < 0 && delta.y > 0)
            {
               new_destination[0] = checkpoint_list[checkpoint_index - 1].x + new_delta_x;
               new_destination[1] = checkpoint_list[checkpoint_index - 1].y - new_delta_y;
            } 
            else if (delta.x > 0 && delta.y > 0)
            {
               new_destination[0] = checkpoint_list[checkpoint_index - 1].x - new_delta_x;
               new_destination[1] = checkpoint_list[checkpoint_index - 1].y - new_delta_y;
            } 
            else if (delta.x > 0 && delta.y < 0)
            {
               new_destination[0] = checkpoint_list[checkpoint_index - 1].x - new_delta_x;
               new_destination[1] = checkpoint_list[checkpoint_index - 1].y + new_delta_y;
            }
         }
      }

      int thrust = 100;

      if (std::abs(next_checkpoint_angle) > 90)
      {
         thrust = 0;
      } 
      else if (next_checkpoint_distance < 1500)
      {
         thrust = 0;
      }

      position_list.push_back(pod_position);

      if (frame_index >= 1)
      {
         Vector2<double> delta = position_list[frame_index - 1] - position_list[frame_index];

         if (std::abs(delta.x) < 350 && std::abs(delta.y) < 350)
         {
            thrust = 100;
         }
      }

      if (boost_used == 0 &&
         opponent_next_checkpoint_distance < 600 &&
         checkpoint_distance > 600 &&
         checkpoint_distance < 1200) 
      {
         boost_used = 1;
         std::cout << opponent_position.x << " " << opponent_position.y << " BOOST\n";
      }
      else if (checkpoint_index >= 2)
      {
         std::cout << static_cast<int>(new_destination[0]) << " " << static_cast<int>(new_destination[1]) << " " << thrust << std::endl;;
      }
      else
      {
         std::cout << next_checkpoint_position.x << " " << next_checkpoint_position.y << " " << thrust << std::endl;
      }

      frame_index++;
   }

   return 0;
}
