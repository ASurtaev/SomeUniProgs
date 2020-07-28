import functools

def compare(j1, j2):
	for i in range(len(line)):
		if line[(j1 + i) % len(line)] > line[(j2 + i) % len(line)]:
			return 1
		if line[(j1 + i) % len(line)] < line[(j2 + i) % len(line)]:
			return -1
	return 0

def kasai(suf):
	n = len(line)
	k = 0
	lcp = [0] * n
	rank = [0] * n
	for i in range(n): rank[suf[i]] = i
	for i in range(n):
		if rank[i] == n - 1 :
			k = 0
			continue
		j = suf[rank[i] + 1]
		while i + k < n and j + k < n and line[i + k] == line[j + k]: 
			k += 1
		lcp[rank[i]] = k;
		if k: k -= 1
	return lcp

def main():
	suf = sorted([i for i in range(len(line))], key=functools.cmp_to_key(compare))
	#print(suf)
	for i,e in enumerate(suf):
		print(i, e, line[i:])
	lcp = kasai(suf)
	print("Lcp:", lcp)
	x, y = 1, 4
	print("lcp of", x,y,":", min(lcp[x:y]))

if __name__=="__main__":
	line = 'abrakadabra'
	main()