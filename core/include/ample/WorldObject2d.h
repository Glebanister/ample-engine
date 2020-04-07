#pragma once

#include "GraphicalObject2d.h"
#include "WorldLayer2d.h"
#include "Vector2d.h"
#include "WorldContact2d.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"

#include <fstream>
#include <sstream>
#include <memory>
#include <vector>

namespace ample::filing
{
class WorldObject2dIO;
}

namespace ample::physics
{
class WorldLayer2d;
class WorldContact2d;
class WorldContactEdge2d;
class WorldObject2d;
class WorldJoint2d;
class Fixture final
{
public:
    WorldObject2d &getObject();

    void setDensity(float density);
    void setFriction(float friction);
    void setRestitution(float restitution);
    void setSensor(bool sensor);

private:
    friend WorldObject2d;
    friend WorldContact2d;

    Fixture(b2Fixture *fixture);
    b2Fixture *_fixture = nullptr;
};

enum class BodyType
{
    STATIC_BODY = 0,
    KINEMATIC_BODY,
    DYNAMIC_BODY
};

struct MassData
{
    float mass;
    ample::graphics::Vector2d<float> center;
    float I;
};

class WorldObject2d final : public ample::graphics::GraphicalObject2d
{
public:
    void onActive() override;
    WorldObject2d(WorldLayer2d &layer,
                  BodyType type,
                  const std::vector<ample::graphics::Vector2d<float>> &shape,
                  const float thickness,
                  const float z,
                  const graphics::Vector2d<float> &faceTextureRepeats,
                  const graphics::Vector2d<float> &sideTextureRepeats,
                  const graphics::normalsMode sideNormalsMode,
                  const graphics::Vector2d<float> &translated = {0.0f, 0.0f},
                  float rotated = 0.0f);
    //void onPause() override;//TODO

    Fixture addFixture(const std::vector<ample::graphics::Vector2d<float>> &shape);
    WorldLayer2d &getWorldLayer() const;

    void setSpeedX(float desiredVelX);
    void setSpeedY(float desiredVelY);

    void setTransform(const graphics::Vector2d<float> &position, float angle);
    graphics::Vector2d<float> getPosition() const;
    float getAngle() const;

    graphics::Vector2d<float> getWorldCenter() const;
    graphics::Vector2d<float> getLocalCenter() const;

    graphics::Vector2d<float> getWorldPoint(const graphics::Vector2d<float> &localPoint) const;
    graphics::Vector2d<float> getWorldVector(const graphics::Vector2d<float> &localVector) const;
    graphics::Vector2d<float> getLocalPoint(const graphics::Vector2d<float> &worldPoint) const;
    graphics::Vector2d<float> getLocalVector(const graphics::Vector2d<float> &worldVector) const;

    void setLinearVelocity(const graphics::Vector2d<float> &v);
    graphics::Vector2d<float> getLinearVelocity() const;
    void setAngularVelocity(float omega);
    float getAngularVelocity() const;

    void applyForce(const graphics::Vector2d<float> &force, const graphics::Vector2d<float> &point, bool wake);
    void applyForceToCenter(const graphics::Vector2d<float> &force, bool wake);
    void applyTorque(float torque, bool wake);
    void applyLinearImpulse(const graphics::Vector2d<float> &impulse, const graphics::Vector2d<float> &point, bool wake);
    void applyLinearImpulseToCenter(const graphics::Vector2d<float> &impulse, bool wake);
    void applyAngularImpulse(float impulse, bool wake);

    float getMass() const;
    float getInertia() const;
    MassData getMassData() const;
    void setMassData(const MassData &data);
    void resetMassData();

    graphics::Vector2d<float> getLinearVelocityFromWorldPoint(const graphics::Vector2d<float> &worldPoint) const;
    graphics::Vector2d<float> getLinearVelocityFromLocalPoint(const graphics::Vector2d<float> &localPoint) const;

    float getLinearDamping() const;
    void setLinearDamping(float linearDamping);
    float getAngularDamping() const;
    void setAngularDamping(float angularDamping);

    float getGravityScale() const;
    void setGravityScale(float scale);

    void setSleepingAllowed(bool flag);
    bool isSleepingAllowed() const;

    void setAwake(bool flag);
    bool isAwake() const;

    void setEnabled(bool flag);
    bool isEnabled() const;

    void setFixedRotation(bool flag);
    bool isFixedRotation() const;

    WorldContactEdge2d getContactList();

    void dump();

private:
    friend WorldJoint2d;
    friend ample::filing::WorldObject2dIO;

    WorldLayer2d &_layer;
    b2Body *_body = nullptr;
};
} // namespace ample::physics