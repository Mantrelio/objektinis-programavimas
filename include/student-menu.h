#pragma once

#include "student-vector.h"

void showMainMenu();

template <typename T>
void handleMenuChoice(int choice, T& students);

template <typename T>
void startMainMenu();
