#pragma once

#define TIMER_HZ 1000 //1 MS

static uint64_t timer_ticks;

void init_timer();
void timer_tick();