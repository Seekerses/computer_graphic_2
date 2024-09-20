#include "AssetManager.h"
#include "StringUtils.h"
#include <fstream>
#include <d3dcommon.h>

std::vector<UINT> SplitStringToUINT(const std::string& str, const std::string& delimiter);

Id AssetManager::LoadMesh(const std::filesystem::path& path)
{
	std::ifstream meshFile;
	meshFile.open(path);
	std::string currentLine;

	// Parsing primitive topology

	std::getline(meshFile, currentLine);
	assert(!currentLine.empty());

	auto primitiveTopology =
		static_cast<D3D_PRIMITIVE_TOPOLOGY>(std::stoi(currentLine));

	std::getline(meshFile, currentLine);
	assert(currentLine.empty());

	// Parsing vertex data

	std::vector<Vertex> vertices;

	std::getline(meshFile, currentLine);
	std::string delimiter = " ";
	while (!currentLine.empty())
	{
		std::vector<std::string> verticesString = split(currentLine, delimiter);
		vertices.push_back( Vertex{DirectX::XMFLOAT4(
			std::stof(verticesString[0]),
			std::stof(verticesString[1]),
			std::stof(verticesString[2]),
			std::stof(verticesString[3]))});
		std::getline(meshFile, currentLine);
	}

	// Parsing index data

	std::getline(meshFile, currentLine);
	std::vector<UINT> indices = SplitStringToUINT(currentLine, delimiter);
	std::getline(meshFile, currentLine);
	assert(currentLine.empty());

	// Parsing stripes

	std::getline(meshFile, currentLine);
	std::vector<UINT> stripes = SplitStringToUINT(currentLine, delimiter);
	std::getline(meshFile, currentLine);
	assert(currentLine.empty());

	// Parsing _offsets

	std::getline(meshFile, currentLine);
	std::vector<UINT> offsets = SplitStringToUINT(currentLine, delimiter);

	auto* meshAsset = new MeshAsset(
		primitiveTopology,
		vertices.data(),
		vertices.size(),
		indices.data(),
		indices.size(),
		stripes,
		offsets);

	Id meshId = Id(path.filename().generic_wstring());
	_meshAssets[meshId] = meshAsset;

	return meshId;
}

std::vector<UINT> SplitStringToUINT(const std::string& str, const std::string& delimiter) {
	std::vector<UINT> values;
	std::vector<std::string> strings = split(str, delimiter);
	std::transform(strings.begin(), strings.end(),
		std::back_inserter(values),
		[](const std::string& str) { return std::stoi(str); } );
	return values;
}

AssetManager* AssetManager::_instance;