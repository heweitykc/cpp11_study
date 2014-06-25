#ifndef  _ANIMATION_3D_H_
#define  _ANIMATION_3D_H_

#include "cocos2d.h"

USING_NS_CC;

struct MeshHead
{
	char name[1024];
	unsigned int vertexStart;
	unsigned int vertexCount;
	unsigned int indexStart;
	unsigned int indexCount;
};

struct Vertex{
	float x , y , z;
	float nx , ny , nz;
	float u, v;
	int bones[4];
	float weights[4];
};

class Animation3D : public Node, public BlendProtocol
{
public:
	static void readMesh(const unsigned char *rawdata, int& pos, MeshHead *meshhead);

	static Animation3D* create(const std::string &modelPath, const std::string &texturePath, const std::string &animationPath);

	~Animation3D();

	bool Animation3D::loadFromObj(const std::string& path);	
	void setTexture(const std::string& texFile);

	virtual void setBlendFunc(const BlendFunc &blendFunc) override;
	virtual const BlendFunc &getBlendFunc() const override;
private:
	Mesh              *_mesh;
	MeshCommand        _meshCommand;
	BlendFunc		  _blend;

	Texture2D*				_texture;
	std::vector<MeshHead*>	_meshHeads;

	std::vector<Vertex*>	_vertices;			//��������
	std::vector<unsigned short> _indices;		//��������	
};

#endif