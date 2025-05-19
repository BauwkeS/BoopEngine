#pragma once  
#include "../../BoopEngine/Boop/Components/Component.h" 
#include <string>

namespace boop {  
class GameObject;  
}  

class TankGun : public boop::Component  
{  
public:  
	TankGun(boop::GameObject* owner, const std::string spritePath);

	void FixedUpdate() override;  
	void Update() override;  
	void Render() const override;  
};
