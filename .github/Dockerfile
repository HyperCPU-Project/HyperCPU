FROM debian:latest

ARG USER=ci

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates curl git      \
    build-essential gcc g++         \
    clang lld ninja-build sudo      \
    python3 cmake                   \
    && rm -rf /var/lib/apt/lists/* \

RUN useradd -m ${USER} \
    && echo "${USER} ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

WORKDIR /home/${USER}/workspace
