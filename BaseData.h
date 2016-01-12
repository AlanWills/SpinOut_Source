#pragma once

#include "tinyxml2.h"

using namespace tinyxml2;

class BaseData
{
public:
	BaseData(const std::string& dataAsset);
	~BaseData();

	void LoadData();
	const std::string& GetDataAsset() const { return m_dataAsset; }

protected:
	const tinyxml2::XMLDocument* ConstGetDocument() const { return m_document.get(); }
  tinyxml2::XMLDocument* GetDocument() { return m_document.get(); }

  tinyxml2::XMLDocument* CreateDocument();

private:
	std::unique_ptr<tinyxml2::XMLDocument> m_document;
	std::string m_dataAsset;
};