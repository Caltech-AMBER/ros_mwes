# syntax=docker/dockerfile:1

# base image
FROM ubuntu:22.04 as base
SHELL ["/bin/bash", "-c"]

# set timezone
ENV TZ=America/Los_Angeles
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# basic dependencies
RUN apt-get update && apt-get install -y \
    curl \
    build-essential \
    cmake \
    clang-tools-12 \
    nano \
    vim \
    git \
    python3-dev \
    python-is-python3 \
    python3-pip \
    python3-argcomplete \
    mesa-utils \
    x11-apps \
    libyaml-dev \
    mesa-common-dev \
    libglfw3-dev \
    locales \
    sudo && \
    rm -rf /var/lib/apt/lists/* && \
    locale-gen en_US.UTF-8

# ROS2
RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key \
        -o /usr/share/keyrings/ros-archive-keyring.gpg && \
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] \
        http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | \
        tee /etc/apt/sources.list.d/ros2.list > /dev/null && \
    apt-get update -y && \
    apt-get install -y \
    ros-humble-ros-base \
    ros-humble-rosidl-generator-cpp \
    ros-humble-rosidl-default-generators
RUN echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
WORKDIR /home/test_ws
