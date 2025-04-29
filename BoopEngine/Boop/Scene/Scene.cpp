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

Scene::~Scene() {}

void Scene::CleanupScene()
{
	// Remove all objects that are marked for deletion
	std::erase_if(m_objects, [](const std::unique_ptr<GameObject>& object) {
		return object->ToDelete();
		});

	//check deletes
	for (auto& object : m_objects)
	{
		if (object->ToDelete()) object->CleanupDeletion();
	}
	UpdateTagMap();
}
void boop::Scene::UpdateTagMap()
{
	// Update the tag map
	m_taggedObjects.clear();
	for (const auto& object : m_objects) {
		if (!object->GetTag().empty()) {
 			m_taggedObjects.insert(std::make_pair(object->GetTag(), object.get()));
		}

		//also set the tags on the children
		for (auto& child : object->GetAllChildren())
		{
			if (!child->GetTag().empty()) {
				m_taggedObjects.insert(std::make_pair(child->GetTag(), child.get()));
			}
		}
	}
}
;

void Scene::Add(std::unique_ptr<GameObject> object, bool isPersistent)
{
	GameObject* gameObjectPtr = object.get();
	m_objects.emplace_back(std::move(object));

	// Set the object as persistent if needed
	if (isPersistent) gameObjectPtr->SetPersistent();

	// Update the tag map
	if (!gameObjectPtr->GetTag().empty()) {
		m_taggedObjects.insert(std::make_pair(gameObjectPtr->GetTag(), gameObjectPtr));
	}

	//also set the tags on the children
	for (auto& child : gameObjectPtr->GetAllChildren())
	{
		if (!child->GetTag().empty()) {
			m_taggedObjects.insert(std::make_pair(child->GetTag(), child.get()));
		}
	}
}

void Scene::Remove(std::unique_ptr<GameObject> object)
{
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

void boop::Scene::FixedUpdate()
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate();
	}
	
}

void Scene::Update()
{
	for(auto& object : m_objects)
	{
		if (object->ToDelete()) continue;
		object->Update();
	}

	CleanupScene();
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

	for(auto obj : m_taggedObjects)
	{
		if (obj.first == tag)
		{
			toReturnVec.emplace_back(obj.second);
		}
	}

	return toReturnVec;
}

std::vector<std::unique_ptr<GameObject>> boop::Scene::GetAllPersistentObjects()
{
	std::vector<std::unique_ptr<GameObject>> persistentObjects;

	for (auto& object : m_objects) {
		if (object->IsPersistent()) {
			persistentObjects.emplace_back(std::move(object));
		}
	}

	m_objects.erase(
		std::remove(
			m_objects.begin(),
			m_objects.end(),
			nullptr
		),
		m_objects.end()
	);

	UpdateTagMap();

	return persistentObjects;
}


