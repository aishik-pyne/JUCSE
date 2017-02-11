/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Parenthesis;

/**
 *
 * @author aishi
 */
import java.io.*;
import java.util.Stack;
public class Parenthesis {
    
    
    static String input()throws IOException{
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        String str=br.readLine();
        return str;
    }
     static boolean validExp(String str){
         Stack<Character> s=new Stack();
         for(char c: str.toCharArray()){
             if(s.isEmpty()){
                 s.add(c);
             } else {
                 if(s.lastElement()=='{' && c=='}')
                     s.pop();
                 else if (s.lastElement()=='[' && c==']')
                     s.pop();
                 else if (s.lastElement()=='(' && c==')')
                     s.pop();
                 else 
                     s.add(c);
             }
         }
         if(s.isEmpty())
             return true;
         return false;
     }
     public static void main(String args[])throws IOException{
         String str=input();
         if(validExp(str))
             System.out.println("Valid");
         else
             System.out.println("Not Valid");
         
     }
}
