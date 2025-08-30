# Shader Compilation Using glslc
```
glslc -fshader-stage=vertex vertex_shader.glsl
glslc -fshader-stage=fragment --target-env=opengl -c blur_shader.glsl -o blur.spv
```
