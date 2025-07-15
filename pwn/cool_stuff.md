# Cool random stuff learnt

- i can use .bashrc as an attack vector.
- if i got write access to a dir => i can rm, mv files in here => subsitute file! this can be easily fixed by setting sticky bit, like in /tmp
  which force that only the owner of the file can mv or rm it.
- also if i got write access to a dir, i can create symlink here => possible attack vector(as i did)

- ps -ef (or aux) leaks cli args => can find smt sensitive in shared machine.

- can use read VAR < file && echo $VAR to cat file using only shell builtins(suppose a machine with no cat and other stuff)

- Gdb for C tricks
- Each output get assigned to var name, for out i, var_name= $i 

```
- p *x@12 = print 12 consecutive element in mem(eg array, with coerence respect to the type of course.)

- set $vd = my_model->dataset->vector->data.
- p *$vd@10, in short can create alias!

- set $ptr=&x[3] //set alias 
- p *$ptr = 8 //write to this element, i can write!
- p *($ptr++) #print the pointee, and step forward one
 
```
- little endian = store lsb(bytes,not byes) in lower address of memory and so on.(in short when i'm reading mem in a debugger, the first byte i read is the lsbyte(of course depends of how memory is displayed but in general is like that))
- Different kind of jmp in x86-64. indirect = in register, relative = relative to rip (in code, via label), absolute = given address

