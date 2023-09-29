# Base layer to compile asm code

FROM ubuntu:22.04

MAINTAINER Nicolas Huynh <nihuynh@student.42.fr>

WORKDIR /workdir

RUN apt-get update && apt-get install -y \
  nasm \
  gdb \
  build-essential \
  && rm -rf /var/lib/apt/lists/*

# Run shell if container is started
CMD ["/bin/bash"]