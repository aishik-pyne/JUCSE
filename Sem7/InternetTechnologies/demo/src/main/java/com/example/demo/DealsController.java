package com.example.demo;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.GetMapping;


import java.util.List;

@RestController
public class DealsController {
    @Autowired
    private DealsRepository repository;

    @GetMapping("/deals")
    public List<Deals> getDeals() {
        return this.repository.findAll();
    }
    
}