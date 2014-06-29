CGenericQueue
=============

A generic queue in C created using macros.

About
-----
I used the C preprocessor to create a generic queue. All you need to do is include the header file and you're ready to go!

Example usage
--------------
```
lqueue_t(char) q;       //Create a queue that holds char's
lqueue_init(q);         //Initialize the queue
lqueue_append('c', q);  //Append and remove elements
lqueue_remove(q);
lqueue_del(q);          //Clean up
```

Internals
----------
The most challenging part of making this queue was figuring out how to remove, and conversely add, elements. To be able to do this I implemented the queue as a circular linked list (so the last node points back to the first one). The reason it was challenging to remove elements is because I needed to return the data contained by a node AND free up the memory taken by the node. If we were working with functions (and not macros) then my immediate thought would be to create a temporary variable, store the data in the variable, free the node, and return that variable. The main problem with that approach is that to create such a temporary variable we would need to know the type of the data which isn't good because we want our queue to be generic. 

So creating a function probably wasn't going to work but what if we try to take the same approach with a macro? So in the macro we'll create a temporary variable, store the data, etc... There are two problems with that approach. One is that, I think, declaring a variable inside of a macro is generally a bad idea. Remember that macros are NOT functions, their body just gets pasted into the code itself. So if we "called" this macro multiple times in the same block of code then the variable would get redeclared resulting in multiple declaration problems. The other thing I don't like about this approach is it would require the user to pass in the type of the data into this macro which doesn't seem very user friendly. So it would look like this:
```
lqueue_remove(type, q);
```
When it should really just look like this:
```
lqueue_remove(q);
```

