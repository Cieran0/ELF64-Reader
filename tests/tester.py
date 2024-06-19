#!/usr/bin/python3

import os

def build_tests():
    path, filename = os.path.split(os.path.realpath(__file__))
    for entry in os.listdir(path):
        if entry.endswith(".asm"):
            name = entry[:-4]
            os.system(f"nasm -felf64 {path}/{name}.asm")
            os.system(f"ld -o {path}/{name} {path}/{name}.o")


build_tests()