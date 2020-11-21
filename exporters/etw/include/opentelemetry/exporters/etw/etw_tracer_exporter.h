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
#include "opentelemetry/trace/span_id.h"
#include "opentelemetry/trace/trace_id.h"
#include "opentelemetry/trace/tracer_provider.h"
#include "opentelemetry/trace/span_context_kv_iterable_view.h"

#include "opentelemetry/sdk/trace/exporter.h"
#include "opentelemetry/sdk/trace/recordable.h"
#include "opentelemetry/sdk/trace/etw_data.h"

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

class ETWTracerExporter final : public opentelemetry::sdk::trace::SpanExporter
{
public:
  /**
   * @param providerName
   * @param eventName
   */
  ETWTracerExporter(std::string providerName): providerName_(providerName)
  {
    //data_->InitTracerProvider(providerName);
  }

  /**
   * @return Returns a unique pointer to an empty recordable object
   */
  std::unique_ptr<sdk::trace::Recordable> MakeRecordable() noexcept override
  {
     return std::unique_ptr<sdk::trace::Recordable>(new sdk::trace::ETWSpanData(providerName_));
  }

  /**
   * @param recordables a required span containing unique pointers to the data
   * to add to the ETWTracerExporter
   * @return Returns the result of the operation
   */
  sdk::trace::ExportResult Export(
      const nostd::span<std::unique_ptr<sdk::trace::Recordable>> &recordables) noexcept override
  {
    for (auto &recordable : recordables)
    {
      auto span = std::unique_ptr<sdk::trace::ETWSpanData>(
          dynamic_cast<sdk::trace::ETWSpanData *>(recordable.release()));
      if (span != nullptr)
      {
        char trace_id[32]       = {0};
        char span_id[16]        = {0};
        char parent_span_id[16] = {0};

        span->GetTraceId().ToLowerBase16(trace_id);
        span->GetSpanId().ToLowerBase16(span_id);
        span->GetParentSpanId().ToLowerBase16(parent_span_id);

        std::cout << "{"
                  << "\n  name          : " << span->GetName()
                  << "\n  trace_id      : " << std::string(trace_id, 32)
                  << "\n  span_id       : " << std::string(span_id, 16)
                  << "\n  parent_span_id: " << std::string(parent_span_id, 16)
                  << "\n  start         : " << span->GetStartTime().time_since_epoch().count()
                  << "\n  duration      : " << span->GetDuration().count()
                  << "\n  description   : " << span->GetDescription()
                  << "\n  status        : " << int(span->GetStatus());
        std::cout << "\n}\n";
      }
    }

    return sdk::trace::ExportResult::kSuccess;
  }

  /**
   * @param timeout an optional value containing the timeout of the exporter
   * note: passing custom timeout values is not currently supported for this exporter
   */
  void Shutdown(
      std::chrono::microseconds timeout = std::chrono::microseconds(0)) noexcept override{};

private:
  std::string providerName_;
  std::shared_ptr<sdk::trace::ETWSpanData> data_;
};

} // namespace ETW

OPENTELEMETRY_END_NAMESPACE
