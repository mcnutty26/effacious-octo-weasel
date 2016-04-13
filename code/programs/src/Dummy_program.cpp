/*
This file is part of octoDrone.

octoDrone is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

octoDrone is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with octoDrone.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Dummy_program.hpp"

Dummy_program::Dummy_program(CommMod* cm, double xp, double yp, double zp): BaseStation(cm, xp, yp, zp){};

bool Dummy_program::message_callback(Message*){
    return false;
}

void Dummy_program::run(){}
