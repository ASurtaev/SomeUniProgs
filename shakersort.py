# -*- coding: utf-8 -*-
import random
import string

def whatToSort(arr, arg):
	to_sort = []
	pair = (0, 0)
	i, j = 0, 0
	while i < len(arr) - 1:
		if arr[i].get(arg) == arr[i + 1].get(arg):
			j = i
			while j < len(arr) - 1:
				if j + 1 == len(arr) - 1 and arr[j].get(arg) == arr[j + 1].get(arg):
					pair = (i, len(arr) - 1)
					to_sort.append(pair)
					break 
				if arr[j].get(arg) != arr[j + 1].get(arg):
			 		pair = (i, j)
			 		to_sort.append(pair)
			 		break
				j += 1
			i = j
		i += 1

	for i in range(len(arr) - 1):
		if arr[i] == arr[i + 1]:
			for j in range(i, len(arr) - 1):
				if arr[j] != arr[j + 1]:
					pair = (i, j)
			to_sort.append(pair)
			i = j
	return to_sort

def shakerSort(arr, arg, start, end):
    def swap(i, j):
        arr[i], arr[j] = arr[j], arr[i]
    if end - start == 1 and arr[start].get(arg) > arr[end].get(arg):
    	swap(start, end)
    	return arr
 
    upper = end
    lower = start
 
    no_swap = False
    while (not no_swap and upper - lower > 1):
        no_swap = True
        for j in range(lower, upper):
            if arr[j + 1].get(arg) < arr[j].get(arg):
                swap(j + 1, j)
                no_swap = False
        upper = upper - 1
 
        for j in range(upper, lower, -1):
            if arr[j - 1].get(arg) > arr[j].get(arg):
                swap(j - 1, j)
                no_swap = False
        lower = lower + 1
    return arr

class data:
	x, y, z = 0, 0, 0
	a, b = '', ''
	def fill(self):
		self.letters = ['q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm']
		self.x = random.randint(1,100)
		self.y = random.randint(1,100)
		self.z = random.randint(1,100)
		self.a = ''.join(random.choice(self.letters) for i in range(10))
		self.b = ''.join(random.choice(self.letters) for i in range(10))
	def get(self, arg):
		if arg == 0:
			return self.x
		if arg == 1:
			return self.y
		if arg == 2:
			return self.z
		if arg == 3:
			return self.a
		if arg == 4:
			return self.b

def main():

	n = 500

	arr = []
	print('Unsorted: ')
	for i in range(n):
		arr.append(data())
		arr[i].fill()
		print i, (arr[i].x, arr[i].y, arr[i].z, arr[i].a, arr[i].b)

	poles = [2, 0, 3]

	shakerSort(arr, poles[0], 0, len(arr) - 1)

	print('Sorted by', poles[0], ' :')
	for i in range(n):
		print i, (arr[i].x, arr[i].y, arr[i].z, arr[i].a, arr[i].b)

	to_sort = whatToSort(arr, poles[0])
	print('To sort:')
	print(to_sort)

	for i in to_sort:
		shakerSort(arr, poles[1], i[0], i[1])

	print('Sorted by', poles[1], ' :')
	for i in range(n):
		print i, (arr[i].x, arr[i].y, arr[i].z, arr[i].a, arr[i].b)

	to_sort = whatToSort(arr, poles[1])
	print('To sort:')
	print(to_sort)

	for i in to_sort:
		shakerSort(arr, poles[2], i[0], i[1])

	print('Sorted by', poles[2], ' :')
	for i in range(n):
		print i, (arr[i].x, arr[i].y, arr[i].z, arr[i].a, arr[i].b)	

main()
