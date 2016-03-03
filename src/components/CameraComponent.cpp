#include "components/CameraComponent.h"

#include "game/GameObject.h"

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
		Matrix m = m_pGameObject->GetTransform()->CreateWorldMatrix();
		m.invert(nullptr);
		return m_proj * m;
	}

	Viewport CameraComponent::GetViewport()const
	{
		return m_vp;
	}

	void CameraComponent::setTransform(Matrix &view, const Vector &position)
	{
		view.invert(nullptr);
		m_pGameObject->GetTransform()->Position = view.getColumn(3).asVector3();
		m_pGameObject->GetTransform()->Rotation = Quaternion(view).ToEuler();
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
}