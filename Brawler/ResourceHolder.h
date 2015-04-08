#pragma once
#include <memory>

namespace Textures{ 
		enum ID{ Player, Landscape, Projectile }; 
	}

template <typename Resource, typename Identifier>
class ResourceHolder{
private:	
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
	
public:
	Resource &get(Identifier id);
	const Resource &get(Identifier id) const;
	void load(Identifier id, const std::string &filename);
	template <typename Parameter>
	void load(Identifier id, const std::string &filename, const Parameter &secondParam);
};

#include "ResourceHolder.inl"