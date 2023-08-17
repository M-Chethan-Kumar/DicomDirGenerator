#pragma once
#include <filesystem>

class Generator
{
public:
	Generator();
	void create();

private:
	std::filesystem::path _path;
};