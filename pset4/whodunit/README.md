# Questions

## What's `stdint.h`?

It's a header file in the C standard library

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

It's used to precisely allocate memory for data type needed.
Equivalent to:
    unsigned char
    unsigned short
    unsigned int
    unsigned long long

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE - 1 byte
DWORD - 4 bytes
LONG - not defined to a specific length
WORD - 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

TODO

## What's the difference between `bfSize` and `biSize`?

bfSize represents file size and biSize represents image size

## What does it mean if `biHeight` is negative?

If biHeight is positive, the image is bottom-up. If biHeight is negative, the image is top-down.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

If file doesn't exist.

## Why is the third argument to `fread` always `1` in our code?

Third argument is number of times a record will be read.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

fseek() is used to move file pointer associated with a given file to a specific position.

## What is `SEEK_CUR`?

Current position of the file pointer.
