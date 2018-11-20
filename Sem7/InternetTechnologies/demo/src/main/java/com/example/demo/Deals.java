package com.example.demo;

import org.bson.types.ObjectId;
import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;
// import org.springframework.data.mongodb.

@Document(collection = "Deals")
public class Deals {

    @Id
    public ObjectId _id;

    public String name;
    public Integer discountPercent;

    public Deals() {
    }

    public Deals(String name, Integer discountPercent) {
        this.name = name;
        this.discountPercent = discountPercent;
    }

    public String getName() {
        return name;
    }

    public Integer getDiscountPercent() {
        return discountPercent;
    }
    /**
     * @param name the name to set
     */
    public void setName(String name) {
        this.name = name;
    }
    /**
     * @param discountPercent the discountPercent to set
     */
    public void setDiscountPercent(Integer discountPercent) {
        this.discountPercent = discountPercent;
    }

    @Override
    public String toString() {
        return String.format("Deal[id=%s, name='%s', discountPercent='%s']", _id, name, discountPercent);
    }

}