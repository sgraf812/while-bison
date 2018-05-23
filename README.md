# `while`

A pretty-printer and interpreter for a variant of everyone's favorite `while` dialect.

I wrote this mostly to get familiar with `flex` and `bison`.

You can find examples in `examples/`.

# How to run

Make sure you have `flex`, `bison` and a C compiler installed, or launch a `nix-shell`. Then do the following:

```
$ make
...
$ cat examples/fib.wh | ./pp
n := 10
i := 1
r := 1
while (i <= n) {
  r := (r * i)
  i := (i + 1)
}
$ cat examples/fib.wh | ./while
r := 3628800
i := 11
n := 10
```
