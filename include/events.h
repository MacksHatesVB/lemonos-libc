#pragma once

#include <stdint.h>

typedef struct event {
	int type;
} event_t;

typedef struct {
	int sysrq; // is sysrq held
	int lctrl; // is left control held?
	int rctrl; // is right control held?
	int super; // is super held
	int meta; // is meta (ralt) held
	int lalt; // is left alt you get it
	int ralt;
	int lshift;
	int rshift;

	int caps; // is caps lock on
	int metalock; // is meta lock on
} keyboard_held_t;

typedef struct {
	int left;
	int right;
	int middle;
	int button1;
	int button2;
	int button3;
} mouse_held_t;

typedef struct {
	int button1;
	int button2;
	int button3;
	int button4;
	int button5;
	int button6;
	int lTrigger;
	int rTrigger;
	int lShoulder;
	int rShoulder;
	int is_analog; // are triggers analog (other wise value is 0-1)
} joystick_held_t;

typedef struct {
	int type;
	int device; // device number
	uint32_t keycode;
	int pressed; // is this pressed or nah
	keyboard_held_t * held;
} kbd_event_t;

typedef struct {
	int type;
	int device; // device number
	int x; // where mouse (x, y)
	int y;
	int delta_x; // raw movement straight of the mouse (can go past screen bounds)
	int delta_y;
	int bdelta_x; // mouse movement bound to the edges of the screen
	int bdelta_y;
	mouse_held_t * held;
} mouse_event_t;

typedef struct {
	int type;
	int device; // device number
	int lXAxis; // left and right joystick x and y movement
	int lYAxis;
	int rXAxis;
	int rYAxis;
	int has_right; // not all of these have right joysticks
	joystick_held_t * held;
} joystick_event_t;

typedef struct {
	int type;
	void * from; // who sent, todo: change to pid number for userland (this pointer is meaningless to you)
	int cmd; // the command
	void * data; // some stuff
} ipc_event_t;

typedef struct {
	int type;
	int x;
	int y;
	int deltax;
	int deltay;
} gfx_event_t;

enum {
	EVENT_KEYBOARD,
	EVENT_MOUSE,
	EVENT_JOYSTICK,
	EVENT_GFX,
	EVENT_IPC,
};
