# ROS2 MWEs
A debugging repo with MWEs to explore issues.

## Docker
For reproducibility, we use Docker containers. To build and enter the container, run
```
docker compose run --build test
```
This will mount the `test_ws` directory into the container under `/home/test_ws`. All results are run from the container.


## Reproducing the rosidl error

### By Cloning Obelisk Directly
Within the container, run
```
pixi shell -e dev-no-gpu
pixi run messages-build
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

## TODO:
- (Done) make a simple example with nested messages
- (Done) make the cmake mimic the obelisk cmake
- Install CycloneDDS and try the example with that middleware
- Port the entirety of the obelisk repo to this example repo. Install all the deps through docker. Build and run everything manually to verify that cmake isn't the issue.