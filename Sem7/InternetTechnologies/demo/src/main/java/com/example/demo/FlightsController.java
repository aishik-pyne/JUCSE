package com.example.demo;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.GetMapping;


import java.util.List;

@RestController
public class FlightsController {
    @Autowired
    private FlightsRepository repository;

    @GetMapping("/flights")
    public List<Flights> getFlights() {
        return this.repository.findAll();
        // return this.repository.findBySource("CCU");
    }
    
}