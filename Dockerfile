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

# install pixi
RUN curl -fsSL https://pixi.sh/install.sh | bash

# reproduce error by cloning obelisk
RUN git clone https://github.com/Caltech-AMBER/obelisk
WORKDIR /obelisk
RUN git checkout 46f503cf2ba7068b2b576e5540eb3ab17cea7f10
ENV OBELISK_ROOT=/obelisk
