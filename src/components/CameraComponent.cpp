#include "components/CameraComponent.h"

#include "game/GameObject.h"
#include "util/Memory.h"
#include "util/Convert.h"
#include "graphics/GraphicsManager.h"

namespace CS418
{
	CameraComponent::CameraComponent(const std::string &type) : Behaviour(type)
	{
		Enabled = true;
		m_pSkybox = nullptr;
	}

	CameraComponent::~CameraComponent()
	{

	}

	void CameraComponent::Initialize(const Vector &position, const Vector &target, const Vector &up, F32 fieldOfView, Viewport vp)
	{
		Matrix view = MatrixLookAtLH(position, target, up);
		m_proj = MatrixPerspectiveFOVLH(fieldOfView, (vp.Width - vp.TopLeftX) / (vp.Height - vp.TopLeftY), vp.MinDepth, vp.MaxDepth);

		m_FOV = fieldOfView;
		m_vp = vp;

		setTransform(view, position);
	}

	void CameraComponent::SetViewMatrix(const Vector &position, const Vector &target, const Vector& up)
	{
		Matrix view = MatrixLookAtLH(position, target, up);
		setTransform(view, position);
	}

	void CameraComponent::SetProjection(F32 fieldOfView, Viewport vp)
	{
		m_proj = MatrixPerspectiveFOVLH(fieldOfView, (vp.Width - vp.TopLeftX) / (vp.Height - vp.TopLeftY), vp.MinDepth, vp.MaxDepth);

		m_FOV = fieldOfView;
		m_vp = vp;
	}

	void CameraComponent::Resize(U32 width, U32 height)
	{
		m_vp.Width = (F32)width;
		m_vp.Height = (F32)height;

		SetProjection(m_FOV, m_vp);
	}

	Matrix CameraComponent::buildMatrix()const
	{
		return m_proj * viewMatrix();
	}

	Viewport CameraComponent::GetViewport()const
	{
		return m_vp;
	}

	void CameraComponent::setTransform(Matrix &view, const Vector &position)
	{
		view.invert(nullptr);
		m_pGameObject->GetTransform()->Position = view.getColumn(3).asVector3();
		m_pGameObject->GetTransform()->Rotation = QuaternionFromMatrix(view).ToEuler();
		m_pGameObject->GetTransform()->Scale = VECTOR3F(1.0f, 1.0f, 1.0f);
	}

	void CameraComponent::SetSkybox(SkyboxComponent * pSkybox)
	{
		m_pSkybox = pSkybox;
	}

	SkyboxComponent * CameraComponent::GetSkybox()const
	{
		return m_pSkybox;
	}

	Vector CameraComponent::GetForward()const
	{
		return m_pGameObject->GetTransform()->CreateWorldMatrix().getColumn(2);
	}

	Vector CameraComponent::GetUp()const
	{
		return m_pGameObject->GetTransform()->CreateWorldMatrix().getColumn(1);
	}

	Vector CameraComponent::GetRight()const
	{
		return m_pGameObject->GetTransform()->CreateWorldMatrix().getColumn(0);
	}

	Matrix CameraComponent::GetRotationMatrix()const
	{
		Matrix view = viewMatrix();
		return Matrix(view.getColumn(0), view.getColumn(1), view.getColumn(2), Vector(0.0f, 0.0f, 0.0f, 1.0f));
	}

	Matrix CameraComponent::viewMatrix()const
	{
		Matrix m = m_pGameObject->GetTransform()->CreateWorldMatrix();
		m.invert(nullptr);
		return m;
	}

	CameraComponent * CreateCameraComponent(std::vector<std::string> arguments, GraphicsManager * pGM, GameObject * pGO)
	{
		void * pAlignedMem = AllocateAligned(sizeof(CameraComponent), 16);
		CameraComponent * pCC = new(pAlignedMem)CameraComponent();

		pCC->SetGameObject(pGO);

		VECTOR3F position = StringToVector3f(arguments.at(0));
		VECTOR3F target = StringToVector3f(arguments.at(1));
		VECTOR3F up = StringToVector3f(arguments.at(2));

		F32 fov = StringToFloat(arguments.at(3));
		Viewport v = StringToViewport(arguments.at(4), pGM);

		pCC->Initialize(Vector(position), Vector(target), Vector(up), fov, v);
		pCC->Enabled = StringToBoolean(arguments.at(5));

		return pCC;
	}
}