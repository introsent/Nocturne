#pragma once
#include <memory>
#include <vector>
#include <glm.hpp>

namespace dae {

    class Component;
    class GameObject final {
    public:
        void Update(float deltaTime);
        void Render() const;

        GameObject();
        ~GameObject() = default;

        // --- PARENTING SYSTEM ---
        void SetParent(GameObject* parent, bool keepWorldPosition = false);

        // --- CHILDREN MANAGEMENT ---
        void AddChild(GameObject* child);
        void RemoveChild(GameObject* child);
        bool IsChild(GameObject* potentialChild) const;

        // --- TRANSFORM MANAGEMENT ---
        void SetLocalPosition(const glm::vec3& pos);
        const glm::vec3& GetWorldPosition();
        void UpdateWorldPosition();
        void SetPositionDirty();

        // --- COMPONENT SYSTEM ---
        template <typename ComponentType, typename... Args>
        ComponentType* AddComponent(Args&&... args) {
            auto component = std::make_unique<ComponentType>(std::forward<Args>(args)...);
            ComponentType* ptr = component.get();
            m_components.push_back(std::move(component));
            return ptr;
        }

        template <typename ComponentType>
        ComponentType* GetComponent() {
            for (auto& component : m_components) {
                if (auto castedComponent = dynamic_cast<ComponentType*>(component.get()))
                    return castedComponent;
            }
            return nullptr;
        }

        template <typename ComponentType>
        bool HasComponent() const {
            for (const auto& component : m_components) {
                if (dynamic_cast<ComponentType*>(component.get()))
                    return true;
            }
            return false;
        }

        template <typename ComponentType>
        void RemoveComponent() {
            auto removePosition = std::remove_if(m_components.begin(), m_components.end(),
                [](const std::unique_ptr<Component>& component) {
                    return dynamic_cast<ComponentType*>(component.get()) != nullptr;
                });

            if (removePosition != m_components.end()) {
                m_components.erase(removePosition, m_components.end());
            }
        }

    private:
        glm::vec3 m_localPosition;
        glm::vec3 m_worldPosition;
        bool m_positionIsDirty;

        GameObject* m_parent;
        std::vector<GameObject*> m_children;
        std::vector<std::unique_ptr<Component>> m_components;
    };

} 