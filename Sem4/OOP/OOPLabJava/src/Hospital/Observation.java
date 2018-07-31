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
public class Observation {
    Date date;
    float bloodPressure;
    float temperature;
    Observation(float bloodPressure,float temperature){
        this.bloodPressure=bloodPressure;
        this.temperature=temperature;
        this.date=new Date();
    }
    Observation(){
        this.bloodPressure=0;
        this.temperature=0;
        this.date=new Date();
    }
    void takeReadings(){
        Scanner sc=new Scanner(System.in);
        System.out.print("Enter Temp: ");this.temperature=sc.nextFloat();
        System.out.print("Enter BP  : ");this.bloodPressure=sc.nextFloat();
        
    }
    void display(){
        System.out.print("Temperature:"+this.temperature+"\nBP: "+this.bloodPressure+"\nDate: "+this.date);
    }
}
