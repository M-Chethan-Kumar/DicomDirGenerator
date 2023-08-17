#include "generator.h"
#include <chrono>
#include <Shlwapi.h>
#include <thread>
#include <windows.h>

Generator::Generator(const int& stduyCount, const int& seriesCount):
	_studyCount(stduyCount),
	_seriesCount(seriesCount)
{
	const auto path = getExecutingDirectory();
	_inputPath = path / "SampleData" / "Dicom";

	if(!std::filesystem::exists(_inputPath))
		std::cout << "Error : Input data not found : " << _inputPath << std::endl;

	_outputPath = path / "Output";
}

void Generator::create() const
{
	std::filesystem::remove_all(_outputPath);
	auto dicomPath = _outputPath / "DICOM";
	std::filesystem::create_directory(_outputPath);
	std::filesystem::create_directory(dicomPath);

	auto index = 1;
	for(int i = 0; i < _studyCount; i++)
	{
		auto messages = generateMessages(i);
		for (auto& msg : messages)
		{
			const auto file = msg.toFile();
			auto filename = "IM_" + std::to_string(index++);
			file.write(_outputPath / "DICOM" / filename);
		}
	}
	Dicom::Directory directory(_outputPath);
	if(directory.generate())
	{
		std::cout << "\nDicomDir generation successful :" << _outputPath << std::endl;
	}
}

std::vector<std::filesystem::path> Generator::dicomFileList() const
{
	std::vector<std::filesystem::path> dicomFileList;
	for (auto& tempPath : std::filesystem::directory_iterator(_inputPath))
	{
		if (Dicom::Merge::File::isDicom(tempPath.path()))
		{
			dicomFileList.emplace_back(tempPath);
		}
	}

	if(dicomFileList.empty())
		std::cout << "Error : Failed to read  input dicom file."<< std::endl;

	return dicomFileList;
}

std::vector<Dicom::Merge::Message> Generator::generateMessages(const int& studyIndex) const
{
	const auto files = dicomFileList();
	const Dicom::Merge::Application app(L"Generate");

	std::vector<Dicom::Merge::Message> messages;
	for (int index = 0; index < _seriesCount; index++)
	{
		animateProgress((studyIndex * _seriesCount) + index);
		auto dicomFile = Dicom::Merge::File::open(app, files[0]);
		const auto message = dicomFile.toMessage();
		auto msg = message;
		msg.addNSet(MC_ATT_PATIENT_ID, L"PatientId" + std::to_wstring(studyIndex));
		msg.addNSet(MC_ATT_STUDY_ID, L"StudyId" + std::to_wstring(studyIndex));
		msg.addNSet(MC_ATT_STUDY_INSTANCE_UID, L"StudyUid" + std::to_wstring(studyIndex));
		msg.addNSet(MC_ATT_SERIES_INSTANCE_UID, L"SeriesUid" + std::to_wstring(studyIndex)+std::to_wstring(index));
		msg.addNSet(MC_ATT_SERIES_NUMBER, index);
		messages.emplace_back(msg);
	}

	return messages;
}

std::filesystem::path Generator::getExecutingDirectory()
{
	TCHAR executingDir[MAX_PATH];
	::GetModuleFileNameW(nullptr, executingDir, MAX_PATH);
	::PathRemoveFileSpec(executingDir);

	return std::filesystem::path(executingDir);
}

void Generator::animateProgress(const int& count) const
{
	const auto iterations = _studyCount * _seriesCount;
	constexpr auto end = 100;
	auto progress = ((count +1) * 100) / iterations;
	constexpr int maxRadius = 50;

	const int radius = (progress * maxRadius) / end;
	const int spaces = maxRadius - radius;

	std::cout << "\r[";
	for (int j = 0; j < radius; ++j)
	{
		constexpr char fillChar = '#';
		std::cout << fillChar;
	}
	for (int j = 0; j < spaces; ++j)
	{
		constexpr char emptyChar = ' ';
		std::cout << emptyChar;
	}
	std::cout << "] " << (progress) << "/" << end;

	std::this_thread::sleep_for(std::chrono::milliseconds(50));

	
}
