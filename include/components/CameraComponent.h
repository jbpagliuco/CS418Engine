#pragma once

#include "Behaviour.h"

#include "math/Matrix.h"
#include "graphics/Viewport.h"

namespace CS418
{
	class CameraComponent : public Behaviour
	{
	public:
		CameraComponent(const std::string &type = "CameraComponent");
		virtual ~CameraComponent();

		virtual void Initialize(const Vector &position, const Vector &target, const Vector &up, F32 fieldOfView, Viewport vp);

		virtual void SetViewMatrix(const Vector &position, const Vector &target, const Vector& up);
		virtual void SetProjection(F32 fieldOfView, Viewport vp);

		virtual Viewport GetViewport()const;

		virtual void Resize(U32 width, U32 height);

	private:
		Matrix buildMatrix()const;

	private:
		Matrix m_view;
		Matrix m_proj;

		F32 m_FOV;
		Viewport m_vp;

		friend class Renderer;
	};
}