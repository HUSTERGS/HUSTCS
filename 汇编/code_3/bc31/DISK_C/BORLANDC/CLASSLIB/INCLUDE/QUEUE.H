/*------------------------------------------------------------------------*/
/*                                                                        */
/*  QUEUE.H                                                               */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __QUEUE_H )
#define __QUEUE_H

#if defined( TEMPLATES )

    #if !defined( __QUEUES_H )
    #include <Queues.h>
    #endif  // __QUEUES_H

    #pragma option -Vo-
    #if defined( __BCOPT__ ) && !defined( _ALLOW_po )
    #pragma option -po-
    #endif

    #define Queue   BI_TCQueueAsDoubleList
    #define PQueue  PBI_TCQueueAsDoubleList
    #define RQueue  RBI_TCQueueAsDoubleList
    #define RPQueue RPBI_TCQueueAsDoubleList
    #define PCQueue PCBI_TCQueueAsDoubleList
    #define RCQueue RCBI_TCQueueAsDoubleList

    _CLASSDEF( BI_TCQueueAsDoubleList )

    #define QueueIterator   BI_TCQueueAsDoubleListIterator
    #define PQueueIterator  PBI_TCQueueAsDoubleListIterator
    #define RQueueIterator  RBI_TCQueueAsDoubleListIterator
    #define RPQueueIterator RPBI_TCQueueAsDoubleListIterator
    #define PCQueueIterator PCBI_TCQueueAsDoubleListIterator
    #define RCQueueIterator RCBI_TCQueueAsDoubleListIterator

    _CLASSDEF( BI_TCQueueAsDoubleListIterator )

#else   // TEMPLATES

    #if !defined( __CLSTYPES_H )
    #include <ClsTypes.h>
    #endif  // __CLSTYPES_H

    #if !defined( __DEQUE_H )
    #include <Deque.h>
    #endif  // __DEQUE_H

    #pragma option -Vo-
    #if defined( __BCOPT__ ) && !defined( _ALLOW_po )
    #pragma option -po-
    #endif

    _CLASSDEF(Queue)

    class _CLASSTYPE Queue : public Deque
    {

    public:

        Object _FAR & get()
            {
            return Deque::getRight();
            }

        void put( Object _FAR & o )
            {
            Deque::putLeft( o );
            }

        virtual classType isA() const
            {
            return queueClass;
            }

        virtual char _FAR *nameOf() const
            {
            return "Queue";
            }

    private:

        Object _FAR & getLeft();
        Object _FAR & getRight();

        void putLeft( Object _FAR & );
        void putRight( Object _FAR & );

    };

#endif  // TEMPLATES

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __QUEUE_H

