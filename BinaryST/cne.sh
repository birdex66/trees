#!/bin/sh
gcc BST.c BSTfunc.c -o BST

if [ $? -eq 0 ]; then
   ./BST
fi
