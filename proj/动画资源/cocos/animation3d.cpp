#include "animation3d.h"

Animation3D* Animation3D::create(const std::string &modelPath, const std::string &texturePath, const std::string &animationPath)
{
	auto sprite = new Animation3D();
	sprite->loadFromObj(modelPath);
	return sprite;
}

bool Animation3D::loadFromObj(const std::string& path)
{
	std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);	
	cocos2d::Data meshdata = FileUtils::getInstance()->getDataFromFile(fullPath);
	const unsigned char *rawdata = meshdata.getBytes();



	std::vector<float> v;
	std::vector<float> vn;
	std::vector<float> vt;
	std::vector<std::vector<vertex_index> > faceGroup;




	return true;
}

void Animation3D::setBlendFunc(const BlendFunc &blendFunc)
{
	if (_blend.src != blendFunc.src || _blend.dst != blendFunc.dst)
	{
		_blend = blendFunc;
	}
}

const BlendFunc& Animation3D::getBlendFunc() const
{
	return _blend;
}