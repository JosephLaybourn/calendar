/*******************************************************************************
filename    calendar.c
author      Joey Laybourn
DP email    j.laybourn@digipen.edu
course      CS120
section     A
assignment  8
due date    11/1/2017

Brief Description:
prints out a calendar
*******************************************************************************/

#include <stdio.h>

#define TRUE  1
#define FALSE 0

/******************************************************************************
       Function: is_leapyear

    Description: finds if a given year is a leapyear

         Inputs: year - the year being tested

        Outputs: true or false.  True if leapyear, false if not
******************************************************************************/
int is_leapyear(int year)
{
  /*if the year is divisible by four but not 100*/
  if (year % 4 == 0 && year % 100 != 0)
    return TRUE;
  
  if (year % 400 == 0)                      /*if the year is divisible by 400*/
    return TRUE;

  else              /*if these conditions are not met, year is not a leapyear*/
    return FALSE;
}

/******************************************************************************
       Function: day_of_the_week

    Description: finds what day of the week to start

         Inputs: year  - the year being tested
                 month - the month being tested
                 day   - the day of the week being tested

        Outputs: a number indicating when to start the calendar
******************************************************************************/
int day_of_the_week(int day, int month, int year)
{
  /*variable to add depending on the month*/
  int month_keys[] = {1, 4, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6};

  int lastTwoDigits;                        /*the last two digits of the year*/
  int indicator;                            /*the day of the week to start   */

  /*these two while loops make sure the year is between 1700 - 2099*/
  while (year > 2099)
    year -= 400;
  while(year < 1700)
    year += 400;

  lastTwoDigits = year % 100;          /*gets the last two digits of the year*/
  indicator = lastTwoDigits / 4;       /*divides the last two digits by 4    */
  indicator += day;                    /*add the day to the solution         */

  /*adds a specific number depending on what the month is.  Number was given.*/
  indicator += month_keys[month - 1];

  /*checks to see if the month is either January or February and a leap year.*/
  if (month < 3 && is_leapyear(year) == TRUE)
    indicator -= 1;

  /*these if blocks add a number to the solution depending on the year.      */
  if (year >= 1700 && year <= 1799)
    indicator += 4;
  else if (year >= 1800 && year <= 1899)
    indicator += 2;
  /*no if else for 1900-1999 because indicator does not change               */
  else if (year >= 2000 && year <= 2099)
    indicator += 6;

  indicator += lastTwoDigits; /*add the last two digits to the solution again*/

  if (indicator % 7 == 0)     /*accounts for Sunday                          */
    indicator = 7;
  else 
    indicator %= 7;           /*makes sure the solution is 1-7               */

  return indicator;           /*returns when to start on the calendar        */
}

/******************************************************************************
       Function: print_calendar

    Description: prints the calendar for a given month and year

         Inputs: year  - the year being printed
                 month - the month being printed

        Outputs: none
******************************************************************************/
void print_calendar(int month, int year)
{
  int i;                                       /*loop variable.  Used 3 times*/

  /*the variable used to indicate when to newline the first row of dates     */
  int whenToTab = 7 - day_of_the_week(1, month, year);
  int dayCount = 2;        /*will be incremented by one when a day is printed*/
 
  /*the last day of each month*/
  int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  char *months[] = {"January",   "February", "March",    "April",/*each month*/
                    "May",       "June",     "July",     "August",
                    "September", "October",  "November", "December"};

    /* Print calendar header */
  printf("%s, %i\n", months[month - 1], year);
  printf("Su Mo Tu We Th Fr Sa\n");
  printf("---------------------\n");

  /*this loop finds out when to print the first day*/
  for (i = 1; i < day_of_the_week(1, month, year); i++)
    printf("   ");
  printf(" 1");

  /*this loop prints the days of the first week*/
  for (i = 1; i <= whenToTab; i++)
  {
    printf("%3i", dayCount);
    dayCount++;
  }
  printf("\n");

  /*loop will break after the last day of the month*/
  while (TRUE)
  {
    /*will become false after the last day of the month is printed*/
    int breakPoint = TRUE;

    /*prints a next line every 7 days*/
    for (i = 1; i <= 7; i++)
    {
      printf("%2i ", dayCount);

      /*breaks out of the loop if the final day of the month is printed*/
      if (dayCount == days_in_month[month - 1])
      {
        breakPoint = FALSE;
        break;
      }
      dayCount++;
    }
    if (breakPoint == FALSE)
      break;

    printf("\n");
  }
  printf("\n");
}