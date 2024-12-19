#pragma once

#include "raylib.h"

class ICollidable {
public:
    virtual Rectangle GetCollisionRect() const = 0;
    virtual void OnCollision() = 0;
    virtual ~ICollidable() = default;
};