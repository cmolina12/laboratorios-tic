# Forzamos plataforma x86 para asegurar compatibilidad de 32 bits
FROM --platform=linux/amd64 ubuntu:24.04

# Evitar preguntas interactivas durante la instalación
ENV DEBIAN_FRONTEND=noninteractive

# Instalar Clang, Make y las librerías esenciales de 32 bits (multilib)
RUN apt-get update && apt-get install -y \
    clang \
    lldb \
    make \
    gcc-multilib \
    g++-multilib \
    libc6-dev-i386 \
    git \
    && rm -rf /var/lib/apt/lists/*

# Directorio donde estará tu código dentro del contenedor
WORKDIR /workspace