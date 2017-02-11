/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package assignment3;

/**
 *
 * @author aishi
 */
import java.util.*;
import java.io.*;
class Item{
	private int code;
	private String name;
	private double rate;
	private int quantity;
	
        
        Item(int c,String s,double r,int q){
            code=c;
            name=s;
            rate=r;
            quantity=q;
        }
        public int getCode(){
            return this.code;
        }
        public int getQuantity(){
            return this.quantity;
        }
        public String getName(){
                return name;
            }
        public double getRate(){
                return rate;
            }
        
        
        public boolean updateRate(double r){
            if(r>0){
                this.rate=r;return true;
            }else{
                System.out.print("WRONG RATE");return false;
            }
        }
        public void displayItem(){
            System.out.println("Code: "+code);
            System.out.println("Name: "+name);
            System.out.println("Rate: "+rate);
            System.out.println("Qty : "+quantity);
            System.out.println();
        }
        
        
        public void itemReceived(){
            this.quantity++;
        }
        public boolean itemIssued(){
            if(this.quantity>0){
                this.quantity--;
                return true;
            }
            return false;
        }
        public boolean itemIssued(int amt){
            if(amt<=this.quantity){
                this.quantity--;
                return true;
            }
            return false;
        }
}
public class ItemList {
    static ArrayList<Item> list=new ArrayList();
    private static Item search(int code){
        for(Item i: list){
            if(i.getCode()==code)
                return i;
        }
        return null;
    }
    public static void main(String args[])throws IOException{
        InputStreamReader isr=new InputStreamReader(System.in);
        BufferedReader br=new BufferedReader(isr);
        outer:
        while(true){
            System.out.println();
            System.out.println("1. Add New Items");
            System.out.println("2. Update Rate");
            System.out.println("3. Issue Item");
            System.out.println("4. Display full list");
            int choice = Integer.parseInt(br.readLine());
            System.out.println();
            switch(choice){
                case 1:{
                    System.out.println("Enter Code :");
                    int code=Integer.parseInt(br.readLine());
                    if(search(code)==null){
                        System.out.println("Enter Name :");
                        String name=br.readLine();
                        System.out.println("Enter Rate :");
                        double rate=Double.parseDouble(br.readLine());
                        System.out.println("Enter Qty  :");
                        int qty=Integer.parseInt(br.readLine());
                        Item i=new Item(code,name,rate,qty);       
                        list.add(i);
                        System.out.println("ITEM ADDED SUCCESSFULLY");
                    } else {
                        System.out.println("CODE ALREADY EXISTS");
                    }
                    break;
                }
                case 2:{
                    System.out.println("Enter Code :");
                    int code=Integer.parseInt(br.readLine());
                    if(search(code)!=null){
                         System.out.println("Enter New Rate :");
                        double rate=Double.parseDouble(br.readLine());
                        if(search(code).updateRate(rate)==true)
                            System.out.println("RATE UPDATED SUCCESSFULLY");
                    } else {
                        System.out.println("WRONG CODE");
                    }
                    break;
                }
                case 3:{
                    System.out.println("Enter Code :");
                    int code=Integer.parseInt(br.readLine());
                    if(search(code)!=null){
                        System.out.print("Enter no of items :");
                        int qty=Integer.parseInt(br.readLine());
                        if(search(code).itemIssued(qty)){
                            System.out.println("ITEM ISSUED");
                        }else{
                            System.out.println("OUT OF STOCK");
                        }
                    } else {
                        System.out.println("WRONG CODE");
                    }
                    break;
                }
                case 4:{
                    for(Item i:list){
                        i.displayItem();
                    }
                    break;
                }
                default: break outer;
            }
        }
    }
}
