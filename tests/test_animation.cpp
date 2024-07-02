#include "engine.h"
#include <gtest/gtest.h>

using namespace Cairn::Animation;

TEST(AnimationTest, PlayPauseStopReset) {
  std::shared_ptr<Image> image = std::make_shared<Image>();
  Frame frame(image.get());
  std::vector<Frame> frames = {frame, frame, frame};
  Animation animation(frames);

  animation.play();
  ASSERT_TRUE(animation.is_playing());

  animation.pause();
  ASSERT_FALSE(animation.is_playing());

  animation.play();
  animation.stop();
  ASSERT_FALSE(animation.is_playing());
  ASSERT_EQ(animation.get_current_frame(), frames[0]);

  animation.play();
  animation.reset();
  ASSERT_EQ(animation.get_current_frame(), frames[0]);
}

TEST(AnimationTest, Update) {
  std::shared_ptr<Image> image = std::make_shared<Image>();
  Frame frame(image.get());
  std::vector<Frame> frames = {frame, frame, frame};
  Animation animation(frames);

  animation.play();
  animation.update(1000.f / 24.f);
  ASSERT_EQ(animation.get_current_frame(), frames[1]);

  animation.update(1000.f / 24.f);
  ASSERT_EQ(animation.get_current_frame(), frames[2]);

  animation.update(1000.f / 24.f);
  ASSERT_EQ(animation.get_current_frame(), frames[0]);
}

TEST(AnimationTest, Looping) {
  std::shared_ptr<Image> image = std::make_shared<Image>();
  Frame frame(image.get());
  std::vector<Frame> frames = {frame, frame, frame};
  Animation animation(frames);
  animation.should_loop = true;

  animation.play();
  for (int i = 0; i < 10; ++i) {
    animation.update(1000.f / 24.f);
  }

  ASSERT_TRUE(animation.is_playing());
  ASSERT_EQ(animation.get_current_frame(), frames[1]);

  animation.should_loop = false;
  for (int i = 0; i < 10; ++i) {
    animation.update(1000.f / 24.f);
  }

  ASSERT_FALSE(animation.is_playing());
}
