package org.homobit.jHElib;

import jnr.ffi.LibraryLoader;
import jnr.ffi.Pointer;

public class Context {
    public static interface LibHelibJNI {
        Pointer getContext(long m,long p,long r);
        void test();
        void buildModChian(Pointer context_p,long nBits, long nDgts,
            boolean willBeBootstrappable, long skHwt, long resolution,
            long bitsInSpecialPrimes);
        void zmStarPrint(Pointer context_p);
    }

    public static void main(String[] args) {
        LibHelibJNI libc = LibraryLoader.create(LibHelibJNI.class).load("helibjni");

        Pointer p = libc.getContext(32109,2,1);
        libc.test();

        System.out.println("##pos1 before:");
        libc.zmStarPrint(p);
        libc.buildModChian(p, 300, 2, false, 0L, 3L, 0L);
        System.out.println("##pos2 after:");
        libc.zmStarPrint(p);
    }
}

