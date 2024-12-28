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


	explicit HighscoreManager(int score);

	void InsertNewHighscore(const std::string& name, int score);

	void NewHighscoreInput();

	void RenderList() const noexcept;

	void RenderNameEntry() const noexcept;

	bool IsInNameEntry() const noexcept;

private:
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

	Rectangle text_box_background = { 600, 500, 225, 50 };

	bool LoadHighscoresFromDisk();

	void ReadEntryFromLine(const std::string& line);

	void SaveHighscoresToDisk() const;

	void CheckScore() noexcept;

	[[nodiscard]] bool ScoreMakesTheList(int score) const noexcept;

};