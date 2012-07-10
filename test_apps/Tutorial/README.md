Tutorial Simulation
===================
This is a very simple 'Tutorial' application. The intent is to help me get
familiar with how all of the pieces of the simulation fit together. Hopefully
it will help others who are starting out writing simulations.

The simulation creates a series of objects, and then passes a message around in
a ring. When the messages reaches the first node again the simulation ends.

Build
-----
I have chosen to use cmake to build these examples. The current setup assumes
that the warped files have been installed in a directory off of the root pdes
source (at the same level as utils and warped) called 'build' (when running
configure in the warped directory, set the 'prefix' parameter to this directory)