#pragma once

#include "Behaviour.h"

#include "math/Matrix.h"
#include "graphics/Viewport.h"
#include "SkyboxComponent.h"

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

		virtual void SetSkybox(SkyboxComponent * pSkybox);
		SkyboxComponent * GetSkybox()const;

	private:
		Matrix buildMatrix()const;
		void setTransform(Matrix &view, const Vector &position);

	private:
		Matrix m_proj;

		F32 m_FOV;
		Viewport m_vp;

		SkyboxComponent * m_pSkybox;

		friend class Renderer;
	};
}