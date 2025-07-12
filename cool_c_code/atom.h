/*
   There is only 1 occurrence of every atom.
   Atoms are often used as keys in data structures that are indexed by
   sequences of arbitrary bytes, like tables and sets.

   It is a checked runtime error to pass a null pointer to any function in
   this interface, to pass a negative len to Atom_new, or to pass a pointer
   that is not an atom to Atom_length. It is an unchecked runtime error to
   modify the bytes pointed to by an atom. Atom_length can take time to
   execute proportional to the number of atoms. Atom_new, Atom_string,
   and Atom_int can each raise the exception Mem_Failed.
*/
#ifndef ATOM_INCLUDED
#define ATOM_INCLUDED

extern int Atom_lenght(const char *str);
extern const char *Atom_new(const char *str, int len);
extern const char *Atom_string(const char *str);
extern const char *Atom_int(long n);

#endif
