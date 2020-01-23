#pragma once

#include "Mesh.h"
#include "EntityLump.h"
#include "TextureSampler.h"
#include "Vector.h"
#include "Quaternion.h"
#include <string>
#include <memory>
#include <charconv>

namespace Freeking
{
	struct BspFile;

	class Map;
	class BrushModel;
	class LightmapNode;
	class LightmapImage;

	class BaseEntity
	{
	public:

		BaseEntity(Map* map) :
			_map(map),
			_position(0),
			_rotation(0, 0, 0, 1)
		{
		}

		virtual ~BaseEntity() {}

		virtual void Initialize() = 0;
		virtual void Tick(double dt)
		{
			_transform = Matrix4x4::Translation(_position) * _rotation.ToMatrix4x4();
		}
		virtual void RenderOpaque(const Matrix4x4& viewProjection, const std::shared_ptr<ShaderProgram>& shader) = 0;
		virtual void RenderTranslucent(const Matrix4x4& viewProjection, const std::shared_ptr<ShaderProgram>& shader) = 0;
		virtual bool SetProperty(const EntityKeyValue& keyValue) = 0;

		inline void SetPosition(const Vector3f& position) { _position = position; }
		inline void SetRotation(const Quaternion& rotation) { _rotation = rotation; }

		inline const Vector3f& GetPosition() const { return _position; }
		inline const Quaternion& GetRotation() const { return _rotation; }
		inline const Matrix4x4& GetTransform() const { return _transform; }

	protected:

		Map* _map;
		Vector3f _position;
		Quaternion _rotation;
		Matrix4x4 _transform;
	};

	class BrushModelEntity : public BaseEntity
	{
	public:

		BrushModelEntity(Map* map) : BaseEntity(map),
			_modelIndex(-1)
		{
		}

		virtual void Initialize() override;

		virtual void Tick(double dt) override
		{
			BaseEntity::Tick(dt);
		}

		virtual void RenderOpaque(const Matrix4x4& viewProjection, const std::shared_ptr<ShaderProgram>& shader) override;
		virtual void RenderTranslucent(const Matrix4x4& viewProjection, const std::shared_ptr<ShaderProgram>& shader) override;

		virtual bool SetProperty(const EntityKeyValue& keyValue) override
		{
			if (keyValue.Key == "model" &&
				!keyValue.Value.empty() &&
				keyValue.Value[0] == '*')
			{
				auto modelName = keyValue.Value.substr(1);
				return std::from_chars(modelName.data(), modelName.data() + modelName.size(), _modelIndex).ec == std::errc();
			}

			return false;
		}

	protected:

		int _modelIndex;
		std::shared_ptr<BrushModel> _model;
	};

	class WorldSpawnEntity : public BrushModelEntity
	{
	public:

		WorldSpawnEntity(Map* map) : BrushModelEntity(map)
		{
		}

		virtual void Initialize() override
		{
			_modelIndex = 0;
			BrushModelEntity::Initialize();
		}
	};

	class RotatingEntity : public BrushModelEntity
	{
	public:

		RotatingEntity(Map* map) : BrushModelEntity(map),
			_speed(0.0f)
		{
		}

		virtual void Tick(double dt) override
		{
			_rotation *= Quaternion::FromDegreeAngles(Vector3f(0, _speed * dt, 0));

			BrushModelEntity::Tick(dt);
		}

		virtual bool SetProperty(const EntityKeyValue& keyValue) override
		{
			if (keyValue.Key == "speed")
			{
				return keyValue.ValueAsFloat(_speed);
			}

			return BrushModelEntity::SetProperty(keyValue);
		}

	private:

		float _speed;
	};

	class DoorRotatingEntity : public BrushModelEntity
	{
	public:

		DoorRotatingEntity(Map* map) : BrushModelEntity(map),
			_speed(100.0f),
			_angle(0.0f),
			_distance(0.0f),
			_time(0.0f)
		{
		}

		virtual void Tick(double dt) override
		{
			BrushModelEntity::Tick(dt);

			_time += (dt * Math::DegreesToRadians(_speed));
			_time = std::fmodf(_time, Math::TWO_PI);

			float t = (std::sinf(_time) + 1.0f) * 0.5f;

			_rotation = Quaternion::FromDegreeAngles(Vector3f(0, _distance * (t * -1.0f), 0));
		}

		virtual bool SetProperty(const EntityKeyValue& keyValue) override
		{
			if (keyValue.Key == "speed")
			{
				return keyValue.ValueAsFloat(_speed);
			}
			else if (keyValue.Key == "distance")
			{
				return keyValue.ValueAsFloat(_distance);
			}
			else if (keyValue.Key == "angle")
			{
				_rotation = Quaternion(0, 0, 0, 1);
				return keyValue.ValueAsFloat(_angle);
			}

			return BrushModelEntity::SetProperty(keyValue);
		}

	private:

		float _speed;
		float _angle;
		float _distance;
		float _time;
	};

	class DoorEntity : public BrushModelEntity
	{
	public:

		DoorEntity(Map* map) : BrushModelEntity(map),
			_speed(100.0f),
			_angle(0.0f),
			_time(0.0f)
		{
		}

		virtual void Initialize() override
		{
			BrushModelEntity::Initialize();
		}

		virtual void Tick(double dt) override;

		virtual bool SetProperty(const EntityKeyValue& keyValue) override
		{
			if (keyValue.Key == "speed")
			{
				return keyValue.ValueAsFloat(_speed);
			}
			else if (keyValue.Key == "angle")
			{
				_rotation = Quaternion(0, 0, 0, 1);
				return keyValue.ValueAsFloat(_angle);
			}

			return BrushModelEntity::SetProperty(keyValue);
		}

	private:

		float _speed;
		float _angle;
		float _time;
		Vector3f _initialPosition;
	};

	class BrushModel
	{
	public:

		void RenderOpaque(const Matrix4x4& viewProjection, const std::shared_ptr<ShaderProgram>& shader);
		void RenderTranslucent(const Matrix4x4& viewProjection, const std::shared_ptr<ShaderProgram>& shader);

		std::map<std::string, std::shared_ptr<BrushMesh>> Meshes;

		Vector3f BoundsMin;
		Vector3f BoundsMax;
		Vector3f Origin;
	};

	class Map
	{
	public:

		Map(const BspFile& bspFile);

		void Tick(double dt);
		void Render(const Matrix4x4& viewProjection);

		const std::vector<EntityLump::EntityDef>& Entities() const { return _entityLump->Entities; }
		const std::shared_ptr<BrushModel>& GetBrushModel(uint32_t index) const { return _models.at(index); }

	private:

		std::vector<std::shared_ptr<BrushModel>> _models;
		std::shared_ptr<Texture2D> _lightmapTexture;
		std::map<std::string, std::shared_ptr<Texture2D>> _textures;
		std::shared_ptr<ShaderProgram> _shader;
		std::unique_ptr<EntityLump> _entityLump;
		std::shared_ptr<TextureSampler> _textureSampler;
		std::shared_ptr<TextureSampler> _lightmapSampler;
		std::vector<std::shared_ptr<BaseEntity>> _entities;
	};
}
