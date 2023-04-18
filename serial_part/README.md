# Serial implementation
The serial compilation is done through a `Makefile` with the command `make`, generating objectfiles before finally generating the exectutable. Added some simple timing to `serial_main.c`. This gives the following results, with the regular timestep implementation first, and the fast one second.
```
nx=1001, ny=1001, T=2, dt=0.002, error=3.000719e-15
Time used: 6.809480
nx=1001, ny=1001, T=2, dt=0.002, error=3.016820e-15
Time used: 5.650085
```