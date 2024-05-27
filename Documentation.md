# Pet Vet Health Documentation

## Classes:

 - [Operations](#operations)

---
---

## Operations

This class is used to store and access functions across the system, therefore, it doesn't have any atributes at all, only methods.

**Methods:**

- [Pet Vet Health Documentation](#pet-vet-health-documentation)
  - [Classes:](#classes)
  - [Operations](#operations)
    - [currentDate()](#currentdate)
    - [getAgeDifference()](#getagedifference)

### currentDate()

As the name tells, this function returns a date in the form of a vector. This vector will always have three elements inside, that correspond to `day`, `month` and `year` in that same order. 

In other words, when trying to access to the month in the returned vector, it should be done as:

```cpp
Operation op;
vector<int> v = op.CurrentDate();
cout<<v[1]; //Index 0 is day, Index 2 is year
```

### getAgeDifference()

For this function to work it needs to be given a `vector<int>` with the same format as the one returned in [CurrentDate()](#currentdate). 

This is because, working with the current date, this function returns the age gap between the given date and the current date in years.