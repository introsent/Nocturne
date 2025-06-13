#include "Scene.h"
#include "GameObject.h"

#include <algorithm>
#include "TextureComponent.h"
#include "TextComponent.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject> object)
{
    m_pendingAdds.emplace_back(std::move(object));
}

void Scene::Remove(std::unique_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_clearRequested = true;
}

void Scene::Update(float deltaTime) {
    // Handle deferred clear first
    if (m_clearRequested) {
        m_objects.clear();
        m_clearRequested = false;
        return; // Skip updating this frame
    }

    // Existing update loop
    for (auto it = m_objects.begin(); it != m_objects.end(); ) {
        if ((*it)->IsMarkedForDestroy()) {
            it = m_objects.erase(it);
        }
        else {
            (*it)->Update(deltaTime);
            ++it;
        }
    }

    if (!m_pendingAdds.empty()) {
        for (auto& obj : m_pendingAdds) {
            m_objects.emplace_back(std::move(obj));
        }
        m_pendingAdds.clear();
    }
}

void Scene::Render() const {
    // Collect all renderable components with their game objects
    std::vector<std::pair<float, const GameObject*>> renderables;

    for (const auto& object : m_objects) {
        if (auto textureComp = object->GetComponent<TextureComponent>()) {
            renderables.emplace_back(textureComp->GetDepth(), object.get());
        }
    }

    // Sort by depth (lowest depth first)
    std::sort(renderables.begin(), renderables.end(),
        [](const auto& a, const auto& b) {
            return a.first < b.first;
        });

    // Render in sorted order
    for (const auto& [depth, object] : renderables) {
        object->Render();
    }

    // Render UI on top
    for (const auto& object : m_objects) {
        if (auto textComp = object->GetComponent<TextComponent>())
        {
            textComp->Render();
        }
    }
}

void dae::Scene::RenderUI()
{
	for (const auto& object : m_objects)
	{
		object->RenderUI();
	}
}

