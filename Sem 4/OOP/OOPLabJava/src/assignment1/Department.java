/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package assignment1;

import java.io.*;

/**
 *
 * @author The Guardian
 */
public class Department extends Student {
    String dept;
    String inputName()throws IOException{
        InputStreamReader isr=new InputStreamReader(System.in);
        BufferedReader br=new BufferedReader(isr);
        System.out.println("Enter Name");
        String name=br.readLine();
        return name;
    }
    String inputDept()throws IOException{
        InputStreamReader isr=new InputStreamReader(System.in);
        BufferedReader br=new BufferedReader(isr);
        System.out.println("Enter Name");
        String dept=br.readLine();
        return dept;
    }
    Department(String n,String d){
       super(n);
       dept=d;
    }
    
}
