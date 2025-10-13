import os

os.system('g++ main.cpp -o main.out -std=c++20')
os.system('g++ good.cpp -o good.out -std=c++20')
os.system('g++ gen.cpp -o gen.out -std=c++20')

test=0
while True:
    test+=1
    print(f'TESTING {test}: ', end='')
    os.system('./gen.out >input.txt')
    os.system('./main.out <input.txt >bad.txt')
    os.system('./good.out <input.txt >good.txt')
    bad = open('bad.txt').read().strip()
    good = open('good.txt').read().strip()
    if (good != bad):
       print("FAIL")
       break
    print('OK')