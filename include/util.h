#pragma once

void hlt();
void sleep();
void disable_irq();
void enable_irq();
int save_irq();
void restore_irq(int flag);

