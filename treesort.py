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

class Tree:
	def __init__(self, data, item):
		self.left = None
		self.right = None
		self.item = item
		self.data = data
	def insert(self, data, item):
		if self.data:
			if data < self.data:
				if self.left is None:
					self.left = Tree(data, item)
				else:
					self.left.insert(data, item)
			elif data >= self.data:
				if self.right is None:
					self.right = Tree(data, item)
				else:
					self.right.insert(data, item)
		else:
			self.data = data
			self.item = item
	def printTree(self):
		if self.left:
			self.left.printTree()
		print(self.data),
		if self.right:
			self.right.printTree()

def tsort(res, root):
	if root.left:
		tsort(res, root.left)
	res.append(root.item)
	if root.right:
		tsort(res, root.right)


def treeSort(arr, arg, start, end):
	t = Tree(arr[start].get(arg), arr[start])
	res = []
	for i in range(start + 1, end + 1):

		t.insert(arr[i].get(arg), arr[i])
	tsort(res, t)
	return res


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
	buf = []
	print('Unsorted: ')
	for i in range(n):
		arr.append(data())
		arr[i].fill()
		print i, (arr[i].x, arr[i].y, arr[i].z, arr[i].a, arr[i].b)

	poles = [0, 1, 3]

	arr = treeSort(arr, poles[0], 0, n - 1)

	print
	print('Sorted by', poles[0], ' :')
	for i in range(n):
		print i, (arr[i].x, arr[i].y, arr[i].z, arr[i].a, arr[i].b)

	to_sort = whatToSort(arr, poles[0])
	print
	print('To sort:')
	print(to_sort)
	print

	for i in to_sort:
		buf = treeSort(arr, poles[1], i[0], i[1])
		k = 0
		for j in range(i[0], i[1] + 1):
			arr[j] = buf[k]
			k += 1

	print
	print('Sorted by', poles[1], ' :')
	for i in range(n):
		print i, (arr[i].x, arr[i].y, arr[i].z, arr[i].a, arr[i].b)

	to_sort = whatToSort(arr, poles[1])
	print
	print('To sort:')
	print(to_sort)
	print

	for i in to_sort:
		buf = treeSort(arr, poles[2], i[0], i[1])
		k = 0
		for j in range(i[0], i[1] + 1):
			arr[j] = buf[k]
			k += 1

	print
	print('Sorted by', poles[2], ' :')
	for i in range(n):
		print i, (arr[i].x, arr[i].y, arr[i].z, arr[i].a, arr[i].b)	

main()