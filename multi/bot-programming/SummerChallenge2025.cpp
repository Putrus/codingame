#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <limits>
#include <cmath>

using namespace std;

struct Agent
{
    int player;
    int shoot_cooldown;
    int optimal_range;
    int soaking_power;
    int splash_bombs;
};

struct MyAgent
{
    int x;
    int y;
    int cooldown;
    int splash_bombs;
    int wetness;
};

int main()
{
    std::map<int, Agent> agents;
    int my_id; // Your player id (0 or 1)
    cin >> my_id; cin.ignore();
    int agent_data_count; // Total number of agents in the game
    cin >> agent_data_count; cin.ignore();
    for (int i = 0; i < agent_data_count; i++)
    {
        int agent_id; // Unique identifier for this agent
        int player; // Player id of this agent
        int shoot_cooldown; // Number of turns between each of this agent's shots
        int optimal_range; // Maximum manhattan distance for greatest damage output
        int soaking_power; // Damage output within optimal conditions
        int splash_bombs; // Number of splash bombs this can throw this game
        cin >> agent_id >> player >> shoot_cooldown >> optimal_range >> soaking_power >> splash_bombs; cin.ignore();
        agents.insert({ agent_id, Agent{player, shoot_cooldown, optimal_range, soaking_power, splash_bombs }});
    }
    int width; // Width of the game map
    int height; // Height of the game map
    cin >> width >> height; cin.ignore();
    std::vector<std::pair<int, int>> high_covers;
    std::vector<std::vector<int>> grid;
    for (int i = 0; i < height; i++)
    {
        std::vector<int> row;
        for (int j = 0; j < width; j++)
        {
            int x; // X coordinate, 0 is left edge
            int y; // Y coordinate, 0 is top edge
            int tile_type;
            cin >> x >> y >> tile_type; cin.ignore();
            if (tile_type == 2)
            {
                high_covers.push_back({ x, y });
            }
            row.push_back(tile_type);
        }
        grid.push_back(row);
    }

    std::vector<std::pair<int, int>> corners;
    corners.push_back({ grid[0].size() - 3, grid.size() - 3 });
    corners.push_back({ grid[0].size() - 3, 2});
    corners.push_back({ 2, grid.size() - 3 });
    corners.push_back({ 2, 2 });
    int trapped_player = 0;
    // game loop
    while (1)
    {
        int agent_count; // Total number of agents still in the game
        cin >> agent_count; cin.ignore();
        std::map<int, MyAgent> my_agents;
        std::map<int, MyAgent> enemy_agents;
        for (int i = 0; i < agent_count; i++)
        {
            int agent_id;
            int x;
            int y;
            int cooldown; // Number of turns before this agent can shoot
            int splash_bombs;
            int wetness; // Damage (0-100) this agent has taken
            cin >> agent_id >> x >> y >> cooldown >> splash_bombs >> wetness; cin.ignore();
            if (agents[agent_id].player == my_id)
            {
                my_agents.insert({ agent_id, MyAgent{x , y, cooldown, splash_bombs, wetness }});
            }
            else
            {
                enemy_agents.insert({ agent_id, MyAgent{x , y, cooldown, splash_bombs, wetness }});
            }
        }
        int my_agent_count; // Number of alive agents controlled by you
        cin >> my_agent_count; cin.ignore();

        std::cerr << grid.size() << std::endl;

        for (const auto& my_agent : my_agents)
        {
            std::pair<int, int> throw_destination = { 0, 0 };
            int shortest_corner_distance = std::numeric_limits<int>::max();
            for (const auto& corner : corners)
            {
                int corner_distance = std::sqrt((corner.first - my_agent.second.x) * (corner.first - my_agent.second.x) +
                    (corner.second - my_agent.second.y) * (corner.second - my_agent.second.y));
                if (corner_distance < shortest_corner_distance)
                {
                    throw_destination = corner;
                    shortest_corner_distance = corner_distance;
                }
            }
            
            int throw_distance = shortest_corner_distance;
            std::cerr << "throw_x = " << throw_destination.first << endl;
            std::cerr << "throw_y = " << throw_destination.second << endl;
            std::cerr << "my_x = " << my_agent.second.x << endl;
            std::cerr << "my_y = " << my_agent.second.y << endl;
            if ((abs(throw_destination.first - my_agent.second.x) <= 3 && throw_destination.second == my_agent.second.y)  ||
                (abs(throw_destination.second - my_agent.second.y) <= 3 && throw_destination.first == my_agent.second.x) ||
                throw_distance <= 2)
            {
                if (trapped_player == 0)
                {
                    corners.erase(remove_if(corners.begin(), corners.end(), [throw_destination](const auto& corner)
                    {
                        return corner == throw_destination;
                    }), corners.end());
                    trapped_player  = my_agent.first;
                }

                if (my_agent.first != trapped_player)
                {
                    corners.erase(remove_if(corners.begin(), corners.end(), [throw_destination](const auto& corner)
                    {
                        return corner == throw_destination;
                    }), corners.end());
                    cout << my_agent.first << "; THROW " << throw_destination.first << " " << throw_destination.second;
                }
                else
                {
                    cout << my_agent.first << "; MOVE " << throw_destination.first << " " << throw_destination.second;
                }
            }
            else
            {
                if (throw_destination.first >= 6)
                {
                    throw_destination.first -= 3;
                }
                else
                {
                    throw_destination.first += 3;
                }
                cout << my_agent.first << "; MOVE " << throw_destination.first << " " << throw_destination.second;
            }
            cout << endl;
        }
    }
}