package com.example.demo;

import org.bson.types.ObjectId;
import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.DBRef;
import org.springframework.data.mongodb.core.mapping.Document;
import org.springframework.data.mongodb.core.mapping.Field;

@Document(collection = "Flights")
public class Flights {

    @Id
    public ObjectId _id;

    public String name;
    public String source;
    public String destination;
    public String departure;
    public Integer cost;

    // @DBRef
    @Field("deal")
    public Deals deal;

    public Flights() {
    }

    public Flights(String name, String source, String destination, String departure, Integer cost, Deals deal) {
        this.name = name;
        this.source = source;
        this.destination = destination;
        this.departure = departure;
        this.cost = cost;
        this.deal = deal;
    }

    @Override
    public String toString() {
        return String.format("Flight[id=%s, source='%s', departure='%s']", _id, source, destination);
    }

}