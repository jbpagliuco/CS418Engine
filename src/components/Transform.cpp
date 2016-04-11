#include "components/Transform.h"

#include "math/Quaternion.h"
#include "util/Memory.h"
#include "util/Convert.h"

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
		Rotation = VECTOR3F(0.0f, 0.0f, 0.0f);
		Scale = VECTOR3F(1.0f, 1.0f, 1.0f);

		m_worldMat = MatrixIdentity();
	}

	void Transform::Initialize(const VECTOR3F &position, const VECTOR3F &rotation, const VECTOR3F &scale)
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

		Quaternion qX = Quaternion(1.0f, 0.0f, 0.0f, Rotation.x);
		Quaternion qY = Quaternion(0.0f, 1.0f, 0.0f, Rotation.y);
		Quaternion qZ = Quaternion(0.0f, 0.0f, 1.0f, Rotation.z);
		Matrix mRot = MatrixRotationQuaternion(qZ * qY * qX);

		m_worldMat = mTrans * mRot * mScale;
		
		return m_worldMat;
	}

	const Matrix & Transform::GetWorldMatrix()const
	{
		return m_worldMat;
	}

	Transform * CreateTransform(std::vector<std::string> arguments)
	{
		void * pAlignedMem = AllocateAligned(sizeof(Transform), 16);
		Transform * pTransform = new(pAlignedMem)Transform();

		pTransform->SetType("Transform");
		if (arguments.size() != 0)
		{
			pTransform->Position = StringToVector3f(arguments[0]);
			pTransform->Rotation = StringToVector3f(arguments[1]);
			pTransform->Scale = StringToVector3f(arguments[2]);
		}

		return pTransform;
	}
}