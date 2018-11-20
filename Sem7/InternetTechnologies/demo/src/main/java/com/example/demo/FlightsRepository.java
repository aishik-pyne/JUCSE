package com.example.demo;

import java.util.List;

import org.springframework.data.mongodb.repository.MongoRepository;

public interface FlightsRepository extends MongoRepository<Flights, String> {

    public List<Flights> findByName(String name);
    public List<Flights> findBySource(String source);

}