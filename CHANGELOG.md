# Changelog

All notable changes to this Vulkan project will be documented in this file.

## [Unreleased] - 2024-11-17

### Added
- Initial Vulkan project setup following vulkan-tutorial.com
- Complete VSCode development environment configuration
  - Build tasks for debug and release modes
  - Debug launch configurations for both builds
  - IntelliSense configuration for C++ and Vulkan headers
  - Shader compilation task using glslangValidator
- Vulkan application with validation layers support
  - Debug callback implementation for validation layer messages
  - Conditional validation layer enabling (debug vs release)
  - GLFW window management integration
- Git repository setup with proper .gitignore
- GitHub repository integration with authentication

### Technical Details
- Debug build: Validation layers enabled, debug symbols included
- Release build: Validation layers disabled, optimized with -O2 -DNDEBUG
- Supports F5 debugging and Ctrl+Shift+P task execution
- Proper handling of Vulkan ICD warnings (gfxstream fallback)

### Build System
- GCC/G++ with C++17 standard
- pkg-config integration for Vulkan and GLFW libraries
- Separate executables for debug (tutorial_debug) and release (tutorial)
- Automated shader compilation with SPIR-V output
