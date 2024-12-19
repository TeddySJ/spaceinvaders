#pragma once

#include "raylib.h"
#include <vector>
#include <ranges>
#include <algorithm>

class ICollidable
{
public:
    virtual Rectangle GetCollisionRect() const = 0;
    virtual void OnCollision() = 0;
    virtual ~ICollidable() = default;

    template<std::ranges::input_range R1, std::ranges::input_range R2>
    static void CheckCollisions(R1&& range1, R2&& range2)
    {
        for (auto& obj1 : range1)
        {
            for (auto& obj2 : range2)
            {
                if (Intersects(obj1.GetCollisionRect(), obj2.GetCollisionRect()))
                {
                    obj1.OnCollision();
                    obj2.OnCollision();
                }
            }
        }
    }

    template<std::ranges::input_range R1>
    static void CheckCollisions(R1&& range1, ICollidable& c2)
    {
        const auto c2rect = c2.GetCollisionRect();
        for (auto& obj1 : range1)
        {
            if (Intersects(obj1.GetCollisionRect(), c2rect))
            {
                obj1.OnCollision();
                c2.OnCollision();
            }
        }
    }

    static constexpr bool Intersects(Rectangle r1, Rectangle r2)
    {
        return (r1.x < r2.x + r2.width &&
            r1.x + r1.width > r2.x &&
            r1.y < r2.y + r2.height &&
            r1.y + r1.height > r2.y);
    }
};