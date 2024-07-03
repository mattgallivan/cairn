#include "node.h"

namespace Cairn::Animation {

void AnimationNode::start() { animation->play(); }

void AnimationNode::stop() { animation->stop(); }

void AnimationNode::update(float delta_time_ms) { animation->update(delta_time_ms); }

} // namespace Cairn::Animation