#include <stdio.h>
#include <math.h>

int main(){
    double values[] = {
        0.00001,     // 1e-05  (exponent -5 < -4 → %e)
        0.0001,      // 0.0001 (exponent -4 → %f)
        0.12345,     // 0.12345
        1.2345,      // 1.2345
        12345.0,     // 12345
        123456.0,    // 123456
        1234567.0,   // 1.23457e+06 (exponent 6 ≥ precision 6 → %e)
    };
    
    for (int i = 0; i < 7; i++) {
        printf("Value: %-15g (auto-format)\n", values[i]);
    }
    
    double inf = 1.0 / 0.0;    // Infinity
    double nan = 0.0 / 0.0;    // NaN
    
    printf("Infinity: %g\n", inf);   // inf
    printf("NaN:      %g\n", nan);   // nan
    printf("Inf (G):  %G\n", inf);   // INF (uppercase)
    
    // Exactly zero
    printf("Zero: %g\n", 0.0);       // 0
    
    // Negative numbers
    printf("Negative: %g\n", -123.456);  // -123.456

    return 0;
}