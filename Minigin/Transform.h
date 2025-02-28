#pragma once
#include <glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		// --- POSITION ---
		const glm::vec3& GetLocalPosition() const { return m_localPosition; }
		const glm::vec3& GetWorldPosition() const { return m_worldPosition; }

		void SetLocalPosition(float x, float y, float z)
		{
			m_localPosition = { x, y, z };
			UpdateWorldTransform(); // Apply changes
		}

		void SetWorldPosition(float x, float y, float z)
		{
			m_worldPosition = { x, y, z };
			// If we have a parent, calculate new local position
			if (m_parentTransform)
			{
				m_localPosition = m_worldPosition - m_parentTransform->GetWorldPosition();
			}
		}

		// --- PARENTING SYSTEM ---
		void SetParentTransform(const Transform& parentTransform)
		{
			m_parentTransform = &parentTransform;

			// Convert current world position to local relative to new parent
			m_localPosition = m_worldPosition - parentTransform.GetWorldPosition();

			// Update the world transform using the new parent
			UpdateWorldTransform();
		}

		void ClearParent()
		{
			m_parentTransform = nullptr;
		}

	private:
		glm::vec3 m_localPosition{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_worldPosition{ 0.0f, 0.0f, 0.0f };

		const Transform* m_parentTransform = nullptr;

		void UpdateWorldTransform()
		{
			if (m_parentTransform)
			{
				m_worldPosition = m_parentTransform->GetWorldPosition() + m_localPosition;
			}
			else
			{
				m_worldPosition = m_localPosition;
			}
		}
	};
}

