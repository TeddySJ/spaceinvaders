#include "Highscore.h"
#include "raylib.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include "CustomExceptions.h"
#include <string>

HighscoreManager::HighscoreManager(size_t score)
	: score_from_game{ score }
{
	if (!LoadHighscoresFromDisk())
	{
		entries = { {"Empty", 0}, {"Empty", 0}, {"Empty", 0}, {"Empty", 0}, {"Empty", 0} };
	}

	entering_new_highscore = ScoreMakesTheList(score_from_game);
}

bool HighscoreManager::ScoreMakesTheList(size_t score) const noexcept
{
	return score > entries.back().score;
}

void HighscoreManager::RenderList() const
{
	constexpr auto continuetext_pos_x = 600;
	constexpr auto continuetext_pos_y = 200;
	DrawText("PRESS ENTER TO CONTINUE", continuetext_pos_x, continuetext_pos_y, 40, YELLOW);

	constexpr auto leaderboardtext_pos_x = 50;
	constexpr auto leaderboardtext_pos_y = 100;
	DrawText("LEADERBOARD", leaderboardtext_pos_x, leaderboardtext_pos_y, 40, YELLOW);

	constexpr auto leaderboard_name_startpos_x = 50;
	constexpr auto leaderboard_score_startpos_x = 350;
	constexpr auto leaderboard_entry_startpos_y = 140;
	constexpr auto leaderboard_vertical_margin = 40;

	for (int row = 0; const auto& entry : entries)
	{
		DrawText(entry.name.c_str(), leaderboard_name_startpos_x, leaderboard_entry_startpos_y + (row * leaderboard_vertical_margin), 40, YELLOW);
		DrawText(std::to_string(entry.score).c_str(), leaderboard_score_startpos_x, leaderboard_entry_startpos_y + (row * leaderboard_vertical_margin), 40, YELLOW);
		row++;
	}
}

void HighscoreManager::RenderNameInput() const
{
	constexpr auto title_pos_x = 600;
	constexpr auto title_pos_y = 300;
	DrawText("NEW HIGHSCORE!", title_pos_x, title_pos_y, 60, YELLOW);

	DrawRectangleRec(text_box_background, LIGHTGRAY);
	DrawRectangleLines(static_cast<int>(text_box_background.x), static_cast<int>(text_box_background.y), static_cast<int>(text_box_background.width), static_cast<int>(text_box_background.height), DARKGRAY);

	DrawText(enter_name.data(), static_cast<int>(text_box_background.x) + 5, static_cast<int>(text_box_background.y) + 8, 40, MAROON);
	auto s = std::format("INPUT CHARS: {}/{}", enter_name.length(), HighscoreManager::NAME_MAX_LENGTH);
	DrawText(s.c_str(), 600, 600, 20, YELLOW);

	constexpr auto continuetext_pos_x = 600;
	constexpr auto continuetext_pos_y = 800;

	if (enter_name.length() > 0)
	{
		DrawText("PRESS ENTER TO CONTINUE", continuetext_pos_x, continuetext_pos_y, 40, YELLOW);
	}
}

bool HighscoreManager::IsInNameEntry() const noexcept
{
	return entering_new_highscore;
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

void HighscoreManager::ReadEntryFromLine(const std::string& line)
{
	const size_t comma = line.find(',');
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
		throw HighscoreSaveException();
	}

	for (const auto& entry : entries) 
	{
		file << entry.name << ',' << entry.score << '\n';
	}
}

void HighscoreManager::InsertNewHighscore(const std::string& name, size_t score)
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
	while (const int key = GetCharPressed())
	{
		if (HighscoreManager::IsValidHighscoreInput(key) && enter_name.length() < HighscoreManager::NAME_MAX_LENGTH)
		{
			enter_name += static_cast<char>(key);
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
