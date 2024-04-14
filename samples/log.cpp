#include "log.h"

#include <thread>
#include <vector>

using namespace Cairn;

void perform_logging(int thread_id) {
  Log::set_log_severity(Log::Severity::Warning);

  Log::debug(Log::Graphics, "Thread " + std::to_string(thread_id) + ": Loading graphics module");
  Log::info(Log::ECS, "Thread " + std::to_string(thread_id) + ": Entity component system initialized successfully");
  Log::warn(Log::Audio, "Thread " + std::to_string(thread_id) + ": Audio file missing: defaulting to backup track");
  Log::error(Log::Resource, "Thread " + std::to_string(thread_id) + ": Failed to load texture file");
  Log::verbose(Log::Math, "Thread " + std::to_string(thread_id) + ": Vector calculations executed");
  Log::info(Log::UI, "Thread " + std::to_string(thread_id) +
                         ": UI updates are now smoother with the new rendering optimizations");
  Log::error(Log::Physics,
             "Thread " + std::to_string(thread_id) + ": Physics simulation error: object collision undefined");
  Log::debug(Log::Animation, "Thread " + std::to_string(thread_id) + ": Animation blending state changed");
  Log::verbose(Log::Time,
               "Thread " + std::to_string(thread_id) + ": Frame time logging enabled for performance monitoring");
  Log::warn(Log::Input, "Thread " + std::to_string(thread_id) + ": Input latency higher than expected");
}

int main() {
  std::vector<std::thread> threads;
  for (int i = 1; i <= 5; ++i) {
    threads.emplace_back(perform_logging, i);
  }
  for (auto& t : threads) {
    t.join();
  }
  return 0;
}
