#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

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
	m_objects.emplace_back(std::move(object));
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

