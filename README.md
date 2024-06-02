# GRP */grape/*

<img src=https://private-user-images.githubusercontent.com/140568241/335350947-ef5da6e6-3d2e-4c39-96f4-fd74dae0f70d.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3MTczNzE1MzUsIm5iZiI6MTcxNzM3MTIzNSwicGF0aCI6Ii8xNDA1NjgyNDEvMzM1MzUwOTQ3LWVmNWRhNmU2LTNkMmUtNGMzOS05NmY0LWZkNzRkYWUwZjcwZC5wbmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjQwNjAyJTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI0MDYwMlQyMzMzNTVaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT1jMDUwOTQyY2Q3ODg1NTgyOGUyZGMzODE0NTlhODkyZDQwYmVhOGY3NTZlYzVmNGY0Yjg4OGY4NDhiNDEyZDdmJlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCZhY3Rvcl9pZD0wJmtleV9pZD0wJnJlcG9faWQ9MCJ9.HQSWOqHo9uytC__JtOmt8tl1J5t_QL5aBHrb2aZpbBQ>

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