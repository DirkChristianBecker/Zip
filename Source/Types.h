#pragma once


#include <string>
#include <filesystem>
#include <vector>
namespace Zip
{
	using String = std::string;
	using Path = std::filesystem::path;
	template<typename T> using Vector = std::vector<T>;
	using Size = size_t;
	using UInt = uint32_t;
}