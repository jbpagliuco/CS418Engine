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

		virtual void Initialize(const Matrix &view, const Matrix &proj);
		virtual void Initialize(const Vector &position, const Vector &target, const Vector &up, F32 fieldOfView, Viewport vp);

		virtual void SetViewMatrix(const Matrix & view);
		virtual void SetViewMatrix(const Vector &position, const Vector &target, const Vector& up);
		virtual void SetProjection(const Matrix & proj);
		virtual void SetProjection(F32 fieldOfView, Viewport vp);

		virtual Viewport GetViewport()const;

	private:
		Matrix buildMatrix()const;

	private:
		Matrix m_view;
		Matrix m_proj;

		Viewport m_vp;

		friend class Renderer;
	};
}