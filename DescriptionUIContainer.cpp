#include "pch.h"

#include "DescriptionUIContainer.h"
#include "ScreenManager.h"


//-----------------------------------------------------------------------------------------------------------------------------------
DescriptionUIContainer::DescriptionUIContainer(ID3D11Device* device, int selectedIndex) :
  UIPanel(device, ScreenManager::GetScreenCentre(), "", LoadType::kNoLoad),
  m_currentUIIndex(selectedIndex)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
DescriptionUIContainer::~DescriptionUIContainer()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void DescriptionUIContainer::Initialize()
{
  UIPanel::Initialize();

  HideAllButCurrent();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void DescriptionUIContainer::HandleInput(float elapsedSeconds, const Vector2& mousePosition)
{
  UIPanel::HandleInput(elapsedSeconds, mousePosition);

  if (AcceptsInput())
  {
    const KeyboardInput& keyboard = ScreenManager::GetKeyboardInput();
    if (keyboard.IsKeyPressed(Keyboard::Keys::Left))
    {
      m_currentUIIndex--;
      m_currentUIIndex = MathUtils::Clamp<int>(m_currentUIIndex, 0, m_descriptionUI.size() - 1);
      HideAllButCurrent();
    }
    else if (keyboard.IsKeyPressed(Keyboard::Keys::Right))
    {
      m_currentUIIndex++;
      m_currentUIIndex = MathUtils::Clamp<int>(m_currentUIIndex, 0, m_descriptionUI.size() - 1);
      HideAllButCurrent();
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void DescriptionUIContainer::HideAllButCurrent()
{
  assert(m_descriptionUI.size() > 0);

  for (size_t index = 0, count = m_descriptionUI.size(); index < count; ++index)
  {
    m_descriptionUI[index]->SetVisible(index == m_currentUIIndex);
  }
}


//-----------------------------------------------------------------------------------------------------------------------------------
void DescriptionUIContainer::AddDescriptionUI(DescriptionUI* descriptionUI)
{
  // Assume that we are adding within an 'AddInitialUI' function here
  AddUIObject(descriptionUI);
  m_descriptionUI.push_back(descriptionUI);
}