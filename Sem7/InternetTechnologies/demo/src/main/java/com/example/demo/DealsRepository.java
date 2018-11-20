package com.example.demo;

import org.springframework.data.mongodb.repository.MongoRepository;

public interface DealsRepository extends MongoRepository<Deals, String> {


}