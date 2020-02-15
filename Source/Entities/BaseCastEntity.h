#pragma once

#include "PrimitiveEntity.h"
#include "DynamicModel.h"
#include <array>

namespace Freeking
{
	class DynamicModel;
	class Texture2D;
	class Shader;

	class BaseCastEntity : public PrimitiveEntity
	{
	public:

		BaseCastEntity();

		virtual void Initialize() override;
		virtual void Tick(double dt) override;
		virtual void PostTick() override;
		virtual void PreRender(bool translucent) override;
		virtual void RenderOpaque() override;

		virtual void Trace(const Vector3f& start, const Vector3f& end, const Vector3f& mins, const Vector3f& maxs, TraceResult& trace, const BspContentFlags& brushMask) override;

	protected:

		virtual bool SetProperty(const EntityProperty& property) override;

		std::string _modelFolder;
		std::array<std::string, 3> _skinFolder;
		std::array<std::string, 3> _artSkins;

	private:

		std::vector<std::shared_ptr<DynamicModel>> _meshes;
		std::vector<std::shared_ptr<Texture2D>> _meshTextures;
		std::shared_ptr<Shader> _shader;

		FrameAnimator _animator;
	};
}
