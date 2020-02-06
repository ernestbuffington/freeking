#pragma once

#include <glad/gl.h>
#include <vector>
#include <memory>

namespace Freeking
{
	class Texture2D;

	struct RenderTargetAttachmentInitializer
	{
		GLenum internalFormat;
		GLenum format;
		GLenum type;
	};

	struct RenderTargetInitializer
	{
		int width;
		int height;

		std::vector<RenderTargetAttachmentInitializer> colorAttachments;
		RenderTargetAttachmentInitializer depthAttachement;
	};

	class RenderTarget
	{
	public:

		RenderTarget(const RenderTargetInitializer& initializer);
		~RenderTarget();

		void Bind();
		void Unbind();
		void Resolve();

		Texture2D* GetColorAttachment(int index);
		Texture2D* GetDepthAttachment();

		inline int GetWidth() const { return _width; }
		inline int GetHeight() const { return _height; }

		inline GLuint GetHandle() const { return _handle; }

	private:

		GLuint _handle;
		int _width;
		int _height;
		std::vector<std::unique_ptr<Texture2D>> _colorAttachements;
		std::unique_ptr<Texture2D> _depthAttachment;
	};
}
