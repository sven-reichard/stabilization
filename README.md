
# Table of Contents

1.  [Outline](#orgd99f28e)
2.  [Building](#orgcedf520)
3.  [Filters](#org88e2f4d)
4.  [File format](#orgc57f383)


<a id="orgd99f28e"></a>

# Outline

This is a collection of utilities for coherent configurations, built
on a small library. It is possible to use the library directly (it's
written in C++); however, it can be used without programming by
using the filters or programs that are provided.


<a id="orgcedf520"></a>

# Building

A simple "make" should to the trick. Assuming g++ is installed.


<a id="org88e2f4d"></a>

# Filters

Following the Unix philosophy, the programs that are included
perform  small and specific transformations on configurations. They
read one or more configurations from standard input and write one
or more configurations to standard output.

The filters provided so far are

-   increase-arity
-   decrease-arity
-   check-t checks whether the t-vertex condition is satisfied; if <t>
    is not given, the arity plus one is used, checking ordinary
    coherence. If the condition is satisfied, the configuration is
    written out, otherwise it isn't.


<a id="orgc57f383"></a>

# File format

The format is both human and computer readable. It contains  the
keywords "order" and "dimension", followed by the order and arity of
the structure, respectively. After that the colors appear in the
lexicographical order of the multiedges.

