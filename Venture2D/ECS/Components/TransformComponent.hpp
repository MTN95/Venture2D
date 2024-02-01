#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include "../Entity.hpp"
#include "../IComponent.hpp"
#include "../../Util/Log.hpp"

namespace venture
{
	class TransformComponent : public IComponent
	{
	public:

		TransformComponent();
		TransformComponent(glm::vec2 position);
		TransformComponent(glm::vec2 position, float rotation);
		TransformComponent(glm::vec2 position, float rotation, glm::vec2 scale);
		
		TransformComponent(const TransformComponent& other);
		TransformComponent(TransformComponent&& other) noexcept;

		~TransformComponent() override;


		TransformComponent& operator=( const TransformComponent& other );
		TransformComponent& operator=( TransformComponent&& other ) noexcept;


		void Update(float deltaTime) override;

		void SetPosition(const glm::vec2& newPosition) { mPosition = newPosition; }
		void SetRotation(float newRotation) { mRotation = newRotation; }
		void SetScale(const glm::vec2& newScale) { mScale = newScale; }
		
		void SetDefaultPosition(const glm::vec2& newPosition) { mDefaultPosition = newPosition; }
		void SetDefaultRotation(float newRotation) { mDefaultRotation = newRotation; }
		void SetDefaultScale(const glm::vec2& newScale) { mDefaultScale = newScale; }
		
		void ResetPosition()	{ mPosition = mDefaultPosition; }
		void ResetRotation()	{ mRotation = mDefaultRotation; }
		void ResetScale()		{ mScale = mDefaultScale; }

		const glm::vec2& GetPosition() const { return mPosition; }
		const float& GetRotation() const { return mRotation; }
		const glm::vec2& GetScale() const { return mScale; }
		
		void TranslateX(float x) 
		{
			mPosition.x += x;
		}
		
		void TranslateY(float y) 
		{
			mPosition.y += y;
		}
		
		void TranslateXY(float x,float y) 
		{
			mPosition += glm::vec2(x, y);
		}

		void Rotate(float angleRadians) 
		{
			mRotation += angleRadians;
		}

		void ScaleX(float scaleFactor)
		{
			mScale.x *= scaleFactor;
		}
		
		void ScaleY(float scaleFactor)
		{
			mScale.y *= scaleFactor;
		}
		
		void Scale(float scaleFactor) 
		{
			mScale *= scaleFactor;
		}

		const void LogPosition(const char* msg = "")
		{
			LOG_DEBUG("{0} -- (X,Y): ({1},{2})", msg, mPosition.x, mPosition.y);
		}

		std::unique_ptr<IComponent, IComponentDeleter> Clone() const override
		{
			return std::unique_ptr<IComponent, IComponentDeleter>( new TransformComponent( *this ) );
		}

		

	private:
		glm::vec2 mPosition;
		float mRotation;
		glm::vec2 mScale;

		glm::vec2 mDefaultPosition = glm::vec2(0.f,0.f);
		float		mDefaultRotation = 0.f;
		glm::vec2 mDefaultScale = glm::vec2(1.f,1.f);
	};

}