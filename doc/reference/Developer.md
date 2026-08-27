# Developer Guide

## Docker Development Container

The `bolt-dev` development container is a development environment packaged as a Docker container that includes all necessary dependencies to build and test `BOLT` locally and to run workflows on GitHub Actions.

### Prerequisites

To build the image the following tools must be installed on your system:

- [Docker Engine](https://docs.docker.com/engine/): Container runtime
- [Docker Buildx](https://docs.docker.com/build/building/multi-platform/): Extended Docker build command supporting multi-architecture builds
- [QEMU](https://www.qemu.org/): Emulation framework for building containers for non-native architectures

### Installing Prerequisites

#### Ubuntu

Follow the [official instructions](https://docs.docker.com/engine/install/ubuntu/#install-using-the-repository) to install Docker Engine and Docker Buildx using `apt`. Afterwards add your Linux User ID (`UID`) to the `docker` group:

```bash
sudo usermod -aG docker $USER
```

Install QEMU:

```bash
docker run --privileged --rm tonistiigi/binfmt --install all
```

Building a multi-architecture Docker image requires a Docker Buildx [builder](https://docs.docker.com/build/builders/) with multi-architecture capabilities.
To create one run:

```bash
docker buildx create \
  --name multi-arch \
  --driver docker-container \
  --driver-opt image=moby/buildkit:latest \
  --platform linux/amd64,linux/arm64,linux/riscv64
```

### Building and Pushing the Image

To build a new multi-architecture `bolt-dev` image with `latest` and version number `<x.y.z>` as tags run:

```bash
docker buildx build \
  --builder multi-arch \
  --platform linux/amd64,linux/arm64,linux/riscv64 \
  --file docker/ubuntu.Dockerfile \
  --tag ghcr.io/cfbaptista/bolt-dev:latest \
  --tag ghcr.io/cfbaptista/bolt-dev:<x.y.z> \
  --output type=registry,push=false \
  .
```

To push the built image to the GitHub Container Registry (GHCR) run:

```bash
docker buildx build \
  --builder multi-arch \
  --platform linux/amd64,linux/arm64,linux/riscv64 \
  --file docker/ubuntu.Dockerfile \
  --tag ghcr.io/cfbaptista/bolt-dev:latest \
  --tag ghcr.io/cfbaptista/bolt-dev:<x.y.z> \
  --output type=registry,push=true \
  .
```

Alternatively, you can build and push in one go:

```bash
docker buildx build \
  --builder multi-arch \
  --platform linux/amd64,linux/arm64,linux/riscv64 \
  --file docker/ubuntu.Dockerfile \
  --tag ghcr.io/cfbaptista/bolt-dev:latest \
  --tag ghcr.io/cfbaptista/bolt-dev:<x.y.z> \
  --push \
  .
```

**NOTE**: Replace `<x.y.z>` with an actual version number, e.g., `2.1.3`.

### Downloading the Image

To download the latest `bolt-dev` image from the GitHub Container Registry (GHCR) run:

```bash
docker pull ghcr.io/cfbaptista/bolt-dev
```

To download a specific version include a tag:

```bash
docker pull ghcr.io/cfbaptista/bolt-dev:0.5.0
```

See the [container registry](https://github.com/CFBaptista/BOLT/pkgs/container/bolt-dev) of `bolt-dev` for a full list of available tags.
