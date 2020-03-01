  #g++ Context.c -shared -fPIC -Wl,-soname,libhelibjni.so.1  -o libhelibjni.so.1.0.0
  #gcc Context.c -shared -fPIC -Wl,-soname,libhelibjni.so.1  -o libhelibjni.so.1.0.0

 g++ Context.cpp -shared -fPIC -Wl,-soname,libhelibjni.so.1 -I/home/q/xueyu/helib2/install/include/ -I/usr/lib/jvm/java-1.8.0-openjdk.x86_64/include/ -I/usr/lib/jvm/java-1.8.0-openjdk.x86_64/include/linux/  -L. -lhelib -o libhelibjni.so.1.0.0
  mv /usr/lib64/libhelibjni.so.1* /home/q/xueyu/tmp/
  cp libhelibjni.so.1.0.0 /usr/lib64/
  ldconfig
