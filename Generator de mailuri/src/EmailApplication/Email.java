package EmailApplication;

import java.util.Locale;
import java.util.Scanner;

public class Email {
    private String firstName;
    private String lastName;
    private String password;
    private String departament;
    private String email;
    private int mailboxCpacity=500;
    private String alternateEmail;
    private int defaultPasswordLenght=10;
    private String companySufix="company.com";

    //Constructor care sa ia first name si last name
    public Email(String firstName, String lastName){
        this.firstName=firstName;
        this.lastName=lastName;
        //System.out.println("EMAIL CREATED: " +this.firstName+" "+this.lastName);

        //Apelam o metoda care o sa ceara departamentul si dupa care il returneaza
        this.departament=SetDepartament();
     //   System.out.println("Department: "+this.departament);

        //Apelam o metoda care ne face o parola
        this.password=RandomPassword(defaultPasswordLenght);
       // System.out.println("Your password is: "+this.password);

        //Combinam toate elementele sa generam un mail
        email=firstName.toLowerCase() + "." +lastName.toLowerCase()+"@"+departament+"."+companySufix;
        //System.out.println("Your email is: "+email);
    }

    //Input pentru departamnet
    private String SetDepartament()
    {
        System.out.print("DEPARTMENT CODE\n1 for Sales\n2 for Development\n3 for Accounting\n0 for none\nenter department code: ");
        Scanner in=new Scanner(System.in);
        int depChoice=in.nextInt();
        if (depChoice == 1) return "Sales"; else if(depChoice == 2) return "Development"; else if(depChoice == 3) return "Accounting"; else return "";
    }
    //Generator de password
    private String RandomPassword(int len){
        String passwordSet="zxcvbnmasdfghjklqwertyuiopABCDEFGHIJKLMNOPRSTUXYZ1234567890!@#$%";
        char[] password=new char[len];
        for(int i=0;i<len;i++)
        {
           int rand = (int)(Math.random() * passwordSet.length());
           password[i]=passwordSet.charAt(rand);
        }
        return new String(password);
    }

    //Setam marimea mailboxului
        public void SetMailboxCpacity(int capacity){
            this.mailboxCpacity=capacity;
        }
    //Sa putem schimba mailul
    public void SetAltEmail(String altEmail)
    {
        this.alternateEmail=altEmail;
    }

    //Sa putem schimba parola
    public void ChangePassword(String password)
    {
        this.password=password;
    }
    //Getters
    public int GetMailboxCapacity(){ return mailboxCpacity;}
    public String GetAlternateEmail(){ return alternateEmail;}
    public String GetPassword(){ return password;}
    public String ShowInfo()
    {
        return "DISPLAY NAME: "+firstName+" "+lastName+
                "\nCOMPANY EMAIL: "+ email+
                "\nMAILBOX CAPACITY: "+mailboxCpacity+"mb";
    }
}
