#if !defined( __STACK_H )
#include <Stack.h>
#endif	// __STACK_H

#if !defined( __STRNG_H )
#include <Strng.h>
#endif	// __STRNG_H

#ifndef __IOSTREAM_H
#include <iostream.h>       
#endif

int main()
{
    Stack theStack;
    String reverse("reverse");

    cout << "\nEnter some strings.  Reverse will collect the strings\n";
    cout << "for you until you enter the string \"reverse\".  Reverse\n";
    cout << "will then print out the strings you have entered, but in\n";
    cout << "reverse order.  Begin entering strings now.\n";

    for(;;)
        {
        char inputString[255];
        cin >> inputString;
        String& newString = *( new String( inputString ) );
        if( newString != reverse )
            {
            theStack.push( newString );
            }
        else 
            {
            break;
            }
        }

    cout << "\nThe strings you entered (if any) are:\n";
    while( !(theStack.isEmpty()) )
        {
        Object& oldString = theStack.pop();
        cout << oldString << "\n";
        delete &oldString;
        }
    return 0;
}
