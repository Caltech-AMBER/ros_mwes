# ROS2 MWEs
A debugging repo with MWEs to explore issues.

## Docker
For reproducibility, we use Docker containers. To build and enter the container, run
```
docker compose run --build test
```
This will mount the `test_ws` directory into the container under `/home/test_ws`. All results are run from the container.
