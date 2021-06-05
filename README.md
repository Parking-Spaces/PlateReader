To compile this program:

First install openALPR by following the tutorial found in: (If you are using another platform, use the according install guide)
https://github.com/openalpr/openalpr/wiki/Compilation-instructions-(Ubuntu-Linux)

After that use the following commands:

```bash
$ mkdir cmake-build-debug && cd cmake-build-debug
```

```bash
$ mkdir pictures
```

```bash
$ cp ../take_picture.sh ./take_picture.sh
```
```bash
$ cmake ..
```

```bash
$ make
```
