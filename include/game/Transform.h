#pragma once

#include "GameComponent.h"
#include "math/Vector.h"
#include "math/Matrix.h"

namespace CS418
{
	class Transform : public GameComponent
	{
	public:
		Transform();
		virtual ~Transform();

		// Initializes this transform to location (0, 0, 0), no rotation, and no scale.
		virtual void Initialize();
		// Initializes this transform.
		// - position: Position of this transform in world space.
		// - rotation: Rotation of this tranform.
		// - scale: Scale of this transform.
		virtual void Initialize(const VECTOR3F &position, const VECTOR3F &rotation, const VECTOR3F &scale);

		const Matrix & CreateWorldMatrix();
		const Matrix & GetWorldMatrix()const;

	public:
		VECTOR3F Position;
		VECTOR3F Rotation;
		VECTOR3F Scale;

	private:
		Matrix m_worldMat;
	};
}