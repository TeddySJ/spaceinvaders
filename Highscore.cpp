#include "Highscore.h"
#include "raylib.h"
#include <fstream>
#include <iostream>
#include <filesystem>

HighscoreManager::HighscoreManager(int score)
	: score_from_game{ score }
{
	if (!LoadHighscoresFromDisk())
	{
		entries = { {"Empty", 0}, {"Empty", 0}, {"Empty", 0}, {"Empty", 0}, {"Empty", 0} };
	}

	CheckScore();
}

void HighscoreManager::CheckScore()
{
	entering_new_highscore = ScoreMakesTheList(score_from_game);
}

bool HighscoreManager::ScoreMakesTheList(int score) const noexcept
{
	return score > entries.back().score;
}

void HighscoreManager::RenderList() const
{
	DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);

	DrawText("LEADERBOARD", 50, 100, 40, YELLOW);

	for (int i = 0; i < entries.size(); i++)
	{
		DrawText(entries[i].name.data(), 50, 140 + (i * 40), 40, YELLOW);
		DrawText(TextFormat("%i", entries[i].score), 350, 140 + (i * 40), 40, YELLOW); // TODO: Use std::format
	}
}

bool HighscoreManager::LoadHighscoresFromDisk()
{
	if (!std::filesystem::exists(HIGHSCORE_FILE_PATH))
	{
		return false;
	}

	std::ifstream file{ HIGHSCORE_FILE_PATH };

	if (!file)
	{
		return false;
	}

	std::string line;

	while (std::getline(file, line)) 
	{
		ReadEntryFromLine(line);
	}

	return true;
}

void HighscoreManager::ReadEntryFromLine(std::string line)
{
	size_t comma = line.find(',');
	if (comma != std::string::npos)
	{
		entries.emplace_back(line.substr(0, comma), std::stoi(line.substr(comma + 1)));
	}
}

void HighscoreManager::SaveHighscoresToDisk() const
{
	std::ofstream file{ HIGHSCORE_FILE_PATH };

	if (!file)
	{
		throw std::exception(); // TODO: Improve exception
	}

	for (const auto& entry : entries) 
	{
		file << entry.name << ',' << entry.score << '\n';
	}
}

void HighscoreManager::InsertNewHighscore(const std::string& name, int score)
{
	auto insertPos = std::find_if(entries.begin(), entries.end(),
		[score](const auto& entry) { return score > entry.score; });

	if (insertPos != entries.end())
	{
		entries.emplace(insertPos, name, score);
	}

	while (entries.size() > 5)
		entries.pop_back();

	SaveHighscoresToDisk();
}

void HighscoreManager::NewHighscoreInput()
{
	while (int key = GetCharPressed())
	{
		if (HighscoreManager::IsValidHighscoreInput(key) && enter_name.length() < HighscoreManager::NAME_MAX_LENGTH)
		{
			enter_name += (char)key;
		}
	}

	if (IsKeyPressed(KEY_BACKSPACE) && enter_name.length() > 0)
	{
		enter_name = enter_name.substr(0, enter_name.length() - 1);
	}

	if (enter_name.length() > 0 && IsKeyReleased(KEY_ENTER))
	{
		InsertNewHighscore(enter_name, score_from_game);
		entering_new_highscore = false;
	}

}

void HighscoreManager::RenderNameEntry() const
{
	DrawText("NEW HIGHSCORE!", 600, 300, 60, YELLOW);

	DrawRectangleRec(textBox, LIGHTGRAY);
	DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

	DrawText(enter_name.data(), (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
	DrawText(TextFormat("INPUT CHARS: %i/%i", enter_name.length(), HighscoreManager::NAME_MAX_LENGTH), 600, 600, 20, YELLOW);

	if (enter_name.length() > 0)
	{
		DrawText("PRESS ENTER TO CONTINUE", 600, 800, 40, YELLOW);
	}

}
