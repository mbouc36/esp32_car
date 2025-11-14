# Use a small, common Linux base
FROM mcr.microsoft.com/devcontainers/base:ubuntu24.04

# Install OS deps you want available to devs & CI
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      build-essential git curl bash ca-certificates make python3 python3-pip \
      && rm -rf /var/lib/apt/lists/*

# Optional: create a non-root user "vscode" for devcontainers/CI parity
ARG USERNAME=vscode
RUN usermod -aG sudo $USERNAME && echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# Basic deps + arduino-cli
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    curl ca-certificates python3 python3-pip git udev && \
    rm -rf /var/lib/apt/lists/*

# Install arduino-cli
RUN curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh && \
    mv bin/arduino-cli /usr/local/bin/arduino-cli

# Prepare Arduino directories (cacheable)
RUN useradd -m dev && mkdir -p /sketchbook && chown -R dev:dev /sketchbook /home/dev
USER dev
WORKDIR /workspaces/project

# Official Espressif package index for ESP32:
ENV ARDUINO_ADDITIONAL_URLS="https://espressif.github.io/arduino-esp32/package_esp32_index.json"

# Initialize config and register the ESP32 index
RUN arduino-cli config init && \
    arduino-cli config set board_manager.additional_urls ${ARDUINO_ADDITIONAL_URLS}

# Retry loop to tolerate flaky networks during build
RUN set -eux; \
    for i in 1 2 3; do \
      arduino-cli core update-index && \
      arduino-cli core install esp32:esp32 && \
      exit 0 || echo "arduino-cli install failed (attempt $i), retrying..." && sleep 15; \
    done; \
    echo "arduino-cli install failed after retries" && exit 1

WORKDIR /workspaces/project
