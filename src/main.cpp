#include <bn_backdrop.h>
#include <bn_core.h>
#include <bn_keypad.h>
#include <bn_sprite_ptr.h>

#include "bn_sprite_items_bun.h"

#define FLOOR (80 - 8)

int main()
{
    bool jumping = false;
    bn::core::init();

    bn::backdrop::set_color(bn::color(15, 0, 0));

    auto dot = bn::sprite_items::bun.create_sprite(0, 0);

    bn::fixed speed = 1.5;

    bn::fixed dy = 0;
    bn::fixed gravity = .03;

    bn::fixed jump_strength = 1;

    while (true)
    {
        // if not jumping, jump but don't jump to max height in 1 frame
        if (!jumping)
        {
            dy = dy - jump_strength;
            jumping = true;
        }

        if (bn::keypad::left_held())
        {
            dot.set_x(dot.x() - speed);
        }
        if (bn::keypad::right_held())
        {
            dot.set_x(dot.x() + speed);
        }

        if (bn::keypad::a_pressed())
        {
            // do something
        }

        dy += gravity;

        dot.set_y(dot.y() + dy);

        if (dot.y() > FLOOR)
        {
            dot.set_y(FLOOR);
            dy = 0;
            jumping = false;
        }
        bn::core::update();
    }
}