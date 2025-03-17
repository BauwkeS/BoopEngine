#pragma once
#include <memory>
#include "../../BoopEngine/Boop/Components/TextComponent.h"
#include "../../BoopEngine/Boop/Event/Subject.h"
namespace booble {
	class ScoreObserver : public boop::TextComponent, public boop::Observer
	{
	public:
		ScoreObserver(boop::GameObject* owner);
		~ScoreObserver() = default;
		void OnNotify(boop::Event& event) override;
	private:
		int m_Score{};
	};
}