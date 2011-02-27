## Based mostly on the documentation from Imran Nazar's jsgb project:

- https://github.com/Two9A/jsGB
- http://imrannazar.com/GameBoy-Emulation-in-JavaScript

The MMU's memory model has been modified somewhat to place all of the accessible
memory into a flat array, which the MMU indexes into. The existing MMU.rb/wb
functionality abstractions need to be left in, as there is some special handling
for certain memory locations (eg, exiting BIOS, updating some GPU flags), as well
as holes in the memory space that should always return zero.