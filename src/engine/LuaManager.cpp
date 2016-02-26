#include "engine/LuaManager.h"

#include <LuaBridge.h>
using namespace luabridge;

#include "game/GameObject.h"
#include "components/GameComponent.h"
#include "components/Transform.h"

#include "components/Behaviour.h"
#include "components/ScriptComponent.h"
#include "components/CameraComponent.h"

#include "components/RenderingComponent.h"

#include "util/GameTimer.h"
#include "math/Quaternion.h"

namespace CS418
{
	LuaManager::~LuaManager()
	{
		if (m_pLuaState)
			lua_close(m_pLuaState);
	}

	void LuaManager::Initialize()
	{
		m_pLuaState = luaL_newstate();
		luaL_openlibs(m_pLuaState);

		registerClasses();
	}

	void LuaManager::ExecuteFile(const std::string &file)
	{
		if (luaL_loadfile(m_pLuaState, file.c_str()))
		{
			printf("Could not open script: %s\n", file.c_str());
			return;
		}

		if (lua_pcall(m_pLuaState, 0, 0, 0))
		{
			printf("Failed to execute script: %s\n", file.c_str());
			return;
		}
	}

	LuaRef LuaManager::GetGlobal(const std::string name)
	{
		return getGlobal(m_pLuaState, name.c_str());
	}

	void LuaManager::registerClasses()
	{
		getGlobalNamespace(m_pLuaState)
			.beginClass<VECTOR2F>("Vector2f")
				.addConstructor<void(*) (void) >()
				.addData("x", &VECTOR2F::x, true)
				.addData("y", &VECTOR2F::y, true)
			.endClass()
			.beginClass<VECTOR3F>("Vector3f")
				.addConstructor<void(*) (void) >()
				.addData("x", &VECTOR3F::x, true)
				.addData("y", &VECTOR3F::y, true)
				.addData("z", &VECTOR3F::z, true)
			.endClass()
			.beginClass<VECTOR4F>("Vector4f")
				.addConstructor<void(*) (void) >()
				.addData("x", &VECTOR4F::x, true)
				.addData("y", &VECTOR4F::y, true)
				.addData("z", &VECTOR4F::z, true)
				.addData("w", &VECTOR4F::w, true)
			.endClass()
			.beginClass<Vector>("Vector")
				.addConstructor<void (*) (void)>()
				.addConstructor<void (*) (F32)>()
				.addConstructor<void (*) (F32, F32, F32, F32)>()
				.addConstructor<void (*) (VECTOR2F)>()
				.addConstructor<void (*) (VECTOR3F)>()
				.addConstructor<void (*) (VECTOR4F)>()
				.addConstructor<void (*) (const Vector &)>()
				.addFunction("ToVector2f", &Vector::asVector2)
				.addFunction("ToVector3f", &Vector::asVector3)
				.addFunction("ToVector4f", &Vector::asVector4)
				.addProperty("x", &Vector::getX)
				.addProperty("y", &Vector::getY)
				.addProperty("z", &Vector::getZ)
				.addProperty("w", &Vector::getW)
				.addFunction("Add", &Vector::operator+)
				.addFunction("Subtract", &Vector::operator-)
				.addFunction("AbsoluteValue", &Vector::absoluteValue)
				.addFunction("Negate", &Vector::negate)
				.addFunction("Lerp", &Vector::lerp)
				.addFunction("V2Equals", &Vector::v2equals)
				.addFunction("V2NotEquals", &Vector::v2notEquals)
				.addFunction("V2Less", &Vector::v2less)
				.addFunction("V2LessEq", &Vector::v2lessEq)
				.addFunction("V2Greater", &Vector::v2greater)
				.addFunction("V2GreaterEq", &Vector::v2greaterEq)
				.addFunction("V2Dot", &Vector::v2Dot)
				.addFunction("V2Length", &Vector::v2Length)
				.addFunction("V2LengthSq", &Vector::v2LengthSq)
				.addFunction("V2Normalize", &Vector::v2Normalize)
				.addFunction("V2AngleBetween", &Vector::v2AngleBetween)
				.addFunction("V2AngleBetweenNormals", &Vector::v2AngleBetweenNormals)
				.addFunction("V3Equals", &Vector::v3equals)
				.addFunction("V3NotEquals", &Vector::v3notEquals)
				.addFunction("V3Less", &Vector::v3less)
				.addFunction("V3LessEq", &Vector::v3lessEq)
				.addFunction("V3Greater", &Vector::v3greater)
				.addFunction("V3GreaterEq", &Vector::v3greaterEq)
				.addFunction("V3Dot", &Vector::v3Dot)
				.addFunction("V3Length", &Vector::v3Length)
				.addFunction("V3LengthSq", &Vector::v3LengthSq)
				.addFunction("V3Normalize", &Vector::v3Normalize)
				.addFunction("V3AngleBetween", &Vector::v3AngleBetween)
				.addFunction("V3AngleBetweenNormals", &Vector::v3AngleBetweenNormals)
				.addFunction("V4Equals", &Vector::v4equals)
				.addFunction("V4NotEquals", &Vector::v4notEquals)
				.addFunction("V4Less", &Vector::v4less)
				.addFunction("V4LessEq", &Vector::v4lessEq)
				.addFunction("V4Greater", &Vector::v4greater)
				.addFunction("V4GreaterEq", &Vector::v4greaterEq)
				.addFunction("V4Dot", &Vector::v4Dot)
				.addFunction("V4Length", &Vector::v4Length)
				.addFunction("V4LengthSq", &Vector::v4LengthSq)
				.addFunction("V4Normalize", &Vector::v4Normalize)
				.addFunction("V4AngleBetween", &Vector::v4AngleBetween)
				.addFunction("V4AngleBetweenNormals", &Vector::v4AngleBetweenNormals)
			.endClass();
		
			getGlobalNamespace(m_pLuaState)
				.beginClass<Matrix>("Matrix")
					.addConstructor<void(*) (void)>()
					.addConstructor<void(*) (F32[16])>()
					.addConstructor<void(*) (const Vector &, const Vector &, const Vector &, const Vector &)>()
					.addConstructor<void(*) (const Matrix &)>()
					.addFunction("Equals", &Matrix::equals)
					.addFunction("NotEquals", &Matrix::notEquals)
					.addFunction("Less", &Matrix::less)
					.addFunction("LessEq", &Matrix::lessEq)
					.addFunction("Greater", &Matrix::greater)
					.addFunction("GreaterEq", &Matrix::greaterEq)
					.addFunction("GetElement", &Matrix::operator())
					.addFunction("Add", &Matrix::operator+)
					.addFunction("Subtract", &Matrix::operator-)
					.addFunction("MultiplyMatrix", &Matrix::Lua_MultiplyMatrix)
					.addFunction("MultiplyVector", &Matrix::Lua_MultiplyVector)
					.addFunction("MultiplyScalar", &Matrix::Lua_MultiplyScalar)
					.addFunction("Invert", &Matrix::invert)
					.addFunction("Determinant", &Matrix::determinant)
					.addFunction("Transpose", &Matrix::transpose)
				.endClass()
				.addFunction("MatrixIdentity", &MatrixIdentity)
				.addFunction("MatrixLookAtLH", &MatrixLookAtLH)
				.addFunction("MatrixPerspectiveFOVLH", &MatrixPerspectiveFOVLH)
				.addFunction("MatrixTranslation", &MatrixTranslation)
				.addFunction("MatrixScaling", &MatrixScaling)
				.addFunction("MatrixRotationX", &MatrixRotationX)
				.addFunction("MatrixRotationY", &MatrixRotationY)
				.addFunction("MatrixRotationZ", &MatrixRotationZ)
				.addFunction("MatrixRotationQuaternion", &MatrixRotationQuaternion)
				.addFunction("MatrixRotationEuler", &MatrixRotationEuler);
			
		getGlobalNamespace(m_pLuaState)
			.beginClass<Quaternion>("Quaternion")
				.addConstructor<void (*) (void)>()
				.addConstructor<void (*) (F32, F32, F32, F32)>()
				.addConstructor<void (*) (const VECTOR3F * , F32)>()
				.addConstructor<void (*) (const Matrix &)>()
				.addFunction("Invert", &Quaternion::invert)
				.addFunction("MultiplyQuaternion", &Quaternion::Lua_MultiplyQuaternion)
				.addFunction("MultiplyVector", &Quaternion::Lua_MultiplyVector)
				.addFunction("Lerp", &Quaternion::lerp)
				.addFunction("Slerp", &Quaternion::slerp)
				.addProperty("x", &Quaternion::getX)
				.addProperty("y", &Quaternion::getY)
				.addProperty("z", &Quaternion::getZ)
				.addProperty("w", &Quaternion::getW)
			.endClass();

		getGlobalNamespace(m_pLuaState)
			.beginClass<GameComponent>("GameComponent")
			.endClass()
			.beginClass<GameObject>("GameObject")
				.addFunction("AddComponent", &GameObject::AddComponent)
				.addFunction("RemoveComponent", &GameObject::RemoveComponent)
				.addFunction("GetComponents", &GameObject::GetComponents)

				.addFunction("GetRenderingComponents", &GameObject::Lua_GetComponentsOfType<RenderingComponent>)
				.addFunction("GetScriptComponents", &GameObject::Lua_GetComponentsOfType<ScriptComponent>)

				.addProperty("transform", &GameObject::Lua_GetTransform, &GameObject::Lua_SetTransform)
			.endClass()
			.deriveClass<Transform, GameComponent>("Transform")
				.addData("position", &Transform::Position, true)
				.addData("rotation", &Transform::Rotation, true)
				.addData("scale", &Transform::Scale, true)
			.endClass()
			.deriveClass<Behaviour, GameComponent>("Behaviour")
				.addData("enabled", &Behaviour::Enabled, true)
			.endClass()
			.deriveClass<ScriptComponent, Behaviour>("ScriptComponent")
			.endClass()
			.deriveClass<CameraComponent, Behaviour>("CameraComponent")
			.endClass();

		getGlobalNamespace(m_pLuaState)
			.beginClass<GameTimer>("GameTimer")
				.addProperty("playingTime", &GameTimer::GetPlayingTime)
				.addProperty("totalGameTime", &GameTimer::GetTotalGameTime)
				.addProperty("elapsedTimeSeconds", &GameTimer::GetElapsedTimeInSeconds)
				.addProperty("elapsedTime", &GameTimer::GetElapsedTimeInMillis)
			.endClass();
	}
}