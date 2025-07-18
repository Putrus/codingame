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

        for (const auto& my_agent : my_agents)
        {
            int shoot_agent_id = 0;
            int lowest_cover = std::numeric_limits<int>::max();
            int distance = std::numeric_limits<int>::max();
            for (const auto& enemy_agent : enemy_agents)
            {
                if (abs(enemy_agent.second.x - my_agent.second.x) > 4)
                {
                    continue;
                }
                int d = std::sqrt((enemy_agent.second.x - my_agent.second.x) * (enemy_agent.second.x - my_agent.second.x) -
                    (enemy_agent.second.y - my_agent.second.y) * (enemy_agent.second.y - my_agent.second.y));
                if (enemy_agent.second.x < my_agent.second.x)
                {
                    if (grid[enemy_agent.second.y][enemy_agent.second.x + 1] < lowest_cover ||
                        (grid[enemy_agent.second.y][enemy_agent.second.x + 1] == lowest_cover && d < distance))
                    {
                        shoot_agent_id = enemy_agent.first;
                        lowest_cover = grid[enemy_agent.second.y][enemy_agent.second.x + 1];
                        distance = d;
                    }
                }
                else
                {
                    if (grid[enemy_agent.second.y][enemy_agent.second.x - 1] < lowest_cover ||
                        (grid[enemy_agent.second.y][enemy_agent.second.x - 1] == lowest_cover && d < distance))
                    {
                        shoot_agent_id = enemy_agent.first;
                        lowest_cover = grid[enemy_agent.second.y][enemy_agent.second.x - 1];
                        distance = d;
                    }
                }
            }
            int move_x = 0;
            int move_y = 0;
            distance = std::numeric_limits<int>::max();
            for (const auto& cover : high_covers)
            {
                int d = std::sqrt((cover.first - my_agent.second.x) * (cover.first - my_agent.second.x) -
                    (cover.second - my_agent.second.y) * (cover.second - my_agent.second.y));
                if (d < distance)
                {
                    move_x = cover.first;
                    move_y = cover.second;
                    distance = d;
                }
            }
            cout << my_agent.first << "; MOVE " << move_x << " " << move_y << "; SHOOT " << shoot_agent_id << endl; 
        }
    }
}