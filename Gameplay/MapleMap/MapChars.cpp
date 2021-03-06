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
#include "MapChars.h"

namespace jrc
{
void MapChars::draw(Layer::Id layer,
                    double viewx,
                    double viewy,
                    float alpha) const
{
    chars.draw(layer, viewx, viewy, alpha);
}

void MapChars::update(const Physics& physics)
{
    for (; !spawns.empty(); spawns.pop()) {
        const CharSpawn& spawn = spawns.front();

        std::int32_t cid = spawn.get_cid();
        nullable_ptr<OtherChar> ochar = get_char(cid);
        if (ochar) {
        } else {
            chars.add(spawn.instantiate());
        }
    }

    chars.update(physics);
}

void MapChars::spawn(CharSpawn&& spawn)
{
    spawns.emplace(std::move(spawn));
}

void MapChars::remove(std::int32_t cid)
{
    chars.remove(cid);
}

void MapChars::clear()
{
    chars.clear();
}

void MapChars::send_movement(std::int32_t cid,
                             const std::vector<Movement>& movements)
{
    if (nullable_ptr<OtherChar> otherchar = get_char(cid)) {
        otherchar->send_movement(movements);
    }
}

void MapChars::update_look(std::int32_t cid, const LookEntry& look)
{
    if (nullable_ptr<OtherChar> otherchar = get_char(cid)) {
        otherchar->update_look(look);
    }
}

nullable_ptr<OtherChar> MapChars::get_char(std::int32_t cid)
{
    return chars.get(cid);
}
} // namespace jrc
