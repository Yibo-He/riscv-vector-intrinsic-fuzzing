# RVV Intrinsic Fuzzing (RIF) for RVV C Intrinsic v0.11

This repository aims to create fuzz testing for the RVV C intrinsic v0.11.
This repository is forked from [the sifive repository](https://github.com/sifive/riscv-vector-intrinsic-fuzzing).

Main changes:
- Use the v0p10 compatible header to support transition from v0.10 to v0.11

## 0 - Compiler Support

### 0.0 - Important RVV Intrinsic Release (before Aug 06, 2024)

|                           Version                            |     Time     |                            Update                            |
| :----------------------------------------------------------: | :----------: | :----------------------------------------------------------: |
| [v0.10](https://github.com/riscv-non-isa/rvv-intrinsic-doc/releases/tag/v0.10) | Apr 12, 2021 |                     Improve readability.                     |
| [v0.11](https://github.com/riscv-non-isa/rvv-intrinsic-doc/releases/tag/v0.11) | Feb 08, 2023 | From v0.10 to v0.11, the following changes have been made: - The two sets of intrinsics, non-policy and policy, is simplified into   a single set. This reduces 25% of the out-going intrinsics. - A function `unsigned __riscv_vlenb()`  was added to access the   read-only CSR `vlenb` - The operand order of `vmerge` and `vcompress` is adjusted so `vvm` and   `vxm` mnemonics intrinsics has an aligned interface. - All intrinsics now have a common prefix `__riscv_` |
| [v0.12](https://github.com/riscv-non-isa/rvv-intrinsic-doc/releases/tag/v0.12.0) | Jul 27, 2023 | New changes in v0.12:  - Add reinterpret cast between vector boolean and vector integer m1 value - Let fixed-point intrinsics model control the rounding mode - Add variants of the floating-point intrinsics to control the rounding mode - Prune legacy intrinsics from the document - Add missing _mu variants for some overloaded intrinsics - Add api-testing and overloaded-api-testing with policy - Remove vread_csr and vwrite_csr |
| [v1.0-rc0](https://github.com/riscv-non-isa/rvv-intrinsic-doc/releases/tag/v1.0-rc0) | Dec 21, 2023 | This is a pre-release version for requesting for comment in the architecture review process of RVI |
| [v1.0-rc2](https://github.com/riscv-non-isa/rvv-intrinsic-doc/releases/tag/v1.0-rc2) (latest) | Aug 02, 2024 | Address comment from architecture review committee. Tweak description for vxsat |

#### Note:

- RIF (RVV Intrinsic Fuzzing) supports rvv v0.10
- The v0p10 compatible header supports transition from v0.10 to v0.11
- We currently do not have a compatible header / patch in the upstream to support compatibility for v0.11 to v0.12

### 0.1 - RVV Intrinsic GCC and Clang Support

| [RVV Intrinsic](https://github.com/riscv-non-isa/rvv-intrinsic-doc) |     [GCC](https://gcc.gnu.org)      |    [LLVM (Clang)](https://llvm.org)    |
| :----------------------------------------------------------: | :---------------------------------: | :------------------------------------: |
|                            v0.10                             | [12.x](https://gcc.gnu.org/gcc-12/) |   [15.x](https://releases.llvm.org)    |
|                           v0.11.x                            | [13.x](https://gcc.gnu.org/gcc-13/) |   [16.x](https://releases.llvm.org)    |
|                           v0.12.x                            |                                     | [17.x-18.x](https://releases.llvm.org) |
|                            v1.0.x                            | [14.x](https://gcc.gnu.org/gcc-14/) |                                        |


## 1 - RIF Usage

### 1.1 - How To Use?

`rif-test` is the current driver to fuzz all existing intrinsics in `include/CustomOperator.def`.

```
./rif-test --help
usage: rif-test [-h] [--gen {random_gen,fused_gen}] [--sim SIM] [--cc CC] 
                [--mode {full,fast}] [--node NODE] [--arch ARCH] [--abi ABI]
                [--cflags CFLAGS] [--seed SEED] [--random {on,off}] [--has-policy]

optional arguments:
  -h, --help            show this help message and exit
  --gen {random_gen,fused_gen}
                        Random gen pattern
  --sim SIM             Path to simulator
  --cc CC               Path to compiler
  --mode {full,fast}    Testing mode
  --node NODE           Minimal # of node
  --arch ARCH           Target arch config, default is rv64gcv_zvfh
  --abi ABI             Target ABI config, default is lp64d
  --cflags CFLAGS       Default compilation flag
  --seed SEED           Fixed random seed
  --random {on,off}     Feed random seed
  --has-policy          Enable policy if set
```

RIF already have linked a pre-built simulator from [metal-run](https://github.com/sifive/metal-run). So the minimum
requirement for testing it to specify a compiler that is able to compile RISC-V vector intrinsics. To specify your
own simulator (QEMU), please add `${PATH_TO_QEMU_BINARY} ${CPU_CONFIGS}` of how you wish to run
`${PATH_TO_QEMU_BINARY} ${CPU_CONFIGS} ${PATH_TO_ELF}` under --sim.


```
$ git clone https://github.com/sifive/rvv-intrinsic-fuzzing
$ mkdir test && cd test
$ ../rvv-intrinsic-fuzzing/rif-test --cc <YOUR-COMPILER-PATH>
$ make
```

### 1.2 - How To Build?

```
$ git clone https://github.com/sifive/rvv-intrinsic-fuzzing
$ cd rvv-intrinsic-fuzzing
$ mkdir build; cd build
$ cmake ..
$ make
$ ./tool/random_gen --help
Usage: random_gen [OPTION...]

  -c, --code=FILE            C code file, default filename: 'output.c'
  -d, --dot=FILE             Graphviz visualization file, default filename is
                             'output.dot'
  -h                         Give this help list
  -m, --march=ARCH_STRING    Arch string for testing, default is rv64gcv
  -n, --nodes-to-gen=NODES_TO_GEN
                             The number of nodes to generate for the graph.
  -r, --root=OPERATOR_ENUM   Initial node for the graph generation, default
                             root is 'AddVV32'
  -s, --seed=RANDOM_SEED     Seed for random number generator, default seed is
                             '0xdeadbeef'
  -v, --verbose              Produce verbose output
  -?, --help                 Give this help list
      --usage                Give a short usage message

Mandatory or optional arguments to long options are also mandatory or optional
for any corresponding short options.
```

### 1.3 - Testing GCC 13

#### Getting gcc 13
- [RISC-V GNU Compiler Toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain)
- [GCC 13](https://gcc.gnu.org/gcc-13/)

#### Run RIF
```
$ git clone https://github.com/sifive/rvv-intrinsic-fuzzing
$ mkdir test && cd test
$ ../rvv-intrinsic-fuzzing/rif-test --arch rv64gcv --cc <YOUR-COMPILER-PATH>
$ make
```

### 1.4 - Testing LLVM 16
TBD