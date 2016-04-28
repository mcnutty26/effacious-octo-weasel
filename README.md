# octoDrone
A discrete event network simulator for drone networks

##First time setup
There is a setup script supplied in the code directory which will set up octoDrone and its dependencies for you and then build the entire project. Note that this process requires root access.

`cd code && ./setup.sh`

## Building octoDrone
If you wish to build the entire project a script is supplied in the code directory

`cd code && ./build.sh`

If you wish to build an individual component, `cd` into its directory and run `make`

##Creating a Simulation
Instantiate a simulation environment with sensor data, a timestep, and a visualisation boolean:

`Environment* env = new Environment(*sensor_map, 1.0, true);`

Create communication modules as appropriate (see documentation for more information):

`CommMod* my_comm_mod = new Basic(env, &stdout_lock);`

Create drones and a basestation as appropriate (see documentation for more information):

`BasicTest* my_drone = new BasicTest(my_comm_mod, 0.0, 0.0, 0.0, 0.0, env, false);`

Register drones and the base station with the environment:

`env->addDrone(my_drone);`

`env->setBaseStation(my_base_station);`

Run the simulation:
`env->run();`

##Examples

A number of examples of programs, communications modules, and simulations are provided with octoDrone. These can be found, with make files, in the *programs*, *liboctodronecomms*, and *simulations* directories (under *code*) respectively. If at any point you require more information on individual components, full documentiation of the octoDrone API is provided in the documents folder.

##Licenses
* octoDrone is released under the GPL v3 license (or later)
* the included report is released under the Creative Commons Attribution-ShareAlike 4.0 International license
* the included glew binary is used under license
* the included glfw binary is used under license

###glew
The OpenGL Extension Wrangler Library
Copyright (C) 2008-2016, Nigel Stewart <nigels[]users sourceforge net>
Copyright (C) 2002-2008, Milan Ikits <milan ikits[]ieee org>
Copyright (C) 2002-2008, Marcelo E. Magallon <mmagallo[]debian org>
Copyright (C) 2002, Lev Povalahev
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, 
  this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, 
  this list of conditions and the following disclaimer in the documentation 
  and/or other materials provided with the distribution.
* The name of the author may be used to endorse or promote products 
  derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
THE POSSIBILITY OF SUCH DAMAGE.

###glfw
Copyright © 2002-2006 Marcus Geelnard

Copyright © 2006-2011 Camilla Berglund

This software is provided ‘as-is’, without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

* The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
* Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
* This notice may not be removed or altered from any source distribution.

