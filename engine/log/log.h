#pragma once

#include <mutex>
#include <string>

namespace Cairn {

class Log {
public:
  /** The severity of a log message, from least to most severity. */
  enum Severity { Verbose, Debug, Info, Warning, Error };

  /** A category for each game engine subsystem. */
  enum Category { AI, Animation, Audio, ECS, Graphics, Input, Math, Physics, Resource, Time, UI, Window };

  /** Log a message with the given severity and category. */
  static void log(Severity severity, Category category, const std::string& message);

  /** Log a message with the debug severity. */
  static void debug(Category category, const std::string& message);

  /** Log a message with the error severity. */
  static void error(Category category, const std::string& message);

  /** Log a message with the info severity. */
  static void info(Category category, const std::string& message);

  /** Log a message with the warning severity. */
  static void warn(Category category, const std::string& message);

  /** Log a message with the verbose severity. */
  static void verbose(Category category, const std::string& message);

  /** Set the minimum severity to report. Anything less will not be logged. */
  static void set_log_severity(Severity severity);

private:
  /** Get the current timestamp. */
  static std::string get_timestamp();

  /** Convert a severity to a string */
  static std::string to_string(Severity severity);

  /** Convert a category to a string */
  static std::string to_string(Category category);

  /** The minimum severity to log. */
  static Severity min_severity;

  /** Mutex to ensure thread safety. */
  static std::mutex mutex;
};

} // namespace Cairn
