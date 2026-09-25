#include <bn_backdrop.h>
#include <bn_core.h>
#include <bn_keypad.h>
#include <bn_sprite_ptr.h>

#include "bn_sprite_items_bun.h"

#define FLOOR (80 - 8)

int main()
{
    bool jumping = false;
    bool loadingJump = false;
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
        if (!jumping && !loadingJump)
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

        // super jump. jump in relation to a button hold.
        //  a is x btw
        if (bn::keypad::a_held())
        {
            // get char to stop jumping
            loadingJump = true;

            // increase jump_strength when held
            jump_strength = jump_strength + 0.1;

            // limit
            if (jump_strength >= 4)
            {
                jump_strength = 4;
            }
        }

        // count how long the button is pressed for
        if (bn::keypad::a_released())
        {
            dy = dy - jump_strength;

            // reset jump_strength
            jump_strength = 1;

            loadingJump = false;
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