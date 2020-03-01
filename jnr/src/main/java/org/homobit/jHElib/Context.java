package org.homobit.jHElib;

import jnr.ffi.LibraryLoader;
import jnr.ffi.Pointer;

public class Context {
    public static interface LibHelibJNI {
        void test();
    }

    public static void main(String[] args) {
        LibHelibJNI libc = LibraryLoader.create(LibHelibJNI.class).load("helibjni");

        //libc.getContext(32109,2,1);
        libc.test();
    }
}

