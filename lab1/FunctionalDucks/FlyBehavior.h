#pragma once

#include <functional>

using FlyBehavior = std::function<void()>;

FlyBehavior FlyWithWings();

void FlyNoWay();