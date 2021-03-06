#pragma once
#include "Component_Base.h"
#include "Tile2D_Com.h"

JEONG_BEGIN

class GameObject;
class Transform_Com;
class Tile2D_Com;
class JEONG_DLL Stage2D_Com : public Component_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	Stage2D_Com* Clone() override;
	void AfterClone() override;
	void Save(BineryWrite& Writer) override;
	void Load(BineryRead& Reader) override;

	void SetStageTileType(STAGE2D_TILE_TYPE TileType) { m_TileType = TileType; }
	STAGE2D_TILE_TYPE GetStageTileType() const { return m_TileType; }
	void SetTileOption(const Vector3& Pos, TILE2D_OPTION option);
	void SetNoMoveMesh(const Vector3& Pos, STAGE2D_TILE_TYPE TileType);
	void SetMoveMesh(const Vector3& Pos, STAGE2D_TILE_TYPE TileType);

	Tile2D_Com* GetTile2D(const Vector3& Pos);
	Tile2D_Com* GetTile2D(float X, float Y, float Z);
	Tile2D_Com* GetTile2DIndex(int Idx);
	Vector3 GetTileScale() const { return m_TileScale; }
	int GetTileXCount() const { return m_TileCountX; }
	int GetTileYCount() const { return m_TileCountY; }

	int GetTileIndex(const Vector3& Pos);
	int GetRectTileIndex(const Vector3& Pos);
	int GetIsoTileIndex(const Vector3& Pos);
	Vector2 GetIsoTileIndexVec(const Vector3& Pos);
	void SetLineOn(bool Value);

	void CreateTileMap(int TileCountX, int TileCountY, const Vector3& StartPos, const Vector3& TileScale, STAGE2D_TILE_TYPE tileType, const string& KeyName = "", const TCHAR* FileName = NULLPTR, const string& PathKey = TEXTURE_PATH);
	list<Vector3>* GetPathList(const Vector3& StartPos, const Vector3& EndPos);

private:
	void CreateTile(const Vector3& StartPos, const Vector3& TileScale, const string& KeyName = "", const TCHAR* FileName = NULLPTR,	const string& PathKey = TEXTURE_PATH);
	void CreateIsoTile(const Vector3& StartPos, const Vector3& TileScale, const string& KeyName = "", const TCHAR* FileName = NULLPTR, const string& PathKey = TEXTURE_PATH);

	bool CheckCloseList(Tile2D_Com* tile);
	bool CheckOpenList(Tile2D_Com* tile);

	void Finish(Tile2D_Com* StartTile, Tile2D_Com* EndTile);
	static bool MySort(const Tile2D_Com* Src, const Tile2D_Com* Dest)
	{
		return Src->GetF() < Dest->GetF();
	}

private:
	GameObject** m_vecTileObject;
	Tile2D_Com** m_vecTile2DCom;

	int m_TileObjectCapacity;
	int m_TileObjectSize;
	int m_Tile2DComCapacity;
	int m_Tile2DComSize;

	int m_TileCountX; //���ΰ���
	int m_TileCountY; //���ΰ���

	STAGE2D_TILE_TYPE m_TileType;

	Vector3 m_TileScale;
	Vector3 m_StartPos;

	bool m_isLineOn;
	int	m_StartX;
	int	m_StartY;
	int	m_EndX;
	int	m_EndY;

	list<Vector3> m_PathList;
	list<Tile2D_Com*> m_OpenList;
	set<Tile2D_Com*> m_CloseList;

protected:
	Stage2D_Com();
	Stage2D_Com(const Stage2D_Com& CopyData);
	~Stage2D_Com();

public:
	friend class GameObject;
};

JEONG_END

