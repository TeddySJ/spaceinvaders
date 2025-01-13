#pragma once
#include <string>
#include <vector>
#include <raylib.h>


class HighscoreManager final
{
public:
	struct HighscoreEntry
	{
		std::string name;
		size_t score;
	};


	explicit HighscoreManager(size_t score);

	void InsertNewHighscore(const std::string& name, size_t score);

	void NewHighscoreInput();

	void RenderList() const;

	void RenderNameInput() const;

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
	size_t score_from_game;

	Rectangle text_box_background = { 600, 500, 225, 50 };

	bool LoadHighscoresFromDisk();

	void ReadEntryFromLine(const std::string& line);

	void SaveHighscoresToDisk() const;

	[[nodiscard]] bool ScoreMakesTheList(size_t score) const noexcept;

};