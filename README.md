### Pre-requisites

- Docker

### Compile and Run

```
docker run \
  --rm \
  -v $(pwd):/src \
  -u $(id -u):$(id -g) \
  emscripten/emsdk \
  emcc --no-entry game.cpp -o life.wasm -s EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' -s EXPORTED_FUNCTIONS='["_daysInWeek"]'
```
