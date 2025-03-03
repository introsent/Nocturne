#pragma once
#include "GameObject.h"

namespace dae
{
    class Component
    {
    public:
        virtual void Update(float deltaTime); // Overridden in derived components
        virtual void Render() const {} // Overridden in derived components
        virtual void RenderUI() {};

        virtual ~Component() = default;

        Component(const Component& other) = delete;
        Component(Component&& other) = delete;
        Component& operator= (const Component& other) = delete;
        Component& operator= (Component&& other) = delete;

    protected:
        explicit Component(GameObject* owner) : m_pOwner(owner) {}

        GameObject* GetOwner() const { return m_pOwner; }

    private:
        GameObject* m_pOwner; 
    };
}
