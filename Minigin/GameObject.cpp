#include "GameObject.h"
#include <algorithm> // For std::find and std::remove
#include "Component.h"

namespace dae {
    void GameObject::Update(float deltaTime)
    {
        for (auto& component : m_components)
            component->Update(deltaTime);
    }
    void GameObject::Render() const
    {
        for (const auto& component : m_components)
            component->Render();
    }

    // Constructor
    GameObject::GameObject()
        : m_localPosition(0.f, 0.f, 0.f)
        , m_worldPosition(0.f, 0.f, 0.f)
        , m_positionIsDirty(true)
        , m_parent(nullptr)
    {
    }

    // --- PARENTING SYSTEM ---
    void GameObject::SetParent(GameObject* parent, bool keepWorldPosition) {
        if (IsChild(parent) || parent == this || m_parent == parent)
            return;

        if (parent == nullptr)
            SetLocalPosition(GetWorldPosition());
        else {
            if (keepWorldPosition)
                SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
            SetPositionDirty();
        }

        if (m_parent)
            m_parent->RemoveChild(this);

        m_parent = parent;

        if (m_parent)
            m_parent->AddChild(this);
    }

    // --- CHILDREN MANAGEMENT ---
    void GameObject::AddChild(GameObject* child) {
        if (child == nullptr)
            return;
        if (std::find(m_children.begin(), m_children.end(), child) != m_children.end())
            return;
        m_children.push_back(child);
        child->m_parent = this;
    }

    void GameObject::RemoveChild(GameObject* child) {
        auto it = std::remove(m_children.begin(), m_children.end(), child);
        if (it != m_children.end()) {
            m_children.erase(it, m_children.end());
            child->m_parent = nullptr;
        }
    }

    bool GameObject::IsChild(GameObject* potentialChild) const {
        return std::find(m_children.begin(), m_children.end(), potentialChild) != m_children.end();
    }

    // --- TRANSFORM MANAGEMENT ---
    void GameObject::SetLocalPosition(const glm::vec3& pos) {
        m_localPosition = pos;
        SetPositionDirty();
    }

    const glm::vec3& GameObject::GetWorldPosition() {
        if (m_positionIsDirty)
            UpdateWorldPosition();
        return m_worldPosition;
    }

    void GameObject::UpdateWorldPosition() {
        if (m_positionIsDirty) {
            if (m_parent == nullptr)
                m_worldPosition = m_localPosition;
            else
                m_worldPosition = m_parent->GetWorldPosition() + m_localPosition;
        }
        m_positionIsDirty = false;
    }

    void GameObject::SetPositionDirty() {
        m_positionIsDirty = true;
        for (auto child : m_children)
            child->SetPositionDirty();
    }
} 
