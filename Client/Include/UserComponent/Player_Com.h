#pragma once
#include "UserComponent/UserComponent_Base.h"

#include "Component/Animation2D_Com.h"
#include "Component/Collider_Com.h"
#include <Component/Stage2D_Com.h>

JEONG_USING
class Player_Com : public UserComponent_Base
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	Player_Com* Clone() override;

	void SetStage(Stage2D_Com* stage) { m_Stage = stage; }
	Stage2D_Com* GetStage() const { return m_Stage; }

private:
	bool isCharge;
	bool isAlive;
	float ScaleVar;
	GameObject* BaseBullet;
	Animation2D_Com* myAnimation;
	Stage2D_Com* m_Stage;
	list<Vector3> m_Path;
	list<Tile2D_Com*> m_Path2;

protected:
	Player_Com();
	Player_Com(const Player_Com& userCom);
	~Player_Com();

public:
	friend class GameObject;
};

