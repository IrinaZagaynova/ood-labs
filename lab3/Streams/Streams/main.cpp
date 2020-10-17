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

void ExecuteOptions(int argc, char* argv[])
{
	std::unique_ptr<IInputDataStream> input = std::make_unique<CFileInputStream>(argv[argc - 2]);
	std::unique_ptr<IOutputDataStream> output = std::make_unique<CFileOutputStream>(argv[argc - 1]);

	for (int i = 1; i < argc - 2; i++)
	{
		if (argv[i] == COMPRESS)
		{
			output = std::make_unique<CCompressOutputStream>(move(output));
		}
		else if (argv[i] == DECOMPRESS)
		{
			input = std::make_unique<CDecompressInputStream>(move(input));
		}
		else if (argv[i] == ENCRYPT)
		{
			output = std::make_unique<CEncryptOutputStream>(move(output), std::stoi(argv[++i]));
		}
		else if (argv[i] == DECRYPT)
		{
			input = std::make_unique<CDecryptInputStream>(move(input), std::stoi(argv[++i]));
		}
		else
		{
			throw std::invalid_argument(std::string(argv[i]) + " - invalid option");
		}
	}

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
		ExecuteOptions(argc, argv);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}

	return 0;
}