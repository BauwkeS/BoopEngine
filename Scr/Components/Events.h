#pragma once
#include "../../BoopEngine/Boop/Event/Observer.h"


class PlayerDied final : public boop::Event
{
public:
	PlayerDied() = default;
};

class PlayerHit final : public boop::Event
{
public:
	PlayerHit() = default;
};

class PlayerKillTank final : public boop::Event
{
public:
	PlayerKillTank() = default;
};

class PlayerKillRecognizer final : public boop::Event
{
public:
	PlayerKillRecognizer() = default;
};