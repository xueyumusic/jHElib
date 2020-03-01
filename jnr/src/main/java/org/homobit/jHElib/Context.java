package org.homobit.jHElib;

import jnr.ffi.LibraryLoader;
import jnr.ffi.Pointer;

public class Context {
    public static interface LibHelibJNI {
        Pointer getContext(long m,long p,long r);
        void test();
    }

    public static void main(String[] args) {
        LibHelibJNI libc = LibraryLoader.create(LibHelibJNI.class).load("helibjni");

        Pointer p = libc.getContext(32109,2,1);
        System.out.println("##t:"+p);
        libc.test();
    }
}

