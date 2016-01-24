#pragma once

#include "DescriptionUI.h"

#include "RacetrackScreenData.h"

class RacetrackDescriptionUI : public DescriptionUI
{
public:
  RacetrackDescriptionUI(ID3D11Device* device, const std::string& racetrackScreenDataAsset);
  ~RacetrackDescriptionUI();

  void LoadContent(ID3D11Device* device) override;

  /// \brief Called during load content so we're fine - just need to make sure we load the racetrack screen data before we called Menu::LoadContent
  void AddInitialUI() override;

private:
  std::unique_ptr<RacetrackScreenData> m_racetrackScreenData;
};

