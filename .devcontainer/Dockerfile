# Use a small, common Linux base
FROM mcr.microsoft.com/devcontainers/base:ubuntu

# Install OS deps you want available to devs & CI
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      build-essential git curl bash ca-certificates make python3 python3-pip \
      && rm -rf /var/lib/apt/lists/*

# Optional: create a non-root user "vscode" for devcontainers/CI parity
ARG USERNAME=vscode
RUN usermod -aG sudo $USERNAME && echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers


WORKDIR /workspaces/project
