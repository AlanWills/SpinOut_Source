#pragma once

#include "UIObject.h"
#include "BaseObjectManager.h"

class Menu : public UIObject
{
public:
	Menu(ID3D11Device* device, const Vector2& localPosition, const std::string& dataAsset = "", LoadType loadType = LoadType::kNoLoad, BaseObject* parent = nullptr, float lifeTime = FLT_MAX);
	Menu(ID3D11Device* device, const Vector2& size, const Vector2& localPosition, const std::string& dataAsset = "", LoadType loadType = LoadType::kNoLoad, BaseObject* parent = nullptr, float lifeTime = FLT_MAX);
	~Menu();

	void LoadContent(ID3D11Device* device) override;

	/// \brief Loads the content of all the objects we have already set up
	void Initialize() override;

	/// \brief Updates all the objects in the menu
	void Update(float elapsedSeconds) override;

	/// \brief Draws all objects in the menu and the menu itself
	void Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont) override;

	/// \brief Handles the input of all elements in the menu and the menu object itself
	void HandleInput(float elapsedSeconds, const Vector2& mousePosition) override;

	/// brief Shows, activates and accepts input for all elements in the menu and the menu itself
	void Show();

	/// \brief Hides, deactivates and disables input for all elements in the menu and the menu itself
	void Hide();

	/// \brief Destroys the menu and all it's sub menus
	void Die() override;

	/// \brief Wrapper functions for adding/removing in UI objects
	void AddUIObject(UIObject* uiObject, bool load = false, bool initialize = false);
  UIObject* FindObject(const std::string& uiObjectName) const;

  template <typename T>
  T* FindObjectAs(const std::string& objectName) const { return dynamic_cast<T*>(FindObject(objectName)); }

  void RemoveUIObject(const std::string& uiObjectName);
	void RemoveUIObject(UIObject* uiObject);

protected:
	/// \brief Set ups initial UI before load and initialize functions are called
	virtual void AddInitialUI() { }

private:
	/// \brief Typedefs
	typedef BaseObjectManager<UIObject> UIObjects;

	/// \brief A container for UIObjects.  Will only be able to deal with
	/// the same type as this Menu (i.e. In-Game or Screen)
	std::unique_ptr<UIObjects> m_uiObjects;
};