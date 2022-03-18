#include "stdio.h"
#include "stdlib.h"

/**
 * For all derived Employee classes vtable variable should be the first member
 */

struct Employee {
    void **vtable;
    int age;
};

struct HourlyEmployee {
    void **vtableHourly;
    int age;
    double hourlyRate;
    double hours;
};

struct CommissionEmployee {
    void **vtableCommission;
    int age;
    double salesAmount;
};

/**
 * Cast to HourlyEmployee Pointer and then print its Speak() statement
 * @param e Passing Employee Pointer e
 */
void SpeakHourly(struct Employee *e){
    struct HourlyEmployee *he = (struct HourlyEmployee *) e;
    printf("I work for ", he->hourlyRate, " dollars per hour");
}

/**
 * Cast to HourlyEmployee Pointer and then return their total pay
 * @param e employee pointer
 * @return The total pay = HourlyRate * Hours worked
 */
double GetPayHourly(struct Employee *e) {
    struct HourlyEmployee *f = (struct HourlyEmployee *) e;
    return (f->hourlyRate * f->hours);
}

/**
 * Cast to CommissionEmployee and then print its Speak() statement
 * @param e employee pointer
 */
void SpeakCommission(struct Employee *e) {
    struct CommissionEmployee *c = (struct CommissionEmployee *) e;
    printf("I make commission on ", c->salesAmount, " dollars in sales!");
}

/**
 * Cast to CommissionEmployee and then return their commission
 * @param e
 * @return total pay = 10% of their sales amount plus 4,000
 */
double GetPayCommission(struct Employee *e) {
    struct CommissionEmployee *c = (struct CommissionEmployee *) e;
    return 0.1 * c->salesAmount + 4000;
}

/**
 * Create global variables for all Employee Types.
*/
void **VTableHourly = {SpeakHourly, GetPayHourly};
void **VTableCommission = {SpeakCommission, GetPayCommission};


/**
 * Construct a HourlyEmployee
 * @param he -> HourleEmployee pointer
 * @param a -> age
 * @param hRate -> hourlyRage
 * @param hrs -> hours
 * @return -> A fully constructed HourlyEmployee
 */
struct HourlyEmployee ConstructHourly(struct HourlyEmployee *he, int a, double hRate, double hrs) {
    he->age = a;
    he->hourlyRate = hRate;
    he->hours = hrs;
    he->vtableHourly = VTableHourly;
    return *he;
}

struct CommissionEmployee ConstructCommission(struct CommissionEmployee *c, int a, double sa) {
    c->age = a;
    c->salesAmount = sa;
    c->vtableCommission = VTableCommission;
    return *c
}