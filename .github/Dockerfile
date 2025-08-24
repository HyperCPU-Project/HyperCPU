FROM debian:latest

ARG USER=ci
ARG BAZELISK_TAG=v1.19.0

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates curl git      \
    build-essential gcc g++         \
    clang lld ninja-build sudo      \
    python3                         \
    && rm -rf /var/lib/apt/lists/*

RUN curl -fsSL -o /usr/local/bin/bazelisk \
      "https://github.com/bazelbuild/bazelisk/releases/download/${BAZELISK_TAG}/bazelisk-linux-amd64" \
    && chmod 0755 /usr/local/bin/bazelisk \
    && ln -s /usr/local/bin/bazelisk /usr/local/bin/bazel

RUN useradd -m ${USER} \
    && echo "${USER} ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

WORKDIR /home/${USER}/workspace
