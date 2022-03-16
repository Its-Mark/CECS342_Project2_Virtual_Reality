#include <iostream>
using namespace std;

class Employee {
    void **vtable;
    int age;
public:
    int getAge() { return age; }
    virtual void Speak() = 0;
    virtual double getPay() = 0;
};

class HourlyEmployee : Employee {
    void **vtable;
    int age;
    double hourlyRate;
    double hours;
public:
    virtual void Speak() { cout << "I work for " << hourlyRate << " dollars per hour."; }
};

class CommissionEmployee : Employee {
    void **vtable;
    int age;
    double salesAmount;
public:
    virtual void Speak() { cout << "I make commission on " << salesAmount << " dollars in sales!"; }
};

void SpeakHourly(struct Employee *e){
    (HourlyEmployee*)e;
    e->Speak();
}

double GetPayHourly(struct Employee *e){
    return 0;
}

void ConstructHourly(struct HourlyEmployee *he){

}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
