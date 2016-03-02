#include "components/Transform.h"

#include "math/Quaternion.h"

namespace CS418
{
	Transform::Transform(const std::string &type) : GameComponent(type)
	{

	}

	Transform::~Transform()
	{
		
	}

	void Transform::Initialize()
	{
		Position = VECTOR3F(0.0f, 0.0f, 0.0f);
		Rotation = Quaternion();
		Scale = VECTOR3F(1.0f, 1.0f, 1.0f);

		m_worldMat = MatrixIdentity();
	}

	void Transform::Initialize(const VECTOR3F &position, const Quaternion &rotation, const VECTOR3F &scale)
	{
		Position = position;
		Rotation = rotation;
		Scale = scale;

		CreateWorldMatrix();
	}

	const Matrix & Transform::CreateWorldMatrix()
	{
		Vector vTrans(Position);
		Vector vScale(Scale);

		Matrix mTrans = MatrixTranslation(vTrans);
		Matrix mScale = MatrixScaling(vScale);
		Matrix mRot = MatrixRotationQuaternion(Rotation);

		m_worldMat = mTrans * mRot * mScale;
		
		return m_worldMat;
	}

	const Matrix & Transform::GetWorldMatrix()const
	{
		return m_worldMat;
	}
}