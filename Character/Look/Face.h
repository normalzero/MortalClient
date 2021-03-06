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
#include "../../Graphics/Texture.h"
#include "../../Template/EnumMap.h"
#include "BodyDrawInfo.h"

namespace jrc
{
class Expression
{
public:
    enum Id {
        DEFAULT,
        BLINK,
        HIT,
        SMILE,
        TROUBLED,
        CRY,
        ANGRY,
        BEWILDERED,
        STUNNED,
        BLAZE,
        BOWING,
        CHEERS,
        CHU,
        DAM,
        DESPAIR,
        GLITTER,
        HOT,
        HUM,
        LOVE,
        OOPS,
        PAIN,
        SHINE,
        VOMIT,
        WINK,
        LENGTH
    };

    static Id byaction(std::size_t action);

    static const EnumMap<Id, std::string> names;
};

class Face
{
public:
    Face(std::int32_t face_id);

    void draw(Expression::Id expression,
              std::uint8_t frame,
              const DrawArgument& args) const;

    std::uint8_t next_frame(Expression::Id expression,
                            std::uint8_t frame) const;
    std::int16_t get_delay(Expression::Id expression,
                           std::uint8_t frame) const;
    [[nodiscard]] std::string_view get_name() const noexcept;

private:
    struct Frame {
        Texture texture;
        std::uint16_t delay;

        Frame(nl::node src)
        {
            texture = src["face"];

            Point<std::int16_t> shift = src["face"]["map"]["brow"];
            texture.shift(-shift);

            delay = src["delay"];
            if (delay == 0) {
                delay = 2500;
            }
        }
    };

    std::unordered_map<std::uint8_t, Frame> expressions[Expression::LENGTH];
    std::string name;
};
} // namespace jrc
