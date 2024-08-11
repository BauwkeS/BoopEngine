#include "Scene.h"
#include "../GameObject.h"

#include <algorithm>
#include "../Components/SpriteComponent.h"

using namespace boop;

unsigned int Scene::m_idCounter = 0;

boop::Scene::Scene():
	m_name{"DefaultName"}
{
}

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() {};

void Scene::Add(std::unique_ptr<GameObject> object)
{
	//m_objects.emplace_back(std::move(object));
	GameObject* gameObjectPtr = object.get();
	m_objects.emplace_back(std::move(object));

	// Update the tag map
	if (!gameObjectPtr->GetTag().empty()) {
	//	m_taggedObjects[gameObjectPtr->GetTag()] = gameObjectPtr;
		m_taggedObjects.insert(std::make_pair(gameObjectPtr->GetTag(), gameObjectPtr));
	}
}

void Scene::Remove(std::unique_ptr<GameObject> object)
{
	//m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
	auto it = std::find_if(m_objects.begin(), m_objects.end(), 
        [&object](const std::unique_ptr<GameObject>& elem) {
            return elem.get() == object.get(); // Compare raw pointers
        });

    if (it != m_objects.end())
    {
        m_objects.erase(it);
    }
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void boop::Scene::FixedUpdate(float deltaTime)
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate(deltaTime);
	}
	
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_objects)
	{
		object->Update(deltaTime);
	}
}

void boop::Scene::LateUpdate(float deltaTime)
{
	for (auto& object : m_objects)
	{
		object->LateUpdate(deltaTime);
	}
	
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		
		object->Render();
	}
}

std::string Scene::GetName() const
{
	return m_name;
}

std::vector<std::unique_ptr<GameObject>>& Scene::GetObjects()
{
	return m_objects;
}

GameObject* Scene::FindGameObjectByTag(const std::string& tag) const
{
	auto it = m_taggedObjects.find(tag);
	if (it != m_taggedObjects.end()) {
		return it->second;
	}
	return nullptr;
}

std::vector<GameObject*> Scene::FindAllGameObjectByTag(const std::string& tag) const
{
	std::vector<GameObject*> toReturnVec{};
	//auto found = m_taggedObjects.equal_range(tag);

	////auto range = map.equal_range(1);
	//for (auto it = found.first; it != found.second; ++it)
	//{
	//	toReturnVec.emplace_back(it->second);
	//}

	for(auto obj : m_taggedObjects)
	{
		if (obj.first == tag)
		{
			toReturnVec.emplace_back(obj.second);
		}
	}

	return toReturnVec;
}


