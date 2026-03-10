import numpy as np
A = np.array([[4,1,1],[1,3,0],[1,0,2]])
b = np.array([1,2,3])
print(np.linalg.solve(A, b))