#include "WorldJoint2d.h"

namespace ample::physics
{
WorldJoint2d::WorldJoint2d(WorldObject2d &bodyA, WorldObject2d &bodyB, b2Joint *joint)
    : _joint(joint), _bodyA(bodyA), _bodyB(bodyB) {}

b2Body *WorldJoint2d::getB2Body(WorldObject2d &obj) const
{
    return obj._body;
}

b2Joint *WorldJoint2d::getB2Joint(WorldJoint2d &joint) const
{
    return joint._joint;
}

void WorldJoint2d::initB2Joint(WorldLayer2d &layer, b2JointDef *jointDef)
{
    _joint = layer.addWorldJoint(*this, jointDef);
}

ample::graphics::Vector2d<float> WorldJoint2d::getAnchorA() const
{
    const b2Vec2 &anchor = _joint->GetAnchorA();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldJoint2d::getAnchorB() const
{
    const b2Vec2 &anchor = _joint->GetAnchorB();
    return {anchor.x, anchor.y};
}

ample::graphics::Vector2d<float> WorldJoint2d::getReactionForce(float inv_dt) const
{
    const b2Vec2 &force = _joint->GetReactionForce(inv_dt);
    return {force.x, force.y};
}

float WorldJoint2d::getReactionTorque(float inv_dt) const
{
    return _joint->GetReactionTorque(inv_dt);
}

WorldObject2d &WorldJoint2d::getBodyA()
{
    return _bodyA;
}

WorldObject2d &WorldJoint2d::getBodyB()
{
    return _bodyB;
}
} // namespace ample::physics