
# SCOLIB — Simulation COre LIBrary

**SCOLIB** is a modern, embeddable C++ SPICE-lite core with a clear roadmap to electro‑optical/photonics simulation.
- Minimal but robust analyses: **.OP, .DC, .AC, .TRAN** (to be implemented).
- Clean C++20 API + optional **Python bindings** (pybind11).
- Dual-licensing: **AGPL‑3.0‑or‑later** + **Commercial** (add your commercial terms).

> Version: 0.1.0 (foundation scaffold)

---

## Repo Layout

```
scolib/
  .github/workflows/ci.yml
  bindings/python/scolib_py.cpp
  cmake/scolibConfig.cmake.in
  include/scolib/scolib.hpp
  include/scolib/version.hpp
  src/core/version.cpp
  src/circuit/circuit.cpp
  tests/test_basic.cpp
  CMakeLists.txt
  LICENSE
  .gitignore
  README.md
```

---

## Build (C++)

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
ctest --test-dir build --output-on-failure
```

## Python Bindings (optional)

Requires Python3 and `pybind11`:

```bash
python -m pip install --upgrade pip
python -m pip install pybind11
cmake -S . -B build -DSCOLIB_BUILD_PYTHON=ON
cmake --build build -j
python - <<'PY'
import sys, importlib.util, pathlib
# Load in-place module from build tree (Linux/Mac common path shown)
cand = list(pathlib.Path('build').rglob('scolib*.so')) + list(pathlib.Path('build').rglob('scolib*.pyd'))
print('Found:', cand[:1])
PY
```

---

## Create a New GitHub Repo & Push

1. **Create** an empty repo on GitHub called `scolib` (no README/license).  
2. Locally:

```bash
cd scolib
git init
git add .
git commit -m "chore: bootstrap SCOLIB foundation (CMake, tests, pybind11 skeleton, CI)"
git branch -M main
git remote add origin https://github.com/<your-user>/scolib.git
git push -u origin main
```

---

## CI (GitHub Actions)

A cross‑platform CI is included at `.github/workflows/ci.yml`:
- **Ubuntu, macOS, Windows**
- Configure with CMake, build, and run tests
- Also builds **Python bindings** (installs `pybind11`) to ensure the module compiles

You can run it locally with `act` (optional).

---

## Next Steps (Day 1–7)

- [ ] Implement **graph + MNA scaffolding** (`Stamp` interface, `SparseTriplet`, `KCL/KVL` tests)
- [ ] Device stubs: **R, C, L, Vsrc, Isrc** with stamping hooks
- [ ] Newton–Raphson loop skeleton for **.OP**
- [ ] Parser outline for a minimal SPICE netlist
- [ ] Add docstrings & Python examples

---

## License

AGPL‑3.0‑or‑later for open use. Prepare a **commercial license** (separate file) for closed‑source SDK customers.
```

