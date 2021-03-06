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
#include "../Template/Interpolated.h"
#include "../Template/Rectangle.h"
#include "Texture.h"

#include <algorithm>
#include <vector>

namespace jrc
{
//! A single frame within an animation.
class Frame
{
public:
    Frame(nl::node src);
    Frame() noexcept;

    void draw(const DrawArgument& args) const;

    std::uint8_t start_opacity() const;
    std::uint8_t end_opacity() const;
    std::uint16_t start_scale() const;
    std::uint16_t end_scale() const;
    std::uint16_t get_delay() const;
    Point<std::int16_t> get_origin() const;
    Point<std::int16_t> get_dimensions() const;
    Point<std::int16_t> get_head() const;
    Rectangle<std::int16_t> get_bounds() const;
    float opc_step(std::uint16_t timestep) const;
    float scale_step(std::uint16_t timestep) const;

private:
    Texture texture;
    std::uint16_t delay;
    std::pair<std::uint8_t, std::uint8_t> opacities;
    std::pair<std::int16_t, std::int16_t> scales;
    Rectangle<std::int16_t> bounds;
    Point<std::int16_t> head;
};

//! Class which consists of multiple textures to make an Animation.
class Animation
{
public:
    Animation(nl::node source);
    Animation() noexcept;

    bool update();
    bool update(std::uint16_t timestep);
    void reset();

    void draw(const DrawArgument& arguments, float inter) const;

    std::uint16_t get_delay(std::int16_t frame) const;
    std::uint16_t get_delay_until(std::int16_t frame) const;
    Point<std::int16_t> get_origin() const;
    Point<std::int16_t> get_dimensions() const;
    Point<std::int16_t> get_head() const;
    Rectangle<std::int16_t> get_bounds() const;

private:
    const Frame& get_frame() const;

    std::vector<Frame> frames;
    bool animated;
    bool zigzag;

    Nominal<std::int16_t> frame;
    Linear<float> opacity;
    Linear<float> xy_scale;

    std::uint16_t delay;
    std::int16_t frame_step;
    float opcstep;

    std::int16_t repeat;
    bool finished;
};
} // namespace jrc
