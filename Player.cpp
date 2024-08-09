#include "Player.h"


Player::Player(boop::GameObject* const ownerPtr, const std::string texture, const int cols, const int rows,
	const float frameSec, const int startPicIndex, const int AmountPics, const float scale, boop::Collision* collision)
{
	m_SpriteComp = std::make_unique<boop::SpriteComponent>(ownerPtr, texture, cols, rows, frameSec, startPicIndex, AmountPics, scale, collision);
}
