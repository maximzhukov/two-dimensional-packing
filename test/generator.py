import random

number_of_items = 100
result = list()
print(number_of_items)

width = 400
print(width)

for _ in range(0, 20):
    print(random.randint(50, 150), random.randint(1, 20))

for _ in range(21, 41):
    print(random.randint(1, 40), random.randint(150, 300))

for _ in range(41, 61):
    print(random.randint(1, 20), random.randint(1, 10))

for _ in range(61, 81):
    print(random.randint(1, 20), random.randint(1, 10))

for _ in range(81, 101):
    print(random.randint(80, 200), random.randint(1, 80))