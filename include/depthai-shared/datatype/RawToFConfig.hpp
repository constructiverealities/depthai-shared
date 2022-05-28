#pragma once
#include <cstdint>
#include <vector>

#include "RawImgFrame.hpp"
#include "depthai-shared/common/Rect.hpp"
#include "depthai-shared/datatype/DatatypeEnum.hpp"
#include "depthai-shared/datatype/RawBuffer.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {


struct RawToFConfig : public RawBuffer {
  float minAmplitude;
  float maxError;

  float minDistance, maxDistance;
  float minAlbedo, maxAlbedo, albedoCutoffAmplitude;

  float maxAsymmetry;

  bool useLoadedFilter;
  
    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::ToFConfig;
    };

  DEPTHAI_SERIALIZE(RawToFConfig, minAmplitude, maxError, minDistance, maxDistance,
		      minAlbedo, maxAlbedo, albedoCutoffAmplitude,
		    maxAsymmetry, useLoadedFilter);
};

}  // namespace dai
