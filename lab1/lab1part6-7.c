// Name: Zachary Robin
// Date: 4/4/19
// Title: Lab1 part 6-7– Unix/Linux Commands and Overview of C Programming
// Description: This program performs computations for steps 6 and 7 of lab1. The computatiosn relate both to Circuit switching scenario as well as a Packet switching scenario
#include <stdio.h>      /* printf, stderr */
#include <stdlib.h>     /* atoi */
#include <math.h>


//factorial function used in part g. takes in a double and returns a double
double factorial(double num){
    double i, result;
    result = 1;
    for(i=1; i <= num; i++){
        result = (result * i);
    }
    return result;
}

//binomial distribution
double binomial(double x, double y){
    double r = (factorial(x)/((factorial(y)* factorial((x-y)))));
    return r;
}

int main(int argc, char *argv[]) {
    //Given inputs
    double linkBandwidth = 200;
    double userBandwidth = 20;
    double tPSuser  = 0.10;
    double nPSusers = 19;


    //Step 6 
    double nCSusers = (linkBandwidth / userBandwidth);
    printf("6a: %lf \n", nCSusers);

    //Step 7
    //a
    double pPSusers = tPSuser;
    printf("7a: %lf \n", pPSusers);

    //b
    double pPSusersNotBusy = 1 - pPSusers;
    printf("b: %lf \n", pPSusersNotBusy);

    //c
    //The probability that all of the other specific other users
    double all = pow((1-pPSusers),(nPSusers-1));
    printf("c: %e \n", all);

    //d
    //The probability that one specific user is transmitting and the remaining users are not transmitting 
    double notTransmit = pPSusers * pow(pPSusersNotBusy,(nPSusers-1));
    printf("d: %e \n ", notTransmit);

    //e
    //The probability that exactly one (any one) of the nPSusers users is busy is  pPSusers times the probability that a given specific user is transmitting and the remaining users are not transmitting
    double oneBusy = nPSusers * notTransmit;
    printf("e: %e \n ", oneBusy);

    //f
    //The probability that 10 specific users of nPSusers are transmitting and the others are idle is 
    double anyTen = pow(pPSusers,10) * pow(pPSusersNotBusy,(nPSusers-10));
    printf("f: %e \n ", anyTen);

    //g
    //The probability that any 10 users of nPSusers are transmitting and the others are idle 
    double y = binomial(nPSusers, 10);
    double tenTransmit = y * (pow(pPSusers,10))* pow(pPSusersNotBusy,(nPSusers-10));
    printf("g: %e \n ", tenTransmit);

    //h
    //The probability that more than 10 users of nPSusers are transmitting and the others are idle
    double i,sum;
    double g = nPSusers;
    for (i = 11;  i <= nPSusers; i++){
        sum += (binomial(nPSusers, i) * pow(pPSusers,i) * pow(pPSusersNotBusy,(nPSusers-i)));
    }
    printf("h: %e \n ", sum);
    return 0;
}
