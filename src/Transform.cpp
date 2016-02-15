#include "Transform.h"

namespace CS418
{
	Transform::Transform(std::string name) : GameComponent(name)
	{

	}

	Transform::~Transform()
	{
		
	}

	void Transform::Initialize()
	{
		Position = VECTOR3F(0.0f, 0.0f, 0.0f);
		Rotation = VECTOR3F(0.0f, 0.0f, 0.0f);
		Scale = VECTOR3F(1.0f, 1.0f, 1.0f);

		m_worldMat = MatrixIdentity();
	}

	void Transform::Initialize(const VECTOR3F &position, const VECTOR3F &rotation, const VECTOR3F &scale)
	{
		Position = position;
		Rotation = rotation;
		Scale = scale;

		createWorldMatrix();
	}

	const Matrix & Transform::createWorldMatrix()
	{
		Vector vTrans(Position);
		Vector vScale(Scale);

		Matrix mTrans = MatrixTranslation(vTrans);
		Matrix mRot = MatrixRotationEuler(Rotation.x, Rotation.y, Rotation.z);
		Matrix mScale = MatrixScaling(vScale);

		m_worldMat = mScale * mRot * mTrans;
		
		return m_worldMat;
	}

	const Matrix & Transform::getWorldMatrix()const
	{
		return m_worldMat;
	}

	std::string Transform::GetType()const
	{ 
		return "Transform"; 
	}
}