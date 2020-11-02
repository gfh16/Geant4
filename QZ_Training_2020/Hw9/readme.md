```shell

useG4
mkdir B1_build
cd B1_build/
cmake ../B1
make -j4
./exampleB1

```


```
/vis/open OGL
/vis/drawVolume
/control/execute init_vis.mac

/gun/particle mu+
# gamma,proton,e+,neutron,photon,pi
/gun/energy 10 GeV
/run/beamOn 10

```
