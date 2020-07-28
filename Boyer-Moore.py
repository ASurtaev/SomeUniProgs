#обобщить алгоритм Бойера-Мура на случай поиска 2 подстрок, одна из которых является префиксом другой
def readFile():
	string = "  "
	substring = "  "
	double_substring = "  "
	with open('input2.dat', 'r') as infile:
		tmp = infile.read().splitlines()
		string = tmp[0]
		substring = tmp[1]
		double_substring = tmp[2]
	return string, substring, double_substring

def naive(string, substring):
	for i in range(len(string) - len(substring)):
		if string[i] == substring[0]:
			same = True
			for j in range(len(substring) - 1):
				if string[i + j] != substring[j + 1]:
					same == False
			if same == True:
				print(substring)

def BoyerMooreHorspool(pattern, text):
    m = len(pattern)
    n = len(text)
    if m > n: return -1
    skip = []
    for k in range(256): skip.append(m)
    for k in range(m - 1): skip[ord(pattern[k])] = m - k - 1
    skip = tuple(skip)
    k = m - 1
    while k < n:
        j = m - 1; i = k
        while j >= 0 and text[i] == pattern[j]:
            j -= 1; i -= 1
        if j == -1: return i + 1
        k += skip[ord(text[k])]
    return -1

def boyerMoore(string, substring):
	suffshift()


def main():
	text, pattern, double_substring = readFile()
	#text = str(text)
	#pattern = str(pattern)
	double_substring = str(double_substring)
	s = BoyerMooreHorspool(text, pattern)

	print('Text:',text)
	print([text])
	print('Pattern:',pattern)
	print([pattern])
	if s > -1:
		print('Pattern \"' + pattern + '\" found at position',s)

	text = "this is the string to search in"
	pattern = "the"
	s = BoyerMooreHorspool(pattern, text)

	print('Text:',text)
	print([text])
	print('Pattern:',pattern)
	print([pattern])
	if s > -1:
		print('Pattern \"' + pattern + '\" found at position',s)


if __name__ == "__main__":
	main()