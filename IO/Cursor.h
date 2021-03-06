//////////////////////////////////////////////////////////////////////////////
// This file is part of the LibreMaple MMORPG client                        //
// Copyright © 2015-2016 Daniel Allendorf, 2018-2019 LibreMaple Team        //
//                                                                          //
// This program is free software: you can redistribute it and/or modify     //
// it under the terms of the GNU Affero General Public License as           //
// published by the Free Software Foundation, either version 3 of the       //
// License, or (at your option) any later version.                          //
//                                                                          //
// This program is distributed in the hope that it will be useful,          //
// but WITHOUT ANY WARRANTY; without even the implied warranty of           //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
// GNU Affero General Public License for more details.                      //
//                                                                          //
// You should have received a copy of the GNU Affero General Public License //
// along with this program.  If not, see <https://www.gnu.org/licenses/>.   //
//////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../Graphics/Animation.h"
#include "../Template/EnumMap.h"

namespace jrc
{
//! Class that represents the mouse cursor.
class Cursor
{
public:
    //! Maple-cursor states, linked to the cursor's animation.
    enum State {
        IDLE,
        CAN_CLICK,
        GAME,
        HOUSE,
        CAN_CLICK_2,
        CAN_GRAB,
        GIFT,
        V_SCROLL,
        H_SCROLL,
        V_SCROLL_IDLE,
        H_SCROLL_IDLE,
        GRABBING,
        CLICKING,
        R_CLICK,
        LENGTH
    };

    Cursor();

    void init();

    void draw(float alpha) const;
    void update();
    void set_state(State state);
    void set_position(Point<std::int16_t> position);
    State get_state() const;
    Point<std::int16_t> get_position() const;

private:
    EnumMap<State, Animation> animations;

    State state;
    Point<std::int16_t> position;
    std::int32_t hide_counter;

    static constexpr const std::int64_t HIDE_TIME = 15'000;
};
} // namespace jrc
