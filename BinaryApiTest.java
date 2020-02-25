
import java.util.ArrayList;
import java.util.Arrays;

public class BinaryApiTest {
   static {

   }


   // Test Driver
   public static void main(String[] args) {
      HelibJNIApi obj = new HelibJNIApi();
      //TODO: p,m,r,bits,c should be unsigned
        // Plaintext prime modulus
      long p = 2; 
      // Cyclotomic polynomial - defines phi(m)
      long m = 4095;
      // Hensel lifting (default = 1)
      long r = 1;
      // Number of bits of the modulus chain  
      long bits = 500;
      // Number of columns of Key-Switching matix (default = 2 or 3)
      long c = 2;

      ArrayList<Long> mvec = new ArrayList<Long>(Arrays.asList(7L,5L,9L,13L));

      ArrayList<Long> gens = new ArrayList<Long>();
      gens.add(2341L);
      gens.add(3277L);
      gens.add(911L);

      ArrayList<Long> ords = new ArrayList<Long>();
      ords.add(6L);
      ords.add(4L);
      ords.add(6L);

      System.out.println("##Init context...");
      long cptr = obj.initContext(m, p, r, gens, ords); 
      System.out.println("##cptr:"+cptr);


      obj.printContext(cptr);
      System.out.println("##building modulus chain...");
      obj.buildModChain(cptr,bits,c);

      System.out.println("##isboot before:"+obj.isBootstrappable(cptr));
      obj.makeBootstrappable(cptr, mvec);
      System.out.println("##isboot after:"+obj.isBootstrappable(cptr));
      obj.printContext(cptr);

      System.out.println("##security level:"+obj.securityLevel(cptr));

      System.out.println("##creating secret key...");
      long seckeyptr = obj.initSecKey(cptr);
      obj.genSecKey(seckeyptr);
      obj.genRecryptData(seckeyptr);

      Long unpackSlotEncodingPtrs1 = obj.buildUnpackSlotEncoding1(cptr);

      System.out.println("##number of slots");
      long nslots = obj.eaSize(cptr);
      System.out.println("##nslots:"+nslots);


      long bitSize = 16;
      long outSize = 2 * bitSize;
      long a_data = obj.randomBits_long(bitSize);
      long b_data = obj.randomBits_long(bitSize);
      long c_data = obj.randomBits_long(bitSize);

      System.out.println("Pre-encryption data:");
      System.out.println("a = "+a_data);
      System.out.println("b = "+b_data);
      System.out.println("c = "+c_data);

      long pubkeyptr = seckeyptr;
      long scratchctxtptr = obj.initCtxt(pubkeyptr);
      ArrayList<Long> encrypted_a = new ArrayList<Long>();
      ArrayList<Long> encrypted_b = new ArrayList<Long>();
      ArrayList<Long> encrypted_c = new ArrayList<Long>();

      for (int i=0;i<bitSize;i++) {
         encrypted_a.add(scratchctxtptr);
         encrypted_b.add(scratchctxtptr);
         encrypted_c.add(scratchctxtptr);
      }

      for (int i=0;i<bitSize;i++) {
         ArrayList<Long> a_vec = new ArrayList<Long>((int)nslots);
         ArrayList<Long> b_vec = new ArrayList<Long>((int)nslots);
         ArrayList<Long> c_vec = new ArrayList<Long>((int)nslots);
         System.out.println("##a_vec size:"+a_vec.size());
         for (int j=0;j<(int)nslots;j++) {
            a_vec.add((a_data >> i) & 1);
            b_vec.add((b_data >> i) & 1);
            c_vec.add((c_data >> i) & 1);
         }
         System.out.println("##a_vec size2:"+a_vec.size());
         Long al=obj.initCtxt(pubkeyptr),bl=obj.initCtxt(pubkeyptr),cl=obj.initCtxt(pubkeyptr);
         obj.eaEncrypt(cptr, al, pubkeyptr, a_vec);
         obj.eaEncrypt(cptr, bl, pubkeyptr, b_vec);
         obj.eaEncrypt(cptr, cl, pubkeyptr, c_vec);
         encrypted_a.set(i, al);
         encrypted_b.set(i, bl);
         encrypted_c.set(i, cl);
      }

      long encrypted_product_p = obj.multTwoNumbers(encrypted_a, encrypted_b, false, outSize, unpackSlotEncodingPtrs1);
      long encrypted_add_p = obj.addTwoNumbers(encrypted_product_p, encrypted_c, outSize, unpackSlotEncodingPtrs1);
 
      ArrayList<Long> result = new ArrayList<Long>();
      obj.decryptBinaryNums(result,encrypted_add_p,seckeyptr,cptr,false,true);
      for (int i=0;i<result.size();i++) {
         System.out.println("##inj dv:"+i+":"+result.get(i));
      }

      System.out.println("##add many");
      result.clear();
      ArrayList<ArrayList<Long>> summandsptr = new ArrayList<ArrayList<Long>>();
      summandsptr.add(encrypted_a);
      summandsptr.add(encrypted_b);
      summandsptr.add(encrypted_c);
      long encrypted_addall_p = obj.addManyNumbers(summandsptr,0L,unpackSlotEncodingPtrs1);
      obj.decryptBinaryNums(result,encrypted_addall_p,seckeyptr,cptr,false,true);
      for (int i=0;i<result.size();i++) {
         System.out.println("##inj dv1:"+i+":"+result.get(i));
      }

      System.out.println("##fifteenOrLess4Four");
      encrypted_a.remove(15);
      long fifres_p = obj.fifteenOrLess4Four(encrypted_a, 4, pubkeyptr);
      result.clear();
      obj.decryptBinaryNums(result,fifres_p,seckeyptr,cptr,false,true);
      for (int i=0;i<result.size();i++) {
         System.out.println("##inj dv2:"+i+":"+result.get(i));
      }
   }

}
