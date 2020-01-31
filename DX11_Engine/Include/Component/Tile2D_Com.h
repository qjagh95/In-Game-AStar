#pragma once
#include "Component_Base.h"

JEONG_BEGIN

class Shader;
class Mesh;
class TileImage_Com;
class Stage2D_Com;
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

	int GetG() { return m_G; }
	int GetH() { return m_H; }
	void SetPos(const Vector3& Pos);
	void SettingAdj(int TileXCount, Tile2D_Com** TileList);
	Vector3 GetCenterPos() const { return m_CenterPos; }
	void SetIndex(int Index) { m_MyIndex = Index; }
	void SetStage(Stage2D_Com* stage) { m_Stage = stage; }
	vector<Tile2D_Com*>* GetAdjList() { return &m_AdjList; }
	void SetF(int F) { m_F = F; }
	int GetF() const { return m_F; }
	void SetG(int G) { m_G = G; }
	void SetH(int H) { m_H = H; }
	void SetParent(Tile2D_Com* parent) { m_Parent = parent; }
	Tile2D_Com* GetParent() const { return m_Parent; }

private:
	TILE2D_OPTION m_TileOption;
	STAGE2D_TILE_TYPE m_TileType;
	Shader*	m_Shader;
	Mesh* m_Mesh;
	ID3D11InputLayout* m_Layout;
	bool  m_isLine;
	Vector3 m_CenterPos;
	vector<Tile2D_Com*> m_AdjList;
	Stage2D_Com* m_Stage;
	int m_MyIndex;
	int m_F;
	int m_G;
	int m_H;
	Tile2D_Com* m_Parent;

protected:
	Tile2D_Com();
	Tile2D_Com(const Tile2D_Com& CopyData);
	~Tile2D_Com();

public:
	friend class GameObject;
};

JEONG_END