# Cool random stuff learnt

- i can use .bashrc as an attack vector.
- if i got write access to a dir => i can rm, mv files in here => subsitute file! this can be easily fixed by setting sticky bit, like in /tmp
  which force that only the owner of the file can mv or rm it.
- also if i got write access to a dir, i can create symlink here => possible attack vector(as i did)

- ps -ef (or aux) leaks cli args => can find smt sensitive in shared machine.

- can use read VAR < file && echo $VAR to cat file using only shell builtins(suppose a machine with no cat and other stuff)
