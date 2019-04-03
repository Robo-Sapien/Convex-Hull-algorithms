import numpy as np
import matplotlib.pyplot as plt


def generate_points(seed,num_points):
	np.random.seed(seed)
	num=np.random.uniform(0.0,1.0,num_points)
	den=np.random.uniform(0.0,1.0,num_points)

	new_points=num/den
	print (new_points)
	return new_points

if __name__=="__main__":
	seed=10
	num_points=10000
	generate_points(seed,num_points)
	plt.hist(num_points,orientation='horizontal',bins=100)
	plt.show()
