#include "window.h"

int main() {
  Cairn::Window window(800, 600, "Animation Test");

  Cairn::InputManager input_manager;
  Cairn::InputProfile profile;
  profile.map(Cairn::KeyboardEvent(Cairn::KeyboardEvent::Key::Escape, Cairn::InputEvent::State::Press),
              [&window](const Cairn::InputEvent& event) { window.close(); });
  input_manager.add(&profile);
  window.bind(&input_manager);

  while (window.is_open()) {
    window.refresh();
  }

  return 0;
}
