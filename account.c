//********************************************************************
//  account.c       Author: Lewis/Loftus/binkley
//  a bank account with basic services such as deposit and withdraw.
//********************************************************************

#include <stdio.h>  
#include "memwatch.h"
#include "account.h"


/* purpose: print a message and terminate the program
 * input:   the message
 * returns: never!! terminates progam
 */
static void die(char *msg)
{
  perror(msg);
  exit(-1);
}


/* purpose: set up an account 
 * input:   the owner, owner, account number acct_num, 
 *          and initial balance, init_bal
 * returns: the newly created account 'object'
 */
Account *account_create(char * owner, long acct_num, double init_bal)
{
  Account *acct = (Account *) malloc(sizeof(Account));
  if (acct == NULL)
    die("malloc acct");
  acct->name = (char *) strdup(owner);
  if (acct->name == NULL)
    die("strdup name");

  acct->number = acct_num;
  acct->balance = init_bal;
  return acct;
}


/* purpose: deposit amount into the account. 
 * input:   the account, acct, the amount, amount
 * returns: the updated balance
 */
double account_deposit(Account *acct, double amount)
{
  acct->balance += amount;
  return acct->balance;
}
    

/* purpose: withdraws amount + fee from an account
 * input:   the account, acct, the amount, amount, and the fee, fee
 * returns: the updated balance
 */
double account_withdraw(Account *acct, double amount, double fee)
{
  acct->balance -= amount + fee;
  return acct->balance;
}
    

/* purpose: write account information to a file
 * input: an open file, to, and the account, acct
 * returns:  nothing (file is written as a side effect)
 */
void account_write(FILE *to, Account *acct)
{
  fprintf(to, "%ld\t%s\t%lf\n", acct->number, acct->name, acct->balance);
}


