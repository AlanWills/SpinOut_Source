#pragma once

#include "Menu.h"
#include "DescriptionUI.h"

class DescriptionUIContainer : public Menu
{
public:
  DescriptionUIContainer(ID3D11Device* device, int selectedIndex = 0);
  ~DescriptionUIContainer();

  void Initialize() override;
  void HandleInput(float elapsedSeconds, const Vector2& mousePosition) override;
  void AddDescriptionUI(DescriptionUI* descriptionUI);

  int GetCurrentUIIndex() const { return m_currentUIIndex; }
  DescriptionUI* GetCurrentSelectedUI() const { return m_descriptionUI[m_currentUIIndex]; }

protected:
  void HideAllButCurrent();

private:
  std::vector<DescriptionUI*> m_descriptionUI;
  int m_currentUIIndex;
};

