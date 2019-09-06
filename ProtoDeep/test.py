import numpy as np

#x = np.random.randint(0, 100, size=(2, 3))
x = np.array([[0,1,2],[3,4,5], [6,7,8]])
#x = np.array([[0,1,2],[3,4,5]])
print(x)
print("")
x = np.transpose(x, (1, 0))
print(x)

print("\n\n\n\n")

x = np.array([ [ [1, 2], [3, 4] ], [ [5, 6], [7, 8] ], [ [9, 10], [11, 12] ] ])
print(x)
print("\n\n")
x = np.transpose(x, (1, 2, 0))
print(x)