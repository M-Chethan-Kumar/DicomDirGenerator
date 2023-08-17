#pragma once
#include <dicom.h>
#include <filesystem>

class Generator
{
public:
	Generator(const int& stduyCount, const int& seriesCount);
	void create() const;

private:
	std::vector<std::filesystem::path> dicomFileList() const;
	std::vector<Dicom::Merge::Message> generateMessages(const int& studyIndex) const;
	static std::filesystem::path getExecutingDirectory();
	void animateProgress(const int& count) const;

	std::filesystem::path _inputPath;
	std::filesystem::path _outputPath;
	int _studyCount;
	int _seriesCount;
};