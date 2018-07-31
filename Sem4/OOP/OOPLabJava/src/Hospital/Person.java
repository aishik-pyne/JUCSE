/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Hospital;
import java.util.*;
/**
 *
 * @author The Guardian
 */
public abstract class Person {
    final String name;
    final String address;
    final String phone;
    int id;
    Person(){
        this.name="";
        this.address="";
        this.phone="";
    }
    Person(String name,String address,String phone){
        this.name=name;
        this.address=address;
        this.phone=phone;
    }
    void displayFull(){
        System.out.println("ID    :"+this.id);
        System.out.println("Name    :"+this.name);
        System.out.println("Address :"+this.address);
        System.out.println("Phone   :"+this.phone+"\n");
    }
    void displayName(){
        System.out.println("ID: "+this.id+ " Name    :"+this.name);
    }
}
