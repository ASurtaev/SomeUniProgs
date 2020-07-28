import random

def shakerSort(arr, start, end, poles):
    def swp(i, j): 
    	arr[i], arr[j] = arr[j], arr[i]

    if end - start == 1 and isBigger(arr[start], arr[end], poles):
    	swp(start, end)
    	return arr
 
    upper = end
    lower = start
 
    no_swap = False
    while (not no_swap and upper - lower > 1):
        no_swap = True
        for j in range(lower, upper):
            if not isBigger(arr[j + 1],arr[j], poles):
                swp(j + 1, j)
                no_swap = False
        upper = upper - 1
 
        for j in range(upper, lower, -1):
            if isBigger(arr[j - 1], arr[j], poles):
                swp(j - 1, j)
                no_swap = False
        lower = lower + 1
    return arr

def isBigger(first, second, poles):
	for p in poles:
		if first[p] > second[p]:
			return True
		elif first[p] < second[p]:
			return False
	return False

def changeTypes(line):
	line = line.split()
	line[0] = int(line[0])
	line[1] = int(line[1])
	line[2] = int(line[2])
	line[3] = str(line[3])
	line[4] = str(line[4])
	return line

def makeInputFile(n):
	with open('data/input.dat', 'w') as file:
		random_int = lambda: random.randint(1,100)
		random_str = lambda: ''.join(random.choice(['q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm']) for i in range(10))
		for _ in range(n):
			line = [str(random_int()), str(random_int()), str(random_int()), random_str(), random_str(), '\n']
			file.write(' '.join(line))

def ddArrToFile(arr, file):
	for ln in arr:
		for p in ln:
			print(p, end = ' ', file = file)
		print(file = file)
	#print(file = file)

def allZero(lst):
	if lst[0] == 0 and lst[1] == 0 and lst[2] == 0 and lst[3] == 0 and lst[4] == 0:
		return True
	return False

def makeNamesFirst(mode):
	file_names = []
	file_names.append(open('data/R0.dat', mode))
	file_names.append(open('data/R1.dat', mode))
	file_names.append(open('data/R2.dat', mode))
	file_names.append(open('data/R3.dat', mode))
	file_names.append(open('data/R4.dat', mode))
	return file_names

def makeNamesSecond(mode):
	file_names2 = []
	file_names2.append(open('data/R5.dat', mode))
	file_names2.append(open('data/R6.dat', mode))
	file_names2.append(open('data/R7.dat', mode))
	file_names2.append(open('data/R8.dat', mode))
	file_names2.append(open('data/R9.dat', mode))
	return file_names2

def closeFiles(file_names):
	for f in file_names:
		f.close()

def toFile(lst, file):
	for e in lst:
		print(e, end = ' ', file = file)
	print(file = file)

def fillLs(n, new_sery_length, cntr):
	ls = []
	kek = int((n - cntr) / new_sery_length)
	left = n - cntr
	for i in range(kek):
		ls.append(new_sery_length)
		left -= new_sery_length
		if i == 4:
			return ls
	if left != 0:
		ls.append(left)
		kek += 1
	for i in range(5 - kek):
		ls.append(0)
	return ls

def sortFinished(n, outfiles):
	a = 0
	saver = outfiles[0].tell()
	outfiles[0].seek(0)
	for line in outfiles[0]:
		a += 1
	outfiles[0].seek(saver)
	if a == n:
		return True
	return False		

def splitAndSort(n, series_length, poles):
	arr = []
	file_names = makeNamesFirst('w')
	file_index = 0
	with open('data/input.dat', 'r') as fin:
		for line in fin:
			arr.append(changeTypes(line))
			if len(arr) == series_length:
				shakerSort(arr, 0, series_length - 1, poles)
				ddArrToFile(arr, file_names[file_index])
				del arr[:]
				file_index += 1
				if file_index == 5:
					file_index = 0

	#rest lines
	for ln in arr:
		for p in ln:
			print(p, end = ' ', file = file_names[file_index])
		print(file = file_names[file_index])

	if len(arr):
		for i in range(series_length - len(arr)):
			print('100 100 100 zzzzzzzzzz zzzzzzzzzz', file = file_names[file_index])
		closeFiles(file_names)
		return series_length - len(arr)
	closeFiles(file_names)
	return 0

def merge(n, series_length, poles):
	cntr = 0
	new_sery_length = series_length 
	min_line = [101,101,101,'zzzzzzzzzzz','zzzzzzzzzzz']
	ls = []
	infiles = []
	outfiles = []
	first_turn = False
	out_file_index = 0
	infiles = makeNamesFirst('r')
	outfiles = makeNamesSecond('a+')
	while True:
		ls = fillLs(n, new_sery_length, cntr)
		while not allZero(ls):
			min_index = 0
			for file_index, f in enumerate(infiles):
				if ls[file_index] == 0:
					continue
				pos = f.tell()
				line = f.readline()
				line = changeTypes(line)
				if isBigger(min_line, line, poles):
					min_line = line
					min_index = file_index
				f.seek(pos)

			cntr += 1
			toFile(min_line, outfiles[out_file_index])
			min_line = infiles[min_index].readline()
			min_line = [101,101,101,'zzzzzzzzzzz','zzzzzzzzzzz']
			ls[min_index] -= 1

		out_file_index += 1
		if cntr == n: #проверяет полностью ли считаны ВСЕ данные из первого набора файлов
			new_sery_length *= 5
			cntr = 0
			if sortFinished(n, outfiles):
				closeFiles(infiles)
				ret = outfiles[0].name
				closeFiles(outfiles)
				del infiles[:]
				del outfiles[:]
				return ret
			closeFiles(infiles)
			closeFiles(outfiles)
			del infiles[:]
			del outfiles[:]
			if first_turn:
				infiles = makeNamesFirst('r')
				outfiles = makeNamesSecond('w')
				closeFiles(outfiles)
				outfiles = makeNamesSecond('a+')
				first_turn = False
			else:
				infiles = makeNamesSecond('r')
				outfiles = makeNamesFirst('w')
				closeFiles(outfiles)
				outfiles = makeNamesFirst('a+')
				first_turn = True
			out_file_index = 0

		if out_file_index == 5:
			out_file_index = 0

def toOutput(name, n):
	with open(str(name), 'r') as inf:
		with open('data/output.dat', 'w') as outf:
			for _ in range(n):
				toFile(changeTypes(inf.readline()), outf)

def main():
	n = 100000
	poles = [0, 1, 3]
	series_length = 20
	
	with open('data/output.dat', 'w') as fout:
		pass
	to_clear = makeNamesFirst('w')
	closeFiles(to_clear)
	del to_clear[:]
	to_clear = makeNamesSecond('w')
	closeFiles(to_clear)
	
	print('creating input file')
	makeInputFile(n)
	print('starting split n sort')
	amount_added = splitAndSort(n, series_length, poles)
	print('starting merge')
	name = merge(n + amount_added, series_length, poles)
	toOutput(name, n - amount_added)

	to_clear = makeNamesFirst('w')
	closeFiles(to_clear)
	del to_clear[:]
	to_clear = makeNamesSecond('w')
	closeFiles(to_clear)
	print('finished')


main()
