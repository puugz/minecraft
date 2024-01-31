# minecraft++

A minecraft clone written in C++ using OpenGL.

![minecraftpp_screenshot](https://github.com/puugz/minecraft/assets/33222334/6441d066-692b-481e-a1b3-9e5a391cc4e1)

## Features
- [x] Simple world generation
- [x] Free-look style camera

## Using submodules
```
git clone --recurse-submodules https://github.com/puugz/minecraft
```
or, after cloning:
```
git submodule update --init --recursive
```

## Textures
Textures are from [Faithless](https://www.curseforge.com/minecraft/texture-packs/faithless)

## TODO
- [ ] Framebuffer resizing
- [ ] Fix trees (blocks aren't placed if in another chunk)
- [ ] Fix water transparency
- [ ] Add vertical chunks?
- [ ] Block breaking & placing
- [ ] Chunk queueing
- [ ] Multithreaded chunk generation
- [ ] Frustum culling (hide what is not in camera view)
- [ ] View distance (hide chunks that are too far away)
- [ ] Occlusion culling (hide invisible chunks)
- [ ] Ambient occlusion?
- [ ] Infinite world?
- [ ] Physics?
- [ ] Lighting?
