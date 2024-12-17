This is a bare-bones reimplementation of the Vector sequence container
found in the Standard Template Library. It can be found in
/include/ics_vector.hpp. It includes an Iterator class for range-based
for loops, as well as methods for pushing and poping to the end of the
list.

Under the hood, the Vector is just an array of type T. When the user
tries to add an element but the array is already at its maximum capacity,
a new array is created with double the capacity of the old one, and
everything is moved over.

Everything from The Rule of Five is implemented, with operator
overloading used to achieve this and other goals.
