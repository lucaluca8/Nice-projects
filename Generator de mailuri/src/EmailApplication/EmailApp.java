package EmailApplication;

public class EmailApp {
    public static void main(String[] args) {
        Email em1=new Email("John","Smith");

        em1.SetAltEmail("newmail@gs.com");
      //  System.out.println(em1.GetAlternateEmail());
       System.out.println( em1.ShowInfo());


    }
}
