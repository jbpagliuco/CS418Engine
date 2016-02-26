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

	void CameraComponent::Initialize(const Matrix & view, const Matrix & proj)
	{
		m_view = view;
		m_proj = proj;
	}

	void CameraComponent::Initialize(const Vector &position, const Vector &target, const Vector &up, F32 fieldOfView, Viewport vp)
	{
		m_view = MatrixLookAtLH(position, target, up);
		m_proj = MatrixPerspectiveFOVLH(fieldOfView, (vp.Width - vp.TopLeftX) / (vp.Height - vp.TopLeftY), vp.MinDepth, vp.MaxDepth);

		m_vp = vp;
	}

	void CameraComponent::SetViewMatrix(const Matrix & view)
	{
		m_view = view;
	}

	void CameraComponent::SetViewMatrix(const Vector &position, const Vector &target, const Vector& up)
	{
		m_view = MatrixLookAtLH(position, target, up);
	}

	void CameraComponent::SetProjection(const Matrix & proj)
	{
		m_proj = proj;
	}

	void CameraComponent::SetProjection(F32 fieldOfView, Viewport vp)
	{
		m_proj = MatrixPerspectiveFOVLH(fieldOfView, (vp.Width - vp.TopLeftX) / (vp.Height - vp.TopLeftY), vp.MinDepth, vp.MaxDepth);

		m_vp = vp;
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