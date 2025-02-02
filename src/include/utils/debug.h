#pragma once
#include <stdbool.h>
#include <stdint.h>

bool debugger_attached();
void handle_debug_event();