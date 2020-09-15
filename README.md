# jHElib
java for HElib

jHElib is "java for HElib", which makes java could use homomorphic encryption HElib. 

It provides two ways to connect java and HElib c++ lib, one is based on jnr-ffi and the other uses native JNI.

**NOTE: The first version of jHElib is not optimized and does not check poiter. It only makes "java for HElib" practical and runnable.**

The api now implemented are:

| java | HElib |
| ---- | ----- |
| initContext | Context constructor |
| buildModChain | buildModChain |
| printContext | zMStar.printOut |
| securityLevel | securityLevel |
| initSecKey | SecKey constructor |
| genSecKey | genSecKey |
| printSecKey | SecKey print|
| addSome1DMatrices | addSome1DMatrices |
| eaSize | ea.size |
| initCtxt | Ctxt constructor |
| eaEncrypt | ea.encrypt |
| eaDecrypt | ea.decrypt |
| mul | ctxt.mul |
| add | ctxt.add |
| makeBootstrappable | makeBootstrappable |
| isBootstrappable | isBootstrappable |
| genRecryptData | genRecryptData |
| buildUnpackSlotEncoding1 | buildUnpackSlotEncoding |
| multTwoNumbers | multTwoNumbers |
| addTwoNumbers | addTwoNumbers |
| decryptBinaryNums | decryptBinaryNums |
| addManyNumbers | addManyNumbers |
| fifteenOrLess4Four | fifteenOrLess4Four |

The `TestHelibJNI.java` implements the example of `BGV_general_example` in HElib.

The `BinaryApiTest.java` implements the example of `binaryArith_example` in HElib.

Usage:
```
javac -h . HelibJNIApi.java

mkdir build
cd build
export JAVA_HOME=/Library/Java/JavaVirtualMachines/jdk1.8.0_241.jdk/Contents/Home  (cmake use JAVA_HOME as include base path)
cmake -Dhelib_DIR=<helib install prefix>/share/cmake/helib ..
make
cd ..
javac TestHelibJNI.java
java -Djava.library.path=<helib install prefix>/lib/:./build TestHelibJNI
```

jnr-ffi usage:
```
cd jnr
mkdir build
cd build
cmake -Dhelib_DIR=<helib install prefix>/share/cmake/helib ..
make
make install
cd ..

```
