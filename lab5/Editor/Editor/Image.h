#pragma once
#include "IImage.h"
#include "ResizeImageCommand.h"

const int MAX_IMAGE_SIZE = 1000;
const int MIN_IMAGE_SIZE = 1;

class CImage : public IImage
{
public:
	CImage(std::unique_ptr<ICommandSink>&& commandSink, const Path& path, int width, int height)
		: m_commandSink(move(commandSink))
	{
		if (width > MAX_IMAGE_SIZE || height > MAX_IMAGE_SIZE || width < MIN_IMAGE_SIZE || height < MIN_IMAGE_SIZE)
		{
			throw std::invalid_argument("invalid image sizes\n");
		}

		m_width = width;
		m_height = height;

		if (!exists(path))
		{
			throw std::invalid_argument("given path doesn't exists\n");
		}

		char buffer[L_tmpnam];              
		tmpnam(buffer);
		m_path = std::filesystem::temp_directory_path() / (buffer + path.extension().string());
		std::filesystem::copy_file(path, m_path);
	}

	~CImage()
	{
		size_t count = 0;
		while (std::filesystem::exists(m_path) && count < 3)
		{
			try
			{
				std::filesystem::remove(m_path);
				break;
			}
			catch (const std::exception&)
			{
			}
			count++;
		}
	}

	Path GetPath() const override
	{
		return m_path;
	}

	int GetWidth() const override
	{
		return m_width;
	}

	int GetHeight() const override
	{
		return m_height;
	}

	void Resize(int width, int height) override
	{
		m_commandSink->SaveCommand(move(std::make_unique<CResizeImageCommand>(m_width, m_height, width, height)));
	}

private:

	std::unique_ptr<ICommandSink> m_commandSink;
	Path m_path;
	int m_width, m_height;
};