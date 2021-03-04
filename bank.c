//********************************************************************
//  bank.c        Author: Dawn Lawrie, then binkley
//********************************************************************

#include <stdio.h>
#include "memwatch.h"
#include "account.h"

static const int MAX_SIZE=2000;
static const int INIT_BANK_SIZE=2;

typedef struct bank Bank;
struct bank
{
  Account **bank_data;
  char* account_file;
  int account_count;
  int account_max;
};


/* purpose: print a message and terminate the program
 * input:   the message
 * returns: never!! terminates progam
 */
static void die(char *msg)
{
  perror(msg);
  exit(-1);
}


/* purpose: create an empty bank 
 * input:   the bank's (data file) name, filename
 * returns: the new bank 'object'
 */
Bank* bank_create (char* filename)
{
  Bank *bank = (Bank*) malloc(sizeof(Bank));
  if (bank == NULL)
    die("malloc bank");
  bank->bank_data = (Account **) malloc(INIT_BANK_SIZE*sizeof(Account*));
  if (bank->bank_data == NULL)
    die("malloc bank_data");
  bank->account_file = strdup(filename);
  if (bank->account_file == NULL)
    die("malloc account_file");
  bank->account_count = 0;
  bank->account_max = INIT_BANK_SIZE;

  return bank;
}


/* purpose: free memory allocated to a bank
 * input:   the bank
 * returns: nothing (as a side effect returns memory to the heap)
 */
void bank_free (Bank *bank)
{

//  free each account

  free(bank->account_file);
  free(bank->bank_data);
  free(bank);
}


/* purpose: loads the account information from bank's account file
 * input:   the bank 
 * returns: accounts from the file are added to the bank
 */
void read_acct_file(Bank *bank)
{
  FILE *fin = fopen(bank->account_file, "r");
  if (fin == NULL)
    die("read_acct_file fopen");

  char fname[MAX_SIZE];
  char lname[MAX_SIZE];
  char owner[MAX_SIZE];
  long acct_num;
  double balance;

  while (fscanf(fin, "%ld %s %s %lf", &acct_num, fname, lname, &balance) == 4)
  {
    sprintf(owner, "%s %s", fname, lname);

    // double array size if there is insufficient room for the new account
    if (bank->account_count >= bank->account_max)
	{
	  printf("double!\n");
      bank->account_max *= 2;
      bank->bank_data = (Account **) realloc(bank->bank_data,
                                     bank->account_max * sizeof(Account*));
      if (bank->bank_data == NULL)
        die("realloc");
	}

    bank->bank_data[bank->account_count++] 
	  = account_create(owner, acct_num, balance);
  }

  fclose(fin);
}


/* purpose: save the current bank information to its file
 * input:   the bank
 * returns: nothing (as a side effect the file is updated)
 */
void save_account_file(Bank *bank)
{
  FILE *out = fopen(bank->account_file, "w");
  if (!out)
    die("fopen account_file");

  int i;
  for(i=0; i<bank->account_count; i++)
    if (bank->bank_data[i] != NULL)
      account_write(out, bank->bank_data[i]);

  fclose(out);
}

/* purpose: print out the bank account holders
 * input:   the bank
 * returns: nothing (prints to the screen as a side effect)
 */
void print_bank(Bank *bank)
{
  int i;
  for(i=0; i<bank->account_count; i++)
    if(bank->bank_data[i] != NULL)
      printf("Account number: %ld\n\tOwner: %s\n",bank->bank_data[i]->number,
                                                  bank->bank_data[i]->name);
}

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "Usage: %s <data file>\n", argv[0]);
    return 42;
  }

  Bank *my_bank = bank_create(argv[1]);
  read_acct_file(my_bank);
  save_account_file(my_bank);
  print_bank(my_bank);
  bank_free(my_bank);
  return 0;
}


