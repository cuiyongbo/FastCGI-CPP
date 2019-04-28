#include "fcgi_stdio.h"
#include <stdlib.h>
#include <string.h>

#define POTENTIALLY_PRIME 0
#define COMPOSITE 1
#define VALS_IN_SIEVE_TABLE 1000000
#define MAX_NUMBER_OF_PRIME_NUMBERS 78600 

long int  sieve_table[VALS_IN_SIEVE_TABLE]; 
long int  prime_table[MAX_NUMBER_OF_PRIME_NUMBERS];  

void initialize_prime_table(void)
{
    long int prime_counter = 1;
    long int current_prime = 2; 
  
    prime_table[prime_counter]=current_prime;

    while (current_prime < VALS_IN_SIEVE_TABLE)
    {
        /* Mark off composite numbers. */
        // value = n * current_prime is not a prime
        for (long c = current_prime; c <= VALS_IN_SIEVE_TABLE; c += current_prime)
            sieve_table[c] = COMPOSITE;

        /* Find the next prime number. */
        long d = current_prime + 1;
        for (; sieve_table[d] == COMPOSITE; d++); 

        prime_table[++prime_counter] = d; 
        current_prime = d;
    }
}

int main(void)
{
    initialize_prime_table();

    while(FCGI_Accept() >= 0)
    {
        printf("Content-type: text/html\r\n"
               "\r\n");
        printf("<title>Prime FastCGI</title>\n"
               "<h1>Prime FastCGI</h1>\n");

        char* query_string = getenv("QUERY_STRING");
        if(query_string == NULL)
        {
            printf("Usage: Specify a positive number in the query string.\n");
        }
        else
        {
            query_string = strchr(query_string, '=') + 1;
            long int n = strtol(query_string, NULL, 10);
            if(n < 1)
            {
                printf("The query string '%s' is not a positive number.\n", query_string);
            }
            else if(n > MAX_NUMBER_OF_PRIME_NUMBERS)
            {
                printf("The number %ld is too large for this program.\n", n);
            }
            else
            {
                printf("The %ldth prime number is %ld.\n", n, prime_table[n]);
            }
        }
    }

    return 0;
}