FROM ubuntu:latest

ARG USER=bazel
ARG BAZELISK_TAG=v1.15.0

RUN apt update && apt install -y --no-install-recommends \
    git cmake clang libre2-10 libre2-dev python3 python3-pip cmake wget make gcc g++ \
    && pip3 install --no-cache-dir --break-system-packages conan \
    && rm -rf /var/lib/apt/lists/*

RUN wget https://github.com/bazelbuild/bazelisk/releases/download/${BAZELISK_TAG}/bazelisk-linux-amd64 && \
    chmod 755 bazelisk-linux-amd64 && \
    mv bazelisk-linux-amd64 /usr/bin/bazelisk
