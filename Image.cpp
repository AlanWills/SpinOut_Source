#include "pch.h"

#include "Image.h"


//-----------------------------------------------------------------------------------------------------------------------------------
Image::Image(const Vector2& localPosition, const std::string& dataAsset, LoadType loadType, BaseObject* parent, float lifeTime) :
  Image(Vector2::Zero, localPosition, dataAsset, Sizing::kPreserveAspectRatio, loadType, parent, lifeTime)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Image::Image(const Vector2& size, const Vector2& localPosition, const std::string& dataAsset, Sizing preserveAspectRatio, LoadType loadType, BaseObject* parent, float lifeTime) :
  UIObject(size, localPosition, dataAsset, loadType, parent, lifeTime),
  m_sizing(preserveAspectRatio)
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
Image::~Image()
{
}


//-----------------------------------------------------------------------------------------------------------------------------------
void Image::Initialize()
{
  // If we've already set a size we need to amend it to preserve aspect ratio
  if (GetSize().x == GetSize().y && m_sizing == Sizing::kPreserveAspectRatio)
  {
    assert(GetTexture()->GetTexture());

    const Vector2& size = GetSize();
    const Vector2& dimensions = GetTexture()->GetDimensions();

    float maxDimension = max(dimensions.x, dimensions.y);
    assert(maxDimension > 0);

    float scaling = size.x / maxDimension;
    assert(scaling > 0);

    SetSize(Vector2(dimensions.x * scaling, dimensions.y * scaling));
  }

  UIObject::Initialize();
}