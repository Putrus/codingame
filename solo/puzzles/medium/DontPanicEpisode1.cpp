#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
   int nb_floors; // number of floors
   int width; // width of the area
   int nb_rounds; // maximum number of rounds
   int exit_floor; // floor on which the exit is found
   int exit_pos; // position of the exit on its floor
   int nb_total_clones; // number of generated clones
   int nb_additional_elevators; // ignore (always zero)
   int nb_elevators; // number of elevators
   std::cin >> nb_floors >> width >> nb_rounds >> exit_floor >> exit_pos >>
      nb_total_clones >> nb_additional_elevators >> nb_elevators; std::cin.ignore();

   std::vector<int> elevators(nb_elevators + 1);
   for (int i = 0; i < nb_elevators; i++)
   {
      int elevator_floor; // floor on which this elevator is found
      int elevator_pos; // position of the elevator on its floor
      std::cin >> elevator_floor >> elevator_pos; std::cin.ignore();
      elevators[elevator_floor] = elevator_pos;
   }
   elevators[exit_floor] = exit_pos;

   // game loop
   while (1)
   {
      int clone_floor; // floor of the leading clone
      int clone_pos; // position of the leading clone on its floor
      std::string direction; // direction of the leading clone: LEFT or RIGHT
      std::cin >> clone_floor >> clone_pos >> direction; std::cin.ignore();

      if ((direction == "LEFT" && elevators[clone_floor] <= clone_pos) ||
         (direction == "RIGHT" && elevators[clone_floor] >= clone_pos))
      {
         std::cout << "WAIT" << std::endl;
      }
      else
      {
         std::cout << "BLOCK" << std::endl;
      }
   }
}