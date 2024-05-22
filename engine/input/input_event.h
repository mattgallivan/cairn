#pragma once

#include <functional>

namespace Cairn {

/** An input event is an abstract class that represents an event that is triggered by user input. */
class InputEvent {
public:
  enum class Type {
    Keyboard,
    MouseButton,
    MousePosition,
  };

  enum class Modifier {
    None = 0,
    Shift = 1,
    Control = 2,
    Alt = 4,
    Super = 8,
    CapsLock = 16,
    NumLock = 32,
  };

  enum class State {
    Press,
    Release,
    Hold,
    None,
  };

  InputEvent(Type type, State state, Modifier modifier = Modifier::None)
      : type(type), state(state), modifier(modifier) {}

  virtual ~InputEvent() = default;

  bool operator==(const InputEvent& other) const {
    return type == other.type && modifier == other.modifier && state == other.state;
  }

  /** The modifier keys that were pressed. */
  Modifier modifier;

  /** The state that was performed (press, release, hold). */
  State state;

  /** The type of the event (keyboard key, mouse scroll, etc.). */
  Type type;
};

/** A keyboard event is an input event that is triggered by a keyboard key. */
class KeyboardEvent : public InputEvent {

public:
  enum class Key {
    Unknown = -1,
    Space = 32,
    Apostrophe = 39,
    Comma = 44,
    Minus = 45,
    Period = 46,
    Slash = 47,
    Num0 = 48,
    Num1 = 49,
    Num2 = 50,
    Num3 = 51,
    Num4 = 52,
    Num5 = 53,
    Num6 = 54,
    Num7 = 55,
    Num8 = 56,
    Num9 = 57,
    Semicolon = 59,
    Equal = 61,
    A = 65,
    B = 66,
    C = 67,
    D = 68,
    E = 69,
    F = 70,
    G = 71,
    H = 72,
    I = 73,
    J = 74,
    K = 75,
    L = 76,
    M = 77,
    N = 78,
    O = 79,
    P = 80,
    Q = 81,
    R = 82,
    S = 83,
    T = 84,
    U = 85,
    V = 86,
    W = 87,
    X = 88,
    Y = 89,
    Z = 90,
    LeftBracket = 91,
    Backslash = 92,
    RightBracket = 93,
    GraveAccent = 96,
    World1 = 161,
    World2 = 162,
    Escape = 256,
    Enter = 257,
    Tab = 258,
    Backspace = 259,
    Insert = 260,
    Delete = 261,
    Right = 262,
    Left = 263,
    Down = 264,
    Up = 265,
    PageUp = 266,
    PageDown = 267,
    Home = 268,
    End = 269,
    CapsLock = 280,
    ScrollLock = 281,
    NumLock = 282,
    PrintScreen = 283,
    Pause = 284,
    F1 = 290,
    F2 = 291,
    F3 = 292,
    F4 = 293,
    F5 = 294,
    F6 = 295,
    F7 = 296,
    F8 = 297,
    F9 = 298,
    F10 = 299,
    F11 = 300,
    F12 = 301,
    F13 = 302,
    F14 = 303,
    F15 = 304,
    F16 = 305,
    F17 = 306,
    F18 = 307,
    F19 = 308,
    F20 = 309,
  };

  KeyboardEvent(Key key, State state, Modifier modifier = InputEvent::Modifier::None)
      : InputEvent(InputEvent::Type::Keyboard, state, modifier), key(key) {}

  /** The key that was pressed, released, or held. */
  Key key;
};

/** A mouse button event is an input event that is triggered by a mouse button. */
class MouseButtonEvent : public InputEvent {
public:
  enum class MouseButton {
    Unknown = -1,
    Left = 0,
    Right = 1,
    Middle = 2,
    Button1 = Left,
    Button2 = Middle,
    Button3 = Right,
    Button4 = 3,
    Button5 = 4,
    Button6 = 5,
    Button7 = 6,
    Button8 = 7,
  };

  MouseButtonEvent(MouseButton button, State state, Modifier modifier = InputEvent::Modifier::None)
      : InputEvent(InputEvent::Type::MouseButton, state, modifier), button(button), x(0.f), y(0.f) {}

  /** The mouse button that was pressed, released, or held. */
  MouseButton button;

  /** The x-coordinate of the mouse cursor. */
  double x;

  /** The y-coordinate of the mouse cursor. */
  double y;
};

/** A mouse position event is an input event that is triggered by moving the mouse cursor. */
class MousePositionEvent : public InputEvent {
public:
  MousePositionEvent() : InputEvent(InputEvent::Type::MousePosition, InputEvent::State::None), x(0.f), y(0.f) {}

  MousePositionEvent(double x, double y)
      : InputEvent(InputEvent::Type::MousePosition, InputEvent::State::None, InputEvent::Modifier::None), x(x), y(y) {}

  /** The x-coordinate of the mouse cursor. */
  double x;

  /** The y-coordinate of the mouse cursor. */
  double y;
};

} // namespace Cairn

namespace std {

template <>
struct hash<Cairn::InputEvent> {
  size_t operator()(const Cairn::InputEvent& event) const {
    return hash<int>()(static_cast<int>(event.type)) ^ hash<int>()(static_cast<int>(event.modifier)) ^
           hash<int>()(static_cast<int>(event.state));
  }
};

} // namespace std
