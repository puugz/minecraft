# minecraft++

A minecraft clone written in C++ using OpenGL.

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

## TODO
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
