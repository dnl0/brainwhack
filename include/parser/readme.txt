parser (wip)

the parser in its current state is very wanky, and needs
best-case revision worst-case rework, but as of now it does
work, gives an appropriate result, and doesn't leak (i hope
but not confirmed), so i'm gonna leave it at that as of now, 
and fix the code issues later to make it ""better"".

of course with BF being this simple and linear language one
may wonder why would it even need a parser in the first place,
since it is possible to just do a simple bracket check from
the token stream, and use it instead, so why? to be completely
honest i don't have a good answer to that question, i mostly
just wanted to do it for shits and giggles, but speaking of
more reasonable reasons that i can think of is the ability to
add other functionality in the future, for example translate
the code into intermidiate-code, add optimization (which is
gonna come out soon i hope), and probably something else.

now, is it a parse tree or a syntax abstract tree? i really
have no idea, and by this point i'm too lazy to even bother,
it's not a left-right tree, it's a graph (if you may call it
that), so i would assume it's a parse tree, but i'm really 
not sure (let's call it half-ass parse tree).

please don't judge the code too much, i know that my class
hierarchy doesn't make much sense, and there is a lot of
code duplication in places, and there's practically no error
handling, i haven't implemented scope yet, i use passing by
copy too much (i just hope the compiler optimizes those),
i include headers where i shouldn't, there're leaks i think,
the naming sucks, and i really need to use smart pointers,
but i can assure you some of these gonna be fixed soon-TM.
