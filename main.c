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
    void **vtable;
    int age;
    double hourlyRate;
    double hours;
};

struct CommissionEmployee {
    void **vtable;
    int age;
    double salesAmount;
};

struct SeniorSalesMan {
    void **vtable;
    int age;
    double salesAmount;
};

void Speak(struct Employee *e) {
    printf("0");
}

double GetPay(struct Employee *e) {
    return 0.0;
}

/**
 * Cast to HourlyEmployee Pointer and then print its Speak() statement
 * @param e Passing Employee Pointer e
 */
void SpeakHourly(struct Employee *e){
    struct HourlyEmployee *he = (struct HourlyEmployee *) e;
    printf("I work for %lf dollars per hour", he->hourlyRate);
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
    printf("I make commission on %lf dollars in sales!", c->salesAmount);
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
 * Override GetPay() of commission employee
 * @param e employee pointer
 * @return total pay = 20% of their sales and extra 5% if they are at least 40 years old
 */
double GetPaySalesMan(struct Employee *e) {
    struct SeniorSalesMan *s = (struct SeniorSalesMan *) e;
    double ans = 0.2 * s->salesAmount;
    if (s->age >= 40) {
        ans += .05 * s->salesAmount;
    }
    return ans;
}

/**
 * Create global variables for all Employee Types.
*/
void *VTable = {Speak, GetPay};
void *VTableHourly[2] = {SpeakHourly, GetPayHourly};
void *VTableCommission[2] = {SpeakCommission, GetPayCommission};
void *VTableSalesMan[2] = {SpeakCommission, GetPaySalesMan};


/**
 * Construct a HourlyEmployee
 * Construct a Commission Employee
 * Construct a Senior Sales Man
 *
 * INITIALIZE ALL TO 0
 */
struct HourlyEmployee ConstructHourly(struct HourlyEmployee *he) {
    he->vtable = VTableHourly;
    he->age = 0;
    he->hourlyRate = 0;
    he->hours = 0;
    return *he;

}

struct CommissionEmployee ConstructCommission(struct CommissionEmployee *c) {
    c->vtable = VTableCommission;
    c->age = 0;
    c->salesAmount = 0;
    return *c;

}

struct SeniorSalesMan ConstructSeniorSales(struct SeniorSalesMan *s) {
    s->vtable = VTableSalesMan;
    s->age = 0;
    s->salesAmount = 0;
    return *s;
}


int main(){
    struct Employee *e;
    int choice;
    int age;
    printf("What type of employee do you want to make (1-3)?\n");
    printf("1. Hourly Employee\n");
    printf("2. Commission Employee\n");
    printf("3. Senior Sales Man\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    printf("Choice is %d", choice);
    printf("\n----------------\n");
    printf("\nWhat is the employees age: ");
    scanf("%d", &age);
    printf("\nEmployee age: %d", age);
    printf("\n----------------\n");

    if (choice == 1){
        // Hourly Employee chosen
        printf("\nConstructing Hourly Employee...\n");
        struct HourlyEmployee *h = (struct HourlyEmployee*)malloc(sizeof(struct HourlyEmployee));
        ConstructHourly(h);
        printf("\nWhat is the employees hourly rate: ");
        scanf("%lf", &(h->hourlyRate));
        printf("\n----------------\n");
        printf("\nWhat is the employees hours worked: ");
        scanf("%lf", &h->hours);
        h->age = age;

        e = (struct Employee*) h;

    } else if (choice == 2) {
        // Commission Employee Chosen
        printf("\nConstructing Employee Commission Employee...\n");
        struct CommissionEmployee *c = (struct CommissionEmployee *)malloc(sizeof(struct CommissionEmployee));
        ConstructCommission(c);
        printf("\nEnter the employees amount in sales:");
        scanf("%lf", &c->salesAmount);
        c->age = age;

        e = (struct Employee *)c;
    } else if (choice == 3) {
        // Senior Sales person chosen
        printf("\nConstructing Senior Sales Employee...\n");
        struct SeniorSalesMan *s = (struct SeniorSalesMan *)malloc(sizeof(struct SeniorSalesMan));
        ConstructSeniorSales(s);

        printf("\nEnter the employees amount in sales:");
        scanf("%lf", &s->salesAmount);
        s->age = age;

        e = (struct Employee *)s;

    } else {
        printf("Invalid Entry Rerun program");
        return 0;
    }
    printf("\nDone creating employee...\nCalling Speak and GetPay fxns...\n\n");

    ((void (*)(struct Employee*))e->vtable[0])((struct Employee *)e);
    double pay = ((double (*)(struct Employee*))e->vtable[1])((struct Employee *)e);
    printf("\nMy pay is %lf.", pay);
    return 0;
}