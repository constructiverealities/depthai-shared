#pragma once

#include "depthai-shared/datatype/RawToFConfig.hpp"
#include "depthai-shared/properties/Properties.hpp"

namespace dai {

/**
 * Specify properties for ToF
 */
struct ToFProperties : PropertiesSerializable<Properties, ToFProperties> {
  RawToFConfig initialConfig;
  std::vector<uint8_t> filter_config;
};

  DEPTHAI_SERIALIZE_EXT(ToFProperties, initialConfig, filter_config);

}  // namespace dai
