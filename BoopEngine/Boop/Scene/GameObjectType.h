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
                /*if (component) {
                    obj->m_pComponents.emplace_back(std::move(component));
                }*/
                if (component) {
                    obj->AddComponent(std::move(component)); 
                }
            }

             //Instantiate all children
            for (const auto& childType : m_ChildTypes)
            {
                auto child = childType->Instantiate();
                child->SetParent(obj.get(), false);
            }

            return obj;
        }
    };
}