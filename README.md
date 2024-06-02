# GRP */grape/*

<img width=200 height=200 src=https://github.com/piravelha/GRP.c/assets/140568241/15d5b3c1-e387-4f4d-a594-6fe2eee53f67>

This is an alternative implementation of GRP, that compiles to C.

# What is GRP?

GRP is a dynamically-typed, stack-based programming language, with the goal of being approachable to begginers, but also satifsy more advanced needs.

# Snippets

## Printing Numbers

```grp
10 Print
```
Output:
```sh
10
```

## Operators

All built-in functions in GRP have operator variants, here a a few intresting ones:

```grp
Plus        ; +
Minus       ; -
Times       ; *
Div         ; /
Print       ; <?
Show        ; ?
Map         ; <$>
Filter      ; <&>
Reduce      ; <.>
Sum         ; <+>
Product     ; <*>
Concat      ; ++
Head        ; <*
Tail        ; *>>
Length      ; #
Cons        ; :>
```

# Custom Operators

You can define a custom variable/function/operator as follows:

```grp
MyNumber (@) :: 10 5 + ::
```

And then you can use as follows:

```grp
MyNumber <?
; or
@ <?
; (<? is the 'Print' operator)
```

> Note that the operator form is optional, and you do not need to include it when defining a new variable
