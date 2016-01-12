#include "pch.h"
#include "BaseData.h"


//-----------------------------------------------------------------------------------------------------------------------------------
BaseData::BaseData(const std::string& dataAsset) :
	m_document(nullptr),
	m_dataAsset(dataAsset)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
BaseData::~BaseData()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
tinyxml2::XMLDocument* BaseData::CreateDocument()
{
  if (m_document.get())
  {
    m_document->Clear();
  }

  m_document.reset(new tinyxml2::XMLDocument());

  return m_document.get();
}


//-----------------------------------------------------------------------------------------------------------------------------------
void BaseData::LoadData()
{
  CreateDocument();

	m_document->LoadFile(m_dataAsset.c_str());

	assert(m_document.get());
}