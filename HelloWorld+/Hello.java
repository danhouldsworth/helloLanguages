// 1. Done. However the concat() method can sometimes be more efficient depending on the circumstance.

public class Hello {        // Note : public classes need the same name as filename
   public static void main(String[] args) {
      String greeting = "Hello";
      greeting += ", " + "World!";
      System.out.println(greeting);
   }
}
