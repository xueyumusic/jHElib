
import java.util.ArrayList;

public class TestHelibJNI {

   // Test Driver
   public static void main(String[] args) {
      HelibJNIApi obj = new HelibJNIApi();
      //TODO: p,m,r,bits,c should be unsigned
        // Plaintext prime modulus
      long p = 4999; 
      // Cyclotomic polynomial - defines phi(m)
      long m = 32109;
      // Hensel lifting (default = 1)
      long r = 1;
      // Number of bits of the modulus chain  
      long bits = 300;
      // Number of columns of Key-Switching matix (default = 2 or 3)
      long c = 2;

      System.out.println("##Init context...");
      long cptr = obj.initContext(m, p, r);  // Create an instance and invoke the native method
      System.out.println("##cptr:"+cptr);

      obj.printContext(cptr);
      System.out.println("##building modulus chain...");
      obj.buildModChain(cptr,bits,c);
      obj.printContext(cptr);

      System.out.println("##security level:"+obj.securityLevel(cptr));

      System.out.println("##creating secret key...");
      long seckeyptr = obj.initSecKey(cptr);
      obj.genSecKey(seckeyptr);
      obj.printSecKey(seckeyptr);

      System.out.println("##generating keyswitching matrices");
      obj.addSome1DMatrices(seckeyptr);
      obj.printSecKey(seckeyptr);

      System.out.println("##number of slots");
      long nslots = obj.eaSize(cptr);
      System.out.println("##nslots:"+nslots);

      ArrayList<Long> ptxt = new ArrayList<Long>((int)nslots);
      for (long i = 0; i < nslots; i++) {
         ptxt.add(i);
      }
      long pubkeyptr = seckeyptr;
      long ctxtptr = obj.initCtxt(pubkeyptr);
      obj.eaEncrypt(cptr, ctxtptr, pubkeyptr, ptxt);


      obj.mul(ctxtptr,ctxtptr);
      obj.add(ctxtptr,ctxtptr);

      System.out.println("##decrypt");
      ArrayList<Long> decrypted = new ArrayList<Long>((int)nslots);
      obj.eaDecrypt(cptr, ctxtptr, seckeyptr, decrypted);

      for(int i = 0; i < decrypted.size(); i++) {
         System.out.println("##jdecrypted:"+i+":"+decrypted.get(i));
      }
   }
}
