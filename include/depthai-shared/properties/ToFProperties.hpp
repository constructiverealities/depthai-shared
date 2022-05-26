#pragma once

#include "depthai-shared/datatype/RawToFConfig.hpp"
#include "depthai-shared/properties/Properties.hpp"

namespace dai {

/**
 * Specify properties for ToF
 */
struct ToFProperties : PropertiesSerializable<Properties, ToFProperties> {
  RawToFConfig initialConfig;
  int64_t filter_code;
};

  DEPTHAI_SERIALIZE_EXT(ToFProperties, initialConfig, filter_code);

}  // namespace dai
