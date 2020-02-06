#include "RenderTarget.h"
#include "Texture2D.h"
#include <cassert>
#include <iostream>

namespace Freeking
{
	RenderTarget::RenderTarget(const RenderTargetInitializer& initializer) :
		_width(initializer.width),
		_height(initializer.height)
	{
		glGenFramebuffers(1, &_handle);
		glBindFramebuffer(GL_FRAMEBUFFER, _handle);

		std::vector<GLenum> drawBuffers(initializer.colorAttachments.size());

		for (int i = 0; i < drawBuffers.size(); ++i)
		{
			const auto& attachment = initializer.colorAttachments[i];
			auto attachmentTexture = std::make_unique<Texture2D>(_width, _height, attachment.internalFormat, attachment.format, attachment.type, nullptr);

			GLenum attachmentIndex = GL_COLOR_ATTACHMENT0 + i;
			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentIndex, GL_TEXTURE_2D, attachmentTexture->GetHandle(), 0);
			drawBuffers[i] = attachmentIndex;

			_colorAttachements.push_back(std::move(attachmentTexture));
		}

		{
			const auto& attachment = initializer.depthAttachement;
			auto attachmentTexture = std::make_unique<Texture2D>(_width, _height, attachment.internalFormat, attachment.format, attachment.type, nullptr);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, attachmentTexture->GetHandle(), 0);

			_depthAttachment = std::move(attachmentTexture);
		}

		glDrawBuffers(drawBuffers.size(), drawBuffers.data());
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		switch (status)
		{
		case GL_FRAMEBUFFER_COMPLETE:
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED:
			std::cout << "GL_FRAMEBUFFER_UNSUPPORTED" << std::endl;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			std::cout << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT" << std::endl;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			std::cout << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT" << std::endl;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
			std::cout << "GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT" << std::endl;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
			std::cout << "GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT" << std::endl;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
			std::cout << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER" << std::endl;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
			std::cout << "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER" << std::endl;
			break;
		}

		assert(status == GL_FRAMEBUFFER_COMPLETE);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void RenderTarget::Resolve()
	{
	}

	RenderTarget::~RenderTarget()
	{
		if (_handle)
		{
			glDeleteFramebuffers(1, &_handle);
		}
	}

	void RenderTarget::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _handle);
	}

	void RenderTarget::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	Texture2D* RenderTarget::GetColorAttachment(int index)
	{
		return _colorAttachements[index].get();
	}

	Texture2D* RenderTarget::GetDepthAttachment()
	{
		return _depthAttachment.get();
	}
}
