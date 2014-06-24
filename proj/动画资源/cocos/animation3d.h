#ifndef  _ANIMATION_3D_H_
#define  _ANIMATION_3D_H_

#include "cocos2d.h"

USING_NS_CC;

struct vertex_index
{
	int v_idx, vt_idx, vn_idx;
	vertex_index() {};
	vertex_index(int idx) : v_idx(idx), vt_idx(idx), vn_idx(idx) {};
	vertex_index(int vidx, int vtidx, int vnidx) : v_idx(vidx), vt_idx(vtidx), vn_idx(vnidx) {};

};

class Animation3D : public Node, public BlendProtocol
{
public:
	static Animation3D* create(const std::string &modelPath, const std::string &texturePath, const std::string &animationPath);

	bool Animation3D::loadFromObj(const std::string& path);

	virtual void setBlendFunc(const BlendFunc &blendFunc) override;
	virtual const BlendFunc &getBlendFunc() const override;
private:
	Mesh              *_mesh;
	MeshCommand        _meshCommand;
	Texture2D*        _texture;
	BlendFunc		  _blend;
};

#endif