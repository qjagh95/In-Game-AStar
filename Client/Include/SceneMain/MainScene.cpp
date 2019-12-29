#include "ClientHeader.h"
#include "MainScene.h"
#include "StartScene.h"
#include "GameObject.h"

#include "Thread.h"
#include "ThreadManager.h"

#include "Scene/Scene.h"
#include "scene/Layer.h"

#include "Component/Component_Base.h"
#include "Component/ColliderPixel_Com.h"
#include "Component/Button_Com.h"
#include "Component/UICon_Com.h"
#include "Component/IconSlot_Com.h"
#include "Component/Stage2D_Com.h"
#include "Component/Tile2D_Com.h"
#include "Component/CheckBox_Com.h"
#include "Component/BackColor_Com.h"

#include "../UserComponent/Player_Com.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

bool MainScene::Init()
{
	Camera_Com* mainCamera = m_Scene->GetMainCamera();
	mainCamera->SetCameraType(CT_ORTHO);
	mainCamera->SetNear(0.0f);

	KeyInput::Get()->SetShowCursor(false);

	Layer* BackLayer = m_Scene->FindLayer("BackGround");
	Layer* Default = m_Scene->FindLayer("Default");
	Layer* UILayer = m_Scene->FindLayer("UI");
	Layer* TileLayer = m_Scene->FindLayer("Tile");

	GameObject* BackObject = GameObject::CreateObject("BackObject", BackLayer);
	BackColor_Com* BackCom = BackObject->AddComponent<BackColor_Com>("BackColor");

	Vector4 A = ExcelManager::Get()->ReadVector4Data("BackColor", 0, 0);
	BackCom->SetBackColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f));

	SAFE_RELEASE(BackCom);
	SAFE_RELEASE(BackObject);

	GameObject*	pStageObj = GameObject::CreateObject("StageObj", TileLayer);
	Stage2D_Com* pStage = pStageObj->AddComponent<Stage2D_Com>("Stage");
	//pStage->CreateTileMap(100, 100, Vector3::Zero, Vector3(160.0f, 80.0f, 1.0f), STT_ISO);
	BineryRead Reader("AStartTile.tInfo");
	pStage->Load(Reader);
	pStage->SetLineOn(true);

	GameObject* PlayerObject = GameObject::CreateObject("Player", Default);
	Player_Com* player_Com = PlayerObject->AddComponent<Player_Com>("Player_Com");
	player_Com->SetStage(pStage);
	player_Com->GetTransform()->SetWorldPos(Vector3(100.0f, 100.0f, 0.0f));
	SAFE_RELEASE(player_Com);

	mainCamera->SetTarget(PlayerObject);
	SAFE_RELEASE(mainCamera);
	SAFE_RELEASE(PlayerObject);

	SAFE_RELEASE(pStage);
	SAFE_RELEASE(pStageObj);
	SAFE_RELEASE(Default);
	SAFE_RELEASE(UILayer);
	SAFE_RELEASE(TileLayer);
	SAFE_RELEASE(BackLayer);

	return true;
}

int MainScene::Input(float DeltaTime)
{

	return 0;
}

int MainScene::Update(float DeltaTime)
{
	return 0;
}

int MainScene::LateUpdate(float DeltaTime)
{
	return 0;
}

void MainScene::Collision(float DeltaTime)
{
}

void MainScene::CollisionLateUpdate(float DeltaTime)
{
}

void MainScene::Render(float DeltaTime)
{
}