#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

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
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int x; // X coordinate, 0 is left edge
            int y; // Y coordinate, 0 is top edge
            int tile_type;
            cin >> x >> y >> tile_type; cin.ignore();
        }
    }

    // game loop
    while (1)
    {
        int agent_count; // Total number of agents still in the game
        cin >> agent_count; cin.ignore();
        std::map<int, MyAgent> my_agents;
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
        }
        int my_agent_count; // Number of alive agents controlled by you
        cin >> my_agent_count; cin.ignore();

        for (auto my_agent : my_agents)
        {
            cout << my_agent.first << "; MOVE 6 1" << endl; 
        }
    }
}