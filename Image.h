#pragma once

#include "UIObject.h"

class Image : public UIObject
{
public:
  enum Sizing
  {
    kPreserveAspectRatio,
    kDoNotPreserveAspectRatio,
  };

  Image(const Vector2& localPosition, const std::string& dataAsset, LoadType loadType = LoadType::kTexture, BaseObject* parent = nullptr, float lifeTime = FLT_MAX);
  Image(const Vector2& size, 
        const Vector2& localPosition, 
        const std::string& dataAsset, 
        Sizing preserveAspectRatio = kPreserveAspectRatio, 
        LoadType loadType = LoadType::kTexture, 
        BaseObject* parent = nullptr, 
        float lifeTime = FLT_MAX);

  ~Image();

  void Initialize() override;

private:
  Sizing m_sizing;
};

