#pragma once
#include <memory>
#include <vector>
#include <functional>
#include "../Components/Component.h"
#include "../GameObject.h"
#include "glm/vec2.hpp"

namespace boop
{

    class GameObjectType
    {
    private:
        std::vector<std::function<std::unique_ptr<Component>(GameObject*)>> m_ComponentFactories;
        std::vector<std::unique_ptr<GameObjectType>> m_ChildTypes;
        std::string m_DefaultTag;
        bool m_DefaultPersistent;
        bool m_CanScale{ true };

    public:
        GameObjectType() = default;

        template <typename T, typename... Args>
        GameObjectType& AddComponent(Args&&... args)
        {
            m_ComponentFactories.emplace_back(
                [args...](GameObject* owner) {
                    return std::make_unique<T>(owner, args...);
                });
            return *this;
        }

        GameObjectType& AddChildType(std::unique_ptr<GameObjectType> childType)
        {
            m_ChildTypes.emplace_back(std::move(childType));
            return *this;
        }

        GameObjectType& SetDefaultTag(const std::string tag)
        {
			m_DefaultTag = tag;
            return *this;
        }
		bool GetCanScale() const
		{
			return m_CanScale;
		}

        GameObjectType& TurnScalingOff()
        {
            m_CanScale = false;
            return *this;
        }

        std::unique_ptr<GameObject> Instantiate() const {
            auto obj = std::make_unique<GameObject>();
            //obj->SetLocalPosition(m_DefaultLocalPosition);
            obj->SetTag(m_DefaultTag);
            obj->SetPersistent(m_DefaultPersistent);

            // Create all components
            for (const auto& factory : m_ComponentFactories)
            {
                auto component = factory(obj.get());
                // Ensure the component is actually added to the GameObject
                if (component) {
                    obj->AddComponent(std::move(component)); 
                }
            }

            // Temporary storage for children
            std::vector<std::unique_ptr<GameObject>> tempChildren;

             // Instantiate children first
            for (const auto& childType : m_ChildTypes) {
                tempChildren.emplace_back(childType->Instantiate());
            }

            // Then set parent (which will transfer ownership)
            for (auto& child : tempChildren) {
                // Release ownership temporarily
                GameObject* rawChild = child.release();
                rawChild->SetParent(obj.get(), false);

                // Ownership is now with parent's m_pChildren
                // through AddChild() which uses emplace_back
            }

            return obj;
        }
    };
}