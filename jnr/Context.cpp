#include <helib/helib.h>
#include <stdio.h>

using namespace helib;

extern "C" {
void test() {
printf("hi");
}

void* getContext(long m,long p,long r) {
Context* c = new Context(m, p, r);
return (void*)c;
}
}
