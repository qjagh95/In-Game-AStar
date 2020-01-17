#pragma once
#include "Component_Base.h"

JEONG_BEGIN

class Shader;
class Mesh;
class TileImage_Com;
class JEONG_DLL Tile2D_Com : public Component_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	Tile2D_Com* Clone() override;
	void AfterClone() override;
	void Save(BineryWrite& Writer) override;
	void Load(BineryRead& Reader) override;

	TILE2D_OPTION GetTileOption() const { return m_TileOption; }
	void SetTileOption(TILE2D_OPTION option) { m_TileOption = option; }
	void SetLineOn(bool Value) { m_isLine = Value; }
	void SetTileType(STAGE2D_TILE_TYPE type);
	void SetMesh(const string& KeyName);

	float GetG(const Vector3& StartPos);
	float GetH(const Vector3& EndPos);
	void SetPos(const Vector3& Pos);
	Vector3 GetCenterPos() const { return m_CenterPos; }
	void SettingAdj(int TileXCount, Tile2D_Com** TileList);

private:
	TILE2D_OPTION m_TileOption;
	STAGE2D_TILE_TYPE m_TileType;
	Shader*	m_Shader;
	Mesh* m_Mesh;
	ID3D11InputLayout* m_Layout;
	bool  m_isLine;
	Vector3 m_CenterPos;
	vector<Tile2D_Com*> m_AdjList;

protected:
	Tile2D_Com();
	Tile2D_Com(const Tile2D_Com& CopyData);
	~Tile2D_Com();

public:
	friend class GameObject;
};

JEONG_END