package assignment1;
import java.util.*;
import java.io.*;
public class Student {
    private final int roll;
    private final Date date;
    private final String name;
    private double marks[];
    private static int last_roll=0;
    int get_roll(){
        return roll;
    }
    Student(String n){
        last_roll++;
        roll=last_roll;
        name=n;
        marks=new double[5];
        for(int i=0;i<marks.length;i++){
            marks[i]=0;
        }
        date=new Date();
    }
    int count(){
        return last_roll;
    }
    void input_marks(){
        Scanner sc=new Scanner(System.in);
        for(int i=0;i<marks.length;i++){
            System.out.print("Enter marks in subject"+i+" ");
            marks[i]=sc.nextInt();
        }
    }
    void mark_sheet(){
        System.out.println("Roll:"+roll);
        System.out.println("Name:"+name);
        System.out.println("Date:"+date.toString());
        for(int i=0;i<marks.length;i++)
            System.out.print(marks[i]+" ");
        System.out.println();
    }
    double percentage(){
        double sum=0;
        for(double i:marks){
            sum+=i;
        }
        return (sum/marks.length);
    }
    void display(){
        System.out.println("Roll "+roll);
        System.out.println("Name "+name);
        System.out.println("Date of admission "+date.toString());
        System.out.println();
    }
    
    
    public static void main(String args[])throws IOException{
        InputStreamReader isr=new InputStreamReader(System.in);
        BufferedReader br=new BufferedReader(isr);
        Student student_list[]=new Student[10];
        for(int i=0;i<10;i++){
            student_list[i]=null;
        }
        int x=0;
        int choice;
        do{
            System.out.println("Enter Choice: ");
            System.out.println("1.Add Student: ");
            System.out.println("2.Display all students: ");
            System.out.println("3.Marksheet: ");
            System.out.println("4.Enter Marks: ");
            System.out.println("-1.Exit: ");
            choice=Integer.parseInt(br.readLine());
            switch(choice){
                case 1:{
                    System.out.print("Enter name:");
                    String t=br.readLine();
                    Student S=new Student(t);
                    student_list[x++]=S;
                    break;
                }
                case 2:{
                    for(int i=0;i<x;i++){
                        student_list[i].display();
                    }
                    break;
                }
                case 3: {
                    System.out.print("Enter roll:");
                    int t=Integer.parseInt(br.readLine());
                    for(int i=0;i<x;i++){
                        if(student_list[i].get_roll()==t){
                            student_list[i].mark_sheet();
                        }
                    }
                    break;
                }case 4: {
                    int r=Integer.parseInt(br.readLine());
                    Student s=student_list[r-1];
                    for(int i=0;i<5;i++){
                        System.out.println("Enter marks subject " + (i+1));
                        s.marks[i]=Integer.parseInt(br.readLine());
                    }
                    break;
                }
            }
        }while(choice!=-1);
    }
}
