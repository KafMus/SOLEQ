# SOLEQ - Systems Of Linear EQuations
This "library" tries to solve SOLEQs.

## Build
It is recommended to use presets for configuration:

```bash
cmake --preset=[preset-name]
```

And then to build:

```bash
cmake --build build/
```

This will create `build/libSOLEQ.a` file.

## Testing
To run tests:

```bash
cd build/
ctest
```
