/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Hospital;

import java.io.*;
import java.util.*;
/**
 *
 * @author The Guardian
 */
public class Hospital {
    static ArrayList<Patient> patientList=new ArrayList();
    static ArrayList<Doctor> doctorList=new ArrayList();
    public static Doctor searchDoctor(int id){
        for(Doctor d:doctorList){
            if(d.id==id){
                return d; 
            }
        }return null;
    }
    public static Patient searchPatient(int id){
        for(Patient p:patientList){
            if(p.id==id){
                return p; 
            }
        }return null;
    }
    
    
    
    public static void main(String srgs[])throws IOException{
        InputStreamReader isr=new InputStreamReader(System.in);
        BufferedReader br=new BufferedReader(isr);
        outer:
        while(true){
            System.out.println("1.Register new patient");
            System.out.println("2.Add new doctor");
            System.out.println("3.Record Observation");
            System.out.println("4.Display Patient Status");
            int ch=Integer.parseInt(br.readLine());
            System.out.println();
            switch(ch){
                case 1:{
                    System.out.print("Enter name    :");String name=br.readLine();
                    System.out.print("Enter address :");String address=br.readLine();
                    System.out.print("Enter phone   :");String phone=br.readLine();
                    Doctor doc;
                    do{
                        System.out.print("Enter valid doc id  :");int docId=Integer.parseInt(br.readLine());
                        doc=searchDoctor(docId);
                    }while(doc==null);
                    Patient p=new Patient(name,address,phone);
                    p.assignDoctor(doc);
                    doc.assignPatient(p);
                    patientList.add(p);
                    System.out.println("PATIENT ADDED SUCCESSFULLY");
                    break;
                }
                case 2:{
                    System.out.print("Enter name    :");String name=br.readLine();
                    System.out.print("Enter address :");String address=br.readLine();
                    System.out.print("Enter phone   :");String phone=br.readLine();
                    
                    Doctor d=new Doctor(name,address,phone);
                    doctorList.add(d);
                    System.out.println("DOCTOR ADDED SUCCESSFULLY");
                    break;
                }
                case 3:{
                    Doctor d;
                    do{
                        System.out.print("Enter valid doc id  :");int docId=Integer.parseInt(br.readLine());
                        d=searchDoctor(docId);
                    }while(d==null);
                    d.displayPatientList();
                    
                    Patient p;
                    do{
                        System.out.print("Enter valid patient id  :");int patId=Integer.parseInt(br.readLine());
                        p=searchPatient(patId);
                    }while(p==null);
                    Observation ov=new Observation();
                    ov.takeReadings();
                    p.recordObservation(ov);
                    System.out.println("RECORD ADDED SUCCESSFULLY");
                    break;
                }
                case 4:{
                    Patient p;
                    do{
                        System.out.print("Enter valid patient id  :");int patId=Integer.parseInt(br.readLine());
                        p=searchPatient(patId);
                    }while(p==null);
                    p.displayName();
                    p.displayObservations();
                    break;
                }
                default:{
                    break outer;
                }
            }
        }
    }
    
}
