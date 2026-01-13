#pragma once

#include "api.h"

// Intake belt motors run together so the belt keeps a consistent speed.
extern pros::MotorGroup intake_group;

void belt_move(int velocity);
