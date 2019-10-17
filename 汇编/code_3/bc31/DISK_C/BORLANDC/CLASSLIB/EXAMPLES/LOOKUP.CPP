#if !defined( __ASSOC_H )
#include <Assoc.h>
#endif	// __ASSOC_H

#if !defined( __DICT_H )
#include <Dict.h>
#endif	// __DICT_H

#if !defined( __STRNG_H )
#include <Strng.h>
#endif	// __STRNG_H

#ifndef __IOSTREAM_H
#include <iostream.h>    
#endif

#define CLASSDEFINITIONS 23

static char *classNames[CLASSDEFINITIONS] =
    {
        "Object",
        "Error",
        "Sortable",
        "Association",
        "String",
        "Container",
        "Stack",
        "Queue",
        "Deque",
        "Collection",
        "HashTable",
        "Bag",
        "Set",
        "Dictionary",
        "AbstractArray",
        "Array",
        "SortedArray",
        "List",
        "DoubleList",
        "ContainerIterator",
        "ArrayIterator",
        "ListIterator",
        "DoubleListIterator"
    };

static char *classDefs[CLASSDEFINITIONS] =
    {
        "The abstract base class of the hierarchy.\n",
        "Used to indicate the presence of no object reference.\n",
        "Used in ordered collections.\n",
        "A key/value pair, used by the class Dictionary.\n",
        "An example of an instance class, derived from class Sortable.\n",
        "An abstract base class for all classes which contain other objects.\n",
        "A LIFO container class.\n",
        "A FIFO container class.\n",
        "A double-ended container class, allowing both FIFO and LIFO access.\n",
        "An abstract base class for classes which may be tested for membership.\n",
        "A fast lookup implementation of a collection.\n",
        "A collection class implemented by a hash table.\n",
        "A collection in which there may be only one copy of each member.\n",
        "A set of association object, with a lookup function.\n",
        "An abstract base class for arrays.\n",
        "A fixed or expandable array.\n",
        "An array in which objects at successive indices are in order.\n",
        "A collection class in which objects are linked together.\n",
        "A collection of objects which are part of two lists.\n",
        "A class which, when instantiated, is used to iterate over a collection.\n",
        "An iterator which is used on array objects.\n",
        "An iterator which is used on list objects.\n",
        "An iterator which is used on double list objects.\n"
    };

int main( int argc, char *argv[] )
{
    if( argc != 2 )
        {
        cerr << "Usage:  lookup classname\n";
        return 1;
        }

    Dictionary classDefinitions;

    for( int i = 0; i < CLASSDEFINITIONS; i++ )
        {
        String *className = new String( classNames[i] );
        String *classDef = new String( classDefs[i] );
        Association *entry = new Association( *className, *classDef );
        classDefinitions.add( *entry );
        }

    Association& definition =
                    classDefinitions.lookup ( *new String ( argv[1] ) );
    if( definition == NOOBJECT )
        {
        cout << "A definition for " << argv[1] << " was not found in the dictionary.\n";
        }
    else
        {
        cout << definition;
	}
    return 0;
}
