#include "log.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace Cairn {

Log::Severity Log::min_severity = Log::Severity::Verbose;

std::mutex Log::mutex;

void Log::log(Severity severity, Category category, const std::string& message) {
  if (severity < min_severity) {
    return;
  }
  std::lock_guard<std::mutex> lock(mutex);
  std::cout << get_timestamp() << " [" << to_string(category) << "] [" << to_string(severity) << "] " << message
            << std::endl;
}

void Log::debug(Category category, const std::string& message) { log(Debug, category, message); }

void Log::error(Category category, const std::string& message) { log(Error, category, message); }

void Log::info(Category category, const std::string& message) { log(Info, category, message); }

void Log::warn(Category category, const std::string& message) { log(Warning, category, message); }

void Log::verbose(Category category, const std::string& message) { log(Verbose, category, message); }

void Log::set_log_severity(Severity severity) { min_severity = severity; }

std::string Log::get_timestamp() {
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);
  std::stringstream ss;
  ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
  return ss.str();
}

std::string Log::to_string(Severity severity) {
  switch (severity) {
  case Verbose: return "Verbose";
  case Debug: return "Debug";
  case Info: return "Info";
  case Warning: return "Warning";
  case Error: return "Error";
  default: return "Unknown";
  }
}

std::string Log::to_string(Category category) {
  switch (category) {
  case AI: return "AI";
  case Animation: return "Animation";
  case Audio: return "Audio";
  case ECS: return "ECS";
  case Graphics: return "Graphics";
  case Input: return "Input";
  case Math: return "Math";
  case Physics: return "Physics";
  case Resource: return "Resource";
  case Time: return "Time";
  case UI: return "UI";
  case Window: return "Window";
  default: return "Unknown";
  }
}

} // namespace Cairn
