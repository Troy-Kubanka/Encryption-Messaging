/*
Troy Kubanka

This program is a message center that receives inputs of a message & key, then automatically encrypts it. 
The user can choose to add messages, view all encrypted messages stored, or extract a message and decrypt it if authorized.
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
//prototypes
int messageCenter (int num);
void sortMessages (int i, char message[][200]);
void key (int i, char message [][200], int shiftKey[]); 
void encryption (int i, char message[][200], int shiftKey[], char encrypt[][200]);
void allEncrypts (char encrypt[][200], int i);
void decipher (char encrypt[][200], char message[][200], int shiftKey[], int i);

int main()
{
   //main variables
   char message[50][200], encrypt[50][200];
   int shiftKey[50], i = 0, k = 0, num = 0;
   
   //Title and function used as a message center (function repeated within main to avoid clutter)
   cout << endl << endl << setw(40) << "MESSAGE CENTER" << endl;
   num = messageCenter(num); 
   while(num != 4)
   {  
      //input of num==1 brings user to sort and add a message and link a key input to it
      if(num == 1)
      {
      //sort the user's message input 
      sortMessages(i, message);
      //function to link input key to specific message
      key(i, message, shiftKey); 
      //function that encrypts the message given and stores it to encrypt[i]
      encryption(i, message, shiftKey, encrypt);
      if(i <= 49)
         i++;
         k++;
      }
      //input of num==2 reveals all messages encrypted
      else if(num == 2)
      {
         allEncrypts(encrypt, i); 
      }
      //input of num==3 allows user to choose a specific message and, if input correct key, can decipher it  
      else if(num == 3)
      {
         decipher(encrypt, message, shiftKey, i);
      }

      num = messageCenter(num);
   }
   //input of num==4 leaves the message center and closes the program
   cout << endl << endl << "You have successfully exited the message center." << endl;
   return 0;
}

//function for Message Center: to give user choice to encrypt new message, view stored encrypted messages, unencrypt a stored message, or exit message center
int messageCenter (int num)
{ 
   //local variables
   int d;

   for(d=0; d<70; d++)
      cout << "-";
   cout << endl << "Input 1: to insert a new message and a key input for that message" << endl << "Input 2: to view all the current messages encrypted" << endl << "Input 3: to select a certain message and decrypt with the correct key" << endl << "Input 4: to exit the message center" << endl;
   for(d=0; d<70; d++)
      cout << "-";
   cout << endl << "input: ";
   cin >> num; 
   while(num != 1 && num != 2 && num != 3 && num != 4)
   {
      cout << "Error! Please select '1', '2', '3', or '4': ";
      cin >> num;
   } 
   return num;
}

//function to store messages in a 2D array (message[][]) that will later adjust each character of a message 
void sortMessages (int i, char message[][200]) 
{
   //local variables
   int j; 

   if(i > 49)
      cout << "Error! You have exceeded the number of messages you can store. Maximum of 50 messages!";
   else if(i < 49)
   {
      cout << endl << "Enter your one-word message here: ";
      cin >> message[i];
   }
}

//function to add a key to a specific message
void key (int i, char message[][200], int shiftKey[])
{
   //local variables
   int keyNum;

   cout << endl << "Please enter the key you wish to associate with this message: ";
   cin >> keyNum; 
   
   //converting KeyNum to accept all integer values, and have 0 create an error
   while(keyNum == 0)
   {
      cout << "Error! Does not encrypt any code! You must choose a number other than 0: ";
      cin >> keyNum;
   } 
   if(keyNum > 26)
      keyNum = keyNum % 26;
   else if(keyNum < 0 && keyNum > -26)
      keyNum = keyNum * -1;
   else if(keyNum < -26)
      keyNum = (keyNum * -1) % 26;

   shiftKey[i] = keyNum;
}

//function to encrypt the message based on the original message and key given 
void encryption (int i, char message[][200], int shiftKey[], char encrypt[][200]) 
{ 
   //local variables
   int j=0;
   
   //Adjusting characters to make sure only letters change and letters properly change to correct letter encryption
   for(j=0; message[i][j] != '\0'; j++)
      if((message[i][j] < 'A' || message[i][j] > 'Z') && (message[i][j] < 'a' || message[i][j] > 'z'))
         encrypt[i][j] = message[i][j];
      else if(message[i][j] >= 'a' && message[i][j] <= 'z')
      {
         if(message[i][j] + shiftKey[i] > 'z')
            encrypt[i][j] = message[i][j] - 'z' - 1 + 'a' + shiftKey[i];
         else 
            encrypt[i][j] = message[i][j] + shiftKey[i];
      }
      else if(message[i][j] >= 'A' && message[i][j] <= 'Z') 
      {
         if(message[i][j] + shiftKey[i] > 'Z') 
            encrypt[i][j] = message[i][j] - 'z' - 1 + 'a' + shiftKey[i];
         else
            encrypt[i][j] = message[i][j] + shiftKey[i];
      }   
   cout << endl << "Encryption complete." << endl;     
}

//function that lists all the encrypted messages that were already added; using 2D Array loop
void allEncrypts (char encrypt[][200], int i)
{
   //local variables
   int messageRow, j;

   cout << endl << "Your encrypted messages: " << endl << endl;
   for(messageRow = 0; messageRow < i; messageRow++)
   {
      cout << "Message " << messageRow + 1 << ":    ";
      for(j = 0; encrypt[messageRow][j] != '\0'; j++)
         cout << encrypt[messageRow][j];
      cout << endl;
   }
} 

//function that decyphers a particular encrypted message selected, but only if given the correct key. 
void decipher (char encrypt[][200], char message[][200], int shiftKey[], int i)
{
   //local variables
   int numChoice, keyNum, j, quit = 0;

   cout << endl << "Enter the message number you would like to decipher: ";
   cin >> numChoice;
   //Making sure user can only selected messages already stored
   while(numChoice < 1)
   {
      cout << endl << "Error! Lowest message you can select is message 1. Please try a message number that's been encrypted: ";
      cin >> numChoice;
   }
   while(numChoice > i)
   {
      cout << endl << "Error! You don't have that many messages stored. Please choose a message number that's already been encrytped: ";
      cin >> numChoice;
   }
   //outputting the encrypted message asked for, asking for key
   cout << endl << "Your encrypted message is: ";
   for(j=0; j < 200; j++)
      cout << encrypt[numChoice-1][j];
   cout << endl << "Enter the key to decipher this message: ";
   cin >> keyNum;
   //adjusting keyNum so that it takes all integer values
   if(keyNum > 26)
      keyNum = keyNum % 26;
   else if(keyNum < 0 && keyNum > -26)
      keyNum = keyNum * -1;
   else if(keyNum < -26)
      keyNum = (keyNum * -1) % 26;
   //loop until user quits or recieves correct key
   while(keyNum != shiftKey[numChoice-1] && quit == 0)
   {
      cout << endl << "Incorrect key..." << endl << endl << "Select '1' to try again" << endl << "Select '2' to quit" << endl << "input: ";
      cin >> quit;
      while(quit != 1 && quit != 2)
      {
         cout << endl << "Error! Please select '1' or '2': ";
         cin >> quit;
      }      
      if(quit == 1)
      {
         quit--;
         cout << endl << "Enter the key to decipher this message: ";
         cin >> keyNum;
      }
   }
   //If user inputs correct key
   if(keyNum == shiftKey[numChoice-1])
   {
      cout << endl << "Correct. Message ";
      for(j=0; encrypt[numChoice-1][j] != '\0'; j++)
        cout << encrypt[numChoice-1][j];
      cout << " is really: ";
      for(j=0; message[numChoice-1][j] != '\0'; j++)
         cout << message[numChoice-1][j];
      cout << endl; 
   }
}
