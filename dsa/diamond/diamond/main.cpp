//
//  main.cpp
//  dsa
//
//  Created by Abdelrahman Ahmed on 30/03/2016.
//  Copyright © 2016 Abdelrahman Ahmed. All rights reserved.
//

#include <iostream>

using namespace std;

void drawDiamond(int size, char border, char fill);
void drawDiamondArray(int size, char border, char fill);
bool dataOK(int size, char border, char fill);
int getSize();
char getBorder();
char getFill();

int main(int argc, char *argv[])
{
   int size;
   char border, fill;
   
   if (argc > 1)
   {
      size = atoi(argv[1]);;
      border = argv[2][0];
      
      if (argv[3] == NULL)
      {
         fill = ' ';
      }
      else
      {
         fill = argv[3][0];
      }
   }
   else
   {
      size = getSize();
      border = getBorder();
      fill = getFill();
   }
   
   // draw the diamond
   if (dataOK(size, border, fill))
   {
      drawDiamond(size, border, fill);
   }
   else
   {
      cout << "Invalid diamond data\n";
   }
   
   return 0;
}

void println(int spaces, int fills, char border, char filler) {
   cout << std::string(spaces, ' ') << border;
   
   if (fills > 0)
   {
      cout << std::string(fills, filler) << border;
   }
   
   cout << "\n";
}

void printArray(int spaces, int fills, char border, char filler) {
   // code here to prep array for char
}

void drawDiamond(int size, char border, char fill)
{
   int n = (size-1)/2;
   
   for (int i = n; i >= 0; i--) {
      println(i, 2*(n - i) - 1, border, fill);
   }
   
   for (int i = 1; i <= n; i++) {
      println(i, 2*(n - i) - 1, border, fill);
   }
}

void drawDiamondArray(int size, char border, char fill)
{
   int n = (size-1)/2;
   
   char **diamondArray = new char *[size];
   
   for (int i = 0; i < size; i++)
   {
      diamondArray[i] = new char[size];
   }
   
   // example of using
   for (int row = 0; row < size; row++)
   {
      for (int col = 0; col < size; col++)
      {
         if (col - row == n) {
            diamondArray[row][col] = border;
         }
         else if (col - row < n) {
            diamondArray[row][col] = fill;
         }
         else if (col - row > n) {
            diamondArray[row][col] = ' ';
         }
         
         cout << diamondArray[row][col];
      }
      cout << endl;
   }
   
}

bool dataOK(int size, char border, char fill)
{
   // size must be an odd number
   if (size % 2 == 0) {
      return false;
   } else {
      return true;
   }
}

int getSize()
{
   int size;
   
   cout << "Please enter diamond size: ";
   cin >> size;
   return size;
}

char getBorder()
{
   char border;
   
   cout << "Please enter diamond border: ";
   cin >> border;
   return border;
   
}

char getFill()
{
   char fill;
   
   cout << "Please enter diamond fill: ";
   cin >> fill;
   return fill;
}