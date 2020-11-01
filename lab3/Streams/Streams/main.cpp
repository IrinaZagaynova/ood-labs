#include "OutputStreamDecorator.h"
#include "InputStreamDecorator.h"
#include "CompressOutputStream.h"
#include "DecompressInputStream.h"
#include "EncryptOutputStream.h"
#include "DecryptInputStream.h"
#include "FileOutputStream.h"
#include "FileInputStream.h"
#include <iostream>
#include <string>

const std::string COMPRESS = "--compress";
const std::string DECOMPRESS = "--decompress";
const std::string ENCRYPT = "--encrypt";
const std::string DECRYPT = "--decrypt";

struct OptionArg
{
	std::string name;
	int key;
};

void CopyToFile(std::unique_ptr<IInputDataStream>& input, std::unique_ptr<IOutputDataStream>& output)
{
	while (!input->IsEOF())
	{
		try
		{
			output->WriteByte(input->ReadByte());
		}
		catch (const std::exception&) 
		{
		}
	};
}

std::unique_ptr<IInputDataStream> DecorateInputStream(std::unique_ptr<IInputDataStream>&& input, std::vector<OptionArg> const& inputStreamOptions)
{
	for (auto it = inputStreamOptions.rbegin(); it != inputStreamOptions.rend(); it++)
	{
		if (it->name == DECRYPT)
		{
			input = std::make_unique<CDecryptInputStream>(move(input), it->key);
		}
		else if (it->name == DECOMPRESS)
		{
			input = std::make_unique<CDecompressInputStream>(move(input));
		}
	}
	return move(input);
}

std::unique_ptr<IOutputDataStream> DecorateOutputStream(std::unique_ptr<IOutputDataStream>&& output, std::vector<OptionArg> const& outputStreamOptions)
{
	for (size_t i = 0; i < outputStreamOptions.size(); i++)
	{
		if (outputStreamOptions[i].name == ENCRYPT)
		{
			output = std::make_unique<CEncryptOutputStream>(move(output), outputStreamOptions[i].key);
		}
		else if (outputStreamOptions[i].name == COMPRESS)
		{
			output = std::make_unique<CCompressOutputStream>(move(output));
		}
	}
	return move(output);
}

void OptionsHandler(int argc, char* argv[])
{
	std::unique_ptr<IInputDataStream> input = std::make_unique<CFileInputStream>(argv[argc - 2]);
	std::unique_ptr<IOutputDataStream> output = std::make_unique<CFileOutputStream>(argv[argc - 1]);

	std::vector<OptionArg> inputStreamOptions;
	std::vector<OptionArg> outputStreamOptions;

	for (int i = 1; i < argc - 2; i++)
	{
		if (argv[i] == COMPRESS)
		{
			outputStreamOptions.push_back({argv[i], 0});
		}
		else if (argv[i] == DECOMPRESS)
		{
			inputStreamOptions.push_back({ argv[i], 0 });
		}
		else if (argv[i] == ENCRYPT)
		{
			outputStreamOptions.push_back({ argv[i], std::stoi(argv[++i]) });

		}
		else if (argv[i] == DECRYPT)
		{
			inputStreamOptions.push_back({ argv[i], std::stoi(argv[++i]) });	
		}
		else
		{
			throw std::invalid_argument(std::string(argv[i]) + " - invalid option\n");
		}
	}

	input = DecorateInputStream(move(input), inputStreamOptions);
	output = DecorateOutputStream(move(output), outputStreamOptions);

	CopyToFile(input, output);
}

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		std::cout << "Invalid arguments count\n"
			<< "Usage: streams.exe <options> <input file name> <output file name>\n";
		return 1;
	}

	try
	{
		OptionsHandler(argc, argv);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}

	return 0;
}