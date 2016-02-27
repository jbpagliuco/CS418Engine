#include "components/CameraComponent.h"

namespace CS418
{
	CameraComponent::CameraComponent(const std::string &type) : Behaviour(type)
	{
		Enabled = true;
	}

	CameraComponent::~CameraComponent()
	{

	}

	void CameraComponent::Initialize(const Vector &position, const Vector &target, const Vector &up, F32 fieldOfView, Viewport vp)
	{
		m_view = MatrixLookAtLH(position, target, up);
		m_proj = MatrixPerspectiveFOVLH(fieldOfView, (vp.Width - vp.TopLeftX) / (vp.Height - vp.TopLeftY), vp.MinDepth, vp.MaxDepth);

		m_FOV = fieldOfView;
		m_vp = vp;
	}

	void CameraComponent::SetViewMatrix(const Vector &position, const Vector &target, const Vector& up)
	{
		m_view = MatrixLookAtLH(position, target, up);
	}

	void CameraComponent::SetProjection(F32 fieldOfView, Viewport vp)
	{
		m_proj = MatrixPerspectiveFOVLH(fieldOfView, (vp.Width - vp.TopLeftX) / (vp.Height - vp.TopLeftY), vp.MinDepth, vp.MaxDepth);

		m_FOV = fieldOfView;
		m_vp = vp;
	}

	void CameraComponent::Resize(U32 width, U32 height)
	{
		m_vp.Width = width;
		m_vp.Height = height;

		SetProjection(m_FOV, m_vp);
	}

	Matrix CameraComponent::buildMatrix()const
	{
		return m_proj * m_view;
	}

	Viewport CameraComponent::GetViewport()const
	{
		return m_vp;
	}
}