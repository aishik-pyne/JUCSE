/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author aishi
 */

import java.util.*;
import java.io.*;
public class Student {
    int roll;
    Date date;
    String name;
    double marks[];
    static int last_roll=0;
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
    void display(){
        System.out.println("Roll "+roll);
        System.out.println("Name "+name);
        System.out.println("Date of admission "+date.toString());
        System.out.println();
    }
    public static void main(String args[]){
        Scanner sc=new Scanner(System.in);
        Vector student_list=new Vector();
        int choice;
        do{
            System.out.print("Enter Choice: ");
            System.out.print("Add Student: ");
            System.out.print("Display all students: ");
            System.out.print("Marksheet: ");
            System.out.print("Enter Choice: ");
            choice=sc.nextInt();
            switch(choice){
                case 1:{
                    System.out.print("Enter name:");
                    String t=sc.nextLine();
                    Student S=new Student(t);
                    student_list.add(S);
                    break;
                }
                case 2:{
                    for(int i=0;i<student_list.capacity();i++){
                        
                    }
                    break;
                }
            }
        }while(choice!=-1);
        Student S=new Student("Aishik Pyne");
        S.mark_sheet();
    }
}
