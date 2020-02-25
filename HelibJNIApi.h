/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class HelibJNIApi */

#ifndef _Included_HelibJNIApi
#define _Included_HelibJNIApi
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     HelibJNIApi
 * Method:    initContext
 * Signature: (JJJ)J
 */
JNIEXPORT jlong JNICALL Java_HelibJNIApi_initContext__JJJ
  (JNIEnv *, jobject, jlong, jlong, jlong);

/*
 * Class:     HelibJNIApi
 * Method:    test1
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_HelibJNIApi_test1
  (JNIEnv *, jobject, jlong);

/*
 * Class:     HelibJNIApi
 * Method:    test2
 * Signature: (JDJ)D
 */
JNIEXPORT jdouble JNICALL Java_HelibJNIApi_test2
  (JNIEnv *, jobject, jlong, jdouble, jlong);

/*
 * Class:     HelibJNIApi
 * Method:    buildModChain
 * Signature: (JJJ)V
 */
JNIEXPORT void JNICALL Java_HelibJNIApi_buildModChain
  (JNIEnv *, jobject, jlong, jlong, jlong);

/*
 * Class:     HelibJNIApi
 * Method:    printContext
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_HelibJNIApi_printContext
  (JNIEnv *, jobject, jlong);

/*
 * Class:     HelibJNIApi
 * Method:    securityLevel
 * Signature: (J)D
 */
JNIEXPORT jdouble JNICALL Java_HelibJNIApi_securityLevel
  (JNIEnv *, jobject, jlong);

/*
 * Class:     HelibJNIApi
 * Method:    initSecKey
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_HelibJNIApi_initSecKey
  (JNIEnv *, jobject, jlong);

/*
 * Class:     HelibJNIApi
 * Method:    genSecKey
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_HelibJNIApi_genSecKey
  (JNIEnv *, jobject, jlong);

/*
 * Class:     HelibJNIApi
 * Method:    printSecKey
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_HelibJNIApi_printSecKey
  (JNIEnv *, jobject, jlong);

/*
 * Class:     HelibJNIApi
 * Method:    addSome1DMatrices
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_HelibJNIApi_addSome1DMatrices
  (JNIEnv *, jobject, jlong);

/*
 * Class:     HelibJNIApi
 * Method:    eaSize
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_HelibJNIApi_eaSize
  (JNIEnv *, jobject, jlong);

/*
 * Class:     HelibJNIApi
 * Method:    initCtxt
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_HelibJNIApi_initCtxt
  (JNIEnv *, jobject, jlong);

/*
 * Class:     HelibJNIApi
 * Method:    eaEncrypt
 * Signature: (JJJLjava/util/ArrayList;)V
 */
JNIEXPORT void JNICALL Java_HelibJNIApi_eaEncrypt
  (JNIEnv *, jobject, jlong, jlong, jlong, jobject);

/*
 * Class:     HelibJNIApi
 * Method:    eaDecrypt
 * Signature: (JJJLjava/util/ArrayList;)V
 */
JNIEXPORT void JNICALL Java_HelibJNIApi_eaDecrypt
  (JNIEnv *, jobject, jlong, jlong, jlong, jobject);

/*
 * Class:     HelibJNIApi
 * Method:    mul
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_HelibJNIApi_mul
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     HelibJNIApi
 * Method:    add
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_HelibJNIApi_add
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     HelibJNIApi
 * Method:    initContext
 * Signature: (JJJLjava/util/ArrayList;Ljava/util/ArrayList;)J
 */
JNIEXPORT jlong JNICALL Java_HelibJNIApi_initContext__JJJLjava_util_ArrayList_2Ljava_util_ArrayList_2
  (JNIEnv *, jobject, jlong, jlong, jlong, jobject, jobject);

/*
 * Class:     HelibJNIApi
 * Method:    makeBootstrappable
 * Signature: (JLjava/util/ArrayList;)V
 */
JNIEXPORT void JNICALL Java_HelibJNIApi_makeBootstrappable
  (JNIEnv *, jobject, jlong, jobject);

/*
 * Class:     HelibJNIApi
 * Method:    isBootstrappable
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_HelibJNIApi_isBootstrappable
  (JNIEnv *, jobject, jlong);

/*
 * Class:     HelibJNIApi
 * Method:    genRecryptData
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_HelibJNIApi_genRecryptData
  (JNIEnv *, jobject, jlong);

/*
 * Class:     HelibJNIApi
 * Method:    buildUnpackSlotEncoding
 * Signature: (Ljava/util/ArrayList;J)V
 */
JNIEXPORT void JNICALL Java_HelibJNIApi_buildUnpackSlotEncoding
  (JNIEnv *, jobject, jobject, jlong);

/*
 * Class:     HelibJNIApi
 * Method:    buildUnpackSlotEncoding1
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_HelibJNIApi_buildUnpackSlotEncoding1
  (JNIEnv *, jobject, jlong);

/*
 * Class:     HelibJNIApi
 * Method:    randomBits_long
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_HelibJNIApi_randomBits_1long
  (JNIEnv *, jobject, jlong);

/*
 * Class:     HelibJNIApi
 * Method:    multTwoNumbers
 * Signature: (Ljava/util/ArrayList;Ljava/util/ArrayList;ZJJ)J
 */
JNIEXPORT jlong JNICALL Java_HelibJNIApi_multTwoNumbers
  (JNIEnv *, jobject, jobject, jobject, jboolean, jlong, jlong);

/*
 * Class:     HelibJNIApi
 * Method:    addTwoNumbers
 * Signature: (JLjava/util/ArrayList;JJ)J
 */
JNIEXPORT jlong JNICALL Java_HelibJNIApi_addTwoNumbers
  (JNIEnv *, jobject, jlong, jobject, jlong, jlong);

/*
 * Class:     HelibJNIApi
 * Method:    decryptBinaryNums
 * Signature: (Ljava/util/ArrayList;JJJZZ)V
 */
JNIEXPORT void JNICALL Java_HelibJNIApi_decryptBinaryNums
  (JNIEnv *, jobject, jobject, jlong, jlong, jlong, jboolean, jboolean);

/*
 * Class:     HelibJNIApi
 * Method:    addManyNumbers
 * Signature: (Ljava/util/ArrayList;JJ)J
 */
JNIEXPORT jlong JNICALL Java_HelibJNIApi_addManyNumbers
  (JNIEnv *, jobject, jobject, jlong, jlong);

/*
 * Class:     HelibJNIApi
 * Method:    fifteenOrLess4Four
 * Signature: (Ljava/util/ArrayList;JJ)J
 */
JNIEXPORT jlong JNICALL Java_HelibJNIApi_fifteenOrLess4Four
  (JNIEnv *, jobject, jobject, jlong, jlong);

#ifdef __cplusplus
}
#endif
#endif