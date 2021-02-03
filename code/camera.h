#pragma once

#include "application/stdneb.h"
#include "math/mat4.h"
#include "math/vec2.h"
#include "math/polar.h"
#include "math/scalar.h"
#include "imgui.h"
#include "input/inputserver.h"
#include "properties/input.h"

namespace Demo
{

	class Camera
	{
	public:
		void Setup(const Math::point& defaultEyePos, const Math::vector& defaultEyeVec);
		void Reset();
		void MoveTo(Math::point newPos);
		void Update(PlayerInput);
		const Math::mat4& GetTransform() const;
	private:
		Math::point defaultEyePos;
		Math::vector defaultEyeVec;

		Math::polar viewAngles;
		Math::point position;
		Math::point newPosition;
		bool moveComplete = true;
		Math::mat4 transform;

		float rotationSpeed = 0.1f;
		float moveSpeed = 0.1f;
	};

	inline const Math::mat4&
		Camera::GetTransform() const
	{
		return this->transform;
	}
}
