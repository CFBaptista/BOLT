# Developer Guide

## Docker Development Container

The `bolt-dev` development container is a development environment packaged as a Docker container that includes all necessary dependencies to build and test `BOLT` locally and run workflows on GitHub Actions.

### Prerequisites

To build the image locally the following tools must be installed on your system:

- **Docker**: Container runtime
- **Docker Buildx**: Extended Docker build command supporting multi-platform builds
- **QEMU**: Emulation framework for building containers for non-native platforms

### Installing Prerequisites

#### Ubuntu

Update the Ubuntu package lists:

```bash
sudo apt update
```

Install Docker and Docker Buildx:

```bash
sudo apt install docker-ce docker-buildx
```

Add your Linux user ID to the `docker` group:

```bash
sudo usermod -aG docker $USER
```

Install QEMU:

```bash
sudo apt-get install -y qemu-user-static binfmt-support
```

Register QEMU emulators:

```bash
docker run --privileged --rm tonistiigi/binfmt --install all
```

### Building the Container

To build the development container for a particular platform run:

```bash
docker buildx build --platform <platform> --load -t <tag> -f docker/ubuntu.Dockerfile .
```

**Parameters:**
- `<platform>`: Target platform (e.g., `linux/amd64`, `linux/arm64`, `linux/riscv64`)
- `<tag>`: Container image tag (e.g., `bolt-dev:1.0.1-amd64`)

**Example:**
```bash
# Build for AMD64 / x86-64
docker buildx build --platform linux/amd64 --load -t bolt:amd64 -f docker/ubuntu.Dockerfile .

# Build for ARM64 / AArch64
docker buildx build --platform linux/arm64 --load -t bolt:arm64 -f docker/ubuntu.Dockerfile .

# Build for RISC-V
docker buildx build --platform linux/riscv64 --load -t bolt:riscv64 -f docker/ubuntu.Dockerfile .
```

### Using the Container

Run the native container interactively:

```bash
docker run -it --rm -v $(pwd):/app <tag>
```

Parameters:

- `<tag>`: The tag corresponding to the native Docker image.
