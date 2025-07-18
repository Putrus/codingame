#include <iostream>
#include <string>
#include <vector>

struct Score
{
    int timestamp;
    int points;
    int team;
};

std::vector<std::string> split(std::string s, const std::string& delimiter)
{
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
}

void addScores(std::vector<Score>& scores, const std::string& team_scores, int team)
{
    std::vector<std::string> splitted_scores = split(team_scores, ",");

    int points[4] = { 5, 2, 3, 3 };
    for (int i = 0; i < splitted_scores.size(); ++i)
    {
        std::vector<std::string> timestamps_str = split(splitted_scores[i], " ");
        for (std::string timestamp_str : timestamps_str)
        {
            if (timestamp_str.empty())
            {
                continue;
            }
            int timestamp = std::stoi(timestamp_str);
            scores.push_back(Score{ timestamp, points[i], team });
        }
    }
    std::sort(scores.begin(), scores.end(),
        [](const Score& lhs, const Score& rhs)
        {
            return lhs.timestamp < rhs.timestamp;
        });
}

int main()
{
    std::string teams_str;
    getline(std::cin, teams_str);
    std::string scores_str_1;
    getline(std::cin, scores_str_1);
    std::string scores_str_2;
    getline(std::cin, scores_str_2);

    std::string teams[2];
    teams[0] = teams_str.substr(0, teams_str.find(','));
    teams[1] = teams_str.substr(teams_str.find(',') + 1);
    std::vector<Score> scores;
    addScores(scores, scores_str_1, 0);
    addScores(scores, scores_str_2, 1);
    //match ends after 80 minutes
    scores.push_back(Score{ 81, 0, 0 });
    int team_minutes_advantage[2] = { 0, 0 };
    int team_points[2] = { 0, 0 };
    int last_timestamp = 0;
    for (int i = 0; i < scores.size() - 1; ++i)
    {
        int current_timestamp = scores[i].timestamp;
        int next_timestamp = scores[i + 1].timestamp;
        team_points[scores[i].team] += scores[i].points;
        if (team_points[0] > team_points[1])
        {
            team_minutes_advantage[0] += next_timestamp - current_timestamp;
        }
        else if (team_points[1] > team_points[0])
        {
            team_minutes_advantage[1] += next_timestamp - current_timestamp;
        }
    }

    for (int i = 0; i < 2; i++)
    {
        std::cout << teams[i] << ": " << team_points[i] << " " << team_minutes_advantage[i] << std::endl;
    }
    
}