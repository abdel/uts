//
//  main.m
//  isPrime
//
//  Created by Abdelrahman Ahmed on 21/03/2016.
//  Copyright © 2016 UTS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <math.h>

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        int num, result;
        
        NSLog(@"Please enter a positive integer ");
        result = scanf("%d", &num);
        
        if (result == 1 && num >= 0)
        {
            bool isPrime = TRUE;
            
            if (num < 2)
            {
                // prime numbers must be greater than 1
                isPrime = FALSE;
            }
            else if (num > 2 && num % 2 == 0)
            {
                // if number is even and greater than 2 then not prime
                isPrime = FALSE;
            }
            else
            {
                // check if divisible by any odd number between
                // 3 and the square root of the number
                int max = sqrt(num);
                
                for (int i = 3; i <= max; i+=2)
                {
                    if (num % i == 0)
                    {
                        isPrime = FALSE;
                        break;
                    }
                }
            }
            
            if (isPrime)
                NSLog(@"%d is prime", num);
            else
                NSLog(@"%d is not prime", num);
        }
        else
        {
            NSLog(@"Must enter a positive integer");
        }
    }
    return 0;
}
