#include "stdafx.h"

template <typename Resource, typename Identifier>

void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &filename){
	std::unique_ptr<Resource> resource(new Resource());
	if (resource->loadFromFile(filename)){
		auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
		assert(inserted.second);
	}
	else
		throw std::runtime_error("ResourceHolder::load - failed to load " + filename + "\n");
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &filename, const Parameter &secondParam){
	std::unique_ptr<Resource> resource(new Resource());
	if (resource->loadFromFile(filename, secondParam)){
		auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
		assert(inserted.second);
	}
	else
		throw std::runtime_error("ResourceHolder::load - failed to load " + filename + "\n");
}


template <typename Resource, typename Identifier>
const Resource &ResourceHolder<Resource, Identifier>::get(Identifier id) const{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());
	return *found->second;
}

template <typename Resource, typename Identifier>
Resource &ResourceHolder<Resource, Identifier>::get(Identifier id){
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());
	return *found->second;
}