#pragma once
#include <functional>

using QuackBehavior = std::function<void()>;

void Quack();

void Squeak();

void MuteQuack();