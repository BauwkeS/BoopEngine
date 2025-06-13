#pragma once
#include <memory>
#include "../../BoopEngine/Boop/Event/Observer.h"
#include "../../BoopEngine/Boop/Event/Event.h"
#include <string>
#include "../Highscores.h"
#include "../../BoopEngine/Boop/Input/Command.h"
#include "../../BoopEngine/Boop/Components/TextComponent.h"
#include <span>

class boop::GameObject;

class LevelObserver : public boop::Observer
{
public:
	LevelObserver();
	~LevelObserver() = default;

	void OnNotify(boop::Event event) override;

	//const char(&GetLetters() const)[27] {return m_Letters;}

	std::span<const char> GetLetters() const { return m_Letters; }
	int GetSelectedLetter() const { return m_SelectedLetter; }

	void SetUpEndScreen();
	void SetWinningPlayer();
private:
	void SetEndData();
	void SetWinningScore();

	std::unique_ptr<Highscores> m_Highscores{};
	Highscores::highscoreData m_EndData{};

	//Input stuff
	void MakeInputEndScreen();

	char m_Letters[27] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

	int m_LetterIndexes[3]{0,0,0};
	int m_SelectedLetter{ 0 };
};

class ChangeLetter final : public boop::Command {
private:
	LevelObserver* m_pGameObject;
	int* m_Letters;
	int& m_SelectedLetter;
	bool m_MoveUp;
public:
	ChangeLetter(LevelObserver* component, int* letters, int& letter, bool moveUp)
		: m_pGameObject{ component }, m_Letters{ letters }, m_SelectedLetter{
		letter
	}, m_MoveUp{ moveUp } {
	}
	~ChangeLetter() { m_pGameObject = nullptr;}

	void Execute() override;

	ChangeLetter(const ChangeLetter& other) = delete;
	ChangeLetter(ChangeLetter&& other) = delete;
	ChangeLetter& operator=(const ChangeLetter& other) = delete;
	ChangeLetter& operator=(ChangeLetter&& other) = delete;

};

class ChangeSelection final : public boop::Command {
private:
	int& m_Letterindex;
	bool m_MoveUp;
public:
	ChangeSelection(int& letter, bool moveUp)
		: m_Letterindex{ letter }, m_MoveUp{ moveUp } {
	}
	~ChangeSelection() { }

	void Execute() override;

	ChangeSelection(const ChangeSelection& other) = delete;
	ChangeSelection(ChangeSelection&& other) = delete;
	ChangeSelection& operator=(const ChangeSelection& other) = delete;
	ChangeSelection& operator=(ChangeSelection&& other) = delete;

};


class GoToEndScreen final : public boop::Command {
private:
	LevelObserver* m_pLevelObs;
public:
	GoToEndScreen(LevelObserver* LevelObs) : m_pLevelObs{LevelObs} {
	}
	~GoToEndScreen() {}

	void Execute() override;

	GoToEndScreen(const GoToEndScreen& other) = delete;
	GoToEndScreen(GoToEndScreen&& other) = delete;
	GoToEndScreen& operator=(const GoToEndScreen& other) = delete;
	GoToEndScreen& operator=(GoToEndScreen&& other) = delete;

};
