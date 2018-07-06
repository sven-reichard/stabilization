
# Table of Contents

1.  [Outline](#org969945f)
2.  [Building](#org522712d)
3.  [Filters](#orge5ef441)
4.  [File format](#org56e680c)
5.  [Example computations:](#org551932f)


<a id="org969945f"></a>

# Outline

This is a collection of utilities for coherent configurations, built
on a small library. It is possible to use the library directly (it's
written in C++); however, it can be used without programming by
using the filters or programs that are provided.


<a id="org522712d"></a>

# Building

A simple "make" should to the trick. Assuming g++ is installed.


<a id="orge5ef441"></a>

# Filters

Following the Unix philosophy, the programs that are included
perform  small and specific transformations on configurations. They
read one or more configurations from standard input and write one
or more configurations to standard output.

The filters provided so far are

-   increase-arity: take k-ary configuration and construct (k+1)-ary
    configuration from it
-   decrease-arity: construct (k-1)-ary configuration from k-ary
    configuration
-   check-t checks whether the t-vertex condition is satisfied; if <t>
    is not given, the arity plus one is used, checking ordinary
    coherence. If the condition is satisfied, the configuration is
    written out, otherwise it isn't.
-   stabilize <t>: perform (k,t)-WL stabilization. If t is not given
    it defaults to k+1, i.e., the usual k-dim WL is performed
-   weisfeiler: optimised and probabilistic version for the classical
    (2,3)-stabilization


<a id="org56e680c"></a>

# File format

The format is both human and computer readable. It contains  the
keywords "order" and "dimension", followed by the order and arity of
the structure, respectively. After that the colors appear in the
lexicographical order of the multiedges.


<a id="org551932f"></a>

# Example computations:

    cat shrikhande.wl | ./stabilize
    cat shrikhande.wl | ./stabilize 4

