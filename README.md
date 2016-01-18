# effacious-octo-weasel
A drone network simulator and framework for autonomous drone tasking

## Building and running effacious-octo-weasel
TODO

## Code structure
#### Environment
Represents the simulation, and is responsible for propogating messages.

#### Messagable
Represents nodes in the simulation

#### Drone
Messagable with mobility

#### BaseStation
Static Messagable

#### CommMod
Handles communication for a messagable

### Unsorted stuff
####comms
the idea is that this is the life-cycle of a message
messageable decides that it needs to send a message
it decides two things, the contents and the recipient
it then passes this information to its commMod
commMod adds protocol layers including things like error checking
it then broadcasts this string and awaits any acknowledgement signals that are required
the recipient's commMod gets the message and strips away protocol layers and passes the instructional part to its Messageable
the messageable then follows these instructions if they are appropriate
