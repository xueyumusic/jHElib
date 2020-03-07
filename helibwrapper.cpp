#include <helib/helib.h>
#include <jni.h>
#include <helib/binaryArith.h>
#include <helib/intraSlot.h>
#include "HelibJNIApi.h"

using namespace helib;

JNIEXPORT jlong JNICALL Java_HelibJNIApi_initContext__JJJ
  (JNIEnv * jenv, jobject jobj, jlong m, jlong p, jlong r) {

  jlong result;
  result = (jlong)new Context(m,p,r);
  return result;
}

JNIEXPORT jlong JNICALL Java_HelibJNIApi_initContext
  (jlong m, jlong p, jlong r) {
  jlong result;
  result = (jlong)new Context(m,p,r);
  return result;
}

JNIEXPORT jlong JNICALL Java_HelibJNIApi_test1
  (JNIEnv *, jobject, jlong) {
  return 978;
}

JNIEXPORT jdouble JNICALL Java_HelibJNIApi_test2
  (JNIEnv * jenv, jobject jobj, jlong cptr, jdouble mag, jlong deg) {
  Context* ctr = (Context*)cptr;
  jdouble res = ctr->noiseBoundForUniform(mag,deg);
  return res;
}

JNIEXPORT void JNICALL Java_HelibJNIApi_buildModChain
  (JNIEnv *jenv, jobject jobj, jlong cptr, jlong nBits, jlong nDgts) {
  Context* ctr = (Context*)cptr;
  buildModChain(*ctr,nBits,nDgts);
}

JNIEXPORT void JNICALL Java_HelibJNIApi_printContext
  (JNIEnv *jenv, jobject jobj, jlong cptr)
{
  Context* ctr = (Context*)cptr;
  ctr->zMStar.printout();
  std::cout<<*ctr<<std::endl;
}

JNIEXPORT jdouble JNICALL Java_HelibJNIApi_securityLevel
  (JNIEnv *jenv, jobject jobj, jlong cptr) {
  Context* ctr = (Context*)cptr;
  return ctr->securityLevel();
}

JNIEXPORT jlong JNICALL Java_HelibJNIApi_initSecKey
  (JNIEnv *jenv, jobject jobj, jlong cptr) {
  Context* ctr = (Context*)cptr;
  jlong  seckeyptr = (jlong)new SecKey(*ctr);
  return seckeyptr;
}

JNIEXPORT void JNICALL Java_HelibJNIApi_genSecKey
  (JNIEnv *jenv, jobject jobj, jlong seckeyptr) {
  SecKey* key = (SecKey*)seckeyptr;
  key->GenSecKey();
}

JNIEXPORT void JNICALL Java_HelibJNIApi_printSecKey
  (JNIEnv *jenv, jobject jobj, jlong seckeyptr) {
  SecKey* key = (SecKey*)seckeyptr;
  std::cout<<*key<<std::endl;
}

JNIEXPORT void JNICALL Java_HelibJNIApi_addSome1DMatrices
  (JNIEnv *jenv, jobject jobj, jlong seckeyptr) {
  SecKey* key = (SecKey*)seckeyptr;
  addSome1DMatrices(*key);
}

JNIEXPORT jlong JNICALL Java_HelibJNIApi_eaSize
  (JNIEnv *jenv, jobject jobj, jlong cptr) {
  Context* ctr = (Context*)cptr;
  const EncryptedArray& ea = *(ctr->ea);
  long nslots = ea.size();
  return nslots;
}

JNIEXPORT jlong JNICALL Java_HelibJNIApi_initCtxt
  (JNIEnv *jenv, jobject jobj, jlong pubkeyptr) {
  PubKey* pubkey_p = (PubKey*)pubkeyptr;
  jlong ctxt_p = (jlong)new Ctxt(*pubkey_p);
  return ctxt_p; 
}

JNIEXPORT void JNICALL Java_HelibJNIApi_eaEncrypt
  (JNIEnv *jenv, jobject jobj, jlong cptr, jlong ctxtptr, jlong pubkeyptr, jobject jptxt) {
  Context* ctr = (Context*)cptr;
  const EncryptedArray& ea = *(ctr->ea);
  Ctxt* ctxt_p = (Ctxt*)ctxtptr;
  PubKey* pubkey_p = (PubKey*)pubkeyptr;

  //获取ArrayList 对象
  jclass jcs_alist = jenv->GetObjectClass(jptxt);
  //获取Arraylist的methodid
  jmethodID alist_get = jenv->GetMethodID(jcs_alist, "get", "(I)Ljava/lang/Object;");
  jmethodID alist_size = jenv->GetMethodID(jcs_alist, "size", "()I");
  jint len = jenv->CallIntMethod(jptxt, alist_size);

  std::cout<<"##alist_size:"<<len<<std::endl;
  std::vector<long> ptxt(len);
  for (int i = 0; i < len; i++) {
    jobject v = jenv->CallObjectMethod(jptxt, alist_get, i);
    jclass jcs_v = jenv->GetObjectClass(v);

    jmethodID vm = jenv->GetMethodID(jcs_v,"longValue","()J");
    jlong vv = jenv->CallLongMethod(v, vm);
    //std::cout<<"##vv:"<<vv<<std::endl;
    ptxt[i]=vv;
  }
  ea.encrypt(*ctxt_p,*pubkey_p,ptxt);
  //std::cout<<"##ctxt encrypted:"<<*ctxt_p<<std::endl;
}

JNIEXPORT void JNICALL Java_HelibJNIApi_eaDecrypt
  (JNIEnv *jenv, jobject jobj, jlong cptr, jlong ctxtptr, jlong seckeyptr, jobject decrypted) {
  Context* ctr = (Context*)cptr;
  const EncryptedArray& ea = *(ctr->ea);
  Ctxt* ctxt_p = (Ctxt*)ctxtptr;
  SecKey* seckey_p = (SecKey*)seckeyptr;
  std::vector<long> dv(24);
  ea.decrypt(*ctxt_p,*seckey_p,dv);

  //获取ArrayList 对象
  jclass jcs_alist = jenv->GetObjectClass(decrypted);
  //获取Arraylist的methodid
  jmethodID alist_add = jenv->GetMethodID(jcs_alist, "add", "(Ljava/lang/Object;)Z");
  for (int i=0;i<24;i++) {
    //std::cout<<"##dv"<<i<<":"<<dv[i]<<std::endl;

    jclass class_long=jenv->FindClass("java/lang/Long");
    jmethodID long_init = jenv->GetMethodID(class_long,"<init>","(J)V");
    jobject obj_long = jenv->NewObject(class_long, long_init, dv[i]);

    jenv->CallBooleanMethod(decrypted, alist_add, obj_long);
  }
}

JNIEXPORT void JNICALL Java_HelibJNIApi_mul
  (JNIEnv *jenv, jobject jobj, jlong ctxtptr1, jlong ctxtptr2) {
  Ctxt* ctxt_p1 = (Ctxt*)ctxtptr1;
  Ctxt* ctxt_p2 = (Ctxt*)ctxtptr2;
  (*ctxt_p1) *= (*ctxt_p2);
}

JNIEXPORT void JNICALL Java_HelibJNIApi_add
  (JNIEnv *jenv, jobject jobj, jlong ctxtptr1, jlong ctxtptr2) {
  Ctxt* ctxt_p1 = (Ctxt*)ctxtptr1;
  Ctxt* ctxt_p2 = (Ctxt*)ctxtptr2;
  (*ctxt_p1) += (*ctxt_p2);
}

//JNIEXPORT jlong JNICALL Java_BinaryApiTest_initContext__JJJLjava_util_ArrayList_2Ljava_util_ArrayList_2
//JNIEXPORT jlong JNICALL Java_BinaryApiTest_initContext1
//  (JNIEnv *, jobject, jlong, jlong, jlong, jobject, jobject);

JNIEXPORT jlong JNICALL Java_HelibJNIApi_initContext__JJJLjava_util_ArrayList_2Ljava_util_ArrayList_2
  (JNIEnv *jenv, jobject jobj, jlong m, jlong p, jlong r, jobject jgens, jobject jords) {
  //获取ArrayList 对象
  //jclass jcs_alist = jenv->GetObjectClass(jgens);
  jclass jcs_alist = jenv->FindClass("java/util/ArrayList");
  //获取Arraylist的methodid
  jmethodID alist_get = jenv->GetMethodID(jcs_alist, "get", "(I)Ljava/lang/Object;");
  jmethodID alist_size = jenv->GetMethodID(jcs_alist, "size", "()I");

  jint genslen = jenv->CallIntMethod(jgens, alist_size);
  std::cout<<"##gen_size:"<<genslen<<std::endl;
  std::vector<long> gens(genslen);
  for (int i = 0; i < genslen; i++) {
    jobject v = jenv->CallObjectMethod(jgens, alist_get, i);
    jclass jcs_v = jenv->GetObjectClass(v);

    jmethodID vm = jenv->GetMethodID(jcs_v,"longValue","()J");
    jlong vv = jenv->CallLongMethod(v, vm);
    std::cout<<"##vv1:"<<vv<<std::endl;
    gens[i]=vv;
  }

  jint ordslen = jenv->CallIntMethod(jords, alist_size);
  std::cout<<"##ords_size:"<<ordslen<<std::endl;
  std::vector<long> ords(ordslen);
  for (int i = 0; i < ordslen; i++) {
    jobject v = jenv->CallObjectMethod(jords, alist_get, i);
    jclass jcs_v = jenv->GetObjectClass(v);

    jmethodID vm = jenv->GetMethodID(jcs_v,"longValue","()J");
    jlong vv = jenv->CallLongMethod(v, vm);
    std::cout<<"##vv2:"<<vv<<std::endl;
    ords[i]=vv;
  }

  jlong result;
  result = (jlong)new Context(m,p,r,gens,ords);
  return result;

}

JNIEXPORT void JNICALL Java_HelibJNIApi_makeBootstrappable
  (JNIEnv * jenv, jobject jobj, jlong cptr, jobject jmvec) {
  Context* ctr = (Context*)cptr;

  //获取ArrayList 对象
  jclass jcs_alist = jenv->FindClass("java/util/ArrayList");
  //获取Arraylist的methodid
  jmethodID alist_get = jenv->GetMethodID(jcs_alist, "get", "(I)Ljava/lang/Object;");
  jmethodID alist_size = jenv->GetMethodID(jcs_alist, "size", "()I");

  jint mveclen = jenv->CallIntMethod(jmvec, alist_size);
  std::cout<<"##mvec_size:"<<mveclen<<std::endl;
  std::vector<long> mvec(mveclen);
  for (int i = 0; i < mveclen; i++) {
    jobject v = jenv->CallObjectMethod(jmvec, alist_get, i);
    jclass jcs_v = jenv->GetObjectClass(v);

    jmethodID vm = jenv->GetMethodID(jcs_v,"longValue","()J");
    jlong vv = jenv->CallLongMethod(v, vm);
    std::cout<<"##vv3:"<<vv<<std::endl;
    mvec[i]=vv;
  }

  ctr->makeBootstrappable(convert<NTL::Vec<long>, std::vector<long>>(mvec));

}

JNIEXPORT jboolean JNICALL Java_HelibJNIApi_isBootstrappable
  (JNIEnv *jenv, jobject jobj, jlong cptr) {
  Context* ctr = (Context*)cptr;
  return ctr->isBootstrappable();
}

JNIEXPORT void JNICALL Java_HelibJNIApi_genRecryptData
  (JNIEnv *jenv, jobject jobj, jlong seckeyptr) {
  SecKey* key = (SecKey*)seckeyptr;
  key->genRecryptData();
}

JNIEXPORT void JNICALL Java_HelibJNIApi_buildUnpackSlotEncoding
  (JNIEnv *jenv, jobject jobj, jobject unpackSlotEncodingPtrs, jlong cptr) {
  Context* ctr = (Context*)cptr;
  const EncryptedArray& ea = *(ctr->ea);
  std::vector<helib::zzX> unpackSlotEncoding;
  buildUnpackSlotEncoding(unpackSlotEncoding, ea);

  //获取ArrayList 对象
  jclass jcs_alist = jenv->GetObjectClass(unpackSlotEncodingPtrs);
  //获取Arraylist的methodid
  jmethodID alist_add = jenv->GetMethodID(jcs_alist, "add", "(Ljava/lang/Object;)Z");
  for (int i=0;i<unpackSlotEncoding.size();i++) {
    std::cout<<"##uv"<<i<<":"<<unpackSlotEncoding[i]<<std::endl;

    helib::zzX* zzx_p = new helib::zzX(unpackSlotEncoding[i]);
    long zzxPtr = (long)zzx_p;

    jclass class_long=jenv->FindClass("java/lang/Long");
    jmethodID long_init = jenv->GetMethodID(class_long,"<init>","(J)V");
    jobject obj_long = jenv->NewObject(class_long, long_init, zzxPtr);

    jenv->CallBooleanMethod(unpackSlotEncodingPtrs, alist_add, obj_long);
  }
}

JNIEXPORT jlong JNICALL Java_HelibJNIApi_buildUnpackSlotEncoding1
  (JNIEnv *jenv, jobject jobj, jlong cptr) {
  Context* ctr = (Context*)cptr;
  const EncryptedArray& ea = *(ctr->ea);
  std::vector<helib::zzX>* unpackSlotEncoding=new std::vector<helib::zzX>();
  buildUnpackSlotEncoding(*unpackSlotEncoding, ea);
  return (jlong)unpackSlotEncoding;
}

JNIEXPORT jlong JNICALL Java_HelibJNIApi_randomBits_1long
  (JNIEnv *jenv, jobject jobj, jlong bitSize) {
  return NTL::RandomBits_long(bitSize);
}

JNIEXPORT jlong JNICALL Java_HelibJNIApi_multTwoNumbers
  (JNIEnv *jenv, jobject jobj, jobject lhsptr, jobject rhsptr, 
	jboolean cflag, jlong sizeLimit, jlong unpackSlotEncodingPtr1) {

  //获取ArrayList 对象
  jclass jcs_alist = jenv->FindClass("java/util/ArrayList");
  //获取Arraylist的methodid
  jmethodID alist_get = jenv->GetMethodID(jcs_alist, "get", "(I)Ljava/lang/Object;");
  jmethodID alist_size = jenv->GetMethodID(jcs_alist, "size", "()I");

  jint lhslen = jenv->CallIntMethod(lhsptr, alist_size);
  std::cout<<"##lhs_size:"<<lhslen<<std::endl;
  std::vector<Ctxt> encrypted_lhs;
  for (int i = 0; i < lhslen; i++) {
    jobject v = jenv->CallObjectMethod(lhsptr, alist_get, i);
    jclass jcs_v = jenv->GetObjectClass(v);

    jmethodID vm = jenv->GetMethodID(jcs_v,"longValue","()J");
    jlong vv = jenv->CallLongMethod(v, vm);
    //std::cout<<"##vv3:"<<vv<<std::endl;
    Ctxt tmpctxptr = *((Ctxt*)vv);
    encrypted_lhs.push_back(tmpctxptr);
  }

  jint rhslen = jenv->CallIntMethod(rhsptr, alist_size);
  std::cout<<"##rhs_size:"<<rhslen<<std::endl;
  std::vector<Ctxt> encrypted_rhs;
  for (int i = 0; i < rhslen; i++) {
    jobject v = jenv->CallObjectMethod(rhsptr, alist_get, i);
    jclass jcs_v = jenv->GetObjectClass(v);

    jmethodID vm = jenv->GetMethodID(jcs_v,"longValue","()J");
    jlong vv = jenv->CallLongMethod(v, vm);
    //std::cout<<"##vv3:"<<vv<<std::endl;
    Ctxt tmpctxptr = *((Ctxt*)vv);
    encrypted_rhs.push_back(tmpctxptr);
  }

  std::vector<Ctxt>* encrypted_res=new std::vector<Ctxt>();
  helib::CtPtrs_vectorCt* product_wrapper_p = new helib::CtPtrs_vectorCt(*encrypted_res);
  std::vector<helib::zzX>* unpackSlotEncodingPtr = (std::vector<helib::zzX>*)unpackSlotEncodingPtr1;

  helib::multTwoNumbers(
        *product_wrapper_p,
        helib::CtPtrs_vectorCt(encrypted_lhs),
        helib::CtPtrs_vectorCt(encrypted_rhs),
        cflag,
        sizeLimit,
        unpackSlotEncodingPtr); // Information needed for bootstrapping.
  return (jlong)product_wrapper_p;
}

JNIEXPORT jlong JNICALL Java_HelibJNIApi_addTwoNumbers
  (JNIEnv *jenv, jobject jobj, jlong lhsptr, jobject rhsptr, jlong sizeLimit, jlong unpackSlotEncodingPtr1) {
  //获取ArrayList 对象
  jclass jcs_alist = jenv->FindClass("java/util/ArrayList");
  //获取Arraylist的methodid
  jmethodID alist_get = jenv->GetMethodID(jcs_alist, "get", "(I)Ljava/lang/Object;");
  jmethodID alist_size = jenv->GetMethodID(jcs_alist, "size", "()I");

  jint rhslen = jenv->CallIntMethod(rhsptr, alist_size);
  std::cout<<"##rhs_size:"<<rhslen<<std::endl;
  std::vector<Ctxt> encrypted_rhs;
  for (int i = 0; i < rhslen; i++) {
    jobject v = jenv->CallObjectMethod(rhsptr, alist_get, i);
    jclass jcs_v = jenv->GetObjectClass(v);

    jmethodID vm = jenv->GetMethodID(jcs_v,"longValue","()J");
    jlong vv = jenv->CallLongMethod(v, vm);
    //std::cout<<"##vv3:"<<vv<<std::endl;
    Ctxt tmpctxptr = *((Ctxt*)vv);
    encrypted_rhs.push_back(tmpctxptr);
  }

  helib::CtPtrs_vectorCt* lhs_p = (helib::CtPtrs_vectorCt*)lhsptr;

  std::vector<Ctxt>* encrypted_res=new std::vector<Ctxt>();
  helib::CtPtrs_vectorCt* add_wrapper_p = new helib::CtPtrs_vectorCt(*encrypted_res);
  std::vector<helib::zzX>* unpackSlotEncodingPtr = (std::vector<helib::zzX>*)unpackSlotEncodingPtr1;

  helib::addTwoNumbers(
        *add_wrapper_p,
        *lhs_p,
        helib::CtPtrs_vectorCt(encrypted_rhs),
        sizeLimit,
        unpackSlotEncodingPtr); // Information needed for bootstrapping.
  return (jlong)add_wrapper_p;

}

JNIEXPORT void JNICALL Java_HelibJNIApi_decryptBinaryNums
  (JNIEnv *jenv, jobject jobj, jobject resultptr, jlong eNumsPtr, jlong seckeyptr, jlong cptr,
	jboolean twosComplement, jboolean allSlots) {
  Context* ctr = (Context*)cptr;
  const EncryptedArray& ea = *(ctr->ea);
  std::vector<long> decrypted_result;
  helib::CtPtrs_vectorCt* product_wrapper_p = (helib::CtPtrs_vectorCt*)eNumsPtr;
  SecKey* seckey_p = (SecKey*)seckeyptr;
  helib::decryptBinaryNums(decrypted_result,*product_wrapper_p,*seckey_p,ea,twosComplement,allSlots);

  //获取ArrayList 对象
  jclass jcs_alist = jenv->GetObjectClass(resultptr);
  //获取Arraylist的methodid
  jmethodID alist_add = jenv->GetMethodID(jcs_alist, "add", "(Ljava/lang/Object;)Z");
  for (int i=0;i<decrypted_result.size();i++) {
    std::cout<<"##ddv"<<i<<":"<<decrypted_result[i]<<std::endl;

    jclass class_long=jenv->FindClass("java/lang/Long");
    jmethodID long_init = jenv->GetMethodID(class_long,"<init>","(J)V");
    jobject obj_long = jenv->NewObject(class_long, long_init, decrypted_result[i]);

    jenv->CallBooleanMethod(resultptr, alist_add, obj_long);
  }
}

JNIEXPORT jlong JNICALL Java_HelibJNIApi_addManyNumbers
  (JNIEnv *jenv, jobject jobj, jobject summandsptr, jlong sizeLimit, jlong unpackSlotEncodingPtr1) {
  //获取ArrayList 对象
  jclass jcs_alist = jenv->FindClass("java/util/ArrayList");
  //获取Arraylist的methodid
  jmethodID alist_get = jenv->GetMethodID(jcs_alist, "get", "(I)Ljava/lang/Object;");
  jmethodID alist_size = jenv->GetMethodID(jcs_alist, "size", "()I");

  jint summandslen = jenv->CallIntMethod(summandsptr, alist_size);
  std::cout<<"##summands_size:"<<summandslen<<std::endl;
  std::vector<std::vector<Ctxt>> encrypted_sum;
  for (int i = 0; i < summandslen; i++) {
    jobject v = jenv->CallObjectMethod(summandsptr, alist_get, i);
    //jclass jcs_v = jenv->GetObjectClass(v);
    jint vlen = jenv->CallIntMethod(v, alist_size);
    std::vector<Ctxt> vecctxt;
    for (int j = 0; j < vlen; j++) {
      jobject vv = jenv->CallObjectMethod(v, alist_get, j);
      jclass jcs_vv = jenv->GetObjectClass(vv);
      jmethodID vm = jenv->GetMethodID(jcs_vv,"longValue","()J");
      jlong vvl = jenv->CallLongMethod(vv, vm);
      Ctxt tmpctxptr = *((Ctxt*)vvl);
      vecctxt.push_back(tmpctxptr);
    }
    encrypted_sum.push_back(vecctxt);
  }

  helib::CtPtrMat_vectorCt summands_wrapper(encrypted_sum);
  std::vector<Ctxt>* encrypted_res=new std::vector<Ctxt>();
  helib::CtPtrs_vectorCt* add_wrapper_p = new helib::CtPtrs_vectorCt(*encrypted_res);
  std::vector<helib::zzX>* unpackSlotEncodingPtr = (std::vector<helib::zzX>*)unpackSlotEncodingPtr1;

  helib::addManyNumbers(
        *(add_wrapper_p),
        summands_wrapper,
        0,                    // sizeLimit=0 means use as many bits as needed.
        unpackSlotEncodingPtr);

  return (jlong)add_wrapper_p;
}

JNIEXPORT jlong JNICALL Java_HelibJNIApi_fifteenOrLess4Four
  (JNIEnv *jenv, jobject jobj, jobject input_p, jlong sizeLimit, jlong pubkeyptr) {
  PubKey* pubkey_p = (PubKey*)pubkeyptr;
  //获取ArrayList 对象
  jclass jcs_alist = jenv->FindClass("java/util/ArrayList");
  //获取Arraylist的methodid
  jmethodID alist_get = jenv->GetMethodID(jcs_alist, "get", "(I)Ljava/lang/Object;");
  jmethodID alist_size = jenv->GetMethodID(jcs_alist, "size", "()I");

  jint inputlen = jenv->CallIntMethod(input_p, alist_size);
  std::cout<<"##input_size:"<<inputlen<<std::endl;
  std::vector<Ctxt> encrypted_input;
  for (int i = 0; i < inputlen; i++) {
    jobject v = jenv->CallObjectMethod(input_p, alist_get, i);
    jclass jcs_v = jenv->GetObjectClass(v);

    jmethodID vm = jenv->GetMethodID(jcs_v,"longValue","()J");
    jlong vv = jenv->CallLongMethod(v, vm);
    Ctxt tmpctxptr = *((Ctxt*)vv);
    encrypted_input.push_back(tmpctxptr);
  }
  std::vector<Ctxt>* encrypted_res=new std::vector<Ctxt>();
  helib::Ctxt scratch(*pubkey_p);
  encrypted_res->resize(41u,scratch);
  helib::CtPtrs_vectorCt* res_wrapper_p = new helib::CtPtrs_vectorCt(*encrypted_res);

  helib::fifteenOrLess4Four(*res_wrapper_p,
                            helib::CtPtrs_vectorCt(encrypted_input));
  return (jlong)res_wrapper_p;

}
