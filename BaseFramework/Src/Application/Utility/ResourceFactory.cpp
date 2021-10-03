#include "ResourceFactory.h"

const std::shared_ptr<KdModelData> ResourceFactory::GetModelData(const std::string& filename)
{
	//filenameのモデルがすでにあるか
	//std::unordered_map<std::string, std::shared_ptr<KdModelData>>::iterator foundItr = m_modelMap.find(filename);

	//型推論
	auto foundItr = m_modelMap.find(filename);

	//モデルデータがすでに１つ以上あったら
	if (foundItr != m_modelMap.end())
	{
		//見つけたデータを返す
		return (*foundItr).second;
	}

	//モデルデータが１つもないとき
	std::shared_ptr<KdModelData>newModelData = std::make_shared<KdModelData>();

	//モデルの読み込み
	if (newModelData->Load(filename))
	{
		//リストに追加
		m_modelMap.insert(std::pair<std::string,std::shared_ptr<KdModelData>>(filename,newModelData));

		return m_modelMap[filename];
	}

	std::string errorMsg = "ResourceFactory::GetModelData() Failed" + filename;
	assert(0 && errorMsg.c_str());

	//読み込みが失敗したら
	return nullptr;
}

const std::shared_ptr<KdTexture> ResourceFactory::GetTexture(const std::string& filename)
{
	//filenameのテクスチャが存在するか
	auto foundItr = m_TextureMap.find(filename);

	//モデルデータがすでにある
	if (foundItr != m_TextureMap.end())
	{
		return (*foundItr).second;
	}

	std::shared_ptr<KdTexture> newTexture = std::make_shared<KdTexture>();

	//生成、読み込み
	if (newTexture->Load(filename))
	{
		//リストに追加
		m_TextureMap[filename] = newTexture;

		return newTexture;
	}

	//assert(0 && "ResourceFactory::GetTexture() Failed");

	return nullptr;
}


void ResourceFactory::Release()
{
	m_modelMap.clear();

	m_TextureMap.clear();
}
