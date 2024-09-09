#pragma once
#include <functional>

using DanceBehavior = std::function<void()>;

void DanceWaltz();

void DanceMinuet();

void NotDance();