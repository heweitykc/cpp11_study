#include "animation3d.h"
#include "binarytool.h"

Animation3D* Animation3D::create(const std::string &modelPath, const std::string &texturePath, const std::string &animationPath)
{
	auto animation = new Animation3D();
	animation->loadFromObj(modelPath);
	return animation;
}

bool Animation3D::loadFromObj(const std::string& path)
{
	std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);	
	cocos2d::Data meshdata = FileUtils::getInstance()->getDataFromFile(fullPath);
	unsigned int len = meshdata.getSize();
	const unsigned char *rawdata = meshdata.getBytes();
	int pos = 0;
	unsigned int magic = *((int*)rawdata);
	pos += 4;
	
	unsigned int version = *((int*)(rawdata+pos));
	pos += 4;

	unsigned short aniFileLen = *((short*)(rawdata + pos));
	pos += 2;

	pos += aniFileLen;

	unsigned short textureFileLen = *((short*)(rawdata + pos));
	pos += 2;

	pos += textureFileLen;

	unsigned int meshNum = *((int*)(rawdata + pos));
	pos += 4;

	unsigned int i = 0;
	while (i < meshNum){
		MeshHead *meshhead = new MeshHead();
		_meshHeads.push_back(meshhead);
		readMesh(rawdata, pos, meshhead);
		i++;
	}

	unsigned int vertNum = *((int*)(rawdata + pos));
	pos += 4;

	log("magic=%u, ver=%u, meshnum=%u, vertnum=%u", magic, version, meshNum, vertNum);

	i = 0;
	while (i < vertNum){
		Vertex *v = new Vertex();
		v->x = *((float*)(rawdata + pos));
		pos += 4;
		
		v->y = *((float*)(rawdata + pos));
		pos += 4;

		v->z = *((float*)(rawdata + pos));
		pos += 4;

		v->nx = *((float*)(rawdata + pos));
		pos += 4;

		v->ny = *((float*)(rawdata + pos));
		pos += 4;

		v->nz = *((float*)(rawdata + pos));
		pos += 4;

		v->u = *((float*)(rawdata + pos));
		pos += 4;

		v->v = *((float*)(rawdata + pos));
		pos += 4;

		for (int j = 0; j < 4; j++){
			v->bones[j] = *(rawdata + pos);
			pos += 1; //char
		}

		for (int j = 0; j < 4; j++){
			v->weights[j] = *((float*)(rawdata + pos));
			pos += 4;
		}

		_vertices.push_back(v);
		i++;
	}

	unsigned int indicesNum = *((unsigned int*)(rawdata + pos));
	pos += 4;

	i = 0;
	while (i < indicesNum){
		unsigned short indice = *((unsigned short*)(rawdata + pos));
		_indices.push_back(indice);
		pos += 2;
		i++;
	}

	return true;
}

void Animation3D::readMesh(const unsigned char *rawdata, int& pos, MeshHead *meshhead)
{
	unsigned short nameLen = *((short*)(rawdata + pos));
	pos += 2;

	pos += nameLen;

	meshhead->vertexStart = *((int*)(rawdata + pos));
	pos += 4;

	meshhead->vertexCount = *((int*)(rawdata + pos));
	pos += 4;

	meshhead->indexStart = *((int*)(rawdata + pos));
	pos += 4;

	meshhead->indexCount = *((int*)(rawdata + pos));
	pos += 4;
}

void readVertex(const unsigned char *rawdata, int& pos, Vertex *vertex)
{

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