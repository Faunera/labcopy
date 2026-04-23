# Dockerfile for compiling C++ modules
FROM alpine:3.23.2

RUN apk add g++ make vulkan-tools vulkan-loader-dev vulkan-validation-layers spirv-tools-dev libxxf86vm-dev libxi-dev glfw-dev glm-dev shaderc

WORKDIR /app
COPY ./ ./

CMD ["make", "container"]

