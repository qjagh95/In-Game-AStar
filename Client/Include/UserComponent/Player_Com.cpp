#include "ClientHeader.h"
#include "Player_Com.h"
#include "GameObject.h"
#include "KeyInput.h"

#include "Component/ColliderRect_Com.h"
#include "Component/ColliderCircle_Com.h"
#include "Component/ColliderOBB2D_Com.h"
#include "Component/Transform_Com.h"
#include "Component/Renderer_Com.h"
#include "Component/Material_Com.h"
#include "Component/TitleBar_Com.h"

Player_Com::Player_Com()
	:isCharge(false), isAlive(false), ScaleVar(0.0f), myAnimation(NULLPTR)
{
	m_Stage = NULLPTR;
}

Player_Com::Player_Com(const Player_Com & userCom)
	:UserComponent_Base(userCom)
{
}

Player_Com::~Player_Com()
{
	SAFE_RELEASE(myAnimation);
}

bool Player_Com::Init()
{				   
	KeyInput::Get()->AddKey("MouseClick", VK_RBUTTON);
	KeyInput::Get()->AddKey("ChangeAnimation", VK_SPACE);

	Renderer_Com* RenderComponent = m_Object->AddComponent<Renderer_Com>("PlayerRender");
	RenderComponent->SetMesh("TextureRect");
	RenderComponent->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(RenderComponent);

	Material_Com* MaterialComponent = m_Object->FindComponentFromType<Material_Com>(CT_MATERIAL);
	MaterialComponent->SetDiffuseTexture(0, "Player", TEXT("Player.png"));
	MaterialComponent->SetMaterial(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	SAFE_RELEASE(MaterialComponent);

	m_Transform->SetWorldScale(70.0f, 90.0f, 1.0f);
	m_Transform->SetWorldPivot(0.5f, 0.0f, 0.0f);
	m_Transform->SetWorldPos(0.0f, 0.0f, 1.0f);

	myAnimation = m_Object->AddComponent<Animation2D_Com>("PlayerAnimation");
		
	vector<Clip2DFrame>	vecClipFrame;
	Clip2DFrame	tFrame = {};

	for (int i = 0; i < 2; ++i)
	{
		tFrame.LeftTop = Vector2(0.0f + i * 45.0f, 60.f);
		tFrame.RightBottom = Vector2(45.0f + i * 45.0f, 120.f);
		vecClipFrame.push_back(tFrame);
	}

 	myAnimation->AddClip("Idle", A2D_ATLS, AO_LOOP, 1.0f, vecClipFrame, "Player", L"Player.png");
	vecClipFrame.clear();

	return true;
}

int Player_Com::Input(float DeltaTime)
{
	if (KeyInput::Get()->KeyPress("MoveUp"))
		m_Transform->Move(AXIS_Y, 1000.0f, DeltaTime);
	else if (KeyInput::Get()->KeyPress("MoveDown"))
		m_Transform->Move(AXIS_Y, -1000.0f, DeltaTime);

	else if (KeyInput::Get()->KeyPress("ChangeAnimation"))
		m_Transform->SetWorldPos(0.0f, 0.0f, 0.0f);

	if (KeyInput::Get()->KeyPress("MouseClick"))
	{
		Vector3 ClickPos = KeyInput::Get()->GetMouseWorldPos();
		Vector3 myPos = m_Transform->GetWorldPos();

		m_Path = *m_Stage->GetPathList(myPos, ClickPos);
	}

	if (m_Path.size() != 0)
	{
		Vector3 MovePos = m_Path.back();
		Vector3 myPos = m_Transform->GetWorldPos();

		if (MovePos.GetDistance(myPos) < 10.0f)
			m_Path.pop_back();

		cout << m_Path.size() << endl;
		m_Transform->Move(Vector3::Nomallize(MovePos - myPos), 100.0f, DeltaTime);
	}


	return 0;
}

int Player_Com::Update(float DeltaTime)
{

	return 0;
}

int Player_Com::LateUpdate(float DeltaTime)
{
	return 0;
}

void Player_Com::Collision(float DeltaTime)
{
}

void Player_Com::CollisionLateUpdate(float DeltaTime)
{
}

void Player_Com::Render(float DeltaTime)
{
}

Player_Com * Player_Com::Clone()
{
	return new Player_Com(*this);
}