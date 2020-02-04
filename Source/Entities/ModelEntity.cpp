#include "ModelEntity.h"
#include "DynamicModel.h"
#include "Texture2D.h"

namespace Freeking
{
	ModelEntity::ModelEntity() : PrimitiveEntity()
	{
	}

	void ModelEntity::Tick(double dt)
	{
		PrimitiveEntity::Tick(dt);
	}

	void ModelEntity::Initialize()
	{
		PrimitiveEntity::Initialize();

		_shader = Shader::Library.DynamicModel.get();
		_model = DynamicModel::Library.Get(_modelName);

		auto skin = _skinName.empty() ? ((_model && !_model->Skins.empty()) ? _model->Skins[0] : "") : _skinName;
		if (!skin.empty() && skin[0] == '/')
		{
			skin = skin.substr(1);
		}

		if (!skin.empty())
		{
			_texture = Texture2D::Library.Get(skin);
		}
	}

	void ModelEntity::PreRender(bool translucent)
	{
		if (_shader && _model && _texture)
		{
			int frame = 0;

			_shader->SetParameterValue("model", GetTransform());
			_shader->SetParameterValue("delta", 0.0f);
			_shader->SetParameterValue("normalBuffer", DynamicModel::GetNormalBuffer().get());
			_shader->SetParameterValue("diffuse", _texture.get());
			_shader->SetParameterValue("frameVertexBuffer", _model->GetFrameVertexBuffer().get());
			_shader->SetParameterValue("frames[0].index", (int)(frame * _model->GetFrameVertexCount()));
			_shader->SetParameterValue("frames[0].translate", _model->FrameTransforms[frame].translate);
			_shader->SetParameterValue("frames[0].scale", _model->FrameTransforms[frame].scale);
			_shader->SetParameterValue("frames[1].index", (int)(frame * _model->GetFrameVertexCount()));
			_shader->SetParameterValue("frames[1].translate", _model->FrameTransforms[frame].translate);
			_shader->SetParameterValue("frames[1].scale", _model->FrameTransforms[frame].scale);
			_shader->Apply();
		}
	}

	void ModelEntity::RenderOpaque()
	{
		if (_shader && _model && _texture)
		{
			_model->Draw();
		}
	}

	void ModelEntity::RenderTranslucent()
	{
	}

	bool ModelEntity::SetProperty(const EntityProperty& property)
	{
		return PrimitiveEntity::SetProperty(property);
	}
}
