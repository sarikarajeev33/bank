//********************************************************************
//  account.c       Author: Lewis/Loftus/binkley :)
//
//  A bank account with basic services such as deposit and withdraw.
//********************************************************************


typedef struct account Account;
struct account 
{
  long number;
  double balance;
  char *name;
};


Account *account_create(char*, long , double);
double account_deposit (Account *, double);
double account_withdraw (Account *, double, double);
void account_write(FILE *, Account *);




// Lab Instructions:
//   git pull <FIX ME>
//   link in memwatch (see the Makefile)
//   compile and run
//   look at .log
//   fix it!
