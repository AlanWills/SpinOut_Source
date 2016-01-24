#include "pch.h"

#include "ScreenManager.h"

#include "RacetrackDescriptionUI.h"
#include "Image.h"
#include "Label.h"


//-----------------------------------------------------------------------------------------------------------------------------------
RacetrackDescriptionUI::RacetrackDescriptionUI(ID3D11Device* device, const std::string& racetrackScreenDataAsset) :
  DescriptionUI(device),
  m_racetrackScreenData(new RacetrackScreenData(racetrackScreenDataAsset))
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
RacetrackDescriptionUI::~RacetrackDescriptionUI()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackDescriptionUI::LoadContent(ID3D11Device* device)
{
  // MUST be called in this order because we need the data when we call AddInitialUI, which happens during Menu::LoadContent(device)
  m_racetrackScreenData->LoadData();

  DescriptionUI::LoadContent(device);
}


//-----------------------------------------------------------------------------------------------------------------------------------
void RacetrackDescriptionUI::AddInitialUI()
{
  const float spacing = ScreenManager::GetScreenDimensions().y * 0.05f;

  // Add the thumbnail to the centre of the screen
  Image* image = new Image(Vector2(400, 400), Vector2::Zero, m_racetrackScreenData->GetThumbnailAsset());
  AddUIObject(image);

  // Add the name of the race track
  Label* trackName = new Label(Vector2(0, - (spacing + image->GetSize().y * 0.5f)), GenericUtils::CharToWChar(m_racetrackScreenData->GetTrackName()), image);
  AddUIObject(trackName);

  Label* trackDescription = new Label(Vector2(0, spacing + image->GetSize().y * 0.5f), GenericUtils::CharToWChar(m_racetrackScreenData->GetDescription()), image);
  AddUIObject(trackDescription);
}