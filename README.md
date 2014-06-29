CGenericQueue
=============

A generic queue in C created using macros.

About
-----
I used the C preprocessor to create a generic queue. All you need to do is include the header file and you're ready to go!

Example usage
--------------
```
lqueue_t(double) q;       //Create a queue variable that holds double's
lqueue_init(q);           //Initialize the queue
lqueue_append(39.6, q);   //Append and remove elements
lqueue_remove(q);
lqueue_del(q);            //Clean up
```

Internals
----------
The most challenging part of making this queue was figuring out how to remove, and conversely add, elements. To be able to do this I implemented the queue as a circular linked list (so the last node points back to the first one). The reason it was challenging to remove elements is because I needed to return the data contained by a node AND free up the memory taken by the node at the same time (or so I thought). If we were working with functions (and not macros) then my immediate thought would be to create a temporary variable, store the data in the variable, free the node, and return that variable. The main problem with that approach is that to create such a temporary variable we would need to know the type of the data which isn't good because we want our queue to be generic. 

So creating a function probably isn't going to work, but what if we try to take the same approach with a macro? So in the macro we'll create a temporary variable, store the data, etc... There are two problems with that approach. One is that, I think, declaring a variable inside of a macro is generally a bad idea. Remember that macros are NOT functions, their body just gets pasted into the code itself. So if we "called" this macro multiple times in the same block of code then the variable would get redeclared resulting in multiple declaration problems. The other thing I don't like about this approach is it would require the user to pass in the type of the data to the macro, which doesn't seem very user friendly. So it would look like this:
```
lqueue_remove(type, q);
```
When it should really just look like this:
```
lqueue_remove(q);
```

The approach I came up with is to have this queue reuse it's own "deallocated" memory. The idea is that we can put a removed node on a pile of "nodes to be recycled". Since a removed node is not actually free'd, it is still safe to grab whatever value it contained. This approach has the added benefit of using less calls to malloc and free; when adding nodes we can take them from this pile and when removing nodes we can put them back onto this pile. 

To implement this idea only two things need to get done. One is that the queue struct has a third pointer, in addition to the head and tail pointers, which gets used for miscellaneous purposes like returning removed vales. The second is that our linked list is circular. This is neat because to remove a node you just move the head pointer forward and to append a node you just move the tail pointer forward (you can imagine these head and tail pointers running around in a circle). If these pointers are about to collide then either the queue is full (in which case we allocate more memory) or the queue is empty (in which case we have a lot of recycled nodes and we can just move the tail pointer forward).

