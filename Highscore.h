#pragma once
#include <string>
#include <vector>
#include <raylib.h>


class HighscoreManager
{
public:
	struct HighscoreEntry
	{
		std::string name;
		int score;
	};

	static constexpr uint8_t NAME_MAX_LENGTH = 9;
	static constexpr auto HIGHSCORE_FILE_PATH = "highscore.txt";

	static constexpr bool IsValidHighscoreInput(int key)
	{
		return key >= 32 && key <= 125;
	}

	std::vector<HighscoreEntry> entries{};

	bool entering_new_highscore = false;
	std::string enter_name = "";
	int score_from_game;

	Rectangle textBox = { 600, 500, 225, 50 };

	HighscoreManager();

	void Enter(int score);
	
	bool ScoreMakesTheList(int score) const noexcept;

	void InsertNewHighscore(const std::string& name, int score);

	void NewHighscoreInput();

	void RenderNameEntry() const;

	void RenderList() const;

	bool LoadHighscoresFromDisk();
	
	void ReadEntryFromLine(std::string line);

	void SaveHighscoresToDisk() const;
};