#include <helib/helib.h>
#include <stdio.h>

using namespace helib;

extern "C" {
void test() {
printf("hi\n");
}

void* getContext(long m,long p,long r) {
Context* c = new Context(m, p, r);
return (void*)c;
}

void buildModChian(void* context_p,long nBits, long nDgts,
    bool willBeBootstrappable, long skHwt, long resolution,
    long bitsInSpecialPrimes) {
        Context* context = (Context*)context_p;
        buildModChain(*context,nBits,nDgts,willBeBootstrappable,skHwt,resolution,bitsInSpecialPrimes);

    }

void zmStarPrint(void* context_p) {
    Context* context = (Context*)context_p;
    context->zMStar.printout();
    std::cout<<*context<<std::endl;
}
}
