/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Hospital;

import java.util.ArrayList;

/**
 *
 * @author The Guardian
 */
public class Patient extends Person {
    static int noOfPatientAdmited=0;
    static int noOfPatientDischarged=0;
    boolean admited;
    Doctor doctor;
    ArrayList<Observation> observationList=new ArrayList<Observation>();
    
    Patient(String name,String address,String phone){
        super(name,address,phone);
        this.id=++noOfPatientAdmited;
        this.admited=true;
    }
    void discharge(){
        noOfPatientDischarged++;
        admited=false;
    }
    void assignDoctor(Doctor doc){
        this.doctor=doc;
    }
    void recordObservation(float bp,float temp){
        observationList.add(new Observation(bp,temp));
    }
    void recordObservation(Observation ov){
        observationList.add(ov);
    }
    void displayObservations(){
        for(Observation ob:observationList){
            ob.display();
        }
    }

}
