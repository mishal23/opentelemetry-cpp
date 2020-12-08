// Copyright 2020, OpenTelemetry Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#pragma once

#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include <mutex>

#include "opentelemetry/nostd/shared_ptr.h"
#include "opentelemetry/nostd/string_view.h"
#include "opentelemetry/nostd/unique_ptr.h"

#include "opentelemetry/common/key_value_iterable_view.h"
#include "opentelemetry/trace/span.h"
#include "opentelemetry/trace/span_context_kv_iterable_view.h"
#include "opentelemetry/trace/span_id.h"
#include "opentelemetry/trace/trace_id.h"
#include "opentelemetry/trace/tracer_provider.h"

#include "opentelemetry/sdk/trace/etw_data.h"
#include "opentelemetry/sdk/logs/exporter.h"
#include "opentelemetry/sdk/trace/recordable.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <unordered_map>

#include "opentelemetry/exporters/etw/etw_provider_exporter.h"

#include "opentelemetry/exporters/etw/utils.h"

namespace core  = opentelemetry::core;
namespace trace = opentelemetry::trace;

OPENTELEMETRY_BEGIN_NAMESPACE

namespace ETW
{

class ETWLoggerExporter final : public opentelemetry::sdk::logs::LogExporter
{
public:
  /**
   * @param providerName
   */
  ETWLoggerExporter(std::string providerName) : providerName_(providerName) {}

  /**
   * @param records a required log record containing unique pointers to the data
   * to add to the ETWLoggerExporter
   * @return Returns the result of the operation
   */
  sdk::logs::ExportResult Export(
      const nostd::span<std::unique_ptr<opentelemetry::logs::LogRecord>> &records) noexcept override
  {
    // TODO: implement the Export method
    return sdk::logs::ExportResult::kSuccess;
  }

  /**
   * @param timeout an optional value containing the timeout of the exporter
   * note: passing custom timeout values is not currently supported for this exporter
   */
  bool Shutdown(
      std::chrono::microseconds timeout = std::chrono::microseconds(0)) noexcept override{};

private:
  std::string providerName_;
};

}  // namespace ETW

OPENTELEMETRY_END_NAMESPACE
