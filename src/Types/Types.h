#pragma once

#include <string>
#include "SimpleMath.h"

typedef DirectX::XMFLOAT4 Vertex;

typedef DirectX::XMFLOAT4 Color;

class Id {
 private:
	const std::wstring _id;
 public:
	explicit Id(const std::wstring&& id) : _id(id) { };
	explicit Id(const std::wstring& id) : _id(id) { };
	[[nodiscard]] std::wstring Get() const { return _id; };
	Id(const Id&& id)  noexcept : _id(std::move(id.Get())) { };
	Id(const Id& id) : _id(std::move(id.Get())) { };
	bool operator== (const Id& b) const { return this->_id == b._id; };
	bool operator< (const Id& rhs) const { return this->_id < rhs._id; };
};