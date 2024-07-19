# ROS2 MWEs
A debugging repo with MWEs to explore issues.

## Reproducing the rosidl error

### By Cloning Obelisk Directly
Start up the Obelisk container by running
```
docker compose -f docker-compose-obelisk.yml run --build test
```
Within the container, run the following. The docker compose file doesn't use the nvidia runtime to minimize shared info between the local system and the container - it should still reproduce the error.
```
# activate pixi shell
pixi shell -e dev-no-gpu

# within pixi shell, run these commands
pixi run messages-build
source /obelisk/obelisk_ws/install/setup.bash
pixi run source-obelisk
source /obelisk/obelisk_ws/install/setup.bash
ros2 launch obelisk_ros obelisk_bringup.launch.py config_file_path:=dummy_cpp.yaml device_name:=onboard auto_start:=true bag:=false
```
The nodes cannot completely launch without error, since the setup also cannot initialize GLFW right now, but it will still raise the following error:
```
[jointencoders_passthrough_estimator-3] [rcutils|error_handling.c:65] an error string (message, file name, or formatted message) will be truncated
[jointencoders_passthrough_estimator-3] 
[jointencoders_passthrough_estimator-3] >>> [rcutils|error_handling.c:108] rcutils_set_error_state()
[jointencoders_passthrough_estimator-3] This error state is being overwritten:
[jointencoders_passthrough_estimator-3] 
[jointencoders_passthrough_estimator-3]   'Type support not from this implementation. Got:
[jointencoders_passthrough_estimator-3]     Handle's typesupport identifier (rosidl_typesupport_cpp) is not supported by this library, at /opt/conda/build_artifacts/ros-humble-rosidl-typesupport-cpp-0_1707312462476/work/ros-humble-rosidl-typesupport-cpp/src/work/src/type_support_dispatch.hpp:111
[jointencoders_passthrough_estimator-3]     Could not load library libobelisk_sensor_msgs__rosidl_typesupport_introspection_cpp.so: dlopen error: libstd_msgs__rosidl_typesupport_introspection_cpp.so: cannot open shared object file: No such file or directory, at /opt/conda/build_artifacts/ros-humble-rcutils-0_1707311166947/work/ros-humble-rcutils/src/work/src/shared_library.c:99, at /opt/conda/build_artifacts/ros-humble-rosidl-typesupport-cpp-0_1707312462476/work/ros-humble-rosidl-typesupport-cpp/s, at /opt/conda/build_artifacts/ros-humble-rmw-cyclonedds-cpp-0_1707313040772/work/ros-humble-rmw-cyclonedds-cpp/src/work/src/rmw_node.cpp:1958'
[jointencoders_passthrough_estimator-3] 
[jointencoders_passthrough_estimator-3] with this new error message:
[jointencoders_passthrough_estimator-3] 
[jointencoders_passthrough_estimator-3]   'type_support is null, at /opt/conda/build_artifacts/ros-humble-rmw-cyclonedds-cpp-0_1707313040772/work/ros-humble-rmw-cyclonedds-cpp/src/work/src/rmw_node.cpp:2779'
[jointencoders_passthrough_estimator-3] 
[jointencoders_passthrough_estimator-3] rcutils_reset_error() should be called after error handling to avoid this.
[jointencoders_passthrough_estimator-3] <<<
[jointencoders_passthrough_estimator-3] 
[jointencoders_passthrough_estimator-3] >>> [rcutils|error_handling.c:108] rcutils_set_error_state()
[jointencoders_passthrough_estimator-3] This error state is being overwritten:
[jointencoders_passthrough_estimator-3] 
[jointencoders_passthrough_estimator-3]   'type_support is null, at /opt/conda/build_artifacts/ros-humble-rmw-cyclonedds-cpp-0_1707313040772/work/ros-humble-rmw-cyclonedds-cpp/src/work/src/rmw_node.cpp:2779, at /opt/conda/build_artifacts/ros-humble-rcl-0_1707314261614/work/ros-humble-rcl/src/work/src/rcl/subscription.c:109'
[jointencoders_passthrough_estimator-3] 
[jointencoders_passthrough_estimator-3] with this new error message:
[jointencoders_passthrough_estimator-3] 
[jointencoders_passthrough_estimator-3]   'invalid allocator, at /opt/conda/build_artifacts/ros-humble-rcl-0_1707314261614/work/ros-humble-rcl/src/work/src/rcl/subscription.c:219'
[jointencoders_passthrough_estimator-3] 
[jointencoders_passthrough_estimator-3] rcutils_reset_error() should be called after error handling to avoid this.
[jointencoders_passthrough_estimator-3] <<<
[jointencoders_passthrough_estimator-3] invalid allocator, at /opt/conda/build_artifacts/ros-humble-rcl-0_1707314261614/work/ros-humble-rcl/src/work/src/rcl/subscription.c:219
```

### By Using the MWE
In this minimum working example, we define 3 packages:
1. `test_a_msgs`, which contains a simple definition of a trivial message `TestA` that only has a `std_msgs/Header` field.
2. `test_b_msgs`, which contains a message `TestB` with a `TestA` field in it, so this package should depend on `test_a_msgs`. This simulates the setup in `obelisk`, which has one custom message depend on another.
3. `test_pkg`, which spins a trivial node with a timer that publishes a message of `TestB` type.

The `docker-compose-simple.yml` file is very simple, and mounts the repo root into a directory called `/repro` in the container. The main reason for doing this is to allow caches to persist between sessions in the container to reduce debugging friction.
```
services:
  test:
    shm_size: '12gb'
    build:
      context: .
      dockerfile: Dockerfile.simple
    volumes:
      - ./:/repro
    stdin_open: true
    tty: true
    command: /bin/bash
```

Start up the MWE container by running
```
docker compose -f docker-compose-simple.yml run --build test
```
Within the container, run
```
# activate pixi shell
pixi shell

# within pixi shell, run these commands
cd test_ws
rm -rf build install
colcon build --symlink-install --packages-select test_a_msgs test_b_msgs --parallel-workers $(nproc)
source install/setup.bash
colcon build --symlink-install --parallel-workers $(nproc)
source install/setup.bash
ros2 run test_pkg test_node
```
This will raise the error
```
/repro/test_ws/install/test_pkg/lib/test_pkg/test_node: error while loading shared libraries: librosidl_typesupport_cpp.so: cannot open shared object file: No such file or directory
```
Upon running `pixi list`, we see that `rosidl_typesupport_c` is installed (rosidl-related deps shown here):
```
ros-humble-rosidl-adapter                          3.1.5         py311hb335429_6      59.8 KiB   conda  ros-humble-rosidl-adapter-3.1.5-py311hb335429_6.tar.bz2
ros-humble-rosidl-cli                              3.1.5         py311hb335429_6      35.5 KiB   conda  ros-humble-rosidl-cli-3.1.5-py311hb335429_6.tar.bz2
ros-humble-rosidl-cmake                            3.1.5         py311hb335429_6      27.5 KiB   conda  ros-humble-rosidl-cmake-3.1.5-py311hb335429_6.tar.bz2
ros-humble-rosidl-default-generators               1.2.0         py311hb335429_6      12.4 KiB   conda  ros-humble-rosidl-default-generators-1.2.0-py311hb335429_6.tar.bz2
ros-humble-rosidl-default-runtime                  1.2.0         py311hb335429_6      11.5 KiB   conda  ros-humble-rosidl-default-runtime-1.2.0-py311hb335429_6.tar.bz2
ros-humble-rosidl-generator-c                      3.1.5         py311hb335429_6      32.5 KiB   conda  ros-humble-rosidl-generator-c-3.1.5-py311hb335429_6.tar.bz2
ros-humble-rosidl-generator-cpp                    3.1.5         py311hb335429_6      35.8 KiB   conda  ros-humble-rosidl-generator-cpp-3.1.5-py311hb335429_6.tar.bz2
ros-humble-rosidl-generator-py                     0.14.4        py311hb335429_6      45.2 KiB   conda  ros-humble-rosidl-generator-py-0.14.4-py311hb335429_6.tar.bz2
ros-humble-rosidl-parser                           3.1.5         py311hb335429_6      55.3 KiB   conda  ros-humble-rosidl-parser-3.1.5-py311hb335429_6.tar.bz2
ros-humble-rosidl-runtime-c                        3.1.5         py311hb335429_6      31.7 KiB   conda  ros-humble-rosidl-runtime-c-3.1.5-py311hb335429_6.tar.bz2
ros-humble-rosidl-runtime-cpp                      3.1.5         py311hb335429_6      20 KiB     conda  ros-humble-rosidl-runtime-cpp-3.1.5-py311hb335429_6.tar.bz2
ros-humble-rosidl-runtime-py                       0.9.3         py311hb335429_6      36 KiB     conda  ros-humble-rosidl-runtime-py-0.9.3-py311hb335429_6.tar.bz2
ros-humble-rosidl-typesupport-c                    2.0.1         py311hb335429_6      32.1 KiB   conda  ros-humble-rosidl-typesupport-c-2.0.1-py311hb335429_6.tar.bz2
ros-humble-rosidl-typesupport-cpp                  2.0.1         py311hb335429_6      31.1 KiB   conda  ros-humble-rosidl-typesupport-cpp-2.0.1-py311hb335429_6.tar.bz2
ros-humble-rosidl-typesupport-fastrtps-c           2.2.2         py311hb335429_6      31.3 KiB   conda  ros-humble-rosidl-typesupport-fastrtps-c-2.2.2-py311hb335429_6.tar.bz2
ros-humble-rosidl-typesupport-fastrtps-cpp         2.2.2         py311hb335429_6      33.3 KiB   conda  ros-humble-rosidl-typesupport-fastrtps-cpp-2.2.2-py311hb335429_6.tar.bz2
ros-humble-rosidl-typesupport-interface            3.1.5         py311hb335429_6      13 KiB     conda  ros-humble-rosidl-typesupport-interface-3.1.5-py311hb335429_6.tar.bz2
ros-humble-rosidl-typesupport-introspection-c      3.1.5         py311hb335429_6      29.7 KiB   conda  ros-humble-rosidl-typesupport-introspection-c-3.1.5-py311hb335429_6.tar.bz2
ros-humble-rosidl-typesupport-introspection-cpp    3.1.5         py311hb335429_6      29.8 KiB   conda  ros-humble-rosidl-typesupport-introspection-cpp-3.1.5-py311hb335429_6.tar.bz2

```

### Comparing the MWE Without Pixi
We now run the same MWE but without using pixi, instead installing all of the required dependencies via pre-built ROS binaries in the docker container. To start the container, run
```
docker compose -f docker-compose-simple-nopixi.yml run --build test
```
Within the container, run
```
cd test_ws
rm -rf build install
colcon build --symlink-install --packages-select test_a_msgs test_b_msgs --parallel-workers $(nproc)
source install/setup.bash
colcon build --symlink-install --parallel-workers $(nproc)
source install/setup.bash
ros2 run test_pkg test_node
```
This will produce periodic output like this:
```
[INFO] [1721411615.185264056] [test_node]: Publishing message
[INFO] [1721411616.185296777] [test_node]: Publishing message
[INFO] [1721411617.185177851] [test_node]: Publishing message
```
