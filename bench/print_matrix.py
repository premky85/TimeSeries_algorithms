import numpy as np

def dtw_fw(a, b, norm=np.linalg.norm):
	m = len(a); n = len(b)
	t = np.empty((m, n))
	t[0, 0] = abs(a[0] - b[0])
	for i in range(1, m):
		t[i, 0] = t[i-1, 0] + abs(a[i] - b[0])
	for j in range(1, n):
		t[0, j] = t[0, j-1] + abs(a[0] - b[j])
	for i in range(1, n):
		for j in range(1, m):
			t[i, j] = abs(a[i] - b[j]) + min(t[i-1, j-1], t[i-1, j], t[i, j-1])
	return t.T#.transpose(t)


a = input("A: ")
b = input("B: ")

a = [int(x) for x in a.split()]
b = [int(x) for x in b.split()]
#a = [9, 1, 1, 2, 2, 3, 4, 6,]
#b = [3, 7, 9, 0, 9, 2, 8, 8,]

print(dtw_fw(a, b))

