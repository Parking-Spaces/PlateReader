To compile this program:

First install openALPR by following the tutorial found in: (If you are using another platform, use the according install guide)
https://github.com/openalpr/openalpr/wiki/Compilation-instructions-(Ubuntu-Linux)

After that user the following commands:

```bash
$ mkdir cmake-build-debug && cd cmake-build-debug

$ mkdir pictures

$ cp ../take_picture.sh ./take_picture.sh

$ cmake ..

$ make
```
