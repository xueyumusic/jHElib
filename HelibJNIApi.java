
import java.util.ArrayList;

public class HelibJNIApi {
   static {
      System.loadLibrary("helib"); 
      System.loadLibrary("helibjni"); 
   }

   public native long initContext(long m, long p, long r);
   public native long test1(long m);
   public native double test2(long cptr, double mag, long deg);
   public native void buildModChain(long context, long nBits, long nDgts);
   public native void printContext(long cptr);
   public native double securityLevel(long cptr);
   public native long initSecKey(long cptr);
   public native void genSecKey(long seckeyptr);
   public native void printSecKey(long seckeyptr);
   public native void addSome1DMatrices(long seckeyptr);
   public native long eaSize(long cptr);
   public native long initCtxt(long pubkeyptr);
   public native void eaEncrypt(long cptr, long ctxtptr, long pubkeyptr, ArrayList<Long> ptxt);
   public native void eaDecrypt(long cptr, long ctxtptr, long seckeyptr, ArrayList<Long>decrypted);
   public native void mul(long ctxtptr1, long ctxtptr2);
   public native void add(long ctxtptr1, long ctxtptr2);
   public native long initContext(long m, long p, long r, ArrayList<Long> gens, ArrayList<Long> ords);
   public native void makeBootstrappable(long cptr, ArrayList<Long> mvec);
   public native boolean isBootstrappable(long cptr);
   public native void genRecryptData(long seckeyptr);
   public native void buildUnpackSlotEncoding(ArrayList<Long> unpackSlotEncodingPtrs, long cptr);
   public native long buildUnpackSlotEncoding1(long cptr);
   public native long randomBits_long(long bitSize);
   public native long multTwoNumbers(ArrayList<Long> lhs, ArrayList<Long> rhs,
                        boolean rhsTwosComplement, long sizeLimit, long unpackSlotEncoding);
   public native long addTwoNumbers(long lhs, ArrayList<Long> rhs,
                        long sizeLimit, long unpackSlotEncoding);
   public native void decryptBinaryNums(ArrayList<Long> result, long eNums, long seckeyptr, 
                        long cptr, boolean twosComplement, boolean allSlots);

   public native long addManyNumbers(ArrayList<ArrayList<Long>> summandsptr, long sizeLimit, long unpackSlotEncoding);
   public native long fifteenOrLess4Four(ArrayList<Long> input_p, long sizeLimit, long pubkeyptr);

   public static void main(String[] args) {
 
   }
}
