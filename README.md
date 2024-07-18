# ROS2 MWEs
A debugging repo with MWEs to explore issues.

## Docker
For reproducibility, we use Docker containers. To build and enter the container, run
```
docker compose run --build test
```
This will mount the `test_ws` directory into the container under `/home/test_ws`. All results are run from the container.


## TODO:
- (Done) make a simple example with nested messages
- (Done) make the cmake mimic the obelisk cmake
- Install CycloneDDS and try the example with that middleware
- Port the entirety of the obelisk repo to this example repo. Install all the deps through docker. Build and run everything manually to verify that cmake isn't the issue.