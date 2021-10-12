#pragma once

class GameObject;

class GameSystem
{
public:

	void Init();   //初期化
	void Update(); //更新
	void Draw();   //描画

	void RequestChangeScene(const std::string& name);

	void AddObject(std::shared_ptr<GameObject> spObject)
	{
		if (spObject) { m_spObject.push_back(spObject); }
	}

	void SetCamera(std::shared_ptr<KdCamera> pCamera) { m_spCamera = pCamera; }

	const std::shared_ptr<KdCamera> GetCamera() const;

	const std::list<std::shared_ptr<GameObject>>& GetObjects()
	{
		return m_spObject;
	}

	ResourceFactory& WorkResourceFactory() { return m_resourceFactory; }
	
	void LevelSet(int lev) { level = lev; }

	void enemyHit() { enemyNum--; }

	void SetBuild(std::string tex) { m_setBil = tex; }

	static const float s_worlGravity;
private:
	void Release(); // 解放

	void ChangeScene();

	

	void InitTitle();
	void InitSelect();
	void InitGame();
	void InitResult();

	KdModelWork m_sky; // 空
	DirectX::SimpleMath::Matrix m_skyMat;

	std::shared_ptr<KdCamera> m_spCamera; // カメラ

	//ゲームオブジェクトリスト
	std::list<std::shared_ptr<GameObject>> m_spObject;

	bool m_canShot = false;

	ResourceFactory m_resourceFactory;

	std::shared_ptr<KdTexture> m_spTexture;

	std::string m_nextSceneName = "";
	std::string m_nowScene = "";


	std::string m_setBil = "";


	bool m_isRepuestChangeScene = false;



	bool button = false;
	bool chenge = false;
	
	int level = 0;

	int enemyNum;

//-----------------------------------------------
//特殊な書式（デザインパターン）
	//コンストラクタ
	GameSystem() {}

	//デストラクタ
	~GameSystem() { Release(); }
public:
	static GameSystem& GetInstance()
	{
		static GameSystem instance;
		return instance;
	}
//-----------------------------------------------
};

//GameSystemを呼び出す
#define GameInstance GameSystem::GetInstance()

#define GameResourceFactory GameSystem::GetInstance().WorkResourceFactory()
