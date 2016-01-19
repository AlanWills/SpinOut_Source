#include "pch.h"
#include "BaseScreenData.h"


//-----------------------------------------------------------------------------------------------------------------------------------
BaseScreenData::BaseScreenData(const std::string& dataAsset) :
	BaseData(dataAsset)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
BaseScreenData::~BaseScreenData()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
const std::wstring BaseScreenData::GetDisplayName() const
{
  const char* displayName = ConstGetDocument()->RootElement()->FirstChildElement("DisplayName")->GetText();
  if (!displayName)
  {
    return L"";
  }

	return GenericUtils::CharToWChar(displayName);
}


//-----------------------------------------------------------------------------------------------------------------------------------
const char* BaseScreenData::GetBackgroundAsset() const
{
	return ConstGetDocument()->RootElement()->FirstChildElement("BackgroundTextureAsset")->GetText();
}


//-----------------------------------------------------------------------------------------------------------------------------------
std::list<std::wstring> BaseScreenData::GetMusicAssets() const
{
  std::list<std::wstring> musicAssets;

  const XMLElement* musicContainer = ConstGetDocument()->RootElement()->FirstChildElement("MusicAssets");
  assert(musicContainer);

  for (const XMLElement* musicAsset = musicContainer->FirstChildElement(); musicAsset; musicAsset = musicAsset->NextSiblingElement())
  {
    musicAssets.push_back(GenericUtils::CharToWChar(musicAsset->GetText()));
  }

  return musicAssets;
}